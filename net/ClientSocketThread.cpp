#include<QHostAddress>

#include "ClientSocketThread.h"


ClientSocketThread::ClientSocketThread(QString ip,int port){
    socket=new QTcpSocket(this);

    socket->connectToHost(QHostAddress(ip),port);
}
