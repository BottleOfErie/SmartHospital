#ifndef VIEWREGISTRATION_H
#define VIEWREGISTRATION_H

#include <QWidget>

namespace Ui {
class ViewRegistration;
}

class ViewRegistration : public QWidget
{
    Q_OBJECT

public:
    explicit ViewRegistration(QWidget *parent = nullptr);
    ~ViewRegistration();

private:
    Ui::ViewRegistration *ui;
};

#endif // VIEWREGISTRATION_H
