#include "eventadder.h"
#include "ui_eventadder.h"

eventadder::eventadder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eventadder)
{
    ui->setupUi(this);
}

eventadder::~eventadder()
{
    delete ui;
}
