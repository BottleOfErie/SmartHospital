#ifndef PATIENT_H
#define PATIENT_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>
namespace Ui {
class Patient;
}

class Patient : public QWidget
{
    Q_OBJECT

public:
    explicit Patient(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    ~Patient();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_clicked();

    void on_pushButton_9_clicked();

    void aiReply_slot(QString s);

private:
    Ui::Patient *ui;
};

#endif // PATIENT_H
