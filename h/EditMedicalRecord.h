#ifndef EDITMEDICALRECORD_H
#define EDITMEDICALRECORD_H

#include <QMap>
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

    void on_pushButton_clicked();
    void uploadMedicalRecord();
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void getPatientName_slot(NetUtils::Appointment data);
    void addNameItem_slot(NetUtils::PatientData data);
private:
    Ui::EditMedicalRecord *ui;
    QMap<long,QString> idToTime;
    QMap<QString,long> nametoId;

};

#endif // EDITMEDICALRECORD_H
