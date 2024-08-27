#ifndef EDITMEDICALRECORD_H
#define EDITMEDICALRECORD_H

#include <QWidget>

#include <net/NetUtils.h>

namespace Ui {
class EditMedicalRecord;
}

class EditMedicalRecord : public QWidget
{
    Q_OBJECT

public:
    explicit EditMedicalRecord(QWidget *parent = nullptr);
     void paintEvent(QPaintEvent *e);
    ~EditMedicalRecord();


private slots:
    void on_pushButton_2_clicked();
    void setMedicalRecords_slot(NetUtils::MedicalRecord);

private:
    Ui::EditMedicalRecord *ui;
};

#endif // EDITMEDICALRECORD_H
