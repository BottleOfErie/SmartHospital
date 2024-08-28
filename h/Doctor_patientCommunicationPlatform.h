#ifndef DOCTOR_PATIENTCOMMUNICATIONPLATFORM_H
#define DOCTOR_PATIENTCOMMUNICATIONPLATFORM_H

#include "qnchatmessage.h"

#include "net/NetUtils.h"
#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class Doctor_patientCommunicationPlatform;
}

class Doctor_patientCommunicationPlatform : public QWidget
{
    Q_OBJECT

public:
    explicit Doctor_patientCommunicationPlatform(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    QString identity;
    long waitTime;
    ~Doctor_patientCommunicationPlatform();
    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);
protected:
    void resizeEvent(QResizeEvent *event);
private:
    QTimer* timer;
    QList<NetUtils::Message> msgs;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void timerOutGetMsg_slot();
    void getMessage_slot(NetUtils::Message);

private:
    Ui::Doctor_patientCommunicationPlatform *ui;
};

#endif // DOCTOR_PATIENTCOMMUNICATIONPLATFORM_H
