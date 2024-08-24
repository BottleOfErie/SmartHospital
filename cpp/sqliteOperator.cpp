#include "sqliteOperator.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QMessageBox>
#include <string>
#include <QSqlTableModel>

SqliteOperator::SqliteOperator() {
    this->connect("General.db");
    createAccountTable();
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


bool SqliteOperator::createAccountTable()
{
//        qDebug() << this->accountDb.open();
        // 用于执行sql语句的对象
        QSqlQuery query(this->Db);
        query.prepare("CREATE TABLE Account("
                      "userName TEXT PRIMARY KEY,"
                      "password CHARACTER(20) )");

        if (!query.exec()) {
//            QMessageBox::critical(0,
//            QObject::tr("Database Error"),
//            query.lastError().text());
            return false;
        } else {
            qDebug() << "Table created!";
            return true;
        }

    Db.close();
    return true;
}

//I think QString should be ok. But it needed to be tested
bool SqliteOperator::Login(QString userName, QString Password, QString tableName) {
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

