#include "h/Doctor_patientCommunicationPlatform.h"
#include "ui_Doctor_patientCommunicationPlatform.h"
#include <h/Doctor.h>

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
    auto doctor = new Doctor;
    doctor->show();
}
