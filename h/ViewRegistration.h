#ifndef VIEWREGISTRATION_H
#define VIEWREGISTRATION_H

#include <QWidget>

#include <net/NetUtils.h>

namespace Ui {
class ViewRegistration;
}

class ViewRegistration : public QWidget
{
    Q_OBJECT

public:
    explicit ViewRegistration(QWidget *parent = nullptr);
    ~ViewRegistration();

private slots:
    void on_pushButton_clicked();
    void setRegistrationData_slot(NetUtils::Appointment data);

private:
    Ui::ViewRegistration *ui;
};

#endif // VIEWREGISTRATION_H
