#ifndef BATTERY_H
#define BATTERY_H
#include "QObject"

class Battery : public QObject
{
    Q_OBJECT
public:
    Battery();
    void deplete(int amount);
    int getCurrentAmount();
private:
    int percentCharged;
    bool lowPowerState;
signals:
    void sendLowPower();

};

#endif // BATTERY_H
