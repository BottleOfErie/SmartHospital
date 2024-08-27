#include "h/EditMedicalRecord.h"
#include "ui_EditMedicalRecord.h"
#include "h/Doctor.h"
#include "h/usernow.h"

#include <QPainter>
#include <QStyleOption>
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
void EditMedicalRecord::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
