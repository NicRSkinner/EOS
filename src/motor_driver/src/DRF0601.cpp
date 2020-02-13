#include "DRF0601.h"

DRF0601::DRF0601(int pwmPin, int fwPin, int revPin, int pwmRange)
{
    wiringPiSetup();

    this->pwmPin = pwmPin;
    this->fwPin = fwPin;
    this->revPin = revPin;
    this->pwmRange = pwmRange;
}

void DRF0601::start()
{
    pinMode(this->pwmPin, OUTPUT);
    pinMode(this->fwPin, OUTPUT);
    pinMode(this->revPin, OUTPUT);

    digitalWrite(this->fwPin, HIGH);
    digitalWrite(this->revPin, HIGH);
    int ret = softPwmCreate(this->pwmPin, 0, this->pwmRange);

    if (ret != 0)
    {
        std::cerr << strerror(errno) << std::endl;
    }
}

void DRF0601::stop()
{
    softPwmWrite(this->pwmPin, 0);
}

void DRF0601::send(int val, bool reverse)
{
    if (val > this->pwmRange) val = this->pwmRange;
    if (val < 0) val = 0;

    if (reverse)
    {
        digitalWrite(this->revPin, HIGH);
        digitalWrite(this->fwPin, LOW);
    }
    else
    {
        digitalWrite(this->fwPin, HIGH);
        digitalWrite(this->revPin, LOW);
    }

    softPwmWrite(this->pwmPin, val);
}


DRF0601::DRF0601()
{ }
