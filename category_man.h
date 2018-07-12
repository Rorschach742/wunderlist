#ifndef CATEGORY_MAN_H
#define CATEGORY_MAN_H


#include<map>
#include "event.h"
#include <memory>
#include "subject.h"
class category_man : virtual public Subject
{
public:
  std::multimap<QDate, Event> archivio;
  void appaia(QDate date, Event e);
  virtual void subscribe(Observer* o) override;
  virtual void unsubscribe(Observer* o) override;
  virtual void notify() override;

  int completed;
  int starred;
  int first, second;
  void n_update();
  void n_update2();
private:
     std::list<Observer*> observers;
};
#endif // CATEGORY_MAN_H
