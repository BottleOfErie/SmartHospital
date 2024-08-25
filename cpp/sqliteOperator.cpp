#include "h/sqliteOperator.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QMessageBox>
#include <string>
#include <QSqlTableModel>

SqliteOperator::SqliteOperator() {
    this->connect("General.db");
    createTables();
}

bool SqliteOperator::connect(const QString &dbName) {
    this->Db = QSqlDatabase::addDatabase("QSQLITE", QString("%1").arg(dbName));
    this->Db.setDatabaseName(dbName);
    if (!this->Db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"), this->Db.lastError().text());
        return false;
    }
    return true;
}


bool SqliteOperator::createTables()
{
    // 打开数据库
    if (!this->Db.open()) {
        qDebug() << "Database open error!";
        return false;
    }

    QSqlQuery query(this->Db);

    // 创建 Account 表
    query.prepare("CREATE TABLE Account("
                  "userName TEXT PRIMARY KEY,"
                  "password CHARACTER(20))");
    if (!query.exec()) {
        qDebug() << "Error creating Account table: " << query.lastError().text();
        return false;
    } else {
        qDebug() << "Account table created!";
    }

    // 创建病人表
    query.prepare("CREATE TABLE Patient("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "name TEXT NOT NULL,"
                  "idCard TEXT UNIQUE NOT NULL,"
                  "username TEXT UNIQUE NOT NULL,"
                  "password TEXT NOT NULL,"
                  "gender TEXT,"
                  "birthdate DATE,"
                  "phone TEXT)");
    if (!query.exec()) {
        qDebug() << "Error creating Patient table: " << query.lastError().text();
        return false;
    }

    // 创建医生表
    query.prepare("CREATE TABLE Doctor("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "name TEXT NOT NULL,"
                  "idCard TEXT UNIQUE NOT NULL,"
                  "username TEXT UNIQUE NOT NULL,"
                  "password TEXT NOT NULL,"
                  "gender TEXT,"
                  "birthdate DATE,"
                  "phone TEXT,"
                  "title TEXT,"
                  "hospital TEXT,"
                  "department TEXT)");
    if (!query.exec()) {
        qDebug() << "Error creating Doctor table: " << query.lastError().text();
        return false;
    }

    // 创建病历表
    query.prepare("CREATE TABLE MedicalRecord("
                  "patientId INTEGER,"
                  "doctorId INTEGER,"
                  "dateTime DATETIME,"
                  "chatRecord TEXT,"
                  "diagnosisDetails TEXT,"
                  "medicalAdvice TEXT,"
                  "PRIMARY KEY (patientId, doctorId, dateTime),"
                  "FOREIGN KEY (patientId) REFERENCES Patient(id),"
                  "FOREIGN KEY (doctorId) REFERENCES Doctor(id))");
    if (!query.exec()) {
        qDebug() << "Error creating MedicalRecord table: " << query.lastError().text();
        return false;
    }

    // 创建处方表
    query.prepare("CREATE TABLE Prescription("
                  "patientId INTEGER,"
                  "doctorId INTEGER,"
                  "dateTime DATETIME,"
                  "medicineName TEXT,"
                  "medicinePrice REAL,"
                  "medicineQuantity INTEGER,"
                  "usageAdvice TEXT,"
                  "PRIMARY KEY (patientId, doctorId, dateTime, medicineName),"
                  "FOREIGN KEY (patientId) REFERENCES Patient(id),"
                  "FOREIGN KEY (doctorId) REFERENCES Doctor(id))");
    if (!query.exec()) {
        qDebug() << "Error creating Prescription table: " << query.lastError().text();
        return false;
    }

    // 创建预约信息表
    query.prepare("CREATE TABLE Appointment("
                  "patientId INTEGER,"
                  "doctorId INTEGER,"
                  "dateTime DATETIME,"
                  "isCompleted BOOLEAN,"
                  "PRIMARY KEY (patientId, doctorId, dateTime),"
                  "FOREIGN KEY (patientId) REFERENCES Patient(id),"
                  "FOREIGN KEY (doctorId) REFERENCES Doctor(id))");
    if (!query.exec()) {
        qDebug() << "Error creating Appointment table: " << query.lastError().text();
        return false;
    }

    // 创建健康评估信息表
    query.prepare("CREATE TABLE HealthAssessment("
                  "patientId INTEGER,"
                  "dateTime DATETIME,"
                  "height REAL,"
                  "weight REAL,"
                  "heartRate INTEGER,"
                  "bloodPressureHigh INTEGER,"
                  "bloodPressureLow INTEGER,"
                  "lungCapacity REAL,"
                  "PRIMARY KEY (patientId, dateTime),"
                  "FOREIGN KEY (patientId) REFERENCES Patient(id))");
    if (!query.exec()) {
        qDebug() << "Error creating HealthAssessment table: " << query.lastError().text();
        return false;
    }

    qDebug() << "All tables created successfully!";

    // 关闭数据库
    Db.close();
    return true;
}

//I think QString should be ok. But it needed to be tested
bool SqliteOperator::Login(QString userName, QString Password) {
    Db.open();
    QSqlQuery query2(this->Db);
    query2.prepare("SELECT password FROM Account WHERE username = :username");
    query2.bindValue(":username", userName);

    if (!query2.exec()) {
        qDebug() << "Query failed:" << query2.lastError();
        return false;
    }
    if (query2.next()) {
        return false;
    }

    QSqlQuery query(this->Db);
    query.prepare("INSERT INTO Account VALUES(:username, :password)");
    query.bindValue(":username", userName);
    query.bindValue(":password", Password);
    query.exec();
    Db.close();
    return true;
}

bool SqliteOperator::validateLogin(QString username, QString InputPassword) {
    Db.open();
    QSqlQuery query(this->Db);
    query.prepare("SELECT password FROM Account WHERE username = :username");
    query.bindValue(":username", username);
    if (!query.exec()) {
        qDebug() << "Query failed:" << query.lastError();
        return false;
    }

    if (query.next()) {
        QString storedPassword = query.value(0).toString();
        if (storedPassword == InputPassword) {
            return true;
        } else {
            return false;
        }
    } else {
        qDebug() << "No Such user found";
        return false;
    }
   Db.close();
}


