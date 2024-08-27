#ifndef VIEWPRESCRIPTIONSANDCONTRIBUTIONS_H
#define VIEWPRESCRIPTIONSANDCONTRIBUTIONS_H

#include <QWidget>

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

private:
    Ui::ViewPrescriptionsAndContributions *ui;
};

#endif // VIEWPRESCRIPTIONSANDCONTRIBUTIONS_H
