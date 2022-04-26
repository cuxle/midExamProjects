#include "hardwareinfo.h"

HardWareInfo::HardWareInfo(QObject *parent)
    : QObject(parent)
{

}

QString HardWareInfo::getMyMachineCode()
{
    // get cpuid , biosId, board mac Id
    // machine code -> md5(total_id)
    return QString();
}
