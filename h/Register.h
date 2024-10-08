#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include "Placeholders.h"

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

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_backButton_clicked();

    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_toggled(bool checked);

    void on_registerButton_clicked();

    void registerCallbackSlot(long long);

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked);

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
