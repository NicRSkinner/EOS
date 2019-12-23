//#include <wiringPi.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "driverinterface.h"


class ESCDriver : public DriverInterface
{
public:
    ESCDriver(int channel, int min, int max, int center);
    void start();
    void stop();
    void send(int val);
    int read();

private:
    void signalAlarm(int sig_num);

    int chanel;
    int signal;
    int min;
    int max;
    int center;
}