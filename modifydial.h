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
    QString modify_name();
    QDate date_catch();

    bool on_radioButton_clicked();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


private:
    Ui::modifydial *ui;
};

#endif // MODIFYDIAL_H
