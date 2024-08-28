#ifndef HEALTHASSESMENT_H
#define HEALTHASSESMENT_H

#include <QWidget>
#include"net/ClientSocket.h"
namespace Ui {
class HealthAssesment;
}

class HealthAssesment : public QWidget
{
    Q_OBJECT

public:
    explicit HealthAssesment(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    ~HealthAssesment();

private slots:
    void on_pushButton_3_clicked();
    void setTestResult_slot(NetUtils::TestResult);

    void on_pushButton_4_clicked();

private:
    Ui::HealthAssesment *ui;
};

#endif // HEALTHASSESMENT_H
