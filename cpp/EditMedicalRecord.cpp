#include "h/EditMedicalRecord.h"
#include "ui_EditMedicalRecord.h"
#include "h/Doctor.h"
#include "h/usernow.h"

#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>

#include <net/ClientSocket.h>
EditMedicalRecord::EditMedicalRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditMedicalRecord)
{
    ui->setupUi(this);
    ui->lineEdit_2->setReadOnly(true);
    connect(&ClientSocket::getInstance(),SIGNAL(appointment_callback(NetUtils::Appointment)),this,SLOT(getPatientName_slot(NetUtils::Appointment)));
    ClientSocket::getInstance().getAppointmentsByDoctor(usernow::getId().toLong());
    connect(&ClientSocket::getInstance(),SIGNAL(patient_callback(NetUtils::PatientData)),this,SLOT(addNameItem_slot(NetUtils::PatientData)));
}

EditMedicalRecord::~EditMedicalRecord()
{
    delete ui;
}

void EditMedicalRecord::on_pushButton_clicked()
{
    if(ui->lineEdit_3->text()=="" || ui->lineEdit_4->text()==""){
        QMessageBox::warning(this,"error","请填写诊断结果或治疗方案！！");
    }
    else{
        uploadMedicalRecord();
        closeWindow();
    }
}

void EditMedicalRecord::on_pushButton_2_clicked()
{
    if(ui->lineEdit_3->text()!="" && ui->lineEdit_4->text()!=""){
        QMessageBox msgBox;
        msgBox.setWindowTitle("选择操作");           // 设置弹窗标题
        msgBox.setText("是否将病例结果上传？");    // 设置弹窗内容
        msgBox.setIcon(QMessageBox::Question);        // 设置弹窗图标
        msgBox.setWindowFlag(Qt::WindowCloseButtonHint, false);

        // 添加两个按钮选项
        QPushButton *yes = msgBox.addButton(tr("YES"), QMessageBox::ActionRole);
        msgBox.addButton(tr("NO"), QMessageBox::ActionRole);

        // 显示消息框并等待用户选择
        msgBox.exec();

        // 判断用户选择了哪个按钮
        if (msgBox.clickedButton() == yes) {
            uploadMedicalRecord();
        }
    }
    closeWindow();
}

void EditMedicalRecord::uploadMedicalRecord(){
    long id=nametoId.find(ui->comboBox->currentText()).value();
    QString date=idToTime.find(id).value();
    ClientSocket::getInstance().submitMedicalRecord((NetUtils::MedicalRecord){
        id,
        usernow().getId().toLong(),
        date,
        ui->lineEdit_3->text(),
        ui->lineEdit_4->text(),
        });
    QMessageBox::information(NULL, "上传成功", "上传成功！！！", QMessageBox::Yes);
}

void EditMedicalRecord::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void EditMedicalRecord::getPatientName_slot(NetUtils::Appointment data){
    ClientSocket::getInstance().getPatientById(data.patientId);
    idToTime.insert(data.patientId,data.time);
}

void EditMedicalRecord::addNameItem_slot(NetUtils::PatientData data){
    nametoId.insert(data.name,data.id);
    ui->comboBox->addItem(data.name);
}

void EditMedicalRecord::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->lineEdit_2->setText(idToTime.find(nametoId.find(arg1).value()).value());
}

void EditMedicalRecord::closeWindow(){
    this->close();
    disconnect(&ClientSocket::getInstance(),SIGNAL(patient_callback(NetUtils::PatientData)),this,SLOT(addNameItem_slot(NetUtils::PatientData)));
    disconnect(&ClientSocket::getInstance(),SIGNAL(appointment_callback(NetUtils::Appointment)),this,SLOT(getPatientName_slot(NetUtils::Appointment)));
    auto doctor = new Doctor;
    doctor->show();
}
