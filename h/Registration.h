#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include "usernow.h"
#include "h/Placeholders.h"
#include "net/NetUtils.h"
#include "net/ClientSocket.h"

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    ~Registration();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void loadDoctors_slot(NetUtils::DoctorData doctor);

private:
    Ui::Registration *ui;

    QMap<QString, long> doctors;  //a map from doctor's name to doctor's id
};

#endif // REGISTRATION_H
