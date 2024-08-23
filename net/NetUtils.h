#ifndef NETUTILS_H
#define NETUTILS_H

#include <QString>

namespace NetUtils {
    extern const QString messagePrefix;
    extern const QString messageSuffix;
    extern const long waitTime;

    const QByteArray wrapMessage(const QString& message);
}

#endif
