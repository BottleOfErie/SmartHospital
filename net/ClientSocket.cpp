#include<QHostAddress>

#include "ClientSocket.h"

#include "NetUtils.h"

ClientSocket::ClientSocket(){
    socket=new QTcpSocket(this);

    socket->connect(socket,SIGNAL(connected()),this,SIGNAL(connected()));
    socket->connect(socket,SIGNAL(disconnected()),this,SIGNAL(disconnected()));
}

ClientSocket::~ClientSocket(){
    if(socket!=nullptr)
        delete socket;
}

ClientSocket& ClientSocket::getInstance(){
    static ClientSocket instance;
    return instance;
}

void ClientSocket::connectToIP(QString ip, int port){
    socket->connectToHost(QHostAddress(ip),port);
}

void ClientSocket::readyRead_slot(){
    buffer+=socket->readAll();
    int pre=buffer.indexOf(NetUtils::messagePrefix);
    if(pre>0){
        buffer=buffer.mid(pre);
        int suff=buffer.indexOf(NetUtils::messageSuffix);
        if(suff>0){
            doCommand(
                        buffer.mid(
                            NetUtils::messagePrefix.length()
                            ,suff-NetUtils::messagePrefix.length()));
            buffer=buffer.mid(suff);
        }
    }
}

void ClientSocket::doCommand(QString command){
    printf("Client Taken:%s",command.toStdString().data());
}
