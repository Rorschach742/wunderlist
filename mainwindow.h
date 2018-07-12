#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "category_man.h"

using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int head_cols=6;
    category_man cat;

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_toolButton_clicked();
    void refreshtime();
    void refreshdate();
    void print_on_screen();
    void delete_from_gui();
    void ordering(int f);
    int free_slot(int c);




    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
