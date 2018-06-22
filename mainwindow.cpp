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

#include "event_adder.h"
#include "modifydial.h"
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("To Do List");
   QDate date;
   QString d=QDate::currentDate().toString("dd/MM/yyyy");
   ui->label_3->setText(QDate::currentDate().toString("dddd dd MMMM yyyy"));
   QTimer *timer = new QTimer(this);
       connect(timer, SIGNAL(timeout()), this , SLOT(refreshtime()));


       timer->start(1000);
       ui->tableWidget->setRowCount(15);
       ui->tableWidget->setColumnCount(6);
       ui->tableWidget->setHorizontalHeaderLabels(cols_description);
       ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
       ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
       ui->label_2->setText(QTime::currentTime().toString() );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{  int res;
    QString name,date_catch;
    QDate date_as_qdate;

    event_adder add(this);

    add.setWindowTitle("Add your event");
    res=add.exec();
    date_catch=add.date_catch().toString();
    date_as_qdate=add.date_catch();

    name= add.event_name();

    if(res==QDialog::Rejected){
        return;
    }
    else if(name=="hello"){
    QMessageBox::information(this,"Take a look","I won't add the event until the name field is empty");

  }
   else if(name!="hello"){
        if(column==0){
           ui->tableWidget->setItem(row,0,new QTableWidgetItem(name+" \t*"+"\n"+date_catch));
        archivio_(date_as_qdate,name);
          }
        else{
                ui->tableWidget->setItem(row, column, new QTableWidgetItem(name+"\n"+date_catch));
                archivio_(date_as_qdate,name);

    }

}


    void MainWindow::on_toolButton_clicked()
    {
        for(int a=0;a<ui->tableWidget->rowCount(); ++a ){
        ui->tableWidget->setItem(a, ui->tableWidget->currentColumn(), new QTableWidgetItem(""));
        }
    }

    void Dialog::on_pushButton_2_clicked()
    {
        QString new_name, date_catch;

        modifydial dial(this);
        dial.exec();
        new_name=dial.modify_name();
        date_catch=dial.date_catch();

        int row,col;
        col=ui->tableWidget->currentColumn();
        row=ui->tableWidget->currentRow();
        if(new_name=="hello"){

            return;

        }
        else if(new_name!="hello" ){
            if(col==0 ){
                ui->tableWidget->setItem(row,col, new QTableWidgetItem(new_name+"*\n"+ date_catch));
            }
            else{
            ui->tableWidget->setItem(row,col, new QTableWidgetItem(new_name+"\n"+ date_catch));
            }
        }

    }
    void MainWindow::on_pushButton_3_clicked()
    {

        reject();
    }

    void Dialog::on_pushButton_4_clicked()
    {
         ui->tableWidget->setItem(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn(), new QTableWidgetItem(""));
    }



    void MainWindow::on_pushButton_5_clicked()
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
         refreshdate();
         ui->label_2->setText(time.toString());
         print_on_screen();

    }
    void MainWindow::refreshdate(){


        ui->label_3->setText(QDate::currentDate().toString("dddd dd MMMM yyyy"));

    }
    void Dialog::archivio_(QDate date, QString name){
        archivio.insert(pair<QDate, QString>(date,name));

    }

    void MainWindow::print_on_screen(){

        multimap <QDate, QString> :: iterator itr;
            qDebug()<< "\nThe multimap element is : \n";
            qDebug()<< "\tKEY\tELEMENT\n";
             for (itr = archivio.begin(); itr != archivio.end(); ++itr)
            {
                qDebug()<<  '\t' << itr->first
                      <<  '\t' << itr->second << '\n';
            }
            qDebug()<< endl;
    }




