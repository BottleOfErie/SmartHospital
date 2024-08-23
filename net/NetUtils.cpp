#include "NetUtils.h"

extern const QString NetUtils::messagePrefix="=<GeNsHiN>=";
extern const QString NetUtils::messageSuffix="=<IMpAct>=";
extern const long NetUtils::waitTime = 5000l;

const QByteArray NetUtils::wrapMessage(const QString& message){
    auto str=NetUtils::messagePrefix+message+NetUtils::messageSuffix;
    return str.toUtf8();
}
