#ifndef CATEGORY_MAN_H
#define CATEGORY_MAN_H


#include<map>
#include "event.h"
#include <memory>
#include "subject.h"
class category_man : public Subject
{
public:
  void appaia(QDate date, Event e);
  bool delete_event(QString gui_string);  
  void details();
  QStringList ordered_gui(int col);
  int count_ev();
  int count_star_ev();

   virtual void subscribe(Observer* o);
   virtual void unsubscribe(Observer* o);
   virtual void notify();

  int completed;
  int starred;
  int first, second;

private:
     std::list<Observer*> observers;
     std::multimap<QDate, Event> archivio;
};
#endif // CATEGORY_MAN_H
