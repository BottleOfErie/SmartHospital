#include <QString>

namespace NetUtils {
    QString messagePrefix="=<GeNsHiN>=";
    QString messageSuffix="=<IMpAct>=";

    inline QByteArray wrapMessage(QString message){
        auto str=messagePrefix+message+messageSuffix;
        return str.toUtf8();
    }
}
