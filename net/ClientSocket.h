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
    void getAppointmentsByPatient(long id);
    void getAppointmentsByDoctor(long id);
    void getMedicalRecordsByPatient(long id);
    void getMedicalRecordsByDoctor(long id);
    void getPrescriptionsByPatient(long id);
    void getPrescriptionsByDoctor(long id);
    void getTestResultsByPatient(long id);
    void getMessageAsPatient(long id);
    void getMessageAsDoctor(long id);
    void getMedicineById(long id);
    void getMedicineByName(QString name);
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
    void login_slot(bool);
signals:
    void connected();
    void disconnected();
    void recived_ping();

    void login_callback(bool result);
    void patient_callback(NetUtils::PatientData data);
    void doctor_callback(NetUtils::DoctorData data);
    void appointment_callback(NetUtils::Appointment data);
    void medicalRecord_callback(NetUtils::MedicalRecord data);
    void prescription_callback(NetUtils::Prescription data);
    void testResult_callback(NetUtils::TestResult data);
    void message_callback(NetUtils::Message data);
    void medicine_callback(NetUtils::Medicine data);
};

#endif // CLIENTSOCKET_H
