#include "category_man.h"
#include <iostream>
#include <QDebug>
void category_man::appaia(QDate date, Event  n) {
    archivio.insert(std::pair<QDate,Event>(date, n));
    notify();
}

void category_man::subscribe(Observer *o) {
    observers.push_back(o);
}

void category_man::unsubscribe(Observer *o) {
    observers.remove(o);
}

void category_man::notify() {
    for( auto itr = std::begin(observers); itr != std::end(observers); itr++) {
        (*itr)->update();
    }

}

bool category_man::delete_event(QString gui_string){
  auto it = archivio.begin();
    const auto end = archivio.end();
    int i=0;
    QString find_my_string;
    if(!gui_string.isEmpty()){
        while (it != end)
          {
            QString m=it->second.name_ret();
            QString n=gui_string;
            if (m==n && !n.isEmpty())
              {
                bool star=it->second.isStarred();
                archivio.erase(it++);

                find_my_string=n;
                if(star){
                   return true;
                  }
                else{
                    return false;
                  }
                break;
              }
            else{
                ++it;
                ++i;
              }
          }
      }
}

void category_man::details(){
   qDebug()<< "****************************************"
                "\nThe multimap of starred events is : \n";
   for ( auto itr = archivio.begin(); itr != archivio.end(); ++itr){

     qDebug()<<itr->first;

     qDebug()<<itr->second.name_ret();

     qDebug()<<itr->second.isStarred();

     }


}
QStringList category_man::ordered_gui(int col){
  QStringList mylist;
  for(auto iterator=archivio.begin(); iterator!=archivio.end();++iterator){
      if(iterator->second.cat_id_ret()==col){
          mylist.append(iterator->second.name_ret());
        }


    }

return mylist;
}

int category_man::count_ev(){
  int a=0;
  for(auto it=archivio.begin();it!=archivio.end();++it){
      ++a;
    }

  return a;
}


int category_man::count_star_ev(){
  int b=0;
  for(auto it=archivio.begin();it!=archivio.end();++it){
      if(it->second.isStarred()==true){
          ++b;
        }
    }

  return b;

}
