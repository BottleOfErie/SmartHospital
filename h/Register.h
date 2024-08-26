#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    ~Register();

private slots:
    void on_backButton_clicked();

    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_toggled(bool checked);

    void on_registerButton_clicked();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
