#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <string>
#include "NetUtils.h"  // 包含 NetUtils 结构体的定义

class SqliteOperator
{
public:
    SqliteOperator();


    // 打开数据库
    bool openDb(void);
    // 判断数据表是否存在
    bool isTableExist(QString& tableName);
    //whether username matches password
    bool validateLogin(QString username, QString InputPassword);
    // 数据库表操作函数
    // Patient methods
    bool insertPatient(const QString &name, const QString &idCard, const QString &password, int gender, const QString &birthdate, const QString &phone, const QString &medicalHistory);
    bool deletePatient(int patientId);
    bool updatePatient(int patientId, const QString &name, const QString &idCard, const QString &password, int gender, const QString &birthdate, const QString &phone, const QString &medicalHistory);

    // Doctor methods
    bool insertDoctor(const QString &name, const QString& workNumber, const QString &idCard, const QString &password, int gender, const QString &birthdate, const QString &phone, const QString &title, const QString &hospital, const QString &department);
    bool deleteDoctor(int doctorId);
    bool updateDoctor(int doctorId, const QString& workNumber, const QString &name, const QString &idCard, const QString &password, int gender, const QString &birthdate, const QString &phone, const QString &title, const QString &hospital, const QString &department);

    // Appointment methods
    bool insertAppointment(int patientId, int doctorId, const QString &dateTime, const int &status);
    bool deleteAppointment(int patientId, int doctorId, const QString &dateTime);
    bool updateAppointment(int patientId, int doctorId, const QString &dateTime, const int &status);

    // MedicalRecord methods
    bool insertMedicalRecord(int patientId, int doctorId, const QString &dateTime, const QString &diagnosisDetails, const QString &medicalAdvice);
    bool deleteMedicalRecord(int patientId, int doctorId, const QString &dateTime);
    bool updateMedicalRecord(int patientId, int doctorId, const QString &dateTime, const QString &diagnosisDetails, const QString &medicalAdvice);

    // Prescription methods
    bool insertPrescription(int patientId, int doctorId, const QString &dateTime, const QString &medicineName, int medicineId, int medicineQuantity, const QString &usageAdvice);
    bool deletePrescription(int patientId, int doctorId, const QString &dateTime, const int &medicineId);
    bool updatePrescription(int patientId, int doctorId, const QString &dateTime, int medicineId, int medicineQuantity, const QString &usageAdvice);

    // HealthAssessment methods
    bool insertHealthAssessment(int patientId, const QString &dateTime, double height, double weight, int heartRate, double bloodPressureHigh, double bloodPressureLow, int lungCapacity);
    bool deleteHealthAssessment(int patientId, const QString &dateTime);
    bool updateHealthAssessment(int patientId, const QString &dateTime, double height, double weight, int heartRate, double bloodPressureHigh, double bloodPressureLow, int lungCapacity);

    // ChatRecord methods
    bool insertChatRecord(int patientId, int doctorId, const QString &timestamp, const int &direction, const QString &message, bool isRead);
    bool deleteChatRecord(int patientId, int doctorId, const QString &timestamp);
    bool updateChatRecord(int patientId, int doctorId, const QString &timestamp, const QString &message, bool isRead);

    // Medicine methods
    bool insertMedicine(const QString &medicineName, double medicinePrice, int medicineStock, const QString &manufacturer, const QString &batchNumber);
    bool deleteMedicine(int medicineId);
    bool updateMedicine(int medicineId, const QString &medicineName, double medicinePrice, int medicineStock, const QString &manufacturer, const QString &batchNumber);
    // 查询全部数据
    // 查询函数声明
    QList<NetUtils::PatientData> queryPatientByNationId(const QString& nationId);
    QList<NetUtils::PatientData> queryPatientById(int id);

    QList<NetUtils::DoctorData> queryDoctorByNationId(const QString& nationId);
    QList<NetUtils::DoctorData> queryDoctorById(int id);
    QList<NetUtils::DoctorData> queryDoctorBySection(const QString& section);

    QList<NetUtils::Appointment> queryAppointmentByPatientId(int patientId);
    QList<NetUtils::Appointment> queryAppointmentByDoctorId(int doctorId);

    QList<NetUtils::MedicalRecord> queryMedicalRecordByPatientId(int patientId);
    QList<NetUtils::MedicalRecord> queryMedicalRecordByDoctorId(int doctorId);

    QList<NetUtils::Prescription> queryPrescriptionByPatientId(int patientId);
    QList<NetUtils::Prescription> queryPrescriptionByDoctorId(int doctorId);

    QList<NetUtils::TestResult> queryHealthAssessmentByPatientId(int patientId);

    QList<NetUtils::Message> queryChatRecordByPatientId(int patientId);
    QList<NetUtils::Message> queryChatRecordByDoctorId(int doctorId);

    QList<NetUtils::Medicine> queryMedicineById(int medicineId);
    QList<NetUtils::Medicine> queryMedicineByName(const QString& name);
    // function of logging in
    bool Login(QString userName, QString Password);
    void moreInsertData(); // 插入多条数据
    // 修改数据
    void modifyData(int id, QString name, int age);
    // 删除数据
    void deleteData(int id);
    //删除数据表
    void deleteTable(QString& tableName);
    // 关闭数据库
    void closeDb(void);

private:
    // 用于建立和数据库的连接
    QSqlDatabase database;
    //the general database to be establish
    QSqlDatabase Db;
    //
    bool connect(const QString &dbName);
    //create all tables needed
    bool createTables();
};


#endif // SQLITEOPERATOR_H
