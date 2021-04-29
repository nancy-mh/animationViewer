#include "customglwidget.h"
#include <GLUT/glut.h>
#include <OpenGL/GLu.h>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
//#include <QMouseEvent>




customGLWidget::customGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    timerp = new QTimer ();
    timerr = new QTimer ();
    timerf = new QTimer ();
    timerp->setInterval(1000/10);
    timerr->setInterval(1000/10);
    timerf->setInterval(1000/10);
    connect (timerp, SIGNAL(timeout()),
            this, SLOT(on_play_clicked_()));
    connect (timerr, SIGNAL(timeout()),
           //this, SLOT(on_reverse_clicked_()), Qt::QueuedConnection);
            this, SLOT(on_reverse_clicked_()));
    connect (timerf, SIGNAL(timeout()),
            this, SLOT(on_forward_clicked_()));
}

void customGLWidget::setObjects(std::vector<objImageLoader::imageElements> _objects)
{
    objects = _objects;
}

int customGLWidget::getObjectSize()
{
    return objects.size();
}

void customGLWidget::setOBJContainerIndex (int buttonCounter)
{
    OBJContainerIndex = buttonCounter;
}
int customGLWidget:: getOBJContainerIndex ()
{
    return OBJContainerIndex;
}

void customGLWidget::mouseMoveEvent(QMouseEvent * event)
{

    // change x and y
    angleX = lastPosY % 360;
    angleY = lastPosX % 360;

    // stores last position to recall location
    lastPosX = event -> pos().x();
    lastPosY = event -> pos().y();
    update();
}


void customGLWidget::messageToUser(QString message)
{
    QMessageBox popupMessage;
    popupMessage.setText(message);
    popupMessage.exec();
}

void customGLWidget::on_play_clickedC()
{
    timerp->start();
}

void customGLWidget::on_reverse_clickedC()
{
    timerr->start();
}

void customGLWidget::on_forward_clickedC()
{
    timerf->start();
}



void customGLWidget::on_play_clicked_()
{

        if (getOBJContainerIndex() < getObjectSize())
        {

            int counter = getOBJContainerIndex() +1;

            //increase the mesh container by one in the painGL function
            setOBJContainerIndex(counter);

             update();
        }
        else
            timerp -> stop();

}


void customGLWidget::on_reverse_clicked_()
{

    if (getOBJContainerIndex() != 0)
    {
        int reverseCounter;

        if ((getOBJContainerIndex() - 2) > 0)
        {
           reverseCounter = getOBJContainerIndex() - 2;
           setOBJContainerIndex(reverseCounter);
           update();
        }

        else
        {
            timerr -> stop();
        }
    }
    else
    {
        timerr -> stop();
        QString msg = "Cannot reverse player, it is already at the start of the animation.";
        messageToUser(msg);
    }

}


void customGLWidget::on_pause_clicked_()
{

    if (this -> timerp -> isActive() == true)
    {
        timerp -> stop();
        setOBJContainerIndex(getOBJContainerIndex());
        update();
    }
    if (this -> timerr -> isActive() == true)
    {
        timerr -> stop();
        setOBJContainerIndex(getOBJContainerIndex());
        update();
    }
    if (this -> timerf -> isActive() == true)
    {
        timerf -> stop();
        setOBJContainerIndex(getOBJContainerIndex());
        update();
    }
    else
    {
        setOBJContainerIndex(getOBJContainerIndex());
        update();
    }

}

void customGLWidget::on_forward_clicked_()
{

    if (getOBJContainerIndex() != getObjectSize())
    {
        int forwardCounter;

        if ((getOBJContainerIndex() + 2) == 0)
        {
             forwardCounter = getOBJContainerIndex() + 2;
             setOBJContainerIndex(forwardCounter);
             update();
        }
        else if ((getOBJContainerIndex() + 2) > 0 && (getOBJContainerIndex() + 2) < getObjectSize())
        {
            forwardCounter = getOBJContainerIndex() + 2;
            setOBJContainerIndex(forwardCounter);
            update();
        }
        else
        {
            timerf -> stop();
        }
    }
    else
    {
        timerf -> stop();
        QString msg = "Cannot forward player, it is already at the end of the animation.";
        messageToUser(msg);
    }

}


void customGLWidget::on_stop_clicked()
{
    setOBJContainerIndex(0);
    update();
    timerp -> stop();
    timerr -> stop();
    timerf -> stop();

}


void customGLWidget::initializeGL()
{
  initializeOpenGLFunctions();
  glClearColor(0,1,0,0);


}




void customGLWidget::paintGL()
{

       glClear(GL_COLOR_BUFFER_BIT);
       //glClearColor(0,1,0,0);
       glColor3f(0, 1.0, 1.0);
       glMatrixMode(GL_MODELVIEW);
       glLoadIdentity();
       gluLookAt(0, 0, 2, 0, 0, 0, 0, 2, 0);
       glRotatef(angleX, 1, 0, 0);
       glRotatef(angleY, 0, 1, 0);

       if (objects.size() != 0)
       {
           std:: cout << "this is the size of the vec at painGL "<< objects.size() << std::endl;
           glShadeModel(GL_SMOOTH);
           glBegin(GL_TRIANGLES);


                  for (int j = getOBJContainerIndex(); j < objects.size(); j++)
                  {
                      //glVertex3f(OBJContainer_[j].X,OBJContainer_[j].Y, OBJContainer_[j].Z);
//                      glVertex3f(objects[j].X,
//                              objects[j].Y,
//                              objects[j].Z);

                      glNormal3f(objects[j].normalX,
                                 objects[j].normalY,
                                 objects[j].normalZ);

                      glVertex3f(objects[j].X,
                              objects[j].Y,
                              objects[j].Z);

//                              (objects[j].textCoorX,
//                                 objects[j].textCoorY);
                  }

           glEnd();
           glFlush();

           // swaps buffer (Qt uses two buffer, display and draw )
                   this -> context()->swapBuffers(this ->context()-> surface());
       }
       else
           std:: cout << "object vector is empty" << std::endl;

}

void customGLWidget::resizeGL(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //gluPerspective(150, (GLfloat)w / (GLfloat)h, 0.5, 300);
   gluPerspective(150.0, float(w) / float(h), 0.5, 300.0f);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslated(0,0,-3);

   //glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_NORMALIZE);
   //GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
   GLfloat lightPosition[] = {0,5,2,0};
   //GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
   //glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
   glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);



}

void customGLWidget::on_exportAsPOV_clicked()
{
    int value;
    QFile fileName ("POV.txt");
    QString test = "test";
    if (fileName.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream write(&fileName);

        write << "#include \"colors.inc\"\n";
        write << "background {color Green}\n";
        write << "camera {\n"
              << "location < 0, 0, -300 >\n"
              << "look_at < 0, 0, 0> \n";
        write << "mesh{\n"
              << "<" + test + ">";


//        if (objects.size() != 0)
//        {
//            std:: cout << "this is the size of the vec at exportPOV "<< objects.size() << std::endl;



//                   for (int j = getOBJContainerIndex(); j < objects.size(); j++)
//                   {
//                       //glVertex3f(OBJContainer_[j].X,OBJContainer_[j].Y, OBJContainer_[j].Z);
//                       value = ftoi(objects[j].facePosition),
//                               objects[j].faceNormal,
//                               objects[j].faceTexture);

//                       glVertex3f(objects[j].normalX,
//                                  objects[j].normalY,
//                                  objects[j].normalZ);

// //                      glVertex2f(objects[j].textCoorX,
// //                                 objects[j].textCoorY);
//                   }


        fileName.close();


    }
    else
        std:: cout << "Error opening file." << std::endl;

}


