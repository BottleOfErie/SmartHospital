#ifndef SERVERSOCKETTHREAD_H
#define SERVERSOCKETTHREAD_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QThread>

class ServerSocketThread : public QThread{
    Q_OBJECT
public:
    bool alive;
    ServerSocketThread(qintptr descriptor);
    ~ServerSocketThread();
    void run();
    void doCommand(QString str);
private:
    int authority = -1;
    long id = -1;
    QTcpSocket *socket;
    QString buffer;
    bool hasReply;
    qintptr socketDescripter;
    void loginCMD(QString id,QString passwd,int type);
    void getPatientDataById(long id);
private slots:
    void readyRead_slot();
    void doPing_slot();
signals:
    void toDoPing();
};

#endif
