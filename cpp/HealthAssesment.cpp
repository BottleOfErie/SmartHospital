#include "h/HealthAssesment.h"
#include "ui_HealthAssesment.h"
#include <h/Patient.h>
#include "h/usernow.h"
#include <QPainter>
#include <QStyleOption>
#include "net/ClientSocket.h"
HealthAssesment::HealthAssesment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HealthAssesment)
{
    ui->setupUi(this);
    connect(&ClientSocket::getInstance(),SIGNAL(testResult_callback(NetUtils::TestResult)),this,SLOT(setTestResult_slot(NetUtils::TestResult)));
    ClientSocket::getInstance().getTestResultsByPatient(usernow::getId().toLong());
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
void HealthAssesment::setTestResult_slot(NetUtils::TestResult){

}
