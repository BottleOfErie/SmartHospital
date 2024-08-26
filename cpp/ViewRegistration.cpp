#include "h/ViewRegistration.h"
#include "ui_ViewRegistration.h"

ViewRegistration::ViewRegistration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewRegistration)
{
    ui->setupUi(this);
}

ViewRegistration::~ViewRegistration()
{
    delete ui;
}
