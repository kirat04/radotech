#include "battery.h"

Battery::Battery()
{
percentCharged = 100;
lowPowerState = false;
}

void Battery::deplete(int amount){
    if(percentCharged <= amount)
        percentCharged = 0;
    else
    percentCharged -= amount;

    if(!lowPowerState&&percentCharged<20){
        lowPowerState = true;
        emit sendLowPower();
    }
    if (percentCharged<=5) {
        emit sendShutdown();
    }
emit sendCurrentAmount(percentCharged);
}

int Battery::getCurrentAmount(){
    return percentCharged;
}


bool Battery::isLowPower()
{
    return (percentCharged < 20);
}

bool Battery::isCritical()
{
    return (percentCharged <= 5);
}

void Battery::depleteOne(){
    this->deplete(1);
}
