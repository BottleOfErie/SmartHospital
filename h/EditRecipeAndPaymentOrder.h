#ifndef EDITRECIPEANDPAYMENTORDER_H
#define EDITRECIPEANDPAYMENTORDER_H

#include <QMainWindow>

#include <net/NetUtils.h>

namespace Ui {
class EditRecipeAndPaymentOrder;
}

class EditRecipeAndPaymentOrder : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditRecipeAndPaymentOrder(QMainWindow *parent = nullptr);
     //void paintEvent(QPaintEvent *e);
    ~EditRecipeAndPaymentOrder();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void insertRecipe();
    void setPrescription_slot(NetUtils::Prescription data);

private:
    Ui::EditRecipeAndPaymentOrder *ui;
};

#endif // EDITRECIPEANDPAYMENTORDER_H
