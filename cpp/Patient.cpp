#include "h/Patient.h"
#include "ui_Patient.h"
#include <h/ViewCase.h>
#include <h/ViewPrescriptionsAndContributions.h>
#include<h/ViewDoctorInformations.h>
#include<h/HealthAssesment.h>
#include<h/Doctor_patientCommunicationPlatform.h>
#include<h/mainwindow.h>
#include "h/usernow.h"
Patient::Patient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Patient)
{
    ui->setupUi(this);
}

Patient::~Patient()
{
    delete ui;
}

void Patient::on_pushButton_4_clicked()
{
    this->close();
}

void Patient::on_pushButton_2_clicked()
{
    this->close();
    auto viewcase=new ViewCase;
    viewcase->show();
}

void Patient::on_pushButton_7_clicked()
{
    this->close();
    auto viewPrescriptionsAndContributions=new ViewPrescriptionsAndContributions;
    viewPrescriptionsAndContributions->show();
}

void Patient::on_pushButton_3_clicked()
{
    this->close();
    auto viewDoctorInformations=new ViewDoctorInformations;
    viewDoctorInformations->show();
}

void Patient::on_pushButton_8_clicked()
{
    this->close();
    auto healthAssesment=new HealthAssesment;
    healthAssesment->show();
}

void Patient::on_pushButton_5_clicked()
{
    this->close();
    auto doctor_patientCommunicationPlatform=new Doctor_patientCommunicationPlatform;
    doctor_patientCommunicationPlatform->identity="patient";
    doctor_patientCommunicationPlatform->show();
}

void Patient::on_pushButton_6_clicked()
{
    this->close();
    auto mainwindow=new MainWindow;
    mainwindow->show();
}

