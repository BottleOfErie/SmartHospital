#ifndef EDITMEDICALRECORD_H
#define EDITMEDICALRECORD_H

#include <QWidget>

namespace Ui {
class EditMedicalRecord;
}

class EditMedicalRecord : public QWidget
{
    Q_OBJECT

public:
    explicit EditMedicalRecord(QWidget *parent = nullptr);
    ~EditMedicalRecord();


private slots:
    void on_pushButton_2_clicked();

private:
    Ui::EditMedicalRecord *ui;
};

#endif // EDITMEDICALRECORD_H
