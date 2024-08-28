#include "h/ViewPrescriptionsAndContributions.h"
#include "ui_ViewPrescriptionsAndContributions.h"
#include <h/Patient.h>
#include "h/usernow.h"
#include "net/ClientSocket.h"
int cnt;
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
    int newRow = ui->tableWidget->rowCount(); // 获取当前行数
    ui->tableWidget->insertRow(newRow); // 在末尾插入新行
    ui->tableWidget->setVerticalHeaderItem(newRow, new QTableWidgetItem("缴费单"+QString::number(newRow+1)));
    ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(QString::number(data.count)));
    cnt=data.count;
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(data.advice));
    ClientSocket::getInstance().getMedicineById(data.medicineId);
}
void ViewPrescriptionsAndContributions::setmedicine_slot(NetUtils::Medicine data){
    int row=ui->tableWidget->rowCount()-1;
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(data.name));
    ui->tableWidget->setItem(row,3,new QTableWidgetItem(QString::number(data.price*cnt)));
}
