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
  void delete_all_events();
  void details();
  QStringList ordered_gui(int col);
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
     std::multimap<QDate, Event> archivio;
};
#endif // CATEGORY_MAN_H
