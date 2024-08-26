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



//I think QString should be ok. But it needed to be tested
bool SqliteOperator::Login(QString userName, QString Password) {
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
    return true;
}

bool SqliteOperator::validateLogin(QString username, QString InputPassword) {
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
}



bool SqliteOperator::createTables()
{
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
    // 病人表
    query.prepare("CREATE TABLE IF NOT EXISTS Patient ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "name TEXT,"
                  "idCard TEXT,"
                  "password TEXT,"
                  "gender TEXT,"
                  "birthdate DATE,"
                  "phone TEXT,"
                  "medicalHistory TEXT)");
    if (!query.exec()) {
        qDebug() << "Error creating Patient table: " << query.lastError().text();
        return false;
    }

    // 医生表
    query.prepare("CREATE TABLE IF NOT EXISTS Doctor ("
                  "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "name TEXT,"
                  "workNumber TEXT,"
                  "idCard TEXT,"
                  "password TEXT,"
                  "gender TEXT,"
                  "birthdate TEXT,"
                  "phone TEXT,"
                  "title TEXT,"
                  "hospital TEXT,"
                  "department TEXT)");
    if (!query.exec()) {
        qDebug() << "Error creating Doctor table: " << query.lastError().text();
        return false;
    }

    // 预约信息表
    query.prepare("CREATE TABLE IF NOT EXISTS Appointment ("
                  "patientId INTEGER,"
                  "doctorId INTEGER,"
                  "dateTime DATETIME,"
                  "status TEXT,"
                  "PRIMARY KEY (patientId, doctorId, dateTime),"
                  "FOREIGN KEY (patientId) REFERENCES Patient(id),"
                  "FOREIGN KEY (doctorId) REFERENCES Doctor(id))");
    if (!query.exec()) {
        qDebug() << "Error creating Appointment table: " << query.lastError().text();
        return false;
    }

    // 病历表
    query.prepare("CREATE TABLE IF NOT EXISTS MedicalRecord ("
                  "patientId INTEGER,"
                  "doctorId INTEGER,"
                  "dateTime DATETIME,"
                  "diagnosisDetails TEXT,"
                  "medicalAdvice TEXT,"
                  "PRIMARY KEY (patientId, doctorId, dateTime),"
                  "FOREIGN KEY (patientId) REFERENCES Patient(id),"
                  "FOREIGN KEY (doctorId) REFERENCES Doctor(id))");
    if (!query.exec()) {
        qDebug() << "Error creating MedicalRecord table: " << query.lastError().text();
        return false;
    }

    // 处方表
    query.prepare("CREATE TABLE IF NOT EXISTS Prescription ("
                  "patientId INTEGER,"
                  "doctorId INTEGER,"
                  "dateTime TEXT,"
                  "medicineName TEXT,"
                  "medicineId INTEGER,"
                  "medicineQuantity INTEGER,"
                  "usageAdvice TEXT,"
                  "PRIMARY KEY (patientId, doctorId, dateTime, medicineName),"
                  "FOREIGN KEY (patientId) REFERENCES Patient(id),"
                  "FOREIGN KEY (doctorId) REFERENCES Doctor(id))");
    if (!query.exec()) {
        qDebug() << "Error creating Prescription table: " << query.lastError().text();
        return false;
    }

    // 健康评估信息表
    query.prepare("CREATE TABLE IF NOT EXISTS HealthAssessment ("
                  "patientId INTEGER,"
                  "dateTime TEXT,"
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

    // 聊天记录表
    query.prepare("CREATE TABLE IF NOT EXISTS ChatRecord ("
                  "patientId INTEGER,"
                  "doctorId INTEGER,"
                  "timestamp TEXT,"
                  "direction TEXT,"  // "patient_to_doctor" or "doctor_to_patient"
                  "message TEXT,"
                  "isRead BOOLEAN,"
                  "PRIMARY KEY (patientId, doctorId, timestamp),"
                  "FOREIGN KEY (patientId) REFERENCES Patient(id),"
                  "FOREIGN KEY (doctorId) REFERENCES Doctor(id))");
    if (!query.exec()) {
        qDebug() << "Error creating ChatRecord table: " << query.lastError().text();
        return false;
    }

    // 药品表
    query.prepare("CREATE TABLE IF NOT EXISTS Medicine ("
                  "medicineId INTEGER PRIMARY KEY AUTOINCREMENT,"
                  "medicineName TEXT,"
                  "medicinePrice REAL,"
                  "medicineStock INTEGER,"
                  "manufacturer TEXT,"
                  "batchNumber TEXT)");
    if (!query.exec()) {
        qDebug() << "Error creating Medicine table: " << query.lastError().text();
        return false;
    }

    qDebug() << "All tables created successfully!";
    return true;
}

bool SqliteOperator::insertPatient(const QString &name, const QString &idCard, const QString &password, const QString &gender, const QString &birthdate, const QString &phone, const QString &medicalHistory)
{
    QSqlQuery query(this->Db);
    //check if there is a same patient
    query.prepare("SELECT COUNT(*) FROM Patient WHERE idCard = ?");
    query.addBindValue(idCard);
    if (!query.exec() || !query.next() || query.value(0).toInt() > 0) {
        qDebug() << "Patient already exists or query failed";
        return false;
    }

    //insert
    query.prepare("INSERT INTO Patient (name, idCard, password, gender, birthdate, phone, medicalHistory) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(idCard);
    query.addBindValue(password);
    query.addBindValue(gender);
    query.addBindValue(birthdate);
    query.addBindValue(phone);
    query.addBindValue(medicalHistory);
    query.exec();
    return true;
}

bool SqliteOperator::deletePatient(int patientId)
{
    QSqlQuery query(this->Db);
    query.prepare("DELETE FROM Patient WHERE id = ?");
    query.addBindValue(patientId);
    return query.exec();
}

bool SqliteOperator::updatePatient(int patientId, const QString &name, const QString &idCard, const QString &password, const QString &gender, const QString &birthdate, const QString &phone, const QString &medicalHistory)
{
    QSqlQuery query(this->Db);
    query.prepare("UPDATE Patient SET name = ?, idCard = ?, password = ?, gender = ?, birthdate = ?, phone = ?, medicalHistory = ? "
                  "WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(idCard);
    query.addBindValue(password);
    query.addBindValue(gender);
    query.addBindValue(birthdate);
    query.addBindValue(phone);
    query.addBindValue(medicalHistory);
    query.addBindValue(patientId);
    return query.exec();
}

bool SqliteOperator::insertDoctor(const QString &name, const QString& workNumber, const QString &idCard, const QString &password, const QString &gender, const QString &birthdate, const QString &phone, const QString &title, const QString &hospital, const QString &department)
{
    QSqlQuery query(this->Db);
    // 检查医生是否已存在
    query.prepare("SELECT COUNT(*) FROM Doctor WHERE workNumber = ?");
    query.addBindValue(workNumber);
    if (!query.exec() || !query.next() || query.value(0).toInt() > 0) {
        qDebug() << "Doctor already exists or query failed";
        return false;
    }

    //insert
    query.prepare("INSERT INTO Doctor(name, workNumber, idCard, password, gender, birthdate, phone, title, hospital, department)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(workNumber);
    query.addBindValue(idCard);
    query.addBindValue(password);
    query.addBindValue(gender);
    query.addBindValue(birthdate);
    query.addBindValue(phone);
    query.addBindValue(title);
    query.addBindValue(hospital);
    query.addBindValue(department);
    return query.exec();
}

bool SqliteOperator::deleteDoctor(int doctorId)
{
    QSqlQuery query(this->Db);
    query.prepare("DELETE FROM Doctor WHERE id = ?");
    query.addBindValue(doctorId);
    return query.exec();
}

bool SqliteOperator::updateDoctor(int doctorId, const QString& workNumber = " ", const QString &name = " ", const QString &idCard = " ", const QString &password = " ", const QString &gender = " ", const QString &birthdate = " ", const QString &phone = " ", const QString &title = " ", const QString &hospital = " ", const QString &department = " ")
{
    QSqlQuery query(this->Db);
    query.prepare("UPDATE Doctor SET name = ?, workNumber = ?, idCard = ?, password = ?, gender = ?, birthdate = ?, phone = ?, title = ?, hospital = ?, department = ? "
                  "WHERE id = ?");
    query.addBindValue(name);
    query.addBindValue(workNumber);
    query.addBindValue(idCard);
    query.addBindValue(password);
    query.addBindValue(gender);
    query.addBindValue(birthdate);
    query.addBindValue(phone);
    query.addBindValue(title);
    query.addBindValue(hospital);
    query.addBindValue(department);
    query.addBindValue(doctorId);
    return query.exec();
}

bool SqliteOperator::insertAppointment(int patientId, int doctorId, const QString &dateTime, const QString &status)
{
    QSqlQuery query(this->Db);
    // 检查是否已有相同的预约
    query.prepare("SELECT COUNT(*) FROM Appointment WHERE patientId = ? AND doctorId = ? AND dateTime = ?");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);
    if (!query.exec() || !query.next() || query.value(0).toInt() > 0) {
        qDebug() << "Appointment already exists or query failed";
        return false;
    }

    //insert
    query.prepare("INSERT INTO Appointment (patientId, doctorId, dateTime, status) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);
    query.addBindValue(status);
    return query.exec();
}

bool SqliteOperator::deleteAppointment(int patientId, int doctorId, const QString &dateTime)
{
    QSqlQuery query(this->Db);
    query.prepare("DELETE FROM Appointment WHERE patientId = ? AND doctorId = ? AND dateTime = ?");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);
    return query.exec();
}

bool SqliteOperator::updateAppointment(int patientId, int doctorId, const QString &dateTime, const QString &status)
{
    QSqlQuery query(this->Db);
    query.prepare("UPDATE Appointment SET status = ? WHERE patientId = ? AND doctorId = ? AND dateTime = ?");
    query.addBindValue(status);
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);
    return query.exec();
}
bool SqliteOperator::insertMedicalRecord(int patientId, int doctorId, const QString &dateTime, const QString &diagnosisDetails, const QString &medicalAdvice)
{
    QSqlQuery query(this->Db);
    // 检查是否已有相同病历
    query.prepare("SELECT COUNT(*) FROM MedicalRecord WHERE patientId = ? AND doctorId = ? AND dateTime = ?");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);

    if (!query.exec() || !query.next() || query.value(0).toInt() > 0) {
        qDebug() << "Medical record already exists or query failed";
        return false;
    }

    //insert
    query.prepare("INSERT INTO MedicalRecord (patientId, doctorId, dateTime, diagnosisDetails, medicalAdvice) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);
    query.addBindValue(diagnosisDetails);
    query.addBindValue(medicalAdvice);
    return query.exec();
}

bool SqliteOperator::deleteMedicalRecord(int patientId, int doctorId, const QString &dateTime)
{
    QSqlQuery query(this->Db);
    query.prepare("DELETE FROM MedicalRecord WHERE patientId = ? AND doctorId = ? AND dateTime = ?");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);
    return query.exec();
}

bool SqliteOperator::updateMedicalRecord(int patientId, int doctorId, const QString &dateTime, const QString &diagnosisDetails, const QString &medicalAdvice)
{
    QSqlQuery query(this->Db);
    query.prepare("UPDATE MedicalRecord SET diagnosisDetails = ?, medicalAdvice = ? WHERE patientId = ? AND doctorId = ? AND dateTime = ?");
    query.addBindValue(diagnosisDetails);
    query.addBindValue(medicalAdvice);
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);
    return query.exec();
}
bool SqliteOperator::insertPrescription(int patientId, int doctorId, const QString &dateTime, const QString &medicineName, int medicineId, int medicineQuantity, const QString &usageAdvice)
{
    QSqlQuery query(this->Db);
    // 检查是否已有相同处方
    query.prepare("SELECT COUNT(*) FROM Prescription WHERE patientId = ? AND doctorId = ? AND dateTime = ? AND medicineId = ?");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);
    query.addBindValue(medicineId);

    if (!query.exec() || !query.next() || query.value(0).toInt() > 0) {
        qDebug() << "Prescription already exists or query failed";
        return false;
    }

    //insert
    query.prepare("INSERT INTO Prescription (patientId, doctorId, dateTime, medicineName, medicineId, medicineQuantity, usageAdvice) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);
    query.addBindValue(medicineName);
    query.addBindValue(medicineId);
    query.addBindValue(medicineQuantity);
    query.addBindValue(usageAdvice);
    return query.exec();
}

bool SqliteOperator::deletePrescription(int patientId, int doctorId, const QString &dateTime, const int &medicineId)
{
    QSqlQuery query(this->Db);
    query.prepare("DELETE FROM Prescription WHERE patientId = ? AND doctorId = ? AND dateTime = ? AND medicineId = ?");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);
    query.addBindValue(medicineId);
    return query.exec();
}

bool SqliteOperator::updatePrescription(int patientId, int doctorId, const QString &dateTime, int medicineId, int medicineQuantity, const QString &usageAdvice)
{
    QSqlQuery query(this->Db);
    query.prepare("UPDATE Prescription SET medicineQuantity = ?, usageAdvice = ? WHERE patientId = ? AND doctorId = ? AND dateTime = ? AND medicineId = ?");

    query.addBindValue(medicineQuantity);
    query.addBindValue(usageAdvice);
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(dateTime);
    query.addBindValue(medicineId);
    return query.exec();
}
bool SqliteOperator::insertHealthAssessment(int patientId, const QString &dateTime, double height, double weight, int heartRate, int bloodPressureHigh, int bloodPressureLow, double lungCapacity)
{
    QSqlQuery query(this->Db);
    //check if there is a same health assessment
    query.prepare("SELECT COUNT(*) FROM HealthAssessment WHERE patientId = ? AND dateTime = ?");
    query.addBindValue(patientId);
    query.addBindValue(dateTime);

    if (!query.exec() || !query.next() || query.value(0).toInt() > 0) {
        qDebug() << "Health assessment already exists or query failed";
        return false;
    }

    //insert
    query.prepare("INSERT INTO HealthAssessment (patientId, dateTime, height, weight, heartRate, bloodPressureHigh, bloodPressureLow, lungCapacity) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(patientId);
    query.addBindValue(dateTime);
    query.addBindValue(height);
    query.addBindValue(weight);
    query.addBindValue(heartRate);
    query.addBindValue(bloodPressureHigh);
    query.addBindValue(bloodPressureLow);
    query.addBindValue(lungCapacity);
    return query.exec();
}

bool SqliteOperator::deleteHealthAssessment(int patientId, const QString &dateTime)
{
    QSqlQuery query(this->Db);
    query.prepare("DELETE FROM HealthAssessment WHERE patientId = ? AND dateTime = ?");
    query.addBindValue(patientId);
    query.addBindValue(dateTime);
    return query.exec();
}

bool SqliteOperator::updateHealthAssessment(int patientId, const QString &dateTime, double height, double weight, int heartRate, int bloodPressureHigh, int bloodPressureLow, double lungCapacity)
{
    QSqlQuery query(this->Db);
    query.prepare("UPDATE HealthAssessment SET height = ?, weight = ?, heartRate = ?, bloodPressureHigh = ?, bloodPressureLow = ?, lungCapacity = ? WHERE patientId = ? AND dateTime = ?");
    query.addBindValue(height);
    query.addBindValue(weight);
    query.addBindValue(heartRate);
    query.addBindValue(bloodPressureHigh);
    query.addBindValue(bloodPressureLow);
    query.addBindValue(lungCapacity);
    query.addBindValue(patientId);
    query.addBindValue(dateTime);
    return query.exec();
}
bool SqliteOperator::insertChatRecord(int patientId, int doctorId, const QString &timestamp, const QString &direction, const QString &message, bool isRead)
{
    QSqlQuery query(this->Db);
    // 检查是否已有相同聊天记录
    query.prepare("SELECT COUNT(*) FROM ChatRecord WHERE patientId = ? AND doctorId = ? AND timestamp = ?");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(timestamp);

    if (!query.exec() || !query.next() || query.value(0).toInt() > 0) {
        qDebug() << "Chat record already exists or query failed";
        return false;
    }

    //insert
    query.prepare("INSERT INTO ChatRecord (patientId, doctorId, timestamp, direction, message, isRead) "
                  "VALUES (?, ?, ?, ?, ?, ?)");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(timestamp);
    query.addBindValue(direction);
    query.addBindValue(message);
    query.addBindValue(isRead);
    return query.exec();
}

bool SqliteOperator::deleteChatRecord(int patientId, int doctorId, const QString &timestamp)
{
    QSqlQuery query(this->Db);
    query.prepare("DELETE FROM ChatRecord WHERE patientId = ? AND doctorId = ? AND timestamp = ?");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(timestamp);
    return query.exec();
}

bool SqliteOperator::updateChatRecord(int patientId, int doctorId, const QString &timestamp, const QString &message, bool isRead)
{
    QSqlQuery query(this->Db);
    query.prepare("UPDATE ChatRecord SET message = ?, isRead = ? WHERE patientId = ? AND doctorId = ? AND timestamp = ?");
    query.addBindValue(message);
    query.addBindValue(isRead);
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(timestamp);
    return query.exec();
}
bool SqliteOperator::insertMedicine(const QString &medicineName, double medicinePrice, int medicineStock, const QString &manufacturer, const QString &batchNumber)
{
    QSqlQuery query(this->Db);
    // 检查是否已有相同药品
    query.prepare("SELECT COUNT(*) FROM Medicine WHERE medicineName = ?");
    query.addBindValue(medicineName);

    if (!query.exec() || !query.next() || query.value(0).toInt() > 0) {
        qDebug() << "Medicine already exists or query failed";
        return false;
    }

    //insert
    query.prepare("INSERT INTO Medicine (medicineName, medicinePrice, medicineStock, manufacturer, batchNumber) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(medicineName);
    query.addBindValue(medicinePrice);
    query.addBindValue(medicineStock);
    query.addBindValue(manufacturer);
    query.addBindValue(batchNumber);
    return query.exec();
}

bool SqliteOperator::deleteMedicine(int medicineId)
{
    QSqlQuery query(this->Db);
    query.prepare("DELETE FROM Medicine WHERE medicineId = ?");
    query.addBindValue(medicineId);
    return query.exec();
}

bool SqliteOperator::updateMedicine(int medicineId, const QString &medicineName, double medicinePrice, int medicineStock, const QString &manufacturer, const QString &batchNumber)
{
    QSqlQuery query(this->Db);
    query.prepare("UPDATE Medicine SET medicineName = ?, medicinePrice = ?, medicineStock = ?, manufacturer = ?, batchNumber = ? WHERE medicineId = ?");
    query.addBindValue(medicineName);
    query.addBindValue(medicinePrice);
    query.addBindValue(medicineStock);
    query.addBindValue(manufacturer);
    query.addBindValue(batchNumber);
    query.addBindValue(medicineId);
    return query.exec();
}


