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
    void paintEvent(QPaintEvent *e);
    ~ViewCase();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ViewCase *ui;
};

#endif // VIEWCASE_H
