#include "category_man.h"

void category_man::appaia(QDate date, Event  n) {

    archivio.insert(std::pair<QDate,Event>(date, n));

}
