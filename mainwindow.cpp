#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qmessagebox.h>
#include <QtGui>
#include <qstring.h>
#include <QtCore>
#include <QHeaderView>
#include <QDate>

#include <QDebug>
#include <iostream>
#include "eventadder.h"
#include "modifydial.h"
#include "event.h"


using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   QTimer *timer = new QTimer(this);
   timer->start(1000);
   QTime time = QTime::currentTime();

   QStringList cols_description=(QStringList()<<"Starred"<<"Work"<<"Birthday"<<"Meeting"<<"Anniversary"<<"Sport");
   setWindowTitle("To Do List");
   QString d=QDate::currentDate().toString("dd/MM/yyyy");
   ui->label->setText(QDate::currentDate().toString("dddd dd MMMM yyyy"));
   ui->label_2->setText(time.toString());
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


    eventadder add(this);
    add.setWindowTitle("Add your event");
    res=add.exec();      
    QDate date_catch=add.date_catch();
    QString name= add.name();
    if(res==QDialog::Rejected){
        return;
      }
    else if(name=="hello"){
        QMessageBox::information(this,"Take a look","I won't add the event until the name field is empty");
      }
    else if(name!="hello"){
        if(column==0){
           ui->tableWidget->setItem(row,0,new QTableWidgetItem(date_catch.toString() +" \n*"+name));
           std::unique_ptr<Event>mypoint( new Event (date_catch,name,true,false,row,column));
           cat.appaia(column,*mypoint);
          }
        else{
            ui->tableWidget->setItem(row, column, new QTableWidgetItem(date_catch.toString()+" \n"+name));
            std::unique_ptr<Event>mypoint( new Event (date_catch,name,false,false,row,column));
            cat.appaia(column,*mypoint);
            }
      }
}

void MainWindow::on_toolButton_clicked()
{
        for(int a=0;a<ui->tableWidget->rowCount(); ++a ){
            ui->tableWidget->setItem(a, ui->tableWidget->currentColumn(), new QTableWidgetItem(""));
            for(auto itr=cat.archivio.begin(); itr!= cat.archivio.end();++itr){
                if(itr->first==ui->tableWidget->currentColumn()){
                    cat.archivio.erase(itr);
                    break;
                  }
              }
          }
}

void MainWindow::on_pushButton_clicked()
{
  QString new_name, date_as_str;
  QDate date_as_qdate;
  bool chec_starred_state;
  modifydial dial(this);
  dial.exec();
  new_name=dial.modify_name();
  date_as_qdate=dial.date_catch();
  date_as_str=dial.date_catch().toString();
  chec_starred_state=dial.on_radioButton_clicked();
  int row,col,a;
  col=ui->tableWidget->currentColumn();
  row=ui->tableWidget->currentRow();
  if(new_name=="hello"){
            return;
        }
  else if(new_name!="hello" ){
      if(chec_starred_state){
        /*  std::unique_ptr<Event>swap_ptr;
          for(auto itr=cat.archivio.begin();itr!=cat.archivio.end();++itr){
              if(itr->second.getPosX()==row &&itr->second.getPosY()==col){
                  cat.archivio.erase(itr);
                      }
            }
          std::pair<std::multimap<int, Event>::iterator,std::multimap<int, Event>::iterator> r = cat.archivio.equal_range(0);
          for (auto it = r.first; it != r.second; ++it) {
              a=it->second.getPosX();
              qDebug()<< it->first << " : ";
              it->second.details();
            }
        }*/
      //auto t= ui->tableWidget->itemAt(row,0);
      for(int i=0;i<ui->tableWidget->rowCount();++i){
          auto g=ui->tableWidget->item(i,0);
          auto y=ui->tableWidget->item(i,0);
          auto t=ui->tableWidget->item(i,0);
          if(!g|| g->text().isEmpty()){
              ui->tableWidget->setItem(i,0, new QTableWidgetItem(new_name+"\n"+ date_as_str));
              std::unique_ptr<Event>new_ev_ptr( new Event (date_as_qdate,new_name,true,false,row,a));
              cat.appaia(col,*new_ev_ptr);
              i=60;

            }
        }
     // ui->tableWidget->setItem(row,0, new QTableWidgetItem(new_name+"\n"+ date_as_str));
      //ui->tableWidget->setItem(row,col,new QTableWidgetItem(""));

    }}
  else{
      ui->tableWidget->setItem(row,col, new QTableWidgetItem(new_name+"\n"+ date_as_str));
      ui->tableWidget->setItem(row,col,new QTableWidgetItem(""));
    }
}




void MainWindow::on_pushButton_2_clicked()
{
  ui->tableWidget->setItem(ui->tableWidget->currentRow(), ui->tableWidget->currentColumn(), new QTableWidgetItem(""));
  for(auto itr=cat.archivio.begin(); itr!= cat.archivio.end();++itr){
      if(itr->second.getPosX()==ui->tableWidget->currentRow() && itr->first==ui->tableWidget->currentColumn()){
          cat.archivio.erase(itr);
         break;
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
  if(ui->lineEdit->text().isEmpty()){
      QMessageBox::information(this,"Take a look","I can't add a name-less category! ");
    }
    else{
        ui->tableWidget->insertColumn(head_cols);
        ui->tableWidget->setHorizontalHeaderItem(head_cols,new QTableWidgetItem(ui->lineEdit->text()));
        ui->lineEdit->clear();
        on_tableWidget_cellDoubleClicked(0,head_cols);
    }
}
void MainWindow::refreshtime(){
  QTime time = QTime::currentTime();
  ui->label_2->setText(time.toString());
  refreshdate();
  print_on_screen();

}
void MainWindow::refreshdate(){

    ui->label->setText(QDate::currentDate().toString("dddd dd MMMM yyyy"));
}

void MainWindow::print_on_screen(){

    qDebug()<< "****************************************"
               "\nThe multimap of starred events is : \n";

    for ( auto itr = cat.archivio.begin(); itr != cat.archivio.end(); ++itr)
            {
                /*qDebug()<<  '\t' <<"\n"<<itr->first<<"\n"<<(*(itr->second)).details() ;// <<*(itr->second).getposY ;
               */ itr->second.details();
                 qDebug()<<itr->second.getPosX();
            }
    //qDebug()<< endl;

}








