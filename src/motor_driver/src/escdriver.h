//#include <wiringPi.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "driverinterface.h"

#define MAX_BUF 64

class ESCDriver : public DriverInterface
{
public:
    ESCDriver(int channel, int min, int max, int center);
    void start();
    void stop();
    void send(int val);
    int read();

private:
    void export_pwms();
    void set_period(unsigned long int ns);
    void set_duty(unsigned long int duty);
    void start_pwms();
    void stop_pwms();


    int channel;
    unsigned long int minns;
    unsigned long int maxns;
    unsigned long int centerns;
}