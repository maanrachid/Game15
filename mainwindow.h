#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    QTimer *timer;
    QTimer *SecTimer;

private:
    Ui::MainWindow *ui;
    int Gapx;
    int Gapy;
    bool new_game;
    int SecCounter;


private slots:
    void numPressed();
    void new_Game();
    void About();
    void quit();
    void onTimerTimeout();
    void updateSecTime();

};
#endif // MAINWINDOW_H
