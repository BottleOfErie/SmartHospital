#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include<QTcpServer>
#include<QTcpSocket>

#include "ServerSocketThread.h"

class ServerThread:public QTcpServer{
    Q_OBJECT
public:
    ServerThread(int port);
    ~ServerThread();
private:
    QList<ServerSocketThread*>threads;
    virtual void incomingConnection(qintptr handle);
};

#endif // SERVERTHREAD_H
