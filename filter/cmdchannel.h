
#ifndef CMDCHANNEL_H
#define CMDCHANNEL_H

#include "channel.h"

//alternative command

class CmdChannel : public Channel
{
    Q_OBJECT
public:
    CmdChannel(unsigned int);
    unsigned int cmd;

public slots:
    void command();


signals:
    void sendcmd(int);
};

#endif // CMDCHANNEL_H
