
class DriverInterface
{
public:
    virtual void start(int iopins[]);
    virtual void stop();
    virtual void send(int val);
    virtual int read();
}