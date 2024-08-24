#include "h/EditRecipeAndPaymentOrder.h"
#include "ui_EditRecipeAndPaymentOrder.h"
#include "h/Doctor.h"
EditRecipeAndPaymentOrder::EditRecipeAndPaymentOrder(QMainWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::EditRecipeAndPaymentOrder)
{
    ui->setupUi(this);
}

EditRecipeAndPaymentOrder::~EditRecipeAndPaymentOrder()
{
    delete ui;
}

void EditRecipeAndPaymentOrder::on_pushButton_2_clicked()
{
    this->close();
    auto doctor = new Doctor;
    doctor->show();
}
