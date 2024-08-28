#include "h/ViewDoctorInformations.h"
#include "ui_ViewDoctorInformations.h"
#include <h/Patient.h>
#include "h/usernow.h"

ViewDoctorInformations::ViewDoctorInformations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewDoctorInformations)
{
    ui->setupUi(this);
    connect(&ClientSocket::getInstance(),SIGNAL(doctor_callback(NetUtils::DoctorData)),
            this,SLOT(loadDoctors_slot(NetUtils::DoctorData)));

    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);
    ui->lineEdit_6->setReadOnly(true);
}

ViewDoctorInformations::~ViewDoctorInformations()
{
    delete ui;
}

void ViewDoctorInformations::on_pushButton_clicked()
{
    QString doctorName = ui->comboBox_2->currentText();
    if (doctorName != DOCTOR_PLACEHOLDER) {
        NetUtils::DoctorData doctor = doctors[doctorName];
        ui->lineEdit->setText(doctorName);
        ui->lineEdit_2->setText(doctor.jobTitle);
        ui->lineEdit_4->setText(doctor.section);
        ui->lineEdit_5->setText(doctor.organization);
        ui->lineEdit_6->setText(doctor.phoneNumber);
    }
}

void ViewDoctorInformations::on_pushButton_2_clicked()
{
    this->close();
    auto patientWindow=new Patient;
    patientWindow->show();
}

void ViewDoctorInformations::loadDoctors_slot(NetUtils::DoctorData doctor)
{
    doctors.clear();
    doctors[doctor.name] = doctor;
    ui->comboBox_2->addItem(doctor.name);
}

void ViewDoctorInformations::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ViewDoctorInformations::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem(DOCTOR_PLACEHOLDER);
    if (arg1 != SECTION_PLACEHOLDER) {
        ClientSocket::getInstance().getDoctorsBySection(arg1);
    }
}
