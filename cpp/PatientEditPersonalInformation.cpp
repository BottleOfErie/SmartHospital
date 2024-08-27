#include "h/PatientEditPersonalInformation.h"
#include "ui_PatientEditPersonalInformation.h"
#include <h/Patient.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "h/usernow.h"
PatientEditPersonalInformation::PatientEditPersonalInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientEditPersonalInformation)
{
    ui->setupUi(this);
}

PatientEditPersonalInformation::~PatientEditPersonalInformation()
{
    delete ui;
}

void PatientEditPersonalInformation::on_pushButton_3_clicked()
{
    this->close();
    Patient *patientWindow=new Patient();
    patientWindow->show();
}

void PatientEditPersonalInformation::on_pushButton_2_clicked()
{
}
void PatientEditPersonalInformation::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
