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
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
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
{   int res;
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
    for(int i=0;i<ui->tableWidget->rowCount();++i){
        auto f=ui->tableWidget->item(i,ui->tableWidget->currentColumn());
        if(!f|| f->text().isEmpty()){
            ui->tableWidget->setItem(i, column, new QTableWidgetItem(name));           
            Event *e=new Event(name,false,false,column);
            cat.appaia(date_catch,*e);
            delete e;
            break;
            }
      }
 ordering(ui->tableWidget->currentColumn());
}

void MainWindow::on_toolButton_clicked()
{

QStringList list_to_del;
for(int r=0;r<ui->tableWidget->rowCount();++r){
    if(!ui->tableWidget->item(r,ui->tableWidget->currentColumn())->text().isEmpty()){
    list_to_del.append(ui->tableWidget->item(r,ui->tableWidget->currentColumn())->text());
      }
  }
for(int r=0;r<ui->tableWidget->rowCount();++r){
    ui->tableWidget->setItem(r,ui->tableWidget->currentColumn(), new QTableWidgetItem(""));
  }
for(int r=0;r<list_to_del.length();++r){
    bool starred=cat.delete_event(list_to_del.at(r));
    if(starred){
        QString del=list_to_del.at(r);
        delete_from_starred(del);
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
  int col;
  col=ui->tableWidget->currentColumn(); 
  if(new_name=="hello"){
            return;
        }
  else if(new_name!="hello" ){
      if(chec_starred_state){
          on_pushButton_2_clicked();
          for(int i=0;i<ui->tableWidget->rowCount();++i){
             auto f=ui->tableWidget->item(i,ui->tableWidget->currentColumn());
             if(!f|| f->text().isEmpty()){
                 int myslot=free_slot(0);
                 ui->tableWidget->setItem(myslot, 0, new QTableWidgetItem(new_name));
                 ui->tableWidget->setItem(i, col, new QTableWidgetItem(new_name));
                 Event *e=new Event(new_name,true,false,col);
                 cat.appaia(date_as_qdate,*e);
                 delete e;
                 break;
               }
           }
        }
      else if(!chec_starred_state){
          on_pushButton_2_clicked();
          for(int i=0;i<ui->tableWidget->rowCount();++i){
              auto f=ui->tableWidget->item(i,ui->tableWidget->currentColumn());
              if(!f|| f->text().isEmpty()){
                  ui->tableWidget->setItem(i, col, new QTableWidgetItem(new_name));
                  Event *e=new Event(new_name,false,false,col);
                  cat.appaia(date_as_qdate,*e);
                  delete e;
                  break;
                }
            }
        }
    }
  ordering(ui->tableWidget->currentColumn());
}

void MainWindow::on_pushButton_2_clicked()
{
  QString del_from_starred=ui->tableWidget->currentItem()->text();
  bool starred=cat.delete_event(ui->tableWidget->currentItem()->text());
  ui->tableWidget->setItem(ui->tableWidget->currentRow(),ui->tableWidget->currentColumn(),new QTableWidgetItem(""));
  if(starred){
      delete_from_starred(del_from_starred);
    }
 ordering(ui->tableWidget->currentColumn());
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
cat.details();

}


void MainWindow::ordering(int f){
 for(int i=0;i<ui->tableWidget->rowCount();++i){
      ui->tableWidget->setItem(i,f,new QTableWidgetItem(""));
    }
 QStringList name_found=cat.ordered_gui(ui->tableWidget->currentColumn());
 for(int y=0;y<name_found.length();++y){
     ui->tableWidget->setItem(y,ui->tableWidget->currentColumn(),new QTableWidgetItem(name_found.at(y)));
   }
}

int MainWindow::free_slot(int c){
  for(int i=0;i<ui->tableWidget->rowCount();++i){
      auto g=ui->tableWidget->item(i,c);
      if(!g || g->text().isEmpty()){
          return i;
        }

    }

}


void MainWindow::delete_from_starred(QString star_event){

  for(int u=0;u<ui->tableWidget->rowCount();++u){
      auto f=ui->tableWidget->item(u,0);
      if(!f||!f->text().isEmpty()){
          if(f->text()==star_event){
           ui->tableWidget->setItem(u,0,new QTableWidgetItem(""));
           u=200;
            }
        }
      else if(u==14 || f->text().isEmpty()){
           ui->tableWidget->setItem(u,0,new QTableWidgetItem(""));

        }
    }

}
void MainWindow::update(){
  this->cat.n_update();

}
void MainWindow::attach(){

}
void MainWindow::detach(){

}

void MainWindow::on_pushButton_4_clicked()
{
    ordering(ui->tableWidget->currentColumn());
}
