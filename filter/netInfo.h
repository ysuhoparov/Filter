#ifndef NETINFO_H
#define NETINFO_H

// Данные канала
class NetInfo
{
public:
    unsigned char field;
    unsigned char u;
    unsigned char i;
    unsigned char f;

    unsigned char flags;
    unsigned char err;
    unsigned char shake;
    unsigned char errshake;
};

#endif // NETINFO_H
