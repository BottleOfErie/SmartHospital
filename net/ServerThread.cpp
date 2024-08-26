#include"ServerThread.h"

ServerThread::ServerThread(int port):QTcpServer(){
    dbOp=new SqliteOperator();
    this->listen(QHostAddress::Any,port);
}

ServerThread::~ServerThread(){
    foreach(auto th,threads){
        if(th!=nullptr)
            delete th;
    }
    delete dbOp;
}

const SqliteOperator* ServerThread::getDB(){
    return dbOp;
}

void ServerThread::incomingConnection(qintptr handle){
    auto thread=new ServerSocketThread(handle,dbOp);
    thread->start();
    threads.append(thread);
}
