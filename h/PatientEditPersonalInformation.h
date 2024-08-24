#ifndef PATIENTEDITPERSONALINFORMATION_H
#define PATIENTEDITPERSONALINFORMATION_H

#include <QWidget>

namespace Ui {
class PatientEditPersonalInformation;
}

class PatientEditPersonalInformation : public QWidget
{
    Q_OBJECT

public:
    explicit PatientEditPersonalInformation(QWidget *parent = nullptr);
    ~PatientEditPersonalInformation();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::PatientEditPersonalInformation *ui;
};

#endif // PATIENTEDITPERSONALINFORMATION_H
