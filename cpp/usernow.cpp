#include "h/usernow.h"

QString usernow::id="";
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
