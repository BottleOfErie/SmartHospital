#include "h/Doctor_patientCommunicationPlatform.h"
#include "ui_Doctor_patientCommunicationPlatform.h"
#include <h/Doctor.h>
#include <h/Doctor_patientCommunicationPlatform.h>
#include <h/Patient.h>
#include "h/usernow.h"
#include <QDateTime>
#include <QDebug>
Doctor_patientCommunicationPlatform::Doctor_patientCommunicationPlatform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doctor_patientCommunicationPlatform)
{
    ui->setupUi(this);
}

Doctor_patientCommunicationPlatform::~Doctor_patientCommunicationPlatform()
{
    delete ui;
}

void Doctor_patientCommunicationPlatform::on_pushButton_2_clicked()
{
    this->close();
    if(identity=="doctor"){
        auto doctor = new Doctor;
        doctor->show();
    }
    else{
        auto patient = new Patient;
        patient->show();
    }
}
void Doctor_patientCommunicationPlatform::on_pushButton_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳

    bool isSending = true; // 发送中

    qDebug()<<"addMessage" << msg << time << ui->listWidget->count();
    if(ui->listWidget->count()%2) {
        if(isSending) {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
        } else {
            bool isOver = true;
            for(int i = ui->listWidget->count() - 1; i > 0; i--) {
                QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if(messageW->text() == msg) {
                    isOver = false;
                    messageW->setTextSuccess();
                }
            }
            if(isOver) {
                dealMessageTime(time);

                QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
                QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
                dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
                messageW->setTextSuccess();
            }
        }
    } else {
        if(msg != "") {
            dealMessageTime(time);

            QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
            QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
            dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
        }
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void Doctor_patientCommunicationPlatform::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time,  QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(600);
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}

void Doctor_patientCommunicationPlatform::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);

        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

void Doctor_patientCommunicationPlatform::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);


    ui->textEdit->resize(this->width() - 20, ui->widget->height() - 20);
    ui->textEdit->move(10, 10);

    ui->pushButton->move(ui->textEdit->width()+ui->textEdit->x() - ui->pushButton->width() - 10,
                         ui->textEdit->height()+ui->textEdit->y() - ui->pushButton->height() - 10);


    for(int i = 0; i < ui->listWidget->count(); i++) {
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}
