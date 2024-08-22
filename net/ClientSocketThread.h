#ifndef CLIENTSOCKETTHREAD_H
#define CLIENTSOCKETTHREAD_H

#include<QTcpSocket>
#include<QThread>

class ClientSocketThread:public QThread{
public:
    ClientSocketThread(QString ip,int port);
    ~ClientSocketThread();
private:
    QTcpSocket*socket;
private slots:
    void readyRead_slot();
};

#endif // CLIENTSOCKETTHREAD_H
