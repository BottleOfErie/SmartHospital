#include "h/PatientEditPersonalInformation.h"
#include "ui_PatientEditPersonalInformation.h"
#include <h/Patient.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include "h/usernow.h"
#include "net/ClientSocket.h"
//信息是否被修改过
bool isInformationChanged(false);
PatientEditPersonalInformation::PatientEditPersonalInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PatientEditPersonalInformation)
{

    ui->setupUi(this);
    // 设置“更改”按钮为可切换状态
    ui->pushButton->setCheckable(true);

    connect(ui->pushButton, &QPushButton::toggled, this, &PatientEditPersonalInformation::on_pushButton_toggled);

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_lineEdit_textChanged);
    connect(ui->lineEdit_2, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_lineEdit_2_textChanged);
    connect(ui->lineEdit_3, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_lineEdit_3_textChanged);
    connect(ui->name, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_name_textChanged);
    connect(ui->age, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_age_textChanged);
    connect(ui->gender, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_gender_textChanged);
    connect(ui->IDnumber, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_IDnumber_textChanged);
    connect(ui->phone, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_phone_textChanged);
    connect(ui->textEdit, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_textEdit_textChanged);
    connect(ui->textEdit_2, &QLineEdit::textChanged, this, &PatientEditPersonalInformation::on_textEdit_2_textChanged);

    connect(&ClientSocket::getInstance(),SIGNAL(patient_callback(NetUtils::PatientData)),this,SLOT(setPatientData_slot(NetUtils::PatientData)));
    ClientSocket::getInstance().getPatientDataById(usernow::getId().toLong());

    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
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
    PatientEditPersonalInformation::updatePatientData();
    this->close();
    auto patient = new Patient;
    patient->show();
}
void PatientEditPersonalInformation::on_pushButton_3_clicked()
{
    if(isInformationChanged){
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
            isInformationChanged=false;
        }
    }
    this->close();
    auto patient = new Patient;
    patient->show();
}

void PatientEditPersonalInformation::setPatientData_slot(NetUtils::PatientData data){
    currentData=data;
    ui->lineEdit->setText(data.name);
    ui->dateEdit->setDate(QDate::fromString(data.birthday,"yyyy-MM-dd"));
    ui->lineEdit_2->setText(data.nationId);
    ui->lineEdit_3->setText(data.jobTitle);
    ui->lineEdit_4->setText(data.section);
    ui->lineEdit_5->setText(data.phoneNumber);
    isInformationChanged=false;
}

void PatientEditPersonalInformation::updatePatientData(){
    currentData.name=ui->lineEdit->text();
    currentData.birthday=ui->lineEdit_2->text();
    currentData.jobTitle=ui->lineEdit_3->text();
    currentData.section=ui->lineEdit_4->text();
    currentData.phoneNumber=ui->lineEdit_5->text();
    currentData.birthday=ui->dateEdit->date().toString("yyyy-MM-dd");

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
    isInformationChanged=true;
}

void PatientEditPersonalInformation::on_lineEdit_2_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}

void PatientEditPersonalInformation::on_lineEdit_3_textChanged(const QString &arg1)
{
    isInformationChanged=true;
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
    isInformationChanged=true;
}


void PatientEditPersonalInformation::on_age_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}


void PatientEditPersonalInformation::on_gender_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}


void PatientEditPersonalInformation::on_IDnumber_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}


void PatientEditPersonalInformation::on_phone_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}


void PatientEditPersonalInformation::on_textEdit_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}


void PatientEditPersonalInformation::on_textEdit_2_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}

