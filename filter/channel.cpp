#include "channel.h"

Channel::Channel()
{
    last.field=last.u=last.i=last.f=last.flags=last.err=last.shake=last.errshake=0;
    udemo = new unsigned char[4];

    for(int j=0; j<4; j++) {
      udemo[j] = 18+j*2;
     // Channel::status = 1;
    }
     //status[1] = 0;

}

void Channel::network() {
    for(int i = 0;; i++) {    // вечный цикл
        i%=40;
        last.field=i/10 +1;
        int j = i%10;

        if (j==1) {
            if(++udemo[i/10] > 48 + i/10 +rand()%15){
                last.flags = 1;
                udemo[i/10]-=3+rand()%9;
            }
            if(udemo[i/10]<20) udemo[i/10]=20;
            last.flags &= 0x7f;
            if(!(Channel::status &(1 << i/10))) {
                udemo[i/10]=7;
                last.flags |= 0x80;
            }
            last.u = udemo[i/10];

        }
        if (j==2)
            last.i = udemo[i/10]>18 ? udemo[i/10]*udemo[i/10]/(40-i/10) :0;

        if (j==4) {
            if(rand()%5)
                last.shake = 0;
            else last.shake = 1;
        }

        if (j==9) {
            emit send(last);
            last.flags &=0xfe;
        }

        QThread::msleep(10);
    }
}

