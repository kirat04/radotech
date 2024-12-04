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
emit sendCurrentAmount(percentCharged);
}

int Battery::getCurrentAmount(){
    return percentCharged;
}


bool Battery::isLowPower()
{
    return (percentCharged < 20);
}

