#ifndef HEALTHASSESMENT_H
#define HEALTHASSESMENT_H

#include <QWidget>

namespace Ui {
class HealthAssesment;
}

class HealthAssesment : public QWidget
{
    Q_OBJECT

public:
    explicit HealthAssesment(QWidget *parent = nullptr);
    ~HealthAssesment();

private slots:
    void on_pushButton_3_clicked();

private:
    Ui::HealthAssesment *ui;
};

#endif // HEALTHASSESMENT_H
