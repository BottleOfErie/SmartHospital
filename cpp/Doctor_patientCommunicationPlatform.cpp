#include "h/Doctor_patientCommunicationPlatform.h"
#include "ui_Doctor_patientCommunicationPlatform.h"
#include <h/Doctor.h>
#include <h/Doctor_patientCommunicationPlatform.h>
#include <h/DoctorPatientCommunicationUserListWidget.h>
#include <h/Patient.h>
#include "h/usernow.h"
#include <QDateTime>
#include <QDebug>
#include <QMessageBox>
#include <net/ClientSocket.h>
#include <QTimer>
Doctor_patientCommunicationPlatform::Doctor_patientCommunicationPlatform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Doctor_patientCommunicationPlatform)
{
    ui->setupUi(this);

    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    waitTime=8000;
    patientId=doctorId=0;
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerOutGetMsg_slot()));
    timer->start(waitTime);

    connect(&ClientSocket::getInstance(),SIGNAL(appointment_callback(NetUtils::Appointment)),this,SLOT(getFriendList_slot(NetUtils::Appointment)));
    connect(&ClientSocket::getInstance(),SIGNAL(doctor_callback(NetUtils::DoctorData)),this,SLOT(getDoctorFriend_slot(NetUtils::DoctorData)));
    connect(&ClientSocket::getInstance(),SIGNAL(patient_callback(NetUtils::PatientData)),this,SLOT(getPatientFriend_slot(NetUtils::PatientData)));


    connect(&ClientSocket::getInstance(),SIGNAL(message_callback(NetUtils::Message)),this,SLOT(getMessage_slot(NetUtils::Message)));
    if(identity.compare("patient")==0){
        patientId=usernow::getId().toLong();
        ClientSocket::getInstance().getAppointmentsByPatient(patientId);
    }else{
        doctorId=usernow::getId().toLong();
        ClientSocket::getInstance().getAppointmentsByDoctor(doctorId);
    }
}

Doctor_patientCommunicationPlatform::~Doctor_patientCommunicationPlatform()
{
    delete ui;
    delete timer;
}

void Doctor_patientCommunicationPlatform::on_pushButton_2_clicked()
{
    this->close();
    if(identity=="doctor"){
        auto doctor = new Doctor;
        doctor->show();
    }
    else{
        auto patient = new Patient;
        patient->show();
    }
}
void Doctor_patientCommunicationPlatform::on_pushButton_clicked()
{
    if(patientId<=0||doctorId<=0){
        QMessageBox::warning(this,"","请选择聊天对象");
        return;
    }


    QString msg = ui->textEdit->toPlainText();
    ui->textEdit->setText("");
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    dealMessageTime(time);

    QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);

    NetUtils::Message data;
    data.patientId=patientId;
    data.doctorId=doctorId;
    if(identity.compare("patient")==0){
        data.sendDirection=0;
    }else{
        data.sendDirection=1;
    }
    data.timeStamp=QDateTime::currentDateTime().toTime_t();
    data.message=msg;
    data.isRead=false;
    ClientSocket::getInstance().submitMessage(data);
    msgs.append(data);

    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}

void Doctor_patientCommunicationPlatform::timerOutGetMsg_slot(){
    if(patientId>0&&doctorId>0){
        ClientSocket::getInstance().getMessageByPatDoc(patientId,doctorId);
    }
    timer->start(waitTime);
}

void Doctor_patientCommunicationPlatform::getMessage_slot(NetUtils::Message msg){
    bool contains=false;
    foreach(auto m,msgs){
        if(m.doctorId==msg.doctorId&&m.patientId==msg.patientId&&m.timeStamp==msg.timeStamp){
            contains=true;
            for(int i = ui->listWidget->count() - 1; i > 0; i--) {
                QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
                if(messageW->text() == msg.message) {
                    messageW->setTextSuccess();
                }
            }
        }
    }
    if(!contains){
        int myIdentity=identity.compare("patient")==0?1:-1;
        int msgDir=msg.sendDirection==0?1:-1;
        dealMessageTime(QString::number(msg.timeStamp));

        QNChatMessage::User_Type type=myIdentity*msgDir>0?QNChatMessage::User_Me:QNChatMessage::User_She;

        QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, msg.message, QString::number(msg.timeStamp), type);
        messageW->setTextSuccess();

        msgs.append(msg);
    }
}

void Doctor_patientCommunicationPlatform::dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time,  QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(ui->listWidget->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}

void Doctor_patientCommunicationPlatform::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟
//        isShowTime = true;
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);

        QSize size = QSize(ui->listWidget->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

void Doctor_patientCommunicationPlatform::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);


    //ui->textEdit->resize(ui->listWidget->width() - 20, ui->widget->height() - 20);
    //ui->textEdit->move(10, 10);

    /*ui->pushButton->move(ui->textEdit->width()+ui->textEdit->x() - ui->pushButton->width() - 10,
                         ui->textEdit->height()+ui->textEdit->y() - ui->pushButton->height() - 10);*/


    for(int i = 0; i < ui->listWidget->count(); i++) {
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);

        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}
void Doctor_patientCommunicationPlatform::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Doctor_patientCommunicationPlatform::getFriendList_slot(NetUtils::Appointment data){
    auto item=new QListWidgetItem("",ui->listWidget_2);

    if(identity=="patient"){
        idToItem.insert(data.doctorId,item);
        ClientSocket::getInstance().getDoctorDataById(data.doctorId);
    }
    else{
        idToItem.insert(data.patientId,item);
        ClientSocket::getInstance().getPatientById(data.patientId);
    }
}

void Doctor_patientCommunicationPlatform::getDoctorFriend_slot(NetUtils::DoctorData data){
    auto wid=new DoctorPatientCommunicationUserListWidget(data);
    ui->listWidget_2->setItemWidget(idToItem[data.id],wid);
}
void Doctor_patientCommunicationPlatform::getPatientFriend_slot(NetUtils::PatientData data){
    auto wid=new DoctorPatientCommunicationUserListWidget(data);
    ui->listWidget_2->setItemWidget(idToItem[data.id],wid);
}

void Doctor_patientCommunicationPlatform::on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->listWidget->clear();
    msgs.clear();

    if(identity=="patient"){
        doctorId=((DoctorPatientCommunicationUserListWidget*)ui->listWidget_2->itemWidget(current))->id;
    }
    else{
        patientId=((DoctorPatientCommunicationUserListWidget*)ui->listWidget_2->itemWidget(current))->id;
    }
    ClientSocket::getInstance().getMessageByPatDoc(patientId,doctorId);

}

