#ifndef _ESCDRIVER_H_
#define _ESCDRIVER_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>

#define MAX_BUF 64

class ESCDriver
{
public:
    ESCDriver(int channel, unsigned long int minns, unsigned long int maxns, unsigned long int centerns, bool reversible);
    void start();
    void stop();
    void send(int val, int lowerBound, int upperBound);
    int read();
    

private:
    unsigned long int normalize(int minFrom, int maxFrom, unsigned long int minTo,
                                 unsigned long int maxTo, int val);
    void export_pwms();
    void set_period(unsigned long int ns);
    void set_duty(unsigned long int duty);
    void start_pwms();
    void stop_pwms();


    int channel;
    unsigned long int minns;
    unsigned long int maxns;
    unsigned long int centerns;
    bool reversible;

    ESCDriver();
};

#endif
