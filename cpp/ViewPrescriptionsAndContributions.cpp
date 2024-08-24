#include "h/ViewPrescriptionsAndContributions.h"
#include "ui_ViewPrescriptionsAndContributions.h"
#include <h/Patient.h>

ViewPrescriptionsAndContributions::ViewPrescriptionsAndContributions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewPrescriptionsAndContributions)
{
    ui->setupUi(this);
}

ViewPrescriptionsAndContributions::~ViewPrescriptionsAndContributions()
{
    delete ui;
}

void ViewPrescriptionsAndContributions::on_pushButton_clicked()
{
    this->close();
    auto patientWindow=new Patient;
    patientWindow->show();
}
