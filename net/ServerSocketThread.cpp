#include <cstdio>

#include "ServerSocketThread.h"
#include "NetUtils.h"

ServerSocketThread::ServerSocketThread(qintptr descriptor){
    socketDescripter=descriptor;
    buffer = QString();
    alive=true;

    socket=new QTcpSocket();
    socket->setSocketDescriptor(socketDescripter);
    qDebug("ServerSocket connected from:%s",socket->peerAddress().toString().toStdString().data());
    socket->write(NetUtils::wrapMessage("ping"));

    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead_slot()));
    connect(this,SIGNAL(toDoPing()),this,SLOT(doPing_slot()));
}

ServerSocketThread::~ServerSocketThread(){
    socket->close();
    delete socket;
}

void ServerSocketThread::run(){
    while (true) {
        msleep(NetUtils::waitTime);
        if(!hasReply){
            qDebug("Client No-reply For more than %ld ms,disconnected!",NetUtils::waitTime);
            socket->disconnectFromHost();
            socket->waitForDisconnected();
            alive=false;
        }
        emit toDoPing();
        hasReply=false;
    }
}

void ServerSocketThread::doPing_slot(){
    socket->write(NetUtils::wrapMessage("ping"));
}

void ServerSocketThread::readyRead_slot(){
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

void ServerSocketThread::doCommand(QString str){
    hasReply=true;
    qDebug("Server Taken:%s",str.toStdString().data());
    auto arr=str.split(NetUtils::messagePartition);
    if(str.startsWith("login")){
        loginCMD(arr[1],arr[2],arr[3].toInt());
    }else if(str.startsWith("GPatId")){
        getPatientDataById(arr[1].toLong());
    }else if(!str.startsWith("ping")){
        qDebug("Unknown Command:%s",str.toStdString().data());
    }
}

//login <true|false>
void ServerSocketThread::loginCMD(QString id,QString passwd,int type){
    qDebug("Trying Login:Id[%s],Pass[%s]Type[%d]",id.toStdString().data(),
           passwd.toStdString().data(),type);
    //Connect DB
    bool result=true;
    socket->write(NetUtils::wrapStrings({"login",result?"true":"false"}));
}

//pat <id> <name> <nationalId> <sex> <birthday> <phoneNumber> <history>
void ServerSocketThread::getPatientDataById(long id){
    //Connect DB
    NetUtils::PatientData result={114,"Firefly","514",1,"114","514","1919810"};
    socket->write(NetUtils::wrapStrings({"pat",
        std::to_string(result.id),result.name.toStdString(),result.nationId.toStdString(),
        std::to_string(result.sex),result.birthday.toStdString(),
        result.phoneNumber.toStdString(),result.history.toStdString()
    }));
}
