#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
//#include <QApplication>
#include <iostream>
#include <string>
#include "customglwidget.h"
#include <OpenGL/GLu.h>



//// global counter used to keep track of which mesh should be drawn
//int counter = 0;
//bool stopFlag = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    timerp = new QTimer (this);
//    timerr = new QTimer (this);
//    timerf = new QTimer (this);
//    timerp->setInterval(1000/60);
//    timerr->setInterval(1000/60);
//    timerf->setInterval(1000/60);
//    connect (timerp, SIGNAL(timeout()),
//            this, SLOT(on_play_clicked_()), Qt::QueuedConnection);
//    connect (timerr, SIGNAL(timeout()),
//            this, SLOT(reverseTimerFunction_()), Qt::QueuedConnection);
//    connect (timerf, SIGNAL(timeout()),
//            this, SLOT(forwardTimerFunction_()), Qt::QueuedConnection);
    //timerp->start();
    //timerr->start();
    //timerf->start();

//    timer = new QTimer (this);

//    timer->setInterval(1000/60);
//    timer->setSingleShot(false);
//    connect (timer, SIGNAL(timeout()),
//            this, SLOT(timerFunction()), Qt::QueuedConnection);
//    timer ->start();

}

MainWindow::~MainWindow()
{
    delete ui;
//    delete timerp;
//    delete timerr;
//    delete timerf;
}



void MainWindow::on_play_clicked()
{
    //timerp->start();
    ui -> openGLWidget->on_play_clickedC();
}

void MainWindow::on_pause_clicked()
{
    //timerp->start();
    ui -> openGLWidget->on_pause_clicked_();
}

void MainWindow::on_reverse_clicked()
{
    //timerr->start();
    ui -> openGLWidget->on_reverse_clickedC();
}

void MainWindow::on_forward_clicked()
{
    //timerf->start();
    ui -> openGLWidget->on_forward_clickedC();
}

void MainWindow::on_stop_clicked()
{
    //timerp->start();
    ui -> openGLWidget->on_stop_clicked();
}

void MainWindow::on_OpenFile_clicked()
{

    QString directoryName = QFileDialog::getExistingDirectory(this, "open directory", QDir::homePath(),  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    // if user cancels search
    if(directoryName.isEmpty() || directoryName.isNull())
    {
           return;
    }
    QDir dir = directoryName;
    QString dirPath = dir.path();
    std::string path = dirPath.toStdString();
    QStringList objImage = dir.entryList(QStringList() << "*.obj", QDir::Files);
    foreach(QString fileName, objImage) {
        objFilePaths_main.push_back(path+"/"+fileName.toStdString());
    }

    objLoader.loadMesh(objFilePaths_main,false,0);

    // set the vector within opengl with data
    ui -> openGLWidget->setObjects(objLoader.OBJContainer);

    std::cout << "this is the size of the vector " << objFilePaths_main.size() << " " << std::endl;


}


//void MainWindow::on_play_clicked_()
//{
//    //timerp -> start();
//    if (this -> timerp -> isActive() == true)
//    {
//        //this -> timerp -> stop();

//        if (ui->openGLWidget->getOBJContainerIndex() < ui->openGLWidget->getObjectSize())
//        {

//            //timerp -> start();

//            int counter = ui->openGLWidget->getOBJContainerIndex() +1;

//            //increase the mesh container by one in the painGL function
//            ui->openGLWidget->setOBJContainerIndex(counter);

//             update();
//        }
//        else
//            ui->openGLWidget->timerp -> stop();



//    std::cout << "this is play" << std::endl;
//}


//void MainWindow::on_reverse_clicked_()
//{
//    if (this -> ui->openGLWidget->timerr -> isActive() == true)
//    {
//        this -> ui->openGLWidget->timerr -> stop();

//        int reverseCounter = ui->openGLWidget->getOBJContainerIndex();
//        if ((ui->openGLWidget->getOBJContainerIndex() /2) == 0)
//        {
//           reverseCounter = ui->openGLWidget->getOBJContainerIndex() + 10;
//           ui->openGLWidget->setOBJContainerIndex(reverseCounter);
//           update();
//        }
//        else
//        {
//           reverseCounter = ui->openGLWidget->getOBJContainerIndex()/2;
//           ui->openGLWidget->setOBJContainerIndex(reverseCounter);
//           update();
//        }
//    }
//    else
//    {
//        this -> ui->openGLWidget->timerr -> start(1000/60);
//    }


//     std::cout << "this is reverse" << std::endl;
//}

//void MainWindow::on_pause_clicked_()
//{
//    if (this -> ui->openGLWidget->timerp -> isActive() == true)
//    {
//        this -> ui->openGLWidget->timerp -> stop();

//            //this -> timerr -> stop();
//            ui->openGLWidget->setOBJContainerIndex(ui->openGLWidget->getOBJContainerIndex());

//           update();

//    }
//    else
//    {
//        ui->openGLWidget->timerp -> stop();
//    }

//   std::cout << "this is pause" << std::endl;
//}

//void MainWindow::on_forward_clicked_()
//{

//   int forwardCounter = ui->openGLWidget->getOBJContainerIndex();
//    if ((ui->openGLWidget->getOBJContainerIndex() *2) == 0)
//    {
//         forwardCounter = ui->openGLWidget->getOBJContainerIndex() + 10;
//         ui->openGLWidget->setOBJContainerIndex(forwardCounter);
//         update();
//    }
//    else if (ui->openGLWidget->getOBJContainerIndex() > ui->openGLWidget->getObjectSize())
//    {
//         forwardCounter = ui->openGLWidget->getOBJContainerIndex();
//         ui->openGLWidget->setOBJContainerIndex(forwardCounter);
//         update();
//    }
//    else
//    {
//        forwardCounter = ui->openGLWidget->getOBJContainerIndex() *2;
//        ui->openGLWidget->setOBJContainerIndex(forwardCounter);
//        update();
//    }



//    std::cout << "this is forward" << std::endl;
//}

//void MainWindow::on_stop_clicked()
//{
//    QApplication::quit();
//    //update();
//}



