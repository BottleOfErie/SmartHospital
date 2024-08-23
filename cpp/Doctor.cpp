#include "h/Doctor.h"
#include "ui_Doctor.h"

Doctor::Doctor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doctor)
{
    ui->setupUi(this);
}

Doctor::~Doctor()
{
    delete ui;
}
