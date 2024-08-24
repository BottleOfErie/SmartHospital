#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include<QTcpSocket>

class ClientSocket : public QObject{
    Q_OBJECT
public:
    static ClientSocket& getInstance();
    void connectToIP(QString ip,int port);

    void loginC(QString id,QString passwd,int type);
private:
    ClientSocket();
    ~ClientSocket();
    ClientSocket(const ClientSocket&) = delete;
    const ClientSocket &operator=(const ClientSocket&)=delete;
    void doCommand(QString command);
    QTcpSocket*socket;
    QString buffer;
private slots:
    void readyRead_slot();
    void connected_slot();
    void disconnected_slot();
    void error_slot(QAbstractSocket::SocketError socketError);
signals:
    void connected();
    void disconnected();
    void recived_ping();

    void login_callback(bool result);
};

#endif // CLIENTSOCKET_H
