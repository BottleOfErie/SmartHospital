#ifndef VIEWREGISTRATION_H
#define VIEWREGISTRATION_H

#include <QWidget>
#include <QMap>

#include <net/NetUtils.h>

namespace Ui {
class ViewRegistration;
}

class ViewRegistration : public QWidget
{
    Q_OBJECT

public:
    explicit ViewRegistration(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    ~ViewRegistration();
private:
    QMap<long,int>idToLine;
private slots:
    void on_pushButton_clicked();
    void setRegistrationData_slot(NetUtils::Appointment data);
    void setPatientName_slot(NetUtils::PatientData data);

private:
    Ui::ViewRegistration *ui;
};

#endif // VIEWREGISTRATION_H
