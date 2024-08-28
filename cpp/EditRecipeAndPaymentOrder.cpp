#include "h/EditRecipeAndPaymentOrder.h"
#include "ui_EditRecipeAndPaymentOrder.h"
#include "h/Doctor.h"
#include "h/usernow.h"
#include <QMessageBox>
#include <QPainter>
#include <QStyleOption>
#include <net/ClientSocket.h>
EditRecipeAndPaymentOrder::EditRecipeAndPaymentOrder(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::EditRecipeAndPaymentOrder)
{
    ui->setupUi(this);
    ui->lineEdit_3->setReadOnly(true);
    connect(&ClientSocket::getInstance(),SIGNAL(appointment_callback(NetUtils::Appointment)),this,SLOT(getPatientName_slot(NetUtils::Appointment)));
    ClientSocket::getInstance().getAppointmentsByDoctor(usernow::getId().toLong());
    connect(&ClientSocket::getInstance(),SIGNAL(patient_callback(NetUtils::PatientData)),this,SLOT(addNameItem_slot(NetUtils::PatientData)));
    connect(ui->action_2, &QAction::triggered, this,&EditRecipeAndPaymentOrder::insertRecipe);
    connect(ui->action_3, &QAction::triggered, this,&EditRecipeAndPaymentOrder::deleteRecipe);
    connect(&ClientSocket::getInstance(),SIGNAL(medicine_callback(NetUtils::Medicine)),this,SLOT(setMedicine_slot(NetUtils::Medicine)));
    connect(&ClientSocket::getInstance(),SIGNAL(prescription_callback(NetUtils::Prescription)),this,SLOT(setPrescription_slot(NetUtils::Prescription)));
}
EditRecipeAndPaymentOrder::~EditRecipeAndPaymentOrder()
{
    delete ui;
}

void EditRecipeAndPaymentOrder::setPrescription_slot(NetUtils::Prescription data){

}

void EditRecipeAndPaymentOrder::setMedicine_slot(NetUtils::Medicine data){
    medicineNametoId.insert(data.name,data.medicineId);
    QTableWidgetItem *countItem = ui->tableWidget->item(row, 1);
    bool ok;
    int cnt=countItem->text().toInt(&ok);
    if(!ok){return;}
    float price=data.price*cnt;
    ui->tableWidget->item(row, 3)->setText(QString::number(price));
    patientPrescriptions[ui->comboBox->currentText()][row][3]=ui->tableWidget->item(row, 3)->text();
}

void EditRecipeAndPaymentOrder::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("选择操作");           // 设置弹窗标题
    msgBox.setText("是否提交药方？提交后无法再更改");    // 设置弹窗内容
    msgBox.setIcon(QMessageBox::Question);        // 设置弹窗图标
    msgBox.setWindowFlag(Qt::WindowCloseButtonHint, false);

    // 添加两个按钮选项
    QPushButton *yes = msgBox.addButton(tr("YES"), QMessageBox::ActionRole);
    msgBox.addButton(tr("NO"), QMessageBox::ActionRole);

    // 显示消息框并等待用户选择
    msgBox.exec();

    // 判断用户选择了哪个按钮
    if (msgBox.clickedButton() == yes) {
        if(CheckEmpty()){
            QMessageBox::warning(this,"","还有信息未填写!!");
            return;
        }
        submit();
    }
}
void EditRecipeAndPaymentOrder::submit(){
    long id=nametoId.find(ui->comboBox->currentText()).value();
    QString date=idToTime.find(id).value();

    for(int i=0;i<ui->tableWidget->rowCount();i++){
        QString medicineName=ui->tableWidget->item(i, 0)->text();
        QString cnt=ui->tableWidget->item(i, 1)->text();
        QString advice=ui->tableWidget->item(i, 2)->text();
        ClientSocket::getInstance().submitPrescription(NetUtils::Prescription{
                id,
                usernow().getId().toLong(),
                date,
                medicineNametoId[ui->tableWidget->item(i, 0)->text()],
                ui->tableWidget->item(i, 1)->text().toInt(),
                ui->tableWidget->item(i, 2)->text(),
        });
    }
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}
bool EditRecipeAndPaymentOrder::CheckEmpty(){
    for (int i = 0; i < ui->tableWidget->rowCount(); ++i) {
        for (int j = 0; j < 4; ++j) {
            QTableWidgetItem *item = ui->tableWidget->item(i, j);
            if (item->text()=="") {
                return true;
            }
        }
    }
}

void EditRecipeAndPaymentOrder::insertRecipe(){
    int newRow = ui->tableWidget->rowCount(); // 获取当前行数
    ui->tableWidget->insertRow(newRow); // 在末尾插入新行
    ui->tableWidget->setVerticalHeaderItem(newRow, new QTableWidgetItem("药品"+QString::number(newRow+1)));
    QString nowPatient = ui->comboBox->currentText();
    patientPrescriptions[nowPatient].append({"","","",""});
    qDebug()<<ui->tableWidget->rowCount()<<newRow<<ui->tableWidget->columnCount();
    ui->tableWidget->setItem(newRow, 0, new QTableWidgetItem(""));// 将信息插入到新行的第一列
    ui->tableWidget->setItem(newRow, 1, new QTableWidgetItem(""));
    ui->tableWidget->setItem(newRow, 2, new QTableWidgetItem(""));
    ui->tableWidget->setItem(newRow, 3, new QTableWidgetItem(""));
    QTableWidgetItem *item = ui->tableWidget->item(newRow, 3);
    qDebug()<<item;
    // 设置该单元格为只读
    if (item) {
        item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    }
}

void EditRecipeAndPaymentOrder::deleteRecipe(){
    int rowCount = ui->tableWidget->rowCount();
    QString name;
    if (rowCount > 0) {
        name=ui->tableWidget->item(rowCount-1, 0)->text();
        ui->tableWidget->removeRow(rowCount - 1);
    }
    patientPrescriptions.remove(name);
}

void EditRecipeAndPaymentOrder::on_pushButton_2_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("选择操作");           // 设置弹窗标题
    msgBox.setText("药方还未提交，是否提交？提交后无法再更改");    // 设置弹窗内容
    msgBox.setIcon(QMessageBox::Question);        // 设置弹窗图标
    msgBox.setWindowFlag(Qt::WindowCloseButtonHint, false);

    // 添加两个按钮选项
    QPushButton *yes = msgBox.addButton(tr("YES"), QMessageBox::ActionRole);
    msgBox.addButton(tr("NO"), QMessageBox::ActionRole);

    // 显示消息框并等待用户选择
    msgBox.exec();
    if (msgBox.clickedButton() == yes) {
        if(CheckEmpty()){
            QMessageBox::warning(this,"","还有信息未填写!!");
            return;
        }
        submit();
    }
    else{
        this->close();
        auto doctor = new Doctor;
        doctor->show();
    }
}

void EditRecipeAndPaymentOrder::getPatientName_slot(NetUtils::Appointment data){
    idToTime.insert(data.patientId,data.time);
    ClientSocket::getInstance().getPatientById(data.patientId);
}

void EditRecipeAndPaymentOrder::addNameItem_slot(NetUtils::PatientData data){
    nametoId.insert(data.name,data.id);
    QList<QStringList> list;
    list.clear();
    patientPrescriptions.insert(data.name,list);
    ui->comboBox->addItem(data.name);
}

void EditRecipeAndPaymentOrder::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


void EditRecipeAndPaymentOrder::on_comboBox_currentIndexChanged(const QString &arg1)
{
    qDebug()<<114514;
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->lineEdit_3->setText(idToTime.find(nametoId.find(arg1).value()).value());
    QList<QStringList>prescriptionList=patientPrescriptions.find(arg1).value();
    for (int i=0;i<prescriptionList.size();i++){
        QStringList medicine=prescriptionList[i];
        ui->tableWidget->insertRow(i); // 在末尾插入新行
        ui->tableWidget->setVerticalHeaderItem(i, new QTableWidgetItem("药品"+QString::number(i+1)));
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(medicine[0]));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(medicine[1]));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(medicine[2]));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(medicine[3]));
        QTableWidgetItem *item = ui->tableWidget->item(i, 3); // 第1行，第2列 (索引从0开始)
        // 设置该单元格为只读
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    }
}

void EditRecipeAndPaymentOrder::on_tableWidget_itemChanged(QTableWidgetItem *item)
{
    QString nowPatient = ui->comboBox->currentText();
    row = item->row();
    int column = item->column();
    if (column==0){
        ClientSocket::getInstance().getMedicineByName(item->text());
    }
    for (int i=0;i<4;i++){
        patientPrescriptions[nowPatient][row][i]=ui->tableWidget->item(row, i)->text();
    }
}

