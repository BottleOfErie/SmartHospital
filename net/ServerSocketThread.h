#ifndef SERVERSOCKETTHREAD_H
#define SERVERSOCKETTHREAD_H

#include <QTcpSocket>
#include <QThread>

class ServerSocketThread : public QThread{
    Q_OBJECT
public:
    bool alive;
    long waitTime = 1000;
    ServerSocketThread(QTcpSocket *socket);
    ~ServerSocketThread();
    void run();
    void doCommand(QString str);
private:
    int authority = -1;
    long id = -1;
    QTcpSocket *socket;
    QString buffer;
    bool hasReply;
private slots:
    void readyRead_slot();
};

#endif
