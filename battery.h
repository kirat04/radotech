#ifndef BATTERY_H
#define BATTERY_H
#include "QObject"

class Battery : public QObject
{
    Q_OBJECT
public:
     Battery();

int getCurrentAmount();
    bool isLowPower();
    bool isCritical();
public slots:
        void deplete(int amount);
private:
    int percentCharged;
    bool lowPowerState;
signals:
    void sendLowPower();
    int sendCurrentAmount(int amount);
    void sendShutdown();


};

#endif // BATTERY_H
