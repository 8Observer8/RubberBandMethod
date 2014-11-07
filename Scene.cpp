#include <QDebug>
#include "Scene.h"

Scene::Scene( QWidget *parent ) :
    QGLWidget( parent )
{

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
        for ( size_t i = 0; i < segments.size(); ++i ) {
            glVertex2f( segments[i].first.x, segments[i].first.y );
            glVertex2f( segments[i].second.x, segments[i].second.y );
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

void Scene::mousePressEvent( QMouseEvent* pe )
{
    p1.x = pe->pos().x() - this->width() / 2;
    p1.y = -(  pe->pos().y() - this->height() / 2 );
}

void Scene::mouseReleaseEvent( QMouseEvent* pe )
{
    p2.x = pe->pos().x() - this->width() / 2;
    p2.y = -(  pe->pos().y() - this->height() / 2 );
    segments.push_back( std::make_pair( p1, p2 ) );
    updateGL();
}
