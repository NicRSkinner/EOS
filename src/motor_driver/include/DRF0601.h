#ifndef _DRF0601_H_
#define _DRF0601_H_

#ifndef _ARCH_TESTING_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <iostream>

#include <wiringPi.h>
#include <softPwm.h>

class DRF0601
{
public:
    DRF0601(int pwmPin, int fwPin, int revPin, int pwmRange);
    void start();
    void stop();
    void send(int val, bool reverse);

private:
    int pwmPin;
    int fwPin;
    int revPin;
    int pwmRange;

    DRF0601();
};

#endif
#endif
