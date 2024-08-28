#ifndef EDITRECIPEANDPAYMENTORDER_H
#define EDITRECIPEANDPAYMENTORDER_H

#include <QMainWindow>
#include <QMap>
#include <QTableWidget>
#include <net/NetUtils.h>

namespace Ui {
class EditRecipeAndPaymentOrder;
}

class EditRecipeAndPaymentOrder : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditRecipeAndPaymentOrder(QMainWindow *parent = nullptr);
    void paintEvent(QPaintEvent *e);
    ~EditRecipeAndPaymentOrder();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void insertRecipe();
    void setMedicine_slot(NetUtils::Medicine data);
    void setPrescription_slot(NetUtils::Prescription data);
    void deleteRecipe();
    void getPatientName_slot(NetUtils::Appointment data);
    void addNameItem_slot(NetUtils::PatientData data);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
    Ui::EditRecipeAndPaymentOrder *ui;
    QMap<long,QString> idToTime;
    QMap<QString,long> nametoId;
    QMap<QString, QList<QStringList>> patientPrescriptions;
    int row;
    QMap<QString,long> medicineNametoId;
    void submit();
    bool CheckEmpty();
};

#endif // EDITRECIPEANDPAYMENTORDER_H
