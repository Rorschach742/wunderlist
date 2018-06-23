#include "modifydial.h"
#include "ui_modifydial.h"

modifydial::modifydial(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifydial)
{
    ui->setupUi(this);
     setWindowTitle("Modify what you need");
}

modifydial::~modifydial()
{
    delete ui;
}
void modifydial::on_buttonBox_accepted()
{
    return accept();
}

void modifydial::on_buttonBox_rejected()
{
    return reject();
}
QString modifydial::modify_name(){
    if(ui->lineEdit->text()==""){
        return "hello";

    }
    else{
        return ui->lineEdit->text();
    }


}
QDate modifydial::date_catch(){
    return ui->dateEdit->date();

}




