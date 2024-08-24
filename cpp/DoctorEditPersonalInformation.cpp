#include "h/DoctorEditPersonalInformation.h"
#include "ui_DoctorEditPersonalInformation.h"

DoctorEditPersonalInformation::DoctorEditPersonalInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorEditPersonalInformation)
{
    ui->setupUi(this);
}

DoctorEditPersonalInformation::~DoctorEditPersonalInformation()
{
    delete ui;
}
