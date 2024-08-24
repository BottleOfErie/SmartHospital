#include "h/EditRecipeAndPaymentOrder.h"
#include "ui_EditRecipeAndPaymentOrder.h"

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
