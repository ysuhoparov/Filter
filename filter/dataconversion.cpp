#include "dataconversion.h"
#include "qtypes.h"

DataConversion::DataConversion()
{

}

quint64 DataConversion::incode(const NetInfo& nt) {
    quint64 uif = nt.u + (nt.i<<8) + (nt.flags<<16) + ((quint64)nt.err<<24);
    quint64 rgn = ((quint64)nt.shake << 32) + ((quint64)nt.errshake << 40);
    return uif +rgn;
}
