#include "healthmetricVisualization.h"
#include <QDebug>
#include <QPainter>
#include <QFont>
#include <algorithm>

HealthMetricVisualization::HealthMetricVisualization(const QVector<int>& measurements, QWidget *parent)
    : QWidget(parent),
      measurements(measurements),
      primaryColor(QColor(52, 152, 219)),  // Flat Blue
      upperwarningThreshold(70),
      uppercriticalThreshold(100),
      lowerwarningThreshold(40), 
      lowercriticalThreshold(20) {}


void HealthMetricVisualization::setThreshold(int upperwarning, int uppercritical, int lowerwarning, int lowercritical) {
    upperwarningThreshold = upperwarning;
    uppercriticalThreshold = uppercritical;
    lowerwarningThreshold = lowerwarning;
    lowercriticalThreshold = lowercritical;
    update();
}
int HealthMetricVisualization::getMaxMeasurement() const {
    return *std::max_element(measurements.begin(), measurements.end());
}

int HealthMetricVisualization::getMinMeasurement() const {
    return *std::min_element(measurements.begin(), measurements.end());
}

QColor HealthMetricVisualization::getColorForMeasurement(int measurement) const {
    if (measurement >= uppercriticalThreshold || measurement <= lowercriticalThreshold) {
        return QColor(231, 76, 60);  // Flat Red (Critical)
    } else if (measurement >= upperwarningThreshold || measurement <= lowerwarningThreshold) {
        return QColor(241, 196, 15);  // Flat Yellow (Warning)
    } else {
        return QColor(46, 204, 113);  // Flat Green (Normal)
    }
}

void HealthMetricVisualization::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set a clean, readable font
    QFont labelFont("Arial", 10);
    painter.setFont(labelFont);

    // Draw title
    painter.setPen(Qt::black);
    painter.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter, "Health Metrics Visualization");

    drawBarGraph(painter);
}


void HealthMetricVisualization::drawBarGraph(QPainter& painter) {
    if (measurements.isEmpty()) return;

    int maxMeasurement = getMaxMeasurement();

    // Draw graph area with padding for labels
    QRect graphRect = rect().adjusted(70, 80, -50, -50);

    // Draw axes
    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(graphRect.bottomLeft(), graphRect.topLeft());  // Y-axis
    painter.drawLine(graphRect.bottomLeft(), graphRect.bottomRight());  // X-axis

    // Y-axis labels
    painter.setPen(Qt::black);


    // Calculate bar width
    int barWidth = graphRect.width() / measurements.size() * 0.8;

    // Draw bars and labels
    for (int i = 0; i < measurements.size(); ++i) {
        int barHeight = (measurements[i] * graphRect.height()) / maxMeasurement;
        QRect bar(
            graphRect.left() + i * (graphRect.width() / measurements.size()),
            graphRect.bottom() - barHeight,
            barWidth,
            barHeight
        );

        // Color-code based on measurement
        painter.setBrush(getColorForMeasurement(measurements[i]));
        painter.drawRect(bar);

        // Draw bar value
        painter.setPen(Qt::black);
        painter.drawText(bar, Qt::AlignCenter, QString::number(measurements[i]));

        // Determine the label
        QString label;
        if (i < 12) {
            label = QString("H%1").arg(((i + 2)/2));  // H1, H2, ...
        } else {
            label = QString("F%1").arg((i - 10)/2);  // F1, F2, ...
        }

        // Draw the label below the bar
        QRect labelRect(
            graphRect.left() + i * (graphRect.width() / measurements.size()),
            graphRect.bottom() + 15,
            barWidth,
            20
        );
        painter.drawText(labelRect, Qt::AlignCenter, label);
    }
}
