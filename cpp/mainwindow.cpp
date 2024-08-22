
#include "ui_mainwindow.h"

#include <h/mainwindow.h>
#include <h/register.h>
#include <h/patient.h>
#include <h/doctor.h>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->LoginButton, &QPushButton::clicked, this, &MainWindow::on_LoginButton_clicked);
    connect(ui->RegisterButton, &QPushButton::clicked, this, &MainWindow::on_RegisterButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoginButton_clicked()
{
    QString username = ui->username->text();//获取用户名
    QString password = ui->password->text();//获取密码
    //判断用户名密码是否为空，为空则提示不能为空
    if(username=="")
        QMessageBox::warning(this,"","用户名不能为空");
    else if (password=="")
        QMessageBox::warning(this,"","密码不能为空");
    else {
        //TODO 数据库对接
        QString S = QString("select * from user_table where name='%1' and password='%2'").arg(username).arg(password);
        QSqlQuery query;//执行查询语句
        if(query.exec(S)){
            QMessageBox::information(NULL, "登陆成功", "登陆成功！！！", QMessageBox::Yes);        
            switchPage();
        }
        else
            QMessageBox::warning(this,"error","用户名或者密码错误！！");
            // 清空内容并定位光标
        ui->username->clear();
        ui->password->clear();
        ui->username->setFocus();//将光标定位到用户名输入框
    }
}


void MainWindow::on_RegisterButton_clicked()
{
    // 关闭登录界面
    this->close();
    // 创建注册界面对象
    Register *registerWidget = new Register();
    // 显示注册界面
    registerWidget->show();
}

void MainWindow::on_checkBox_toggled(bool checked)
{
    if (checked) {
        ui->checkBox_2->setChecked(false);
    }
}

void MainWindow::on_checkBox_2_toggled(bool checked)
{
    if (checked) {
        ui->checkBox->setChecked(false);
    }
}

void MainWindow::switchPage()
{
    this->close();
    if(ui->checkBox->isChecked()==true){
        // 进入医生主界面
        Doctor *doctorWidget = new Doctor();
        doctorWidget->show();
    }
    else{
        // 进入患者主界面
        Patient *patientWidget = new Patient();
        patientWidget->show();
    }
}
