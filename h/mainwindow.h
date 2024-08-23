#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Sign_inButton_clicked();

    void on_Sign_upButton_clicked();

    void on_LoginButton_clicked();

    void on_RegisterButton_clicked();

    void on_checkBox_toggled(bool checked);

    void on_checkBox_2_toggled(bool checked);

    void switchPage();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
