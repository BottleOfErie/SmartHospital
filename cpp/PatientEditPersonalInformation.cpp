#include "h/PatientEditPersonalInformation.h"
#include "ui_PatientEditPersonalInformation.h"
#include <h/Patient.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "h/usernow.h"
PatientEditPersonalInformation::PatientEditPersonalInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientEditPersonalInformation)
{
    ui->setupUi(this);
}

PatientEditPersonalInformation::~PatientEditPersonalInformation()
{
    delete ui;
}

void PatientEditPersonalInformation::on_pushButton_3_clicked()
{
    this->close();
    Patient *patientWindow=new Patient();
    patientWindow->show();
}

void PatientEditPersonalInformation::on_pushButton_2_clicked()
{
}
