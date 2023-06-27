#ifndef DATACONVERSION_H
#define DATACONVERSION_H

#include "netinfo.h"
#include "qtypes.h"

class DataConversion
{
public:
    DataConversion();

    quint64 incode(const NetInfo&);

};

#endif // DATACONVERSION_H
