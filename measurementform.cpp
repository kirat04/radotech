#include "measurementform.h"
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include<QPixmap>
#include<QTimer>
#include <QDir>
#include  <QProgressBar>

//Need to add innstructions
MeasurementForm::MeasurementForm(QWidget *parent)
    : QWidget(parent) {

battery = new QProgressBar(this);
battery->setValue(100);
    stepNumber = 0;
    isDeviceContacting = false;
    measurementManager = new MeasurementManager(5, 160);

    imagePaths.push_back("../radotech/images/testt.jpeg");
    imagePaths.push_back("../radotech/images/point1.png");
    imagePaths.push_back("../radotech/images/point2.png");
    imagePaths.push_back("../radotech/images/point3.png");
    imagePaths.push_back("../radotech/images/point4.png");
    imagePaths.push_back("../radotech/images/point5.png");
    imagePaths.push_back("../radotech/images/point6.png");
    imagePaths.push_back("../radotech/images/point7.png");
    imagePaths.push_back("../radotech/images/point8.png");
    imagePaths.push_back("../radotech/images/point9.png");
    imagePaths.push_back("../radotech/images/point10.png");
    imagePaths.push_back("../radotech/images/point11.png");
    imagePaths.push_back("../radotech/images/point12.png");

    mainLayout = new QVBoxLayout(this);

    // Instruction Label
    QLabel *instructionLabel = new QLabel("Measurement Instructions:\n"
                                   "1. Press the device to the specified point\n"
                                   "2. Keep device in contact until beep\n"
                                   "3. Lift device off skin\n"
                                   "4. Press 'Next' to continue");
    mainLayout->addWidget(instructionLabel);

    QHBoxLayout* picLayout = new QHBoxLayout();
    picture = new QLabel();
    picture->setText("Moisten the skin with provided spray water. \nPlease press the device to the displayed point to get a reading.\n"
                     "When done, press 'Next' to display the next point.\nPress 'Next' to start");
    picture->setFixedSize(400, 300);  // Set a fixed size for consistent display
    picture->setScaledContents(true);
    picLayout->addWidget(picture);
    mainLayout->addLayout(picLayout);

    // Contact State Indicator
    contactStateLabel = new QLabel("Device Contact State: Not Contacting");
    contactStateLabel->setStyleSheet("color: red; font-weight: bold;");
    contactStateLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(contactStateLabel);

    // Button Layout
    QHBoxLayout* btnLayout = new QHBoxLayout();
    nextBtn = new QPushButton("Next", this);
    exitBtn = new QPushButton("Exit", this);

    btnLayout->addWidget(nextBtn);
    btnLayout->addWidget(exitBtn);
    mainLayout->addLayout(btnLayout);

    viewVisualizationBtn = new QPushButton("View Metrics", this);
    viewVisualizationBtn->setEnabled(false);
    mainLayout->addWidget(viewVisualizationBtn);

    // Connect visualization button
    connect(viewVisualizationBtn, &QPushButton::clicked, this, &MeasurementForm::showMeasurementVisualization);
    connect(nextBtn,&QPushButton::clicked,this,&MeasurementForm::nextClicked);
    connect(exitBtn,&QPushButton::clicked,this,&MeasurementForm::exitClicked);

    btnLayout->addWidget(nextBtn);
    btnLayout->addWidget(exitBtn);

}

void MeasurementForm::startDeviceContact() {
    isDeviceContacting = true;
    contactStateLabel->setText("Device Contact State: Contacting Skin");
    contactStateLabel->setStyleSheet("color: green; font-weight: bold;");
}

void MeasurementForm::endDeviceContact() {
    measurementManager->captureMeasurement();
    nextBtn->setEnabled(true);
    isDeviceContacting = false;
    contactStateLabel->setText("Device Contact State: Not Contacting");
    contactStateLabel->setStyleSheet("color: red; font-weight: bold;");
}

void MeasurementForm::handleNext() {
    // If currently contacting, require device to be lifted
    if (isDeviceContacting) {
        QMessageBox::warning(this, "Contact Error",
            "Please lift the device off the skin before proceeding to the next point.");
        return;
    }

    stepNumber++;

    if (stepNumber == 1) {
        // First measurement point
        simulateDeviceContact();
        nextBtn->setEnabled(false);
        // Show measurement point image
        QPixmap image(imagePaths[stepNumber]);
        picture->setPixmap(image);
    }
    else if (stepNumber > 12) {
        // Test completed
        picture->clear();
        picture->setText("Test Completed");
        measurementManager->storeMeasurements();

        // Enable visualization button
        nextBtn->setEnabled(false);
        viewVisualizationBtn->setEnabled(true);
        emit measurementCompleted();

    }
    else {
        // Subsequent measurement points
        simulateDeviceContact();
        // Show next point image
        nextBtn->setEnabled(false);
        picture->clear();
        QPixmap image(imagePaths[stepNumber]);
        picture->setPixmap(image);
    }
}

// New method to simulate device contact (for demonstration)
void MeasurementForm::simulateDeviceContact() {
    if (!isDeviceContacting) {
        QTimer::singleShot(1000, this, &MeasurementForm::startDeviceContact);
        QTimer::singleShot(3000, this, &MeasurementForm::endDeviceContact);
        emit depleteBattery(5);
    }
}


// Implement the visualization method
void MeasurementForm::showMeasurementVisualization() {
    // Get all measurements
    QVector<int> measurements = measurementManager->getAllMeasurements();

    if (measurements.isEmpty()) {
        QMessageBox::warning(this, "No Data", "No measurements available to visualize.");
        return;
    }

    // Create visualization dialog
    QDialog* visualizationDialog = new QDialog(this);
    visualizationDialog->setWindowTitle("Health Metrics Visualization");

    // Create layout for dialog
    QVBoxLayout* dialogLayout = new QVBoxLayout(visualizationDialog);

    // Create visualization widget
    HealthMetricVisualization* metricsVisualization =
        new HealthMetricVisualization(measurements, visualizationDialog);

    // Add widgets to dialog
    dialogLayout->addWidget(metricsVisualization);


    // Resize and show dialog
    visualizationDialog->resize(600, 400);
    visualizationDialog->show();
}

void MeasurementForm::setBattery(int amount){

    battery->setValue(amount);
}
