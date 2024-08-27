#include "h/HealthAssesment.h"
#include "ui_HealthAssesment.h"
#include <h/Patient.h>
#include "h/usernow.h"
#include <QPainter>
#include <QStyleOption>
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
void HealthAssesment::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
