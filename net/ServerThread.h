#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include<QTcpServer>
#include<QTcpSocket>
#include<QThread>

#include "ServerSocketThread.h"

class ServerThread:public QThread{
public:
    ServerThread(int port);
    ~ServerThread();
    void run();
private:
    QTcpServer * server;
    QList<ServerSocketThread*> threads;
private slots:
    void newConnection_slot();
};

#endif // SERVERTHREAD_H
