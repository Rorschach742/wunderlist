#include "modifydial.h"
#include "ui_modifydial.h"

modifydial::modifydial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifydial)
{
    ui->setupUi(this);
}

modifydial::~modifydial()
{
    delete ui;
}
