#include "h/ViewCase.h"
#include "ui_ViewCase.h"
#include <h/Patient.h>
#include "h/usernow.h"
#include "net/ClientSocket.h"
int i=0;
ViewCase::ViewCase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewCase)
{
    ui->setupUi(this);
    connect(&ClientSocket::getInstance(),SIGNAL(medicalRecord_callback(NetUtils::MedicalRecord)),this,SLOT(setMedicalRecord_slot(NetUtils::MedicalRecord)));
    ClientSocket::getInstance().getMedicalRecordsByPatient(usernow::getId().toLong());
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
    i=0;
    this->close();
    auto patient= new Patient;
    patient->show();
}
void ViewCase::setMedicalRecord_slot(NetUtils::MedicalRecord record)
{

    //int rowCount = ui->tableWidget->rowCount();
   // ui->tableWidget->
            qDebug()<<"dsb"<<i;
    //ui->tableWidget->item(0,0)->setText(record.);
    QTableWidgetItem *newItem = new QTableWidgetItem(QString::fromStdString(std::to_string(record.doctorId)));
    ui->tableWidget->setItem(i,1,newItem);
    newItem=new QTableWidgetItem(record.diagnosis);
    ui->tableWidget->setItem(i,2,newItem);
    newItem=new QTableWidgetItem(record.advice);
    ui->tableWidget->setItem(i,3,newItem);
    newItem=new QTableWidgetItem(record.date);
    ui->tableWidget->setItem(i,4,newItem);
    i++;
}
