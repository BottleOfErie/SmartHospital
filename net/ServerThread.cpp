#include"ServerThread.h"

ServerThread::ServerThread(int port){
    server=new QTcpServer(this);
    server->listen(QHostAddress::Any,port);

    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection_slot()));
}

ServerThread::~ServerThread(){
    delete server;
    foreach(auto th,threads){
        if(th!=nullptr)
            delete th;
    }
}

void ServerThread::run(){
    while(true){
        sleep(100);
        while(threads.first()==nullptr||!threads.first()->alive){
            threads.removeFirst();
        }
    }
}

void ServerThread::newConnection_slot(){
    auto socket=server->nextPendingConnection();
    auto thread=new ServerSocketThread(socket);
    thread->start();
    threads.append(thread);
}
