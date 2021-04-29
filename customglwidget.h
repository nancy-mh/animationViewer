#ifndef CUSTOMGLWIDGET_H
#define CUSTOMGLWIDGET_H
#include "objimageloader.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include "mainwindow.h"
#include <QMouseEvent>

class customGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    customGLWidget(QWidget *parent = nullptr);
    objImageLoader accessMeshes; // irrelevant to the mainwindow
    void setObjects(std::vector<objImageLoader::imageElements> _objects);
    int getObjectSize();
//    MainWindow startTimers;
    QTimer *timerp;
    QTimer *timerr;
    QTimer *timerf;

    //used to obtain loaded meshes from mainwindow open file button
    //MainWindow objFilePathAccesser;
    //void draw();
    void setOBJContainerIndex (int buttonCounter);

    int getOBJContainerIndex ();
    void on_play_clickedC();

    void on_reverse_clickedC();

    void on_forward_clickedC();
    void on_pause_clicked_();
    void on_stop_clicked();

    void messageToUser(QString);



private slots:

    void on_play_clicked_();

    void on_reverse_clicked_();

    void on_forward_clicked_();

    //void on_pause_clicked_();

    //void on_stop_clicked();

     void on_exportAsPOV_clicked();




//    void playButtonTimer_();
//    void reverseButtonTimer_();
//    void forwardButtonTimer_();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mouseMoveEvent(QMouseEvent *) override;



private:
    std::vector<objImageLoader::imageElements> objects;
    int OBJContainerIndex = 0;
    int angleX, angleY, lastPosX, lastPosY;
};

#endif // CUSTOMGLWIDGET_H
