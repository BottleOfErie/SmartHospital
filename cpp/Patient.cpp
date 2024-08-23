#include "h/Patient.h"
#include "ui_Patient.h"

Patient::Patient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Patient)
{
    ui->setupUi(this);
}

Patient::~Patient()
{
    delete ui;
}
