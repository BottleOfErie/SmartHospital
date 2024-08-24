#include "h/DoctorEditPersonalInformation.h"
#include "ui_DoctorEditPersonalInformation.h"
#include <h/Doctor.h>
DoctorEditPersonalInformation::DoctorEditPersonalInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorEditPersonalInformation)
{
    ui->setupUi(this);
}

DoctorEditPersonalInformation::~DoctorEditPersonalInformation()
{
    delete ui;
}
void DoctorEditPersonalInformation::on_pushButton_clicked()
{
    //qDebug("666");
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}
void DoctorEditPersonalInformation::on_pushButton_2_clicked()
{
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}
void DoctorEditPersonalInformation::on_pushButton_3_clicked()
{
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}
