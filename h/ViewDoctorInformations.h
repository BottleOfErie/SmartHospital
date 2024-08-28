#ifndef VIEWDOCTORINFORMATIONS_H
#define VIEWDOCTORINFORMATIONS_H

#include <QWidget>

#include "usernow.h"
#include "h/Placeholders.h"
#include "net/NetUtils.h"
#include "net/ClientSocket.h"

namespace Ui {
class ViewDoctorInformations;
}

class ViewDoctorInformations : public QWidget
{
    Q_OBJECT

public:
    explicit ViewDoctorInformations(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    ~ViewDoctorInformations();

private slots:
    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void loadDoctors_slot(NetUtils::DoctorData doctor);

    void on_pushButton_clicked();

private:
    Ui::ViewDoctorInformations *ui;

    QMap<QString, NetUtils::DoctorData> doctors;  //a map from doctor's name to doctor's data
};

#endif // VIEWDOCTORINFORMATIONS_H
