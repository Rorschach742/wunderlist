#ifndef CATEGORY_MAN_H
#define CATEGORY_MAN_H

#endif // CATEGORY_MAN_H
#include<map>
#include "event.h"
#include <memory>
class category_man{

public:
  std::multimap<QDate, Event> archivio;
  void appaia(QDate date, Event e);
};
