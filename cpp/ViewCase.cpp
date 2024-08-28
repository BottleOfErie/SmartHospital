#include "h/ViewCase.h"
#include "ui_ViewCase.h"
#include <h/Patient.h>
#include "h/usernow.h"
#include "net/ClientSocket.h"
int ii=0,j2=0;
QList<QString> doctorname;
QList<QString> keshi;
ViewCase::ViewCase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewCase)
{
    ui->setupUi(this);
    connect(&ClientSocket::getInstance(),SIGNAL(medicalRecord_callback(NetUtils::MedicalRecord)),this,SLOT(setMedicalRecord_slot(NetUtils::MedicalRecord)));
    ClientSocket::getInstance().getMedicalRecordsByPatient(usernow::getId().toLong());
    connect(&ClientSocket::getInstance(),SIGNAL(doctor_callback(NetUtils::DoctorData)),this,SLOT(setdoctor_slot(NetUtils::DoctorData)));
}

ViewCase::~ViewCase()
{
    delete ui;
}
void ViewCase::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ViewCase::on_pushButton_clicked()
{
    ii=0;j2=0;
    disconnect(&ClientSocket::getInstance(),SIGNAL(medicalRecord_callback(NetUtils::MedicalRecord)),this,SLOT(setMedicalRecord_slot(NetUtils::MedicalRecord)));
    disconnect(&ClientSocket::getInstance(),SIGNAL(doctor_callback(NetUtils::DoctorData)),this,SLOT(setdoctor_slot(NetUtils::DoctorData)));
    this->close();
    auto patient= new Patient;
    patient->show();
}
void ViewCase::setMedicalRecord_slot(NetUtils::MedicalRecord record)
{
    int newRow = ui->tableWidget->rowCount(); // 获取当前行数
    ui->tableWidget->insertRow(newRow); // 在末尾插入新行
    ui->tableWidget->setVerticalHeaderItem(newRow, new QTableWidgetItem("病历"+QString::number(newRow+1)));
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(record.diagnosis));
    ui->tableWidget->setItem(newRow, 3, new QTableWidgetItem(record.advice));
    ui->tableWidget->setItem(newRow, 4, new QTableWidgetItem(record.date));
    ClientSocket::getInstance().getDoctorDataById(record.doctorId);
}
void ViewCase::setdoctor_slot(NetUtils::DoctorData data){
    int row=ui->tableWidget->rowCount()-1;
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(data.section));
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(data.name));
}
