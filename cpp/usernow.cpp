#include "h/usernow.h"

QString usernow::id="";
int usernow::logined=0;
usernow::usernow()
{

}

QString usernow::getId()
{
    return id;
}

void usernow::setId(const QString &value)
{
    id = value;
}
void usernow::setlogined(int value)
{
    logined = value;
}
int usernow::getlogined(){
    return logined;
}
