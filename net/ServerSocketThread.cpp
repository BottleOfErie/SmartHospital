#include <cstdio>

#include "NetUtils.h"
#include "ServerSocketThread.h"

ServerSocketThread::ServerSocketThread(QTcpSocket *socket){
    this->socket=socket;
    buffer = QString();

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead_slot()));
    alive=true;
}

void ServerSocketThread::run(){
    while (true) {
        sleep(waitTime);
        if(!hasReply){
            printf("Client No-reply For more than %ld ms,disconnected!",waitTime);
            socket->close();
            alive=false;
        }
        socket->write(NetUtils::wrapMessage("ping"));
    }
}

void ServerSocketThread::readyRead_slot(){
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

void ServerSocketThread::doCommand(QString str){
    printf("Server Taken:%s",str.toStdString().data());
}
