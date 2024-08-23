#include "h/Doctor.h"
#include "ui_Doctor.h"
#include <h/mainwindow.h>
#include <h/guahaoinformation.h>
#include <h/chufanghebingli.h>
#include <h/editbingli.h>
#include <h/DoctorEditPersonalInformation.h>
Doctor::Doctor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doctor)
{
    ui->setupUi(this);
    //connect(ui->pushButton_6, &QPushButton::clicked, this, &Doctor::on_pushButton6_clicked);
    //connect(ui->pushButton_4, &QPushButton::clicked, this, &Doctor::on_pushButton4_clicked);
    //connect(ui->pushButton_2, &QPushButton::clicked, this, &Doctor::on_pushButton2_clicked);
    //connect(ui->pushButton_3, &QPushButton::clicked, this, &Doctor::on_pushButton3_clicked);
}

Doctor::~Doctor()
{
    delete ui;
}
void Doctor::on_pushButton_6_clicked()
{
    //qDebug("666");
    this->close();
    auto mainwindow = new MainWindow;
    mainwindow->show();
}
void Doctor::on_pushButton_4_clicked()
{
    //qDebug("1");
    this->close();
    auto guahaoInformation = new GuaHaoInformation;
    guahaoInformation->show();
}
void Doctor::on_pushButton_2_clicked()
{
    this->close();
    auto editbingli = new Editbingli;
    editbingli->show();
}
void Doctor::on_pushButton_3_clicked()
{
    this->close();
    auto chufanghebingli = new Chufanghebingli;
    chufanghebingli->show();
}
void Doctor::on_pushButton_clicked()
{
    this->close();
    auto doctoreditpersonalinformation = new DoctorEditPersonalInformation;
    doctoreditpersonalinformation->show();
}

