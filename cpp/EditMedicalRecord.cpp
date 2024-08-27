#include "h/EditMedicalRecord.h"
#include "ui_EditMedicalRecord.h"
#include "h/Doctor.h"
#include "h/usernow.h"

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

void EditMedicalRecord::on_pushButton_2_clicked()
{
    this->close();
    auto doctor = new Doctor;
    doctor->show();
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
    ui->comboBox->addItem(data.name);
    nametoId.insert(data.name,data.id);
}

void EditMedicalRecord::on_pushButton_clicked()
{

    (NetUtils::MedicalRecord){
                    id,ui->lineEdit_2->text(),ui->username->text(),
                    ui->lineEdit_3->text(),
                    ui->radioButton->isChecked()?0:1,
                    ui->dateEdit->date().toString("yyyy-MM-dd"),
                    ui->phone->text(),ui->comboBox->currentText(),
                    ui->organization->text(),
                    ui->lineEdit_4->text()
                    })
}

void EditMedicalRecord::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->lineEdit_2->setText(nametoId.find("QString(arg1)"))
}
