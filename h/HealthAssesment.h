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
private:
    void outputAiResult(QString result);
    NetUtils::TestResult result;
private slots:
    void on_pushButton_3_clicked();
    void setTestResult_slot(NetUtils::TestResult);

    void on_pushButton_4_clicked();
    void takeAiReply(QString reply);
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::HealthAssesment *ui;
};

#endif // HEALTHASSESMENT_H
