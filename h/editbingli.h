#ifndef EDITBINGLI_H
#define EDITBINGLI_H
#include <QWidget>

namespace Ui {
class Editbingli;
}

class Editbingli : public QWidget
{
    Q_OBJECT

public:
    explicit Editbingli(QWidget *parent = nullptr);
    ~Editbingli();

public slots:
    void on_pushButton_clicked();
    void on_pushButton2_clicked();

private:
    Ui::Editbingli *ui;
};


#endif // EDITBINGLI_H
