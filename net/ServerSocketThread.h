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
private slots:
    void readyRead_slot();
    void doPing_slot();
    void doDisconnect_slot();
signals:
    void toDoPing();
    void toDoDisconnect();
};

#endif
