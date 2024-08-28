#include "h/Doctor.h"
#include "ui_Doctor.h"
#include <h/mainwindow.h>
#include <h/Registration.h>
#include <h/EditRecipeAndPaymentOrder.h>
#include <h/EditMedicalRecord.h>
#include <h/DoctorEditPersonalInformation.h>
#include <h/Doctor_patientCommunicationPlatform.h>
#include <h/qnchatmessage.h>
#include <QDebug>
#include "h/usernow.h"
#include "h/ViewRegistration.h"
Doctor::Doctor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doctor)
{
    ui->setupUi(this);
}

Doctor::~Doctor()
{
    delete ui;
}
void Doctor::on_pushButton_6_clicked()
{
    this->close();
    auto mainwindow = new MainWindow;
    mainwindow->show();
}
void Doctor::on_pushButton_4_clicked()
{
    this->close();
    auto registrationWindow = new ViewRegistration;
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
    auto doctor_patientCommunicationPlatform=new Doctor_patientCommunicationPlatform("doctor");
    doctor_patientCommunicationPlatform->show();
}
void Doctor::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
