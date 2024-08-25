#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include<QTcpSocket>
#include "NetUtils.h"

class ClientSocket : public QObject{
    Q_OBJECT
public:
    static ClientSocket& getInstance();
    void connectToIP(QString ip,int port);

    void loginC(QString id,QString passwd,int type);
    void getPatientById(long id);
    void getPatientByNationalId(QString nationalId);
    void getDoctorDataById(long id);
    void getDoctorByNationalId(QString nationalId);
    void getDoctorsBySection(QString section);
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
    void patient_callback(NetUtils::PatientData data);
    void doctor_callback(NetUtils::DoctorData data);
};

#endif // CLIENTSOCKET_H
