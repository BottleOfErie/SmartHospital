#include "h/ViewDoctorInformations.h"
#include "ui_ViewDoctorInformations.h"
#include <h/Patient.h>
#include "h/usernow.h"
ViewDoctorInformations::ViewDoctorInformations(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewDoctorInformations)
{
    ui->setupUi(this);
}

ViewDoctorInformations::~ViewDoctorInformations()
{
    delete ui;
}

void ViewDoctorInformations::on_pushButton_2_clicked()
{
    this->close();
    auto patientWindow=new Patient;
    patientWindow->show();
}
void ViewDoctorInformations::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
