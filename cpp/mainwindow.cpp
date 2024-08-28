
#include "ui_mainwindow.h"

#include<h/extern_variable.h>
#include <h/mainwindow.h>
#include <h/Register.h>
#include <h/Patient.h>
#include <h/Doctor.h>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <h/usernow.h>
#include "net/ClientSocket.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);

    //connect(&ClientSocket::getInstance(),SIGNAL(login_callback(long long)),this,SLOT(loginCallback_slot(long long)));
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
    else if (ui->checkBox->isChecked()==false && ui->checkBox_2->isChecked()==false){
        QMessageBox::warning(this,"","请选择你是医生还是患者！！");
    }
    else {
        connect(&ClientSocket::getInstance(),SIGNAL(login_callback(long long)),this,SLOT(loginCallback_slot(long long)));
        ClientSocket::getInstance().loginC(username,password,ui->checkBox->isChecked()?1:0);
    }
}


void MainWindow::on_RegisterButton_clicked()
{
    /*this->hide();//当前窗体隐藏
    Register *registerWindow = new Register();//新建子窗体
    connect(registerWindow,&Register::BacktoMainWindow,this,&QWidget::show);//关联子窗体关闭信号与父窗体显示事件
    registerWindow->setAttribute(Qt::WA_DeleteOnClose);//设置子窗体属性：关闭即销毁
    registerWindow->show();//显示子窗体*/
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

void MainWindow::loginCallback_slot(long long id){
    disconnect(&ClientSocket::getInstance(),SIGNAL(login_callback(long long)),this,SLOT(loginCallback_slot(long long)));
    if(id>0){
        usernow::setId(QString::number(id));
        if (ui->checkBox_2->isChecked()==true){
            // 进入患者主界面
            QMessageBox::information(NULL, "登陆成功", "登陆成功！！！", QMessageBox::Yes);
            this->close();
            Patient *patientWidget = new Patient();
            patientWidget->show();
        }
        else if(ui->checkBox->isChecked()==true){
            // 进入医生主界面
            this->close();
            QMessageBox::information(NULL, "登陆成功", "登陆成功！！！", QMessageBox::Yes);
            Doctor *doctorWidget = new Doctor();
            doctorWidget->show();
        }
    }
    else{
        QMessageBox::warning(this,"error","用户名或者密码错误！！");
        ui->password->clear();
        ui->username->setFocus();
    }
}
