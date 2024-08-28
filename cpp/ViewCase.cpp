#include "h/ViewCase.h"
#include "ui_ViewCase.h"
#include <h/Patient.h>
#include "h/usernow.h"
#include "net/ClientSocket.h"
int ii=0,j2=0;
QList<QString> doctorname;
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
    ii=0;
    this->close();
    auto patient= new Patient;
    patient->show();
}
void ViewCase::setMedicalRecord_slot(NetUtils::MedicalRecord record)
{

    //int rowCount = ui->tableWidget->rowCount();
   // ui->tableWidget->
            qDebug()<<"dsb"<<ii;
    //ui->tableWidget->item(0,0)->setText(record.);
    ClientSocket::getInstance().getDoctorDataById(record.doctorId);


    QTableWidgetItem *newItem=new QTableWidgetItem(record.diagnosis);
    ui->tableWidget->setItem(ii,2,newItem);
    newItem=new QTableWidgetItem(record.advice);
    ui->tableWidget->setItem(ii,3,newItem);
    newItem=new QTableWidgetItem(record.date);
    ui->tableWidget->setItem(ii,4,newItem);
    ii++;
}
void ViewCase::setdoctor_slot(NetUtils::DoctorData data){
    doctorname.push_back(data.name);
    qDebug()<<data.name;
    QTableWidgetItem *newItem = new QTableWidgetItem(doctorname[j2]);
    ui->tableWidget->setItem(j2,1,newItem);
    j2++;
}
