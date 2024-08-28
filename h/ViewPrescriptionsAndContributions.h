#ifndef VIEWPRESCRIPTIONSANDCONTRIBUTIONS_H
#define VIEWPRESCRIPTIONSANDCONTRIBUTIONS_H

#include <QWidget>
#include"net/ClientSocket.h"
namespace Ui {
class ViewPrescriptionsAndContributions;
}

class ViewPrescriptionsAndContributions : public QWidget
{
    Q_OBJECT

public:
    explicit ViewPrescriptionsAndContributions(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    ~ViewPrescriptionsAndContributions();

private slots:
    void on_pushButton_clicked();
    void setPrescription_slot(NetUtils::Prescription data);
    void setmedicine_slot(NetUtils::Medicine);

private:
    Ui::ViewPrescriptionsAndContributions *ui;
};

#endif // VIEWPRESCRIPTIONSANDCONTRIBUTIONS_H
