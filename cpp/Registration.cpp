#include "h/Registration.h"
#include "ui_Registration.h"

#include <h/Patient.h>
#include <QMessageBox>
#include <QDate>

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);

    QDate date = QDate::currentDate();
    for (int i = 0; i < 7; i++) {
        ui->comboBox_3->addItem(date.addDays(i).toString("yyyy-MM-dd"));
    }

    connect(&ClientSocket::getInstance(),SIGNAL(doctor_callback(NetUtils::DoctorData)),this,SLOT(loadDoctors_slot(NetUtils::DoctorData)));
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
    QString doctorName = ui->comboBox_2->currentText();
    QString dateTime = ui->comboBox_3->currentText();
    if (doctorName != DOCTOR_PLACEHOLDER && dateTime != DATETIME_PLACEHOLDER) {
        NetUtils::Appointment appointment;
        appointment.doctorId = doctors[doctorName];
        appointment.patientId = usernow::getId().toLong();
        appointment.state = 0;  // before the meeting time
        appointment.time = dateTime;
        ClientSocket::getInstance().submitAppointment(appointment);
        QMessageBox::information(NULL, "提交成功", "提交成功！！！", QMessageBox::Yes);
        this->close();
        Patient *patientWindow=new Patient();
        patientWindow->show();
    }
    else{
        QMessageBox::warning(this,"error","提交失败，请确认信息是否全部填写！！");
    }
}
void Registration::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Registration::loadDoctors_slot(NetUtils::DoctorData doctor)
{
    doctors.clear();
    doctors[doctor.name] = doctor.id;
    ui->comboBox_2->addItem(doctor.name);
}

void Registration::on_comboBox_currentIndexChanged(const QString &arg1)
{
    ui->comboBox_2->clear();
    ui->comboBox_2->addItem(DOCTOR_PLACEHOLDER);
    if (arg1 != REG_SECTION_PLACEHOLDER) {
        ClientSocket::getInstance().getDoctorsBySection(arg1);
    }
}
