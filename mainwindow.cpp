#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>
#define GAMETIME 300000


void check_game_over(MainWindow* m);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    // Disable the maximize button
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);

    // Make the window non-resizable
    setFixedSize(size());


    // Set the window icon
    setWindowIcon(QIcon(":/icon.png"));


    QPushButton *numButton [15];
    for(int i=1; i<16;i++){ // Add the event of the buttons
        QString butname = "pushButton_" + QString::number(i); // get buttons by Name
        numButton[i] = MainWindow::findChild<QPushButton *>(butname);  // get buttons by name
        connect(numButton[i],SIGNAL(released()), this, SLOT(numPressed()));  // create an event for each button
    }


    timer = new QTimer(this);   // create a timer
    //Second timer Settings
    SecTimer = new QTimer(this); // this is for seconds

    connect(ui->actionNew_Game,SIGNAL(triggered()), this, SLOT(new_Game()));  // link new_game menu --> function new_Game
    connect(ui->actionExit,SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionAbout,SIGNAL(triggered()), this, SLOT(About()));
    connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTimeout);
    connect(SecTimer, &QTimer::timeout, this, &MainWindow::updateSecTime);

    // set where is the gap at the begining of the game : Gap is the empty space on the board
    Gapx = numButton[15]->x()+ numButton[15]->width(); // set it to the last square (16)
    Gapy = numButton[15]->y();
    new_game=false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete SecTimer;
}


void MainWindow::numPressed(){
    QPushButton *button = (QPushButton*) sender(); // get the sender object
    //QMessageBox::information(this,"" , QString::number( button->x()) + " " + QString::number( button->y())   );
    if (Gapx== button->x() + button->width() && Gapy == button->y()  ) {
        button->move(button->x() + button->width(), button->y());
        Gapx = Gapx- button->width();
    } else if ( Gapx== button->x() - button->width() && Gapy== button->y() ){
        button->move(button->x() - button->width(), button->y());
        Gapx = Gapx + button->width();
    } else if (Gapy == button->y() + button->width() && Gapx== button->x()  ) {
        button->move(button->x(), button->y() + button->width());
        Gapy = Gapy- button->width();
    } else if (Gapy == button->y() - button->width() && Gapx== button->x()) {
        button->move(button->x(), button->y() - button->width());
        Gapy = Gapy + button->width();
    }

    if (!new_game)
        check_game_over(this);
}


void MainWindow::new_Game(){
    srand(time(nullptr));

    new_game = true;
    for(int i=1;i<10000;i++){
        int randomNumber = rand() % 15 + 1;
        QString butname = "pushButton_" + QString::number(randomNumber);
        QPushButton *btn= MainWindow::findChild<QPushButton *>(butname);
        btn->click();
    }

    new_game = false;
    QMessageBox::information(this ,"Game15" , "Game is begun! You have 5 minutes"  );
    timer->start(GAMETIME); // set the timer to 5 minutes
    SecTimer->start(1000);
    SecCounter=GAMETIME/1000;
}

void MainWindow::quit(){
    QApplication::quit();
}

void MainWindow::About(){
    QMessageBox::information(this,"About" , "Programmed by Maan Haj Rachid"  );
}


void check_game_over(MainWindow* m){
    int count=0;
    for(int i=1;i<16;i++){
        QString butname = "pushButton_" + QString::number(i);
        QPushButton *btn= m->findChild<QPushButton *>(butname);
        if (btn->y() == ((i-1)/4) * 80  && btn->x() == ((i-1)%4) * 80 ){
            count++;
        } else {
            return;
        }
    }

    if (count==15){
      QMessageBox::information(m,"" , "Game over! \n You solved it! Good Job!"  );
      if (m->timer->isActive()) {
          m->timer->stop();
      }
      if (m->SecTimer->isActive()){
          m->SecTimer->stop();
      }
    }
}


void MainWindow::onTimerTimeout(){
    if (timer->isActive()) {
        timer->stop();
    }

    if (SecTimer->isActive()){
        SecTimer->stop();
    }

    QMessageBox::information(this,"Game15" , "Time is up! Unfortunately, you didn't solve it. Try another one!"  );
    new_Game();
}

void MainWindow::updateSecTime()
{
    SecCounter--;
    int minutes = SecCounter / 60;
    int seconds = SecCounter % 60;

    // Format with leading zeros: "mm:ss"
    QString timeText = QString("%1:%2").arg(minutes, 2, 10, QChar('0'))
                                       .arg(seconds, 2, 10, QChar('0'));

    if (minutes==0 and seconds<20)
        ui->timegame->setStyleSheet("background-color: red; color: white;");
    else
        ui->timegame->setStyleSheet("");

    ui->timegame->setText(timeText);
    ui->timegame->repaint();
}
