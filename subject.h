#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"
class Subject
{
public:
  virtual void subscribe(Observer* o) = 0;
  virtual void unsubscribe(Observer* o) = 0;
  virtual void notify() = 0;
  virtual ~Subject() {}
};

#endif // SUBJECT_H
