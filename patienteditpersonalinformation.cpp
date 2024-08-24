#include "patienteditpersonalinformation.h"
#include "ui_patienteditpersonalinformation.h"

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
