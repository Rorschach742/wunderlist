#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>
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

    std::multimap<QDate,QString> map1;
    std::multimap<QDate,QString>map2;
    std::multimap<int,QString> mapnames;
    std::multimap<int,QDate> mapdate;
    int head_cols=6;


private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_toolButton_clicked();
    void refreshtime();
    void refreshdate();
    void print_on_screen();


    void  multmap_order_66(QString name);
    QString  multmap_search(int j);
    QDate multmap_search_date(int j);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
