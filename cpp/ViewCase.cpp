#include "h/ViewCase.h"
#include "ui_ViewCase.h"

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
