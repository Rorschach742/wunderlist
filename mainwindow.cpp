#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <QtGui>
#include <qstring.h>
#include <QtCore>
#include <QHeaderView>
#include <QDate>
#include <map>
#include <QDebug>
#include <iostream>

#include "eventadder.h"
#include "modifydial.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   QTimer *timer = new QTimer(this);
    timer->start(100);


   QStringList cols_description=(QStringList()<<"Starred"<<"Work"<<"Birthday"<<"Meeting"<<"Anniversary"<<"Sport"<<"Various");
   setWindowTitle("To Do List");
   QString d=QDate::currentDate().toString("dd/MM/yyyy");
   ui->label->setText(QDate::currentDate().toString("dddd dd MMMM yyyy"));


   ui->tableWidget->setRowCount(15);
   ui->tableWidget->setColumnCount(6);
   ui->tableWidget->setHorizontalHeaderLabels(cols_description);
   ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
   ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    connect(timer, SIGNAL(timeout()), this , SLOT(refreshtime()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{  int res;
    QString name,date_catch;
    QDate date_as_qdate;

    eventadder add(this);

    add.setWindowTitle("Add your event");
    res=add.exec();
    date_catch=add.date_catch().toString();
    date_as_qdate=add.date_catch();

    name= add.name();

    if(res==QDialog::Rejected){
        return;
    }
    else if(name=="hello"){
    QMessageBox::information(this,"Take a look","I won't add the event until the name field is empty");

  }
   else if(name!="hello"){
        if(column==0){
           ui->tableWidget->setItem(row,0,new QTableWidgetItem(name+" \t*"+"\n"+date_catch));
        //archivio_(date_as_qdate,name);
           reg(1,map1,date_as_qdate,name);
          }
        else{
                ui->tableWidget->setItem(row, column, new QTableWidgetItem(name));//+"\n"+date_catch));
               // archivio_2(date_as_qdate,name);
                reg(2,map2,date_as_qdate,name);


    }

}}

void MainWindow::on_toolButton_clicked()
{
        for(int a=0;a<ui->tableWidget->rowCount(); ++a ){
        ui->tableWidget->setItem(a, ui->tableWidget->currentColumn(), new QTableWidgetItem(""));

        }
}

void MainWindow::on_pushButton_clicked()
    {
        QString new_name, date_as_str;
        QDate date_as_qdate;

        modifydial dial(this);
        dial.exec();
        new_name=dial.modify_name();
        date_as_qdate=dial.date_catch();
        date_as_str=dial.date_catch().toString();

        int row,col;
        col=ui->tableWidget->currentColumn();
        row=ui->tableWidget->currentRow();
        if(new_name=="hello"){

            return;

        }
        else if(new_name!="hello" ){
            if(col==0 ){
                ui->tableWidget->setItem(row,col, new QTableWidgetItem(new_name+"*\n"+ date_as_str));
                //archivio_(date_as_qdate,new_name);
                registro(1,map1,date_as_qdate,new_name);
            }
            else{
            ui->tableWidget->setItem(row,col, new QTableWidgetItem(new_name+"\n"+ date_as_str));
            }
        }

    }


void MainWindow::on_pushButton_2_clicked()
{
  ui->tableWidget->setItem(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn(), new QTableWidgetItem(""));


}



void MainWindow::on_pushButton_3_clicked()
{   if(ui->lineEdit->text().isEmpty()){
    QMessageBox::information(this,"Take a look","I can't add a name-less category! ");
    }
    else{
        ui->tableWidget->insertColumn(head_cols);
        ui->tableWidget->setHorizontalHeaderItem(head_cols,new QTableWidgetItem(ui->lineEdit->text()));

        ui->lineEdit->clear();

        head_cols =head_cols+1;
    }
}
void MainWindow::refreshtime(){
         QTime time = QTime::currentTime();
         ui->label_2->setText(time.toString());
         refreshdate();
         /*qDebug()<< "\nThe multimap element is : \n";
         qDebug()<< "\tKEY\tELEMENT\n";
         for ( auto itr = map1.begin(); itr != map1.end(); ++itr)
                 {
                     qDebug()<<  '\t' << itr->first
                           <<  '\t' << itr->second << '\n';
                 }
         qDebug()<< endl;
         qDebug()<< "\nThe multimap 2 element is : \n";
         qDebug()<< "\tKEY\tELEMENT\n";
         for ( auto itr = map2.begin(); itr != map2.end(); ++itr)
                 {
                     qDebug()<<  '\t' << itr->first
                           <<  '\t' << itr->second << '\n';
                 }
         qDebug()<< endl;


*/

        print_on_screen();

}
void MainWindow::refreshdate(){

    ui->label->setText(QDate::currentDate().toString("dddd dd MMMM yyyy"));
}
void MainWindow::archivio_(QDate date, QString name){
    map1.insert(pair<QDate, QString>(date,name));


}
void MainWindow::archivio_2(QDate date, QString name){
    map2.insert(pair<QDate, QString>(date,name));


}

void MainWindow::print_on_screen(){
   // map1<int,multimap <QDate, QString>> :: iterator tr;
    qDebug()<< "\nThe multimap element is : \n";
    qDebug()<< "\tKEY\tELEMENT\n";
    for (auto itr = reg.begin(); itr != reg.end(); ++itr)
            {
                qDebug()<<  '\t' << itr->first
                      <<  '\t' << itr->second << '\n';
            }
            qDebug()<< endl;

}


void MainWindow::registro(int i, std::multimap<QDate,QString>,QDate date, QString name){
    if(i==1){
        map1.insert(pair<QDate, QString>(date,name));
    reg.insert(pair<int,std::multimap<QDate,QString>>(1,map1));

    }
    else{
         map2.insert(pair<QDate, QString>(date,name));
        reg.insert(pair<int,std::multimap<QDate,QString>>(2,map2));
    }
}





