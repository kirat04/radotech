#ifndef HISTORYFORM_H
#define HISTORYFORM_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include "storageManager.h"
#include "usermanager.h"
#include "healthmetricVisualization.h"

class HistoryForm : public QWidget {
    Q_OBJECT

public:
    explicit HistoryForm(QWidget *parent = nullptr);

private:
    void setupUI();
    void loadHistoricalData();
    void createDataTable(const QList<QJsonObject>& measurements);
    void visualizeSelectedData();

    QVBoxLayout* mainLayout;
    QTableWidget* dataTable;
    QPushButton* visualizeButton;
    StorageManager& storageManager;

signals:
    void exitClicked();
};

#endif // HISTORYFORM_H
