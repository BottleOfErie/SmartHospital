#include "h/DoctorEditPersonalInformation.h"
#include "ui_DoctorEditPersonalInformation.h"
#include <h/Doctor.h>
#include "h/usernow.h"
#include "net/ClientSocket.h"
#include "QMessageBox"
//信息是否被修改过
DoctorEditPersonalInformation::DoctorEditPersonalInformation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorEditPersonalInformation)
{

    ui->setupUi(this);
    // 设置“更改”按钮为可切换状态
    ui->pushButton->setCheckable(true);

    connect(ui->pushButton, &QPushButton::toggled, this, &DoctorEditPersonalInformation::on_pushButton_toggled);

    connect(&ClientSocket::getInstance(),SIGNAL(doctor_callback(NetUtils::DoctorData)),this,SLOT(setDoctorData_slot(NetUtils::DoctorData)));
    ClientSocket::getInstance().getDoctorDataById(usernow::getId().toLong());

    ui->lineEdit->setReadOnly(true);
    ui->lineEdit_2->setReadOnly(true);
    ui->lineEdit_3->setReadOnly(true);
    ui->lineEdit_4->setReadOnly(true);
    ui->lineEdit_5->setReadOnly(true);
    ui->lineEdit_6->setReadOnly(true);
    ui->dateEdit->setReadOnly(true);
}

DoctorEditPersonalInformation::~DoctorEditPersonalInformation()
{
    delete ui;
}
void DoctorEditPersonalInformation::on_pushButton_2_clicked()
{
    DoctorEditPersonalInformation::updateDoctorData();
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}
void DoctorEditPersonalInformation::on_pushButton_3_clicked()
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
            DoctorEditPersonalInformation::updateDoctorData();
            isInformationChanged=false;
        }
    }
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}

void DoctorEditPersonalInformation::setDoctorData_slot(NetUtils::DoctorData data){
    currentData=data;
    ui->lineEdit->setText(data.name);
    ui->dateEdit->setDate(QDate::fromString(data.birthday,"yyyy-MM-dd"));
    ui->lineEdit_2->setText(data.nationId);
    ui->lineEdit_3->setText(data.jobTitle);
    ui->lineEdit_4->setText(data.section);
    ui->lineEdit_5->setText(data.phoneNumber);
    ui->lineEdit_6->setText(data.organization);
    isInformationChanged=false;
}

void DoctorEditPersonalInformation::updateDoctorData(){
    currentData.name=ui->lineEdit->text();
    currentData.jobTitle=ui->lineEdit_3->text();
    currentData.section=ui->lineEdit_4->text();
    currentData.phoneNumber=ui->lineEdit_5->text();
    currentData.birthday=ui->dateEdit->date().toString("yyyy-MM-dd");
    currentData.nationId=ui->lineEdit_2->text();
    currentData.organization=ui->lineEdit_6->text();

    ClientSocket::getInstance().submitDoctorData(currentData);
    QMessageBox::information(NULL, "修改成功", "修改成功！！！", QMessageBox::Yes);

}


void DoctorEditPersonalInformation::on_pushButton_toggled(bool checked)
{
    if (checked) {
        // 如果按钮被按下，QLineEdit 变为可编辑，按钮高亮
        ui->lineEdit->setReadOnly(false);
        ui->lineEdit_2->setReadOnly(false);
        ui->lineEdit_3->setReadOnly(false);
        ui->lineEdit_4->setReadOnly(false);
        ui->lineEdit_5->setReadOnly(false);
        ui->pushButton->setStyleSheet("background-color: lightblue;");  // 按钮高亮
    } else {
        // 如果按钮被释放，QLineEdit 变为只读，取消按钮高亮
        ui->lineEdit->setReadOnly(true);
        ui->lineEdit_2->setReadOnly(true);
        ui->lineEdit_3->setReadOnly(true);
        ui->lineEdit_4->setReadOnly(true);
        ui->lineEdit_5->setReadOnly(true);
        ui->pushButton->setStyleSheet("");  // 恢复按钮默认样式
    }
}

void DoctorEditPersonalInformation::on_lineEdit_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}

void DoctorEditPersonalInformation::on_lineEdit_2_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}

void DoctorEditPersonalInformation::on_lineEdit_3_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}

void DoctorEditPersonalInformation::on_lineEdit_4_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}

void DoctorEditPersonalInformation::on_lineEdit_5_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}

void DoctorEditPersonalInformation::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void DoctorEditPersonalInformation::on_dateEdit_dateChanged(const QDate &date)
{
    isInformationChanged=true;
}

void DoctorEditPersonalInformation::on_lineEdit_6_textChanged(const QString &arg1)
{
    isInformationChanged=true;
}

void DoctorEditPersonalInformation::on_lineEdit_5_cursorPositionChanged(int arg1, int arg2)
{
    isInformationChanged=true;
}
