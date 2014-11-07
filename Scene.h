#ifndef SCENE_H
#define SCENE_H

#include <QGLWidget>
#include <QMouseEvent>
#include <vector>       // std::vector
#include "Point.h"

class Scene : public QGLWidget
{
public:
    Scene( QWidget *parent = 0 );

private:
    void initializeGL();
    void paintGL();
    void resizeGL( int w, int h );

    void mouseMoveEvent( QMouseEvent* pe );
    void mouseReleaseEvent( QMouseEvent* pe );

private:
    std::vector<Point> points;
    std::vector< std::vector<Point> > shapes;
    Point m_point;
};

#endif // SCENE_H
