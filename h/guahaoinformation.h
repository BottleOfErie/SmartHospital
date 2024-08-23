#ifndef GUAHAOINFORMATION_H
#define GUAHAOINFORMATION_H
#include <QWidget>

namespace Ui {
    class GuaHaoInformation;
}

class GuaHaoInformation : public QWidget
{
    Q_OBJECT

public:
    explicit GuaHaoInformation(QWidget *parent = nullptr);
    ~GuaHaoInformation();

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::GuaHaoInformation *ui;
};

#endif // GUAHAOINFORMATION_H

