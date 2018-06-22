#ifndef MODIFYDIAL_H
#define MODIFYDIAL_H

#include <QDialog>

namespace Ui {
class modifydial;
}

class modifydial : public QDialog
{
    Q_OBJECT

public:
    explicit modifydial(QWidget *parent = 0);
    ~modifydial();

private:
    Ui::modifydial *ui;
};

#endif // MODIFYDIAL_H
