#include "h/Registration.h"
#include "ui_Registration.h"

#include <h/Patient.h>

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
}

void Registration::on_pushButton_2_clicked()
{
    this->close();
    Patient *patientWindow=new Patient();
    patientWindow->show();
}

void Registration::on_pushButton_clicked()
{

}
void Registration::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
