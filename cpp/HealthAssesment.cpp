#include "h/HealthAssesment.h"
#include "ui_HealthAssesment.h"
#include <h/Patient.h>
#include "h/usernow.h"
#include <QPainter>
#include <QMessageBox>
#include <QStyleOption>
#include "net/QwenClient.h"
#include "net/ClientSocket.h"
HealthAssesment::HealthAssesment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HealthAssesment)
{
    ui->setupUi(this);
    connect(&ClientSocket::getInstance(),SIGNAL(testResult_callback(NetUtils::TestResult)),this,SLOT(setTestResult_slot(NetUtils::TestResult)));
    ClientSocket::getInstance().getTestResultsByPatient(usernow::getId().toLong());
    connect(&QwenClient::getInstance(),SIGNAL(aiReply(QString)),this,SLOT(takeAiReply(QString)));
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
void HealthAssesment::setTestResult_slot(NetUtils::TestResult result){
    qDebug("date:%s",result.date.toStdString().data());

    this->result=result;
    ui->lineEdit->setText(QString::number(result.height));
    ui->lineEdit_2->setText(QString::number(result.weight));
    ui->lineEdit_3->setText(QString::number(result.vitalCapacity));
    ui->lineEdit_4->setText(QString::number(result.heartRate));
    ui->lineEdit_5->setText(QString::number(result.highBP));
    ui->lineEdit_7->setText(QString::number(result.lowBP));
    ui->lineEdit_8->setText(result.date);
}

void HealthAssesment::on_pushButton_4_clicked()
{
    QwenClient::getInstance().ask(QString("这是我的体检报告，他说我的身高为%1，体重为%2，心率为%3，血压高压为%4，血压低压%5，肺活量为%6。请你简短地分析我的身体健康状态。")
                    .arg(ui->lineEdit->text()).arg(ui->lineEdit_2->text())
                    .arg(ui->lineEdit_4->text()).arg(ui->lineEdit_5->text())
                    .arg(ui->lineEdit_7->text()).arg(ui->lineEdit_3->text()));
}

void HealthAssesment::takeAiReply(QString reply){
    QMessageBox::information(this,"",reply);
}

void HealthAssesment::on_pushButton_2_clicked()
{

}

void HealthAssesment::on_pushButton_clicked()
{

}
