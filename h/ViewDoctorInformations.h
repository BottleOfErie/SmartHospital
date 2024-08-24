#ifndef VIEWDOCTORINFORMATIONS_H
#define VIEWDOCTORINFORMATIONS_H

#include <QWidget>

namespace Ui {
class ViewDoctorInformations;
}

class ViewDoctorInformations : public QWidget
{
    Q_OBJECT

public:
    explicit ViewDoctorInformations(QWidget *parent = nullptr);
    ~ViewDoctorInformations();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::ViewDoctorInformations *ui;
};

#endif // VIEWDOCTORINFORMATIONS_H
