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
#include <vector>


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
            std::unique_ptr<Event>mypoint( new Event (name,false,false,column));
            cat.appaia(date_catch,*mypoint);
            break;
            }
      }

}

void MainWindow::on_toolButton_clicked()
{
  auto iter=cat.archivio.begin();
  const auto end=cat.archivio.end();
  int i=0;
while(iter!= end){
//int cc=iter->second.cat_id_ret();
if(iter->second.name_ret()==ui->tableWidget->item(i,ui->tableWidget->currentColumn())->text()){
cat.archivio.erase(iter);

  ++iter;
  i++;
  }
else{
    ++iter;

  }
}
for(int i=0;i<ui->tableWidget->rowCount();++i){

    ui->tableWidget->setItem(i,ui->tableWidget->currentColumn(), new QTableWidgetItem(""));

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
  int row,col;
  col=ui->tableWidget->currentColumn();
  row=ui->tableWidget->currentRow();
  if(new_name=="hello"){
            return;
        }
  else if(new_name!="hello" ){
      if(chec_starred_state){
          for(int i=0;i<ui->tableWidget->rowCount();++i){
               for(auto iter=cat.archivio.begin();iter!=cat.archivio.end();++iter){
                   auto g=ui->tableWidget->item(i,col);
                   if(!g|| g->text().isEmpty()){
                           ui->tableWidget->setItem(i,0, new QTableWidgetItem(new_name));
                           std::unique_ptr<Event>new_ev_ptr( new Event (new_name,true,false,col));
                           cat.appaia(date_as_qdate,*new_ev_ptr);
                           i=60;
                         }
                 }
            }
        }
      else{
          for(int i=0;i<ui->tableWidget->rowCount();++i){
              for(auto iter=cat.archivio.begin();iter!=cat.archivio.end();++iter){
              auto g=ui->tableWidget->item(i,col);
              if(!g|| g->text().isEmpty()){
                  ui->tableWidget->setItem(i,col, new QTableWidgetItem(new_name));
                  std::unique_ptr<Event>new_ev_ptr( new Event (new_name,true,false,col));
                  cat.appaia(date_as_qdate,*new_ev_ptr);
                  i=60;

                }
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
 while (it != end)
  {
      QString m=it->second.name_ret();
      QString n=ui->tableWidget->item(ui->tableWidget->currentRow(),col)->text();
      int o=QString::compare(m,n,Qt::CaseInsensitive);
      if (m==n)
      {
          cat.archivio.erase(it++);

          break;

      }
      else
      {
         ++it;
          ++i;
      }
  }/*
  for(auto itr=cat.archivio.begin();itr!=cat.archivio.end();++itr){
      QString m,n;
      m=itr->second.name_ret();
      n=ui->tableWidget->item(ui->tableWidget->currentRow(),col)->text();
      if(m==n){
          cat.archivio.erase(it++);
break;

        }

    }*/
 ui->tableWidget->setItem(ui->tableWidget->currentRow(),col,new QTableWidgetItem(""));

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

      qDebug()<<itr->first<<"\t"<<itr->second.name_ret();

    }

}
void MainWindow::delete_from_gui(){
  int j=ui->tableWidget->currentColumn();
  for(int i=0;i<ui->tableWidget->rowCount();++i){
      ui->tableWidget->setItem(i,j,new QTableWidgetItem(""));
    }
}

void MainWindow::ordering(int f){

  for(int i=0;i<ui->tableWidget->rowCount();++i){
      ui->tableWidget->setItem(i,f,new QTableWidgetItem(""));
    }

          auto iter=cat.archivio.begin();
          const auto end=cat.archivio.end();
          int i=0;
    while(iter!= end){
        //int cc=iter->second.cat_id_ret();
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


void MainWindow::on_pushButton_4_clicked()
{
    ordering(ui->tableWidget->currentColumn());
}
int MainWindow::free_slot(int c){
  for(int i=0;i<ui->tableWidget->rowCount();++i){
      auto g=ui->tableWidget->item(i,c);
      if(!g|| g->text().isEmpty()){
          return i;
        }
      else return NULL;
    }

}
