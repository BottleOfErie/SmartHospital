#include "h/ViewCase.h"
#include "ui_ViewCase.h"
#include <h/Patient.h>
#include "h/usernow.h"


ViewCase::ViewCase(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewCase)
{
    ui->setupUi(this);
}

ViewCase::~ViewCase()
{
    delete ui;
}
void ViewCase::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ViewCase::on_pushButton_clicked()
{
    this->close();
    auto patient= new Patient;
    patient->show();
}

