#include "h/chufanghebingli.h"
#include "ui_chufanghebingli.h"
#include <h/Doctor.h>
Chufanghebingli::Chufanghebingli(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chufanghebingli)
{
    ui->setupUi(this);
    //connect(ui->pushButton, &QPushButton::clicked, this, &Chufanghebingli::on_pushButton_clicked);
   //connect(ui->pushButton_2, &QPushButton::clicked, this, &Chufanghebingli::on_pushButton2_clicked);
}

Chufanghebingli::~Chufanghebingli()
{
    delete ui;
}
void Chufanghebingli::on_pushButton_clicked()
{
    //qDebug("666");
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}
void Chufanghebingli::on_pushButton_2_clicked()
{
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}


