#include "event.h"
#include <QString>
#include <QDate>
#include <QDebug>
Event::Event(QString name, bool starred , bool completed, int id): ev_name(name),starred(starred),completed(completed),cat_id(id){}
Event::~Event(){}
void Event::setta_completed(bool comp){completed=comp;}
QString Event::name_ret(){
  QString nome=ev_name;
  return nome;
}

int Event::cat_id_ret(){return cat_id;}
