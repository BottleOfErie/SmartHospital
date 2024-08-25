#include "h/Doctor_patientCommunicationPlatform.h"
#include "ui_Doctor_patientCommunicationPlatform.h"
#include <h/Doctor.h>
#include <h/Patient.h>
#include "h/usernow.h"
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
