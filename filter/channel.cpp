#include "channel.h"

Channel::Channel()
{
    udemo = new unsigned char[8];

    for(int i=0; i<8; i++)
        udemo[i] = 18+i%3;

}

Channel::~Channel()
{
    delete udemo;
}


// Controllers data files modeling
void Channel::network() {
    for(int i = 0;; i++) {    // вечный цикл
        i%=50;
        controllerData.field=i/10 +1;
        int j = i%10;

        if (j==1) {
            if(++udemo[i/10] > 48 + i/10 +rand()%15){
                controllerData.flags = 1;
                udemo[i/10]-=3+rand()%9;
            }
            if(udemo[i/10]<20) {
                udemo[i/10]=20;
                controllerData.flags &= 0x7f;
            }
            if(!(Channel::status &(1 << i/10))) {
                udemo[i/10]=7;
                controllerData.flags |= 0x80;
            }
            controllerData.u = udemo[i/10];

        }
        if (j==2)
            controllerData.i = udemo[i/10]>18 ? udemo[i/10]*udemo[i/10]/(50-i/10) :0;

        if (j==4) {
            if(rand()%5)
                controllerData.shake = 0;
            else controllerData.shake = 1;
        }

        // Data ready
        if (j==9) {
            emit send(controllerData);
            controllerData.flags &=0xfe;
        }

        QThread::msleep(10);
    }
}

