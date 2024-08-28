#include "h/EditRecipeAndPaymentOrder.h"
#include "ui_EditRecipeAndPaymentOrder.h"
#include "h/Doctor.h"
#include "h/usernow.h"
#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>
#include <net/ClientSocket.h>
EditRecipeAndPaymentOrder::EditRecipeAndPaymentOrder(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::EditRecipeAndPaymentOrder)
{
    ui->setupUi(this);
    connect(ui->action_2, &QAction::triggered, this,&EditRecipeAndPaymentOrder::insertRecipe);
    connect(&ClientSocket::getInstance(),SIGNAL(prescription_callback(NetUtils::Prescription)),this,SLOT(setPrescription_slot(NetUtils::Prescription)));
    //ClientSocket::getInstance().getPrescriptionsByPatient();
}

EditRecipeAndPaymentOrder::~EditRecipeAndPaymentOrder()
{
    delete ui;
}

void EditRecipeAndPaymentOrder::setPrescription_slot(NetUtils::Prescription data){
    /*// 1. 插入一行
    int newRow = ui->tableWidget->rowCount(); // 获取当前行数
    ui->tableWidget->insertRow(newRow); // 在末尾插入新行
    ui->tableWidget->setVerticalHeaderItem(newRow, new QTableWidgetItem("患者"+QString::number(newRow+1)));
    // 3. 插入内容到指定单元格
    ui->tableWidget->setItem(newRow, 0, new QTableWidgetItem());// 将信息插入到新行的第一列
    ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(data.count));
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(data.advice));
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(data.));
    idToLine.insert(data.patientId,newRow);
    ClientSocket::getInstance().getPatientById(data.patientId);*/
}

void EditRecipeAndPaymentOrder::on_pushButton_clicked()
{

}

void EditRecipeAndPaymentOrder::insertRecipe(){
    int newRow = ui->tableWidget->rowCount(); // 获取当前行数
    ui->tableWidget->insertRow(newRow); // 在末尾插入新行
    ui->tableWidget->setVerticalHeaderItem(newRow, new QTableWidgetItem("药品"+QString::number(newRow+1)));

}

void EditRecipeAndPaymentOrder::on_pushButton_2_clicked()
{
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}

void EditRecipeAndPaymentOrder::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

