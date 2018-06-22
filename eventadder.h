#ifndef EVENTADDER_H
#define EVENTADDER_H

#include <QDialog>

namespace Ui {
class eventadder;
}

class eventadder : public QDialog
{
    Q_OBJECT

public:
    explicit eventadder(QWidget *parent = 0);
    ~eventadder();

private:
    Ui::eventadder *ui;
};

#endif // EVENTADDER_H
