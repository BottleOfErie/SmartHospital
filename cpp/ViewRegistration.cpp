#include "h/ViewRegistration.h"
#include "ui_ViewRegistration.h"

#include <h/Doctor.h>
#include <h/usernow.h>

#include <net/ClientSocket.h>

ViewRegistration::ViewRegistration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewRegistration)
{
    ui->setupUi(this);
    connect(&ClientSocket::getInstance(),SIGNAL(appointment_callback(NetUtils::Appointment)),this,SLOT(setRegistrationData_slot(NetUtils::Appointment)));
    ClientSocket::getInstance().getAppointmentsByDoctor(usernow::getId().toLong());
    connect(&ClientSocket::getInstance(),SIGNAL(patient_callback(NetUtils::PatientData)),this,SLOT(setPatientName_slot(NetUtils::PatientData)));

}

ViewRegistration::~ViewRegistration()
{
    delete ui;
}



void ViewRegistration::on_pushButton_clicked()
{
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}
void ViewRegistration::setRegistrationData_slot(NetUtils::Appointment data){
    // 1. 插入一行
    int newRow = ui->tableWidget->rowCount(); // 获取当前行数
    ui->tableWidget->insertRow(newRow); // 在末尾插入新行
    ui->tableWidget->setVerticalHeaderItem(newRow, new QTableWidgetItem("患者"+QString::number(newRow)));
    // 3. 插入内容到指定单元格
    ui->tableWidget->setItem(newRow, 0, new QTableWidgetItem(data.patientId));// 将信息插入到新行的第一列
    ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(data.doctorId));
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(data.time));
    ui->tableWidget->setItem(newRow, 3, new QTableWidgetItem(data.state));
    idToLine.insert(data.patientId,newRow);
    ClientSocket::getInstance().getPatientById(data.patientId);
}

void ViewRegistration::setPatientName_slot(NetUtils::PatientData data){
    ui->tableWidget->setVerticalHeaderItem(idToLine.find(data.id).value(),new QTableWidgetItem(data.name));
}
