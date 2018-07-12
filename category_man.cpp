#include "category_man.h"

void category_man::appaia(QDate date, Event  n) {
    archivio.insert(std::pair<QDate,Event>(date, n));
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
void category_man::n_update(){
  first+=first;
  notify();
}
void category_man::n_update2(){
  second+=second;
  notify();
}
