#ifndef NETUTILS_H
#define NETUTILS_H

#include <initializer_list>
#include <QString>
#include <string>

namespace NetUtils {
    extern const QString messagePrefix;
    extern const QString messageSuffix;
    extern const QString messagePartition;
    extern const long waitTime;

    const QByteArray wrapMessage(const QString& message);
    const QString combineStrings(const std::initializer_list<std::string>& args);
    const QByteArray wrapStrings(const std::initializer_list<std::string>& args);
}

#endif
