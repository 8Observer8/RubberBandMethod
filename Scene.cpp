#include <QDebug>
#include "Scene.h"

Scene::Scene( QWidget *parent ) :
    QGLWidget( parent )
{
    this->setMouseTracking( true );
}

void Scene::initializeGL()
{
    glClearColor( 0.94f, 0.94f, 0.94f, 1.0f );
}

void Scene::paintGL()
{
    // Clear the window with current clearing color
    glClear( GL_COLOR_BUFFER_BIT );

    // Set current drawing color to red
    //		   R	 G	   B
    glColor3f( 1.0f, 0.0f, 0.0f );

    glLineWidth( 2.0f );
    glBegin( GL_LINES );
    {
        if ( points.size() > 1 ) {
            for ( size_t i = 0; i < points.size(); ++i ) {
                if ( i == 0 ) {
                    continue;
                }
                glVertex2f( points[i-1].x, points[i-1].y );
                glVertex2f( points[i].x, points[i].y );
            }
        }

        if ( points.size() != 0 ) {
            glVertex2f( points[points.size()-1].x, points[points.size()-1].y );
            glVertex2f( m_point.x, m_point.y );
        }

        for ( size_t i = 0; i < shapes.size(); ++i ) {
            for ( size_t j = 0; j < shapes[i].size(); ++j ) {
                if ( j == 0 ) {
                    continue;
                }
                glVertex2f( shapes[i][j-1].x, shapes[i][j-1].y );
                glVertex2f( shapes[i][j].x, shapes[i][j].y );
            }
        }
    }
    glEnd();
}

void Scene::resizeGL( int w, int h )
{
    // Prevent a divide by zero
    if( h == 0 ) {
        h = 1;
    }

    // Set Viewport to window dimensions
    glViewport( 0, 0, w, h );

    // Reset coordinate system
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    glOrtho( -640.0f/2.0f, 640.0f/2.0f, -480.0f / 2.0f, 480.0f / 2.0f,
             1.0, -1.0);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void Scene::mouseMoveEvent( QMouseEvent* pe )
{
    m_point.x = pe->pos().x() - this->width() / 2;
    m_point.y = -(  pe->pos().y() - this->height() / 2 );

    updateGL();
}

void Scene::mouseReleaseEvent( QMouseEvent *pe )
{
    // RightButton
    if ( pe->button() & Qt::RightButton ) {
        shapes.push_back( points );
        points.clear();
    }

    // LeftButton
    if ( pe->button() & Qt::LeftButton ) {
        Point p;
        p.x = pe->pos().x() - this->width() / 2;
        p.y = -(  pe->pos().y() - this->height() / 2 );

        points.push_back( p );
    }

    updateGL();
}
