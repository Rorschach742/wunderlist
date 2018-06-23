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

    std::multimap<int,std::multimap<QDate,QString>> reg;
    void archivio_(QDate,QString);
    void archivio_2(QDate,QString);
    void registro(int i, std::multimap<QDate,QString>,QDate date, QString name);
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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
