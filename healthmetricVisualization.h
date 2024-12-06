#ifndef HEALTHMETRICVISUALIZATION_H
#define HEALTHMETRICVISUALIZATION_H

#include <QWidget>
#include <QVector>
#include <QPainter>
#include <QLinearGradient>


class HealthMetricVisualization : public QWidget {
    Q_OBJECT

public:
    explicit HealthMetricVisualization(const QVector<int>& measurements, QWidget *parent = nullptr);

    void setThreshold(int upperwarningThreshold, int uppercriticalThreshold, int lowerwarningThreshold, int lowercriticalThreshold;);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QVector<int> measurements;
    QColor primaryColor;
    int upperwarningThreshold;
    int uppercriticalThreshold;
    int lowerwarningThreshold;
    int lowercriticalThreshold;

    void drawBarGraph(QPainter& painter);


    // Utility methods
    int getMaxMeasurement() const;
    int getMinMeasurement() const;
    QColor getColorForMeasurement(int measurement) const;
};

#endif // HEALTHMETRICVISUALIZATION_H
