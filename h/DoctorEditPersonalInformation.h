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

private:
    Ui::DoctorEditPersonalInformation *ui;
};

#endif // DOCTOREDITPERSONALINFORMATION_H
