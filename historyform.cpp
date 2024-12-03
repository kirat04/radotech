#include "historyform.h"
#include <QHeaderView>
#include <QMessageBox>

HistoryForm::HistoryForm(QWidget *parent)
    : QWidget(parent),
    storageManager(StorageManager::getInstance()) {
    setupUI();
    loadHistoricalData();
}

void HistoryForm::setupUI() {
    mainLayout = new QVBoxLayout(this);

    // Data Table
    dataTable = new QTableWidget();
    dataTable->setColumnCount(5);
    dataTable->setHorizontalHeaderLabels({"Date", "Total Readings", "Average", "Max", "Min"});
    dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mainLayout->addWidget(dataTable);

    // Visualization Button
    visualizeButton = new QPushButton("Visualize Selected");
    connect(visualizeButton, &QPushButton::clicked, this, &HistoryForm::visualizeSelectedData);
    mainLayout->addWidget(visualizeButton);

    // Exit Button
    QPushButton* exitButton = new QPushButton("Back");
    connect(exitButton, &QPushButton::clicked, this, &HistoryForm::exitClicked);
    mainLayout->addWidget(exitButton);
}

void HistoryForm::loadHistoricalData() {
    UserManager& userManager = UserManager::getInstance();
    UserProfile* currentUser = userManager.getCurrentUser();
    if (currentUser) {
        QList<QJsonObject> measurements = storageManager.loadAllMeasurements();

        // Filter measurements for the current user
        QList<QJsonObject> userMeasurements;
        for (const QJsonObject& measurement : measurements) {
            // Assuming you store the user ID or username in the measurement JSON
            if (measurement["username"].toString() == currentUser->getFullName()) {
                userMeasurements.append(measurement);
            }
        }

        createDataTable(userMeasurements);
    }
}

void HistoryForm::createDataTable(const QList<QJsonObject>& measurements) {
    dataTable->setRowCount(measurements.size());

    for (int row = 0; row < measurements.size(); ++row) {
        const QJsonObject& measurement = measurements[row];

        // Date
        QTableWidgetItem* dateItem = new QTableWidgetItem(
            measurement["timestamp"].toString()
        );
        dataTable->setItem(row, 0, dateItem);

        // Total Readings
        QTableWidgetItem* readingsItem = new QTableWidgetItem(
            QString::number(measurement["total_readings"].toInt())
        );
        dataTable->setItem(row, 1, readingsItem);

        // Average
        QTableWidgetItem* avgItem = new QTableWidgetItem(
            QString::number(measurement["avg"].toDouble(), 'f', 2)
        );
        dataTable->setItem(row, 2, avgItem);

        // Max
        QTableWidgetItem* maxItem = new QTableWidgetItem(
            QString::number(measurement["max"].toInt())
        );
        dataTable->setItem(row, 3, maxItem);

        // Min
        QTableWidgetItem* minItem = new QTableWidgetItem(
            QString::number(measurement["min"].toInt())
        );
        dataTable->setItem(row, 4, minItem);
    }
}

void HistoryForm::visualizeSelectedData() {
    QList<QTableWidgetItem*> selectedItems = dataTable->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select measurements to visualize.");
        return;
    }

    // Get unique rows of selected items
    QSet<int> selectedRows;
    for (QTableWidgetItem* item : selectedItems) {
        selectedRows.insert(item->row());
    }

    // Convert selected measurements to a vector of integers
    QVector<int> selectedMeasurementValues;
    for (int row : selectedRows) {
        // Extract the full array of readings from the original measurement
        QJsonObject measurement = storageManager.loadMeasurement(
            "measurements/measurement_" + dataTable->item(row, 0)->text().replace(" ", "_") + ".json"
        );

        QJsonArray readings = measurement["readings"].toArray();
        for (const QJsonValue& reading : readings) {
            selectedMeasurementValues.append(reading.toInt());
        }
    }

    // Create visualization dialog
    QDialog* visualizationDialog = new QDialog(this);
    visualizationDialog->setWindowTitle("Historical Health Metrics");
    QVBoxLayout* dialogLayout = new QVBoxLayout(visualizationDialog);

    // Create visualization widget with all readings
    HealthMetricVisualization* metricsVisualization =
            new HealthMetricVisualization(selectedMeasurementValues, visualizationDialog);
    dialogLayout->addWidget(metricsVisualization);
    visualizationDialog->resize(600, 400);
    visualizationDialog->show();
}
