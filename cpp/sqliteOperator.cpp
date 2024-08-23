#include "sqliteOperator.h"
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QMessageBox>
#include <string>
#include <QSqlTableModel>

SqliteOperator::SqliteOperator() {
    this->createTable();
}

bool SqliteOperator::connect(const QString &dbName) {
    this->accountDb = QSqlDatabase::addDatabase("QSQLITE", QString("%1").arg(dbName));
    this->accountDb.setDatabaseName(dbName);
    if (!this->accountDb.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"), this->accountDb.lastError().text());
        return false;
    }
    return true;
}


bool SqliteOperator::createTable()
{
    if (connect("Account.db")) {
//        qDebug() << this->accountDb.open();
        // 用于执行sql语句的对象
        QSqlQuery query(this->accountDb);
        if (!query.exec("CREATE TABLE Account("
        "userName TEXT PRIMARY KEY,"
        "password CHARACTER(20) )")) {
//            QMessageBox::critical(0,
//            QObject::tr("Database Error"),
//            query.lastError().text());
            return false;
        } else {
            qDebug() << "Table created!";
            return true;
        }
    }
    accountDb.close();
    return true;
}

//I think QVariant should be ok. But it needed to be tested
bool SqliteOperator::singleInsertData(QVariant userName, QVariant Password) {
    accountDb.open();
    QSqlQuery query2(this->accountDb);
    query2.prepare("SELECT password FROM Account WHERE username = :username");
    query2.bindValue(":username", userName);
    if (!query2.exec()) {
        qDebug() << "Query failed:" << query2.lastError();
        return false;
    }
    if (query2.next()) {
        return false;
    }

    QSqlQuery query(this->accountDb);
    query.prepare("INSERT INTO Account VALUES(?, ?)");
    QVariantList username;
    username << userName;
    query.addBindValue(username);
    QVariantList password;
    password << Password;
    query.addBindValue(password);

    if (!query.execBatch()) {
        QMessageBox::critical(0, QObject::tr("Database Error"),
        query.lastError().text());
    }

    accountDb.close();
    return true;
}

bool SqliteOperator::validateLogin(QString username, QString InputPassword) {
    accountDb.open();
    QSqlQuery query(this->accountDb);
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
    accountDb.close();
}

