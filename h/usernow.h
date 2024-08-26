#ifndef USERNOW_H
#define USERNOW_H

#include<QString>
class usernow
{
public:
    usernow();
    static QString getId();
    static void setId(const QString &value);

private:
    static QString id;
};

#endif // USERNOW_H
