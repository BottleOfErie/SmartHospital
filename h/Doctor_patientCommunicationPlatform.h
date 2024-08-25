#ifndef DOCTOR_PATIENTCOMMUNICATIONPLATFORM_H
#define DOCTOR_PATIENTCOMMUNICATIONPLATFORM_H

#include <QWidget>

namespace Ui {
class Doctor_patientCommunicationPlatform;
}

class Doctor_patientCommunicationPlatform : public QWidget
{
    Q_OBJECT

public:
    explicit Doctor_patientCommunicationPlatform(QWidget *parent = nullptr);
    QString identity;
    ~Doctor_patientCommunicationPlatform();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::Doctor_patientCommunicationPlatform *ui;
};

#endif // DOCTOR_PATIENTCOMMUNICATIONPLATFORM_H
