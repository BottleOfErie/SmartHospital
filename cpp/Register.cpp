#include "ui_Register.h"
#include <h/Register.h>
#include <h/mainwindow.h>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QPainter>
#include "net/ClientSocket.h"

Register::Register(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(false);
    ui->checkBox_2->setChecked(false);
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
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
    if(ui->lineEdit_2->text()=="")//判断用户名和密码是否为空
        QMessageBox::warning(this,"","姓名不能为空!!");
    else if(username=="")
        QMessageBox::warning(this,"","身份证号不能为空!!");
    else if (password=="")
        QMessageBox::warning(this,"","密码不能为空!!");
    else if (password!=ui->lineEdit->text())
        QMessageBox::warning(this,"","两次输入的密码不相同!!");
    else if (ui->radioButton->isChecked()==false && ui->radioButton_2->isChecked()==false){
        QMessageBox::warning(this,"ERROR","请选择你的性别！！");
    }
    else{
        if(ui->checkBox->isChecked()==false && ui->checkBox_2->isChecked()==false){
            QMessageBox::warning(this,"ERROR","请选择你是医生还是患者！！");
        }
        else if (ui->checkBox->isChecked()==true){
            connect(&ClientSocket::getInstance(),SIGNAL(register_callback(long long)),this,SLOT(registerCallbackSlot(long long)));
            ClientSocket::getInstance().registerAsDoctor(username,password);
        }
        else{
            connect(&ClientSocket::getInstance(),SIGNAL(register_callback(long long)),this,SLOT(registerCallbackSlot(long long)));
            ClientSocket::getInstance().registerAsPatient(username,password);
        }
        //ClientSocket::getInstance().regist
        /*if(query.first()){
            QMessageBox::warning(this,"ERROR","用户名重复");//如果用户名重复，则提示用户名重复
        }else if (query.exec(i)) {//如果用户名不重复，添加数据进入数据库
            QMessageBox::information(this,"提示","注册成功！！",QMessageBox::Yes);
            this->close();
            MainWindow *mainWindow=new MainWindow();
            mainWindow->show();
        }
        else
            QMessageBox::warning(this,"ERROR","注册失败，请重试！！");*/
    }
}

void Register::registerCallbackSlot(long long id){
    if(id<=0){
        QMessageBox::warning(this,"ERROR","注册失败，请重试！！");
    }
    else{
        QMessageBox::information(this,"提示","注册成功！！",QMessageBox::Yes);
        if (ui->checkBox->isChecked()==true){
            ClientSocket::getInstance().submitDoctorData((NetUtils::DoctorData){
                id,ui->lineEdit_2->text(),ui->username->text(),
                ui->lineEdit_3->text(),
                ui->radioButton->isChecked()?0:1,
                ui->dateEdit->date().toString("yyyy-MM-dd"),
                ui->phone->text(),ui->comboBox->currentText(),
                ui->organization->text(),
                ui->lineEdit_4->text()
                });
            this->close();
            MainWindow *mainWindow=new MainWindow();
            mainWindow->show();
        }
        else if(ui->checkBox_2->isChecked()==true){
            ClientSocket::getInstance().submitPatientData((NetUtils::PatientData){
                id,ui->lineEdit_2->text(),ui->username->text(),
                ui->radioButton->isChecked()?0:1,
                ui->dateEdit->date().toString("yyyy-MM-dd"),
                ui->phone->text(),
                ui->textEdit->toPlainText()
            });
            this->close();
            MainWindow *mainWindow=new MainWindow();
            mainWindow->show();
        }
    }

}

void Register::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void Register::on_radioButton_toggled(bool checked)
{
    if (checked) {
        ui->radioButton_2->setChecked(false);
    }
}

void Register::on_radioButton_2_toggled(bool checked)
{
    if (checked) {
        ui->radioButton->setChecked(false);
    }
}
