#ifndef PATIENTEDITPERSONALINFORMATION_H
#define PATIENTEDITPERSONALINFORMATION_H
#include <QWidget>
#include "net/NetUtils.h"
namespace Ui {
class PatientEditPersonalInformation;
}

class PatientEditPersonalInformation : public QWidget
{
    Q_OBJECT

public:
    explicit PatientEditPersonalInformation(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    ~PatientEditPersonalInformation();


private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void setPatientData_slot(NetUtils::PatientData data);
    void updatePatientData();
    void on_pushButton_toggled(bool checked);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);



    void on_name_textChanged(const QString &arg1);

    void on_age_textChanged(const QString &arg1);

    void on_gender_textChanged(const QString &arg1);

    void on_IDnumber_textChanged(const QString &arg1);

    void on_phone_textChanged(const QString &arg1);

    void on_textEdit_textChanged(const QString &arg1);

    void on_textEdit_2_textChanged(const QString &arg1);

private:
    Ui::PatientEditPersonalInformation *ui;
    NetUtils::PatientData currentData;
};

#endif // PatientEDITPERSONALINFORMATION_H
