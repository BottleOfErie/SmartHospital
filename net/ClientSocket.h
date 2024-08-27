#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include<QTcpSocket>
#include "NetUtils.h"

class ClientSocket : public QObject{
    Q_OBJECT
public:
    static ClientSocket& getInstance();
    void connectToIP(QString ip,int port);

    void registerAsDoctor(QString nationalId,QString passwd);
    void registerAsPatient(QString nationalId,QString passwd);
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

    //id<=0 equals NONE
    void submitPatientData(NetUtils::PatientData data);
    void submitDoctorData(NetUtils::DoctorData data);
    void submitAppointment(NetUtils::Appointment data);
    void submitMedicalRecord(NetUtils::MedicalRecord data);
    void submitPrescription(NetUtils::Prescription data);
    void submitTestResult(NetUtils::TestResult data);
    void submitMessage(NetUtils::Message data);
    void submitMedicine(NetUtils::Medicine data);
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
    void login_slot(long long);
signals:
    void connected();
    void disconnected();
    void recived_ping();

    void register_callback(long long id);
    void login_callback(long long id);
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
