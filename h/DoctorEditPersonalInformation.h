#ifndef DOCTOREDITPERSONALINFORMATION_H
#define DOCTOREDITPERSONALINFORMATION_H
#include <QWidget>
namespace Ui {
class DoctorEditPersonalInformation;
}

class DoctorEditPersonalInformation : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorEditPersonalInformation(QWidget *parent = nullptr);
    ~DoctorEditPersonalInformation();

public slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::DoctorEditPersonalInformation *ui;
};

#endif // DOCTOREDITPERSONALINFORMATION_H
