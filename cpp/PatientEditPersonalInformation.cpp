#include "h/PatientEditPersonalInformation.h"
#include "ui_PatientEditPersonalInformation.h"
#include <h/Patient.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include<QDebug>
#include "h/usernow.h"
#include "net/ClientSocket.h"
//信息是否被修改过
bool passwordright=false;
bool isInformationChanged2(false),isempty(true);
PatientEditPersonalInformation::PatientEditPersonalInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientEditPersonalInformation)
{

    ui->setupUi(this);
    // 设置“更改”按钮为可切换状态
    ui->pushButton->setCheckable(true);

    connect(ui->pushButton, &QPushButton::toggled, this, &PatientEditPersonalInformation::on_pushButton_toggled);

    /*connect(ui->lineEdit, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_lineEdit_textChanged);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_lineEdit_2_textChanged);
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_lineEdit_3_textChanged);
    connect(ui->name, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_name_textChanged);
    connect(ui->age, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_age_textChanged);
    connect(ui->gender, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_gender_textChanged);
    connect(ui->IDnumber, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_IDnumber_textChanged);
    connect(ui->phone, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_phone_textChanged);
    connect(ui->textEdit, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_textEdit_textChanged);
    connect(ui->textEdit_2, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_textEdit_2_textChanged);*/

    connect(&ClientSocket::getInstance(),SIGNAL(patient_callback(NetUtils::PatientData)),this,SLOT(setPatientData_slot(NetUtils::PatientData)));
    ClientSocket::getInstance().getPatientById(usernow::getId().toLong());
    connect(&ClientSocket::getInstance(),SIGNAL(resetPassword_callback(bool)),this,SLOT(resetPassword_slot(bool)));
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->name->setReadOnly(true);
    ui->age->setReadOnly(true);
    ui->gender->setReadOnly(true);
    ui->IDnumber->setReadOnly(true);
    ui->phone->setReadOnly(true);
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setReadOnly(true);
}

PatientEditPersonalInformation::~PatientEditPersonalInformation()
{
    delete ui;
}
void PatientEditPersonalInformation::on_pushButton_2_clicked()
{
    //if(pd()&&passwordright)
    //{
        PatientEditPersonalInformation::updatePatientData();
        //qDebug("666");
        this->close();
        auto patient = new Patient;
        patient->show();
    //}
   // else
    //{
    //    QMessageBox::warning(this,"","原密码错误或两次输入的新密码不相同!!");
   //}

}
void PatientEditPersonalInformation::on_pushButton_3_clicked()
{
    if(isInformationChanged2){
        // 创建一个消息框
        QMessageBox msgBox;
        msgBox.setWindowTitle("选择操作");           // 设置弹窗标题
        msgBox.setText("是否保存更改？");    // 设置弹窗内容
        msgBox.setIcon(QMessageBox::Question);        // 设置弹窗图标
        msgBox.setWindowFlag(Qt::WindowCloseButtonHint, false);

        // 添加两个按钮选项
        QPushButton *yes = msgBox.addButton(tr("YES"), QMessageBox::ActionRole);
        msgBox.addButton(tr("NO"), QMessageBox::ActionRole);

        // 显示消息框并等待用户选择
        msgBox.exec();

        // 判断用户选择了哪个按钮
        if (msgBox.clickedButton() == yes) {
            PatientEditPersonalInformation::updatePatientData();
            isInformationChanged2=false;
        }
    }
   // if(pd()&&passwordright)
   // {
        this->close();
        auto patient = new Patient;
        patient->show();
    //}
    //else
   // {
    //    QMessageBox::warning(this,"","原密码错误或两次输入的新密码不相同!!");
    //}
}

void PatientEditPersonalInformation::setPatientData_slot(NetUtils::PatientData data){
    qDebug()<<data.name;
    currentData=data;
    ui->name->setText(data.name);
    ui->age->setText(data.birthday);
   // ui->gender->setText(data.gender);
    ui->phone->setText(data.phoneNumber);
    ui->textEdit->setText(data.history);
    ui->IDnumber->setText(data.nationId);
    isInformationChanged2=false;
}

void PatientEditPersonalInformation::updatePatientData(){
    currentData.name=ui->name->text();
    currentData.birthday=ui->age->text();
    currentData.nationId=ui->IDnumber->text();
    currentData.phoneNumber=ui->phone->text();
    currentData.history=ui->textEdit->toPlainText();
    ClientSocket::getInstance().submitPatientData(currentData);
    QMessageBox::information(NULL, "修改成功", "修改成功！！！", QMessageBox::Yes);

}


void PatientEditPersonalInformation::on_pushButton_toggled(bool checked)
{
    if (checked) {
        // 如果按钮被按下，QLineEdit 变为可编辑，按钮高亮
        ui->lineEdit->setReadOnly(false);
        ui->lineEdit_2->setReadOnly(false);
        ui->lineEdit_3->setReadOnly(false);
        ui->name->setReadOnly(false);
        ui->age->setReadOnly(false);
        ui->gender->setReadOnly(false);
        ui->IDnumber->setReadOnly(false);
        ui->phone->setReadOnly(false);
        ui->textEdit->setReadOnly(false);
        ui->textEdit_2->setReadOnly(false);
        ui->pushButton->setStyleSheet("background-color: lightblue;");  // 按钮高亮
    } else {
        // 如果按钮被释放，QLineEdit 变为只读，取消按钮高亮
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit_2->setReadOnly(true);
        ui->lineEdit_3->setReadOnly(true);
        ui->name->setReadOnly(true);
        ui->age->setReadOnly(true);
        ui->gender->setReadOnly(true);
        ui->IDnumber->setReadOnly(true);
        ui->phone->setReadOnly(true);
        ui->textEdit->setReadOnly(true);
        ui->textEdit_2->setReadOnly(true);
        ui->pushButton->setStyleSheet("");  // 恢复按钮默认样式
    }
}

void PatientEditPersonalInformation::on_lineEdit_textChanged(const QString &arg1)
{
    isInformationChanged2=true;
}

void PatientEditPersonalInformation::on_lineEdit_2_textChanged(const QString &arg1)
{
    isInformationChanged2=true;
}

void PatientEditPersonalInformation::on_lineEdit_3_textChanged(const QString &arg1)
{
    isInformationChanged2=true;
}

void PatientEditPersonalInformation::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void PatientEditPersonalInformation::on_name_textChanged(const QString &arg1)
{
    isInformationChanged2=true;
}


void PatientEditPersonalInformation::on_age_textChanged(const QString &arg1)
{
    isInformationChanged2=true;
}


void PatientEditPersonalInformation::on_gender_textChanged(const QString &arg1)
{
    isInformationChanged2=true;
}


void PatientEditPersonalInformation::on_IDnumber_textChanged(const QString &arg1)
{
    isInformationChanged2=true;
}


void PatientEditPersonalInformation::on_phone_textChanged(const QString &arg1)
{
    isInformationChanged2=true;
}


void PatientEditPersonalInformation::on_textEdit_textChanged(const QString &arg1)
{
    isInformationChanged2=true;
}


void PatientEditPersonalInformation::on_textEdit_2_textChanged(const QString &arg1)
{
    isInformationChanged2=true;
}
int PatientEditPersonalInformation::pd()
{
    QString password=ui->lineEdit_2->text();
    if(password=="")isempty=true;
    else isempty=false;qDebug("reset");
    if(password!=ui->lineEdit_3->text())return 0;

    ClientSocket::getInstance().resetPassword(usernow::getId().toLong(),ui->lineEdit->text(),password);
    return 1;
}
void PatientEditPersonalInformation::resetPassword_slot(bool b)
{
    qDebug()<<b;
    passwordright=b;
}
