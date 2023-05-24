
#include "cmdchannel.h"

CmdChannel::CmdChannel(uint cmd)
{
    this->cmd =cmd;
}

void CmdChannel::command()
{
    Channel::status = cmd;
    emit sendcmd(cmd);
}

