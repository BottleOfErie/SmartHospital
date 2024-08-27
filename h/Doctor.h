#ifndef DOCTOR_H
#define DOCTOR_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
namespace Ui {
class Doctor;
}

class Doctor : public QWidget
{
    Q_OBJECT

public:
    explicit Doctor(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    ~Doctor();

public slots:
    void on_pushButton_6_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();

private slots:
    void on_pushButton_5_clicked();

private:
    Ui::Doctor *ui;
};

#endif // DOCTOR_H
