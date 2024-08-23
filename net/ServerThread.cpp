#include"ServerThread.h"

ServerThread::ServerThread(int port){
    QTcpServer();
    this->listen(QHostAddress::Any,port);
}

ServerThread::~ServerThread(){
    foreach(auto th,threads){
        if(th!=nullptr)
            delete th;
    }
}

void ServerThread::incomingConnection(qintptr handle){
    auto thread=new ServerSocketThread(handle);
    thread->start();
    threads.append(thread);
}
