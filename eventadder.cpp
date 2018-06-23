#include "eventadder.h"
#include "ui_eventadder.h"

eventadder::eventadder(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eventadder)
{
    ui->setupUi(this);
    QString d=QDate::currentDate().toString("dd/MM/yyyy");
    ui->dateEdit->setDate(QDate::currentDate());
}

eventadder::~eventadder()
{
    delete ui;
}
QDate eventadder::date_catch(){

    return ui->dateEdit->date();
}
QString eventadder::name(){
    if(ui->lineEdit->text()==""){
        return "hello";

    }
    else{
        return ui->lineEdit->text();
    }
}
