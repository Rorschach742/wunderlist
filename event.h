#ifndef EVENT_H
#define EVENT_H
#include <QString>
#include <QDate>

class Event
{
public:
  Event(QString name, bool starred, bool completed,int id);

  ~Event();
  bool isStarred() const {
    return starred;
  }

  void setStarred(bool starred) {
    Event::starred = starred;
  }
  const QString &getEv_name() const {
    return ev_name;
  }
  void setEv_name(const QString &ev_name) {
    Event::ev_name = ev_name;
  }
  bool isCompleted() const {
    return completed;
  }
  void setCompleted(bool completed) {
    Event::completed = completed;
  }
  void setta_completed(bool comp);
  QString name_ret();
  int cat_id_ret();
  int cat_id;

private:
     QString ev_name;
     bool starred;
     bool completed;



};

#endif // EVENT_H
