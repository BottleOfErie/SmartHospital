#ifndef DOCTOREDITPERSONALINFORMATION_H
#define DOCTOREDITPERSONALINFORMATION_H
#include <QWidget>
#include "net/NetUtils.h"
namespace Ui {
class DoctorEditPersonalInformation;
}

class DoctorEditPersonalInformation : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorEditPersonalInformation(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    ~DoctorEditPersonalInformation();


private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void setDoctorData_slot(NetUtils::DoctorData data);
    void updateDoctorData();
    void on_pushButton_toggled(bool checked);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_dateEdit_dateChanged(const QDate &date);

    void on_lineEdit_6_textChanged(const QString &arg1);

    void on_lineEdit_5_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::DoctorEditPersonalInformation *ui;
    NetUtils::DoctorData currentData;
    bool isInformationChanged=false;
};

#endif // DOCTOREDITPERSONALINFORMATION_H
