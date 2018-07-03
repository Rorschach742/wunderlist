#include "event.h"
#include <QString>
#include <QDate>
#include <QDebug>
Event::Event(QDate date, QString ev_name, bool starred , bool completed, int posx, int posy): date(date), ev_name(ev_name),starred(starred),
                                                                                              completed(completed),posX(posx), posY(posy)
{


}
Event::~Event(){

}

void Event::setta_completed(bool comp){completed=comp;}

void Event::setta_posx(int d){posX=d;}
void Event::setta_posy(int d){posY=d;}

void Event::details(){

  qDebug()<<date<<"\n"<<ev_name<<"\n"<<starred<<"\n";
}

