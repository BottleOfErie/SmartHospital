#include "h/ViewPrescriptionsAndContributions.h"
#include "ui_ViewPrescriptionsAndContributions.h"
#include <h/Patient.h>
#include "h/usernow.h"
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
void ViewPrescriptionsAndContributions::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
