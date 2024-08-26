#include "h/Doctor.h"
#include "ui_Doctor.h"
#include <h/mainwindow.h>
#include <h/Registration.h>
#include <h/EditRecipeAndPaymentOrder.h>
#include <h/EditMedicalRecord.h>
#include <h/DoctorEditPersonalInformation.h>
#include <h/Doctor_patientCommunicationPlatform.h>
#include <QDebug>
#include "h/usernow.h"
Doctor::Doctor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doctor)
{
    ui->setupUi(this);
    qDebug() << usernow::getId();
    //connect(ui->pushButton_6, &QPushButton::clicked, this, &Doctor::on_pushButton6_clicked);
    //connect(ui->pushButton_4, &QPushButton::clicked, this, &Doctor::on_pushButton4_clicked);
    //connect(ui->pushButton_2, &QPushButton::clicked, this, &Doctor::on_pushButton2_clicked);
    //connect(ui->pushButton_3, &QPushButton::clicked, this, &Doctor::on_pushButton3_clicked);
}

Doctor::~Doctor()
{
    delete ui;
}
void Doctor::on_pushButton_6_clicked()
{
    //qDebug("666");
    this->close();
    auto mainwindow = new MainWindow;
    mainwindow->show();
}
void Doctor::on_pushButton_4_clicked()
{
    //qDebug("1");
    this->close();
    auto registrationWindow = new Registration;
    registrationWindow->show();
}
void Doctor::on_pushButton_2_clicked()
{
    this->close();
    auto editMedicalRecord = new EditMedicalRecord;
    editMedicalRecord->show();
}
void Doctor::on_pushButton_3_clicked()
{
    this->close();
    auto editRecipeAndPaymentOrder = new EditRecipeAndPaymentOrder;
    editRecipeAndPaymentOrder->show();
}
void Doctor::on_pushButton_clicked()
{
    this->close();
    auto doctoreditpersonalinformation = new DoctorEditPersonalInformation;
    doctoreditpersonalinformation->show();
}


void Doctor::on_pushButton_5_clicked()
{
    this->close();
    auto doctor_patientCommunicationPlatform=new Doctor_patientCommunicationPlatform;
    doctor_patientCommunicationPlatform->identity="doctor";
    doctor_patientCommunicationPlatform->show();
}
