#include "ui_Register.h"
#include <h/Register.h>
#include <h/mainwindow.h>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

void Register::on_backButton_clicked()
{
    this->close(); // 关闭对话框
    MainWindow *mainWindow=new MainWindow();
    mainWindow->show();
}

void Register::on_checkBox_toggled(bool checked)
{
    if (checked) {
        ui->checkBox_2->setChecked(false);
    }
}

void Register::on_checkBox_2_toggled(bool checked)
{
    if (checked) {
        ui->checkBox->setChecked(false);
    }
}

void Register::on_registerButton_clicked()
{
    QString username=ui->username->text();//获取输入的信息
    QString password=ui->password->text();
    if(username=="")//判断用户名和密码是否为空
        QMessageBox::warning(this,"","用户名不能为空");
    else if (password=="")
        QMessageBox::warning(this,"","密码不能为空");
    else{
        //TODO 数据库对接
        QString i =QString("insert into user_table values('%1','%2');").arg(username).arg(password);//插入一条信息到数据库的user_table表中
        QString s =QString("select * from user_table where name = '%1'").arg(username);//在user表中查询是否有存在的用户名
        QSqlQuery query;
        query.exec(s);
        if(query.first()){
            QMessageBox::warning(this,"ERROR","用户名重复");//如果用户名重复，则提示用户名重复
        }else if (query.exec(i)) {//如果用户名不重复，添加数据进入数据库
            QMessageBox::information(this,"提示","注册成功！！",QMessageBox::Yes);
            this->close();
            MainWindow *mainWindow=new MainWindow();
            mainWindow->show();
        }
        else
            QMessageBox::warning(this,"ERROR","注册失败，请重试！！");
    }
}
