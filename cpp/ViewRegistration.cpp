#include "h/ViewRegistration.h"
#include "ui_ViewRegistration.h"

#include <QPainter>
#include <QStyleOption>

ViewRegistration::ViewRegistration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewRegistration)
{
    ui->setupUi(this);
}

ViewRegistration::~ViewRegistration()
{
    delete ui;
}
void ViewRegistration::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
