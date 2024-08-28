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
    if(data.state)
        return;
    // 1. 插入一行
    int newRow = ui->tableWidget->rowCount(); // 获取当前行数
    ui->tableWidget->insertRow(newRow); // 在末尾插入新行
    ui->tableWidget->setVerticalHeaderItem(newRow, new QTableWidgetItem("患者"+QString::number(newRow+1)));
    // 3. 插入内容到指定单元格
    ClientSocket::getInstance().getPatientById(data.patientId);// 将信息插入到新行的第一列
    ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(data.time));
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem("未就诊"));
    idToLine.insert(data.patientId,newRow);
    ClientSocket::getInstance().getPatientById(data.patientId);
    for (int col = 0; col < ui->tableWidget->columnCount(); ++col) {
        QTableWidgetItem *item = ui->tableWidget->item(newRow, col);
        if (item) {
            item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }
}

void ViewRegistration::setPatientName_slot(NetUtils::PatientData data){
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, new QTableWidgetItem(data.name));
}
void ViewRegistration::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
