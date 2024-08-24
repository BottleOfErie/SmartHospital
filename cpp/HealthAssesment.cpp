#include "h/HealthAssesment.h"
#include "ui_HealthAssesment.h"
#include <h/Patient.h>

HealthAssesment::HealthAssesment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HealthAssesment)
{
    ui->setupUi(this);
}

HealthAssesment::~HealthAssesment()
{
    delete ui;
}

void HealthAssesment::on_pushButton_3_clicked()
{
    this->close();
    auto patientWindow=new Patient;
    patientWindow->show();
}
