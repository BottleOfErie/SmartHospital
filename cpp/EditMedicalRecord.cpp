#include "h/EditMedicalRecord.h"
#include "ui_EditMedicalRecord.h"
#include "h/Doctor.h"
#include "h/usernow.h"
EditMedicalRecord::EditMedicalRecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditMedicalRecord)
{
    ui->setupUi(this);
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
