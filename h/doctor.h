#ifndef DOCTOR_H
#define DOCTOR_H

#include <QWidget>

namespace Ui {
class Doctor;
}

class Doctor : public QWidget
{
    Q_OBJECT

public:
    explicit Doctor(QWidget *parent = nullptr);
    ~Doctor();

public slots:
    void on_pushButton6_clicked();
    void on_pushButton4_clicked();
    void on_pushButton2_clicked();
    void on_pushButton3_clicked();

private:
    Ui::Doctor *ui;
};

#endif // DOCTOR_H
