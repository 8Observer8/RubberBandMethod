#ifndef SCENE_H
#define SCENE_H

#include <QGLWidget>
#include <QMouseEvent>
#include <utility>      // std::pair
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

    void mousePressEvent( QMouseEvent* pe );
    void mouseReleaseEvent( QMouseEvent* pe );

private:
    std::vector< std::pair<Point, Point> > segments;
    Point p1, p2;
};

#endif // SCENE_H
