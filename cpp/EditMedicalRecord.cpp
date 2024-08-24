#include "h/EditMedicalRecord.h"
#include "ui_EditMedicalRecord.h"

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
