#include "h/ViewCase.h"
#include "ui_ViewCase.h"
#include <h/Patient.h>
#include "h/usernow.h"
#include "net/ClientSocket.h"

ViewCase::ViewCase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewCase)
{
    ui->setupUi(this);
    connect(&ClientSocket::getInstance(),SIGNAL(doctor_callback(NetUtils::MedicalRecord)),this,SLOT(setMedicalRecord_slot(NetUtils::MedicalRecord)));
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
    this->close();
    auto patient= new Patient;
    patient->show();
}
void ViewCase::setMedicalRecord_slot(NetUtils::MedicalRecord record)
{

    //ui->tableWidget->item(0,0)->setText(record.);
    ui->tableWidget->item(0,1)->setText(QString::fromStdString(std::to_string(record.doctorId)));
    ui->tableWidget->item(0,2)->setText(record.diagnosis);
    ui->tableWidget->item(0,3)->setText(record.advice);
    ui->tableWidget->item(0,4)->setText(record.date);
}
