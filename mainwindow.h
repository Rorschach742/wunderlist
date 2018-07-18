#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "category_man.h"

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Observer
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = 0);
    ~MainWindow();
    int head_cols=6;
    category_man cat;
    int free_slot(int c);
    void delete_from_starred(QString star_event);
    virtual void update() override;
    virtual void attach() override ;
    virtual void detach() override;

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_toolButton_clicked();
    void refreshtime();
    void refreshdate();
    void print_on_screen();
    void ordering(int f);




    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    Subject * sub;

};

#endif // MAINWINDOW_H
