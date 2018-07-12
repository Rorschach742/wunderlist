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

}

void MainWindow::on_toolButton_clicked()
{
  ordering(ui->tableWidget->currentColumn());
  auto iter=cat.archivio.begin();
  const auto end=cat.archivio.end();
  int i=0;
  QString find_my_string;
  while(iter!= end){
      QString m=iter->second.name_ret();
      find_my_string=m;
      QString n=ui->tableWidget->item(i,ui->tableWidget->currentColumn())->text();
      bool star=iter->second.isStarred();
      if(m==n || star){
          cat.archivio.erase(iter++);
          int counter=0;
          ui->tableWidget->setItem(i,ui->tableWidget->currentColumn(), new QTableWidgetItem(""));
          if(star){
          for(int o=0;o<ui->tableWidget->rowCount();++o){
              if(ui->tableWidget->item(o,0)->text() !=find_my_string) {
                  ++counter;
                }
              else{
                  ui->tableWidget->setItem(counter,0,new QTableWidgetItem(""));
                  o=1000;
                }
            }
            }
          i++;
        }
      else{
          ++iter;
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
          auto it = cat.archivio.begin();
          const auto end = cat.archivio.end();
          int i=0;
          int col=ui->tableWidget->currentColumn();
         while (it != end)
          {
              QString m=it->second.name_ret();
              QString n=ui->tableWidget->item(ui->tableWidget->currentRow(),col)->text();
              if (m==n){
                  cat.archivio.erase(it++);
                  break;
              }
              else{
                 ++it;
                  ++i;
              }
          }
         ui->tableWidget->setItem(ui->tableWidget->currentRow(),col,new QTableWidgetItem(""));
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
          auto it = cat.archivio.begin();
          const auto end = cat.archivio.end();
          int i=0;
          int col=ui->tableWidget->currentColumn();
         while (it != end)
          {
              QString m=it->second.name_ret();
              QString n=ui->tableWidget->item(ui->tableWidget->currentRow(),col)->text();
              if (m==n){
                  cat.archivio.erase(it++);
                  break;
              }
              else{
                 ++it;
                  ++i;
              }
          }
         ui->tableWidget->setItem(ui->tableWidget->currentRow(),col,new QTableWidgetItem(""));
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
}

void MainWindow::on_pushButton_2_clicked()
{
  auto it = cat.archivio.begin();
  const auto end = cat.archivio.end();
  int i=0;
  int col=ui->tableWidget->currentColumn();
  QString find_my_string;
  if(!ui->tableWidget->item(ui->tableWidget->currentRow(),col)->text().isEmpty()){
      while (it != end)
        {
          QString m=it->second.name_ret();
          QString n=ui->tableWidget->item(ui->tableWidget->currentRow(),col)->text();
          if (m==n && !n.isEmpty())
            {
              bool star=it->second.isStarred();
              cat.archivio.erase(it++);
              ui->tableWidget->setItem(ui->tableWidget->currentRow(),col,new QTableWidgetItem(""));
              find_my_string=n;
              if(star){
                  delete_from_starred(find_my_string);
                }
              break;
            }
          else{
              ++it;
              ++i;
            }
        }
    }

    ui->tableWidget->setItem(ui->tableWidget->currentRow(),col,new QTableWidgetItem(""));
ordering(col);
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
  for ( auto itr = cat.archivio.begin(); itr != cat.archivio.end(); ++itr){

      qDebug()<<itr->first<<"\t"<<itr->second.name_ret()<<itr->second.isStarred();

    }

}


void MainWindow::ordering(int f){

  for(int i=0;i<ui->tableWidget->rowCount();++i){
      ui->tableWidget->setItem(i,f,new QTableWidgetItem(""));
    }
  if(f==0){
      auto iter=cat.archivio.begin();
      const auto end=cat.archivio.end();
      int i=0;
      while(iter!= end){
          if(iter->second.isStarred()){
              QString s=iter->second.name_ret();
              ui->tableWidget->setItem(i,0,new QTableWidgetItem(s));
              ++iter;
              i++;
              }
            else{
                ++iter;
            }
        }
    }
  else{
  auto iter=cat.archivio.begin();
  const auto end=cat.archivio.end();
  int i=0;
  while(iter!= end){
      if(iter->second.cat_id_ret()==f){
          QString s=iter->second.name_ret();
          ui->tableWidget->setItem(i,f,new QTableWidgetItem(s));
          ++iter;
          i++;
          }
        else{
            ++iter;
        }
    }
    }
}

int MainWindow::free_slot(int c){
  for(int i=0;i<ui->tableWidget->rowCount();++i){
      auto g=ui->tableWidget->item(i,c);
      if(!g|| g->text().isEmpty()){
          return i;
        }

    }

}


void MainWindow::delete_from_starred(QString star_event){

  for(int u=0;u<ui->tableWidget->rowCount();++u){
      QString f=ui->tableWidget->item(u,0)->text();
      if(!f.isEmpty()){
          if(f==star_event){
           ui->tableWidget->setItem(u,0,new QTableWidgetItem(""));
           u=200;
            }
        }
      else if(u==14 || f.isEmpty()){
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
