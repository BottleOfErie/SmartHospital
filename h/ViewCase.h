#ifndef VIEWCASE_H
#define VIEWCASE_H

#include <QWidget>

namespace Ui {
class ViewCase;
}

class ViewCase : public QWidget
{
    Q_OBJECT

public:
    explicit ViewCase(QWidget *parent = nullptr);
    ~ViewCase();

private:
    Ui::ViewCase *ui;
};

#endif // VIEWCASE_H
