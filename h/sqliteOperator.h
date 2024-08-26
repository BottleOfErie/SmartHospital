#ifndef SQLITEOPERATOR_H
#define SQLITEOPERATOR_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <string>

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
    bool insertPatient(const QString &name, const QString &idCard, const QString &password, const QString &gender, const QString &birthdate, const QString &phone, const QString &medicalHistory);
    bool deletePatient(int patientId);
    bool updatePatient(int patientId, const QString &name, const QString &idCard, const QString &password, const QString &gender, const QString &birthdate, const QString &phone, const QString &medicalHistory);

    // Doctor methods
    bool insertDoctor(const QString &name, const QString& workNumber, const QString &idCard, const QString &password, const QString &gender, const QString &birthdate, const QString &phone, const QString &title, const QString &hospital, const QString &department);
    bool deleteDoctor(int doctorId);
    bool updateDoctor(int doctorId, const QString& workNumber, const QString &name, const QString &idCard, const QString &password, const QString &gender, const QString &birthdate, const QString &phone, const QString &title, const QString &hospital, const QString &department);

    // Appointment methods
    bool insertAppointment(int patientId, int doctorId, const QString &dateTime, const QString &status);
    bool deleteAppointment(int patientId, int doctorId, const QString &dateTime);
    bool updateAppointment(int patientId, int doctorId, const QString &dateTime, const QString &status);

    // MedicalRecord methods
    bool insertMedicalRecord(int patientId, int doctorId, const QString &dateTime, const QString &diagnosisDetails, const QString &medicalAdvice);
    bool deleteMedicalRecord(int patientId, int doctorId, const QString &dateTime);
    bool updateMedicalRecord(int patientId, int doctorId, const QString &dateTime, const QString &diagnosisDetails, const QString &medicalAdvice);

    // Prescription methods
    bool insertPrescription(int patientId, int doctorId, const QString &dateTime, const QString &medicineName, int medicineId, int medicineQuantity, const QString &usageAdvice);
    bool deletePrescription(int patientId, int doctorId, const QString &dateTime, const int &medicineId);
    bool updatePrescription(int patientId, int doctorId, const QString &dateTime, int medicineId, int medicineQuantity, const QString &usageAdvice);

    // HealthAssessment methods
    bool insertHealthAssessment(int patientId, const QString &dateTime, double height, double weight, int heartRate, int bloodPressureHigh, int bloodPressureLow, double lungCapacity);
    bool deleteHealthAssessment(int patientId, const QString &dateTime);
    bool updateHealthAssessment(int patientId, const QString &dateTime, double height, double weight, int heartRate, int bloodPressureHigh, int bloodPressureLow, double lungCapacity);

    // ChatRecord methods
    bool insertChatRecord(int patientId, int doctorId, const QString &timestamp, const QString &direction, const QString &message, bool isRead);
    bool deleteChatRecord(int patientId, int doctorId, const QString &timestamp);
    bool updateChatRecord(int patientId, int doctorId, const QString &timestamp, const QString &message, bool isRead);

    // Medicine methods
    bool insertMedicine(const QString &medicineName, double medicinePrice, int medicineStock, const QString &manufacturer, const QString &batchNumber);
    bool deleteMedicine(int medicineId);
    bool updateMedicine(int medicineId, const QString &medicineName, double medicinePrice, int medicineStock, const QString &manufacturer, const QString &batchNumber);
    // 查询全部数据
    void queryTable();
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
