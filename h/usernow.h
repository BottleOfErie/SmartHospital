#ifndef USERNOW_H
#define USERNOW_H

#include<QString>
class usernow
{
public:
    usernow();
    static QString getId();
    static void setId(const QString &value);
    static int getlogined();
    static void setlogined(const int);

private:
    static QString id;
};

#endif // USERNOW_H
