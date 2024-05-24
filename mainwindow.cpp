#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

void check_game_over(MainWindow* m);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *numButton [15];
    for(int i=1; i<16;i++){ // add the event of the buttons
        QString butname = "pushButton_" + QString::number(i); // get buttons by
        numButton[i] = MainWindow::findChild<QPushButton *>(butname); // name
        connect(numButton[i],SIGNAL(released()), this, SLOT(numPressed()));
    }


    connect(ui->actionNew_Game,SIGNAL(triggered()), this, SLOT(new_Game()));  // link new game menu button to code
    connect(ui->actionExit,SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->actionAbout,SIGNAL(triggered()), this, SLOT(About()));



    // set where is the gap at the begining of the game
    Gapx = numButton[15]->x()+ numButton[15]->width();
    Gapy = numButton[15]->y();
    new_game=false;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::numPressed(){
    QPushButton *button = (QPushButton*) sender();
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
    }
}

