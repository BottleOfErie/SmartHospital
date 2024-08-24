#ifndef CHUFANGHEBINGLI_H
#define CHUFANGHEBINGLI_H
#include <QWidget>
#include <QMainWindow>
namespace Ui {
    class Chufanghebingli;
}

class Chufanghebingli : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chufanghebingli(QWidget *parent = nullptr);
    ~Chufanghebingli();

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Chufanghebingli *ui;
};
#endif // CHUFANGHEBINGLI_H
