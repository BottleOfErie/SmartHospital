#ifndef SERVERSOCKETTHREAD_H
#define SERVERSOCKETTHREAD_H

#include <QTcpSocket>
#include <QTcpServer>
#include <QThread>

#include "NetUtils.h"
#include "h/sqliteOperator.h"

class ServerSocketThread : public QThread{
    Q_OBJECT
public:
    bool alive;
    ServerSocketThread(qintptr descriptor,SqliteOperator*dbop);
    ~ServerSocketThread();
    void run();
    void doCommand(QString str);
private:
    int authority = -1;
    long id = -1;
    QTcpSocket *socket;
    QString buffer;
    int noReplyCount;
    qintptr socketDescripter;
    SqliteOperator* dbop;
    void loginCMD(QString id,QString passwd,int type);
    void getPatientDataById(long id);
    void getPatientDataByNationalId(QString name);
    void getDoctorDataById(long id);
    void getDoctorDataByNationalId(QString name);
    void getDoctorDatasBySection(QString section);
    void getAppointmentsByDoctorId(long id);
    void getAppointmentsByPatientId(long id);
    void getMedicalRecordsByDoctorId(long id);
    void getMedicalRecordsByPatientId(long id);
    void getPrescriptionsByPatient(long id);
    void getPrescriptionsByDoctor(long id);
    void getTestResultsByPatient(long id);
    void getMessageAsPatient(long id);
    void getMessageAsDoctor(long id);
    void getMedicineById(long id);
    void getMedicineByName(QString name);

    void setPatient(NetUtils::PatientData data);
    void setDoctor(NetUtils::DoctorData data);
    void setAppointment(NetUtils::Appointment data);
    void setMedicalRecord(NetUtils::MedicalRecord data);
    void setPrescription(NetUtils::Prescription data);
    void setTestResult(NetUtils::TestResult data);
    void setMessage(NetUtils::Message data);
    void setMedicine(NetUtils::Medicine data);
private slots:
    void readyRead_slot();
    void doPing_slot();
    void doDisconnect_slot();
signals:
    void toDoPing();
    void toDoDisconnect();
};

#endif
