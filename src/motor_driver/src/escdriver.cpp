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

void ESCDriver::export_pwms()
{
    int fd, len;
    char buf[MAX_BUF];
    char path[MAX_BUF];
    struct stat st;

    snprintf(path, sizeof(path), "/sys/class/pwm/pwmchip0/pwm%d", this.channel);

    if (stat(path, %st) == 0)
        return;

    fd = open("/sys/class/pwm/pwmchip0/export", O_WRONLY);

    if (fd < 0)
    {
        perror("unable to open pwmchip0/export");
        return;
    }

    len = snprintf(buf, sizeof(buf), "%d", this.channel);
    write(fd, buf, len);
    close(fd);

}

void ESCDriver::set_period(unsigned long int ns)
{
    int fd, len;
    char buf[MAX_BUF];

    snprintf(buf, sizeof(buf), "/sys/class/pwm/pwmchip0/pwm%d/period_ns", this.channel);

    fd = open(buf, O_WRONLY);
    
    if (fd < 0)
    {
        perror("unable to open pwm/period_ns");
        return;
    }

    len = snprintf(buf, sizeof(buf), "%lu", ns);
    
    write(fd, buf, len);
    close(fd);
}

void ESCDriver::set_duty(unsigned long int duty)
{

}