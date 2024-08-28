#ifndef DOCTOR_PATIENTCOMMUNICATIONPLATFORM_H
#define DOCTOR_PATIENTCOMMUNICATIONPLATFORM_H

#include "qnchatmessage.h"

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
    QString identity;
    ~Doctor_patientCommunicationPlatform();
    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
        void dealMessageTime(QString curMsgTime);
    protected:
        void resizeEvent(QResizeEvent *event);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Doctor_patientCommunicationPlatform *ui;
};

#endif // DOCTOR_PATIENTCOMMUNICATIONPLATFORM_H
