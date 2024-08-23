#include<QHostAddress>

#include "ClientSocket.h"
#include "NetUtils.h"

ClientSocket::ClientSocket(){
    socket=new QTcpSocket(this);

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead_slot()));
    connect(socket,SIGNAL(connected()),this,SLOT(connected_slot()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected_slot()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),
        this,SLOT(error_slot(QAbstractSocket::SocketError)));
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
    if(pre>=0){
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

void ClientSocket::connected_slot(){
    qDebug("ClientSocket:Connected\n");
    emit connected();
}

void ClientSocket::disconnected_slot(){
    qDebug("ClientSocket:Disconnected\n");
    emit disconnected();
}

void ClientSocket::error_slot(QAbstractSocket::SocketError socketError){
    qDebug("ClientSocket:Error %d\n",socketError);
}

void ClientSocket::doCommand(QString command){
    qDebug("Client Taken:%s",command.toStdString().data());
    if(command.startsWith("ping")){
        socket->write(NetUtils::wrapMessage("ping"));
    }
}
