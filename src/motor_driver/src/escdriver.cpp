#include "escdriver.h"

ESCDriver::ESCDriver(int channel, int min, int max, int center)
{
    this.channel = channel;
    this.signal = 0;
    this.min = min;
    this.max = max;
    this.center = center;
}

void ESCDriver::start()
{
    
}

void ESCDriver::stop()
{

}

void ESCDriver::send(int val)
{

}

int ESCDriver::read()
{

}

void ESCDriver::signalAlarm(int sig_num)
{

}