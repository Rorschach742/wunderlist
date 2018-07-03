#ifndef EVENT_H
#define EVENT_H
#include <QString>
#include <QDate>

class Event
{
public:
  Event(QDate date, QString ev_name, bool starred, bool completed, int posx, int posy);
     ~Event();

     bool isStarred() const {
         return starred;
     }

     void setStarred(bool starred) {
         Event::starred = starred;
     }

     const QDate &getDate() const {
         return date;
     }

     void setDate(const QDate &date) {
         Event::date = date;
     }

     const QString &getEv_name() const {
         return ev_name;
     }

     void setEv_name(const QString &ev_name) {
         Event::ev_name = ev_name;
     }
     void set_starred();

     bool isCompleted() const {
         return completed;
     }

     void setCompleted(bool completed) {
         Event::completed = completed;
     }

     int getPosX() const {
         return posX;
     }

     void setPosX(int posX) {
         Event::posX = posX;
     }

     int getPosY() const {
         return posY;
     }

     void setPosY(int posY) {
         Event::posY = posY;
     }


     void setta_posx(int d);
     void setta_posy(int d);
     void setta_completed(bool comp);
     void details();





private:
     QDate date;
     QString ev_name;
     bool starred,completed;
     int posX,posY;


};

#endif // EVENT_H
