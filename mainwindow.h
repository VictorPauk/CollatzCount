/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "collatzcounter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void StopSlot();
private:
    Ui::MainWindow *ui;
    QVector<QString> values;
    CollatzCounter *collatzCounter;
private slots:
    void on_Start_button_clicked();
    void on_Stop_button_clicked();
    void finishedCalculation(long long maxNum, long long maxSteps,int time);
    //void StopSlot();
signals:
   // void stopSignal();

};
#endif // MAINWINDOW_H*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "collatzcounter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QVector<QString> values;
    CollatzCounter *collatzCounter;
private slots:
    void on_Start_button_clicked();
    void on_Stop_button_clicked();
    void finishedCalculation(long long maxNum, long long maxSteps,int time);
    signals:
    void stopSignal();

};
#endif // MAINWINDOW_H
