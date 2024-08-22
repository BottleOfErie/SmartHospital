#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include<QTcpSocket>

class ClientSocket : public QObject{
    Q_OBJECT
public:
    static ClientSocket& getInstance();
    void connectToIP(QString ip,int port);
private:
    ClientSocket();
    ~ClientSocket();
    void doCommand(QString command);
    QTcpSocket*socket;
    QString buffer;
private slots:
    void readyRead_slot();
signals:
    void connected();
    void disconnected();
    void recived_ping();
};

#endif // CLIENTSOCKET_H
