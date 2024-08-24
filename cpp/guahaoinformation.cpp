#include "h/guahaoinformation.h"
#include "ui_guahaoinformation.h"
#include <h/Doctor.h>
GuaHaoInformation::GuaHaoInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GuaHaoInformation)
{
    ui->setupUi(this);
    //connect(ui->pushButton, &QPushButton::clicked, this, &GuaHaoInformation::on_pushButton_clicked);
    //connect(ui->pushButton_2, &QPushButton::clicked, this, &GuaHaoInformation::on_pushButton2_clicked);
}

GuaHaoInformation::~GuaHaoInformation()
{
    delete ui;
}
void GuaHaoInformation::on_pushButton_clicked()
{
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}
void GuaHaoInformation::on_pushButton_2_clicked()
{
    //?
}
