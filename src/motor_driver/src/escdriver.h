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
    void set_period(long ns);
    void set_duties();


    int chanel;
    int signal;
    int min;
    int max;
    int center;
}