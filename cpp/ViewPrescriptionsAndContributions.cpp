#include "h/ViewPrescriptionsAndContributions.h"
#include "ui_ViewPrescriptionsAndContributions.h"
#include <h/Patient.h>
#include "h/usernow.h"
#include "net/ClientSocket.h"
int i=0,jj=0;
QList<float>price;
QList<QString>medicine_name;
ViewPrescriptionsAndContributions::ViewPrescriptionsAndContributions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewPrescriptionsAndContributions)
{
    ui->setupUi(this);
    connect(&ClientSocket::getInstance(),SIGNAL(prescription_callback(NetUtils::Prescription)),this,SLOT(setPrescription_slot(NetUtils::Prescription)));
    ClientSocket::getInstance().getPrescriptionsByPatient(usernow::getId().toLong());
    connect(&ClientSocket::getInstance(),SIGNAL(medicine_callback(NetUtils::Medicine)),this,SLOT(setmedicine_slot(NetUtils::Medicine)));
}

ViewPrescriptionsAndContributions::~ViewPrescriptionsAndContributions()
{
    delete ui;
}

void ViewPrescriptionsAndContributions::on_pushButton_clicked()
{
    i=0;jj=0;
    disconnect(&ClientSocket::getInstance(),SIGNAL(prescription_callback(NetUtils::Prescription)),this,SLOT(setPrescription_slot(NetUtils::Prescription)));
    disconnect(&ClientSocket::getInstance(),SIGNAL(medicine_callback(NetUtils::Medicine)),this,SLOT(setmedicine_slot(NetUtils::Medicine)));
    this->close();
    auto patientWindow=new Patient;
    patientWindow->show();
}
void ViewPrescriptionsAndContributions::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
void ViewPrescriptionsAndContributions::setPrescription_slot(NetUtils::Prescription data)
{

    //int rowCount = ui->tableWidget->rowCount();
   // ui->tableWidget->
            qDebug()<<"dsb"<<i;
    //ui->tableWidget->item(0,0)->setText(record.);
    QTableWidgetItem *newItem ;
    newItem=new QTableWidgetItem(data.count);
    ui->tableWidget->setItem(i,2,newItem);
    newItem=new QTableWidgetItem(data.advice);
    ui->tableWidget->setItem(i,3,newItem);
    /*newItem=new QTableWidgetItem(data.date);
    ui->tableWidget->setItem(i,4,newItem);*/
    i++;
}
void ViewPrescriptionsAndContributions::setmedicine_slot(NetUtils::Medicine data){
    medicine_name[jj]=data.name;
    price[jj]=data.price;
    QTableWidgetItem *newItem = new QTableWidgetItem(data.name);
    ui->tableWidget->setItem(jj,1,newItem);
    newItem = new QTableWidgetItem(data.price);
    ui->tableWidget->setItem(jj,4,newItem);
    jj++;
}
