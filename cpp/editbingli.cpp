#include "h/editbingli.h"
#include "ui_editbingli.h"
#include <h/Doctor.h>
Editbingli::Editbingli(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Editbingli)
{
    ui->setupUi(this);
    //connect(ui->pushButton, &QPushButton::clicked, this, &Editbingli::on_pushButton_clicked);
   // connect(ui->pushButton_2, &QPushButton::clicked, this, &Editbingli::on_pushButton2_clicked);
}

Editbingli::~Editbingli()
{
    delete ui;
}
void Editbingli::on_pushButton_clicked()
{
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}
void Editbingli::on_pushButton_2_clicked()
{
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}
