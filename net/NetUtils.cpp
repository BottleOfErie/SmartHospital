#include "NetUtils.h"

extern const QString NetUtils::messagePrefix="=<GeNsHiN>=";
extern const QString NetUtils::messageSuffix="=<IMpAct>=";
extern const QString NetUtils::messagePartition="|miD|";
extern const long NetUtils::waitTime = 10000l;

const QByteArray NetUtils::wrapMessage(const QString& message){
    auto str=NetUtils::messagePrefix+message+NetUtils::messageSuffix;
    return str.toUtf8();

}

const QString NetUtils::combineStrings(const std::initializer_list<std::string>& args){
    QString ret=messagePrefix;
    for(const std::string& x:args){
        ret.append(x.data());
        ret.append(messagePartition);
    }
    return ret+messageSuffix;
}

const QByteArray NetUtils::wrapStrings(const std::initializer_list<std::string>& args){
    return combineStrings(args).toUtf8();
}
