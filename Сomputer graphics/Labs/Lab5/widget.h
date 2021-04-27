#ifndef WIDGET_H
#define WIDGET_H

#include <cstdio>
#include <cmath>

#include <QOpenGLWidget>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <QTimer>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>

#include "mesh.h"

class Widget: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
	explicit Widget(QWidget *parent = 0);
	~Widget()
	{
		/* this could have worked if Qt's texture wrapper implementation was done right
		 * (apparently it wasn't), so enjoy your tiny memory leaks
		 *
		 * delete groundTexture;
         * delete sphereTexture;
		 */
	}

    void initializeGL();
    void resizeGL(int w, int h) { glViewport (0, 0, w, h); }
    void paintGL();

    void mousePressEvent (QMouseEvent *e) { pmouse.setX (e->x()), pmouse.setY (e->y()); }
    void mouseMoveEvent (QMouseEvent *e);
    void keyPressEvent (QKeyEvent *e);
    void keyReleaseEvent (QKeyEvent *e);

    void move();

private:
    QTimer timer;
    Mesh groundMesh, sphereMesh, ladderMesh;
	QOpenGLShaderProgram myShader;
    QOpenGLTexture *groundTexture, *sphereTexture, *ladderTexture;
    QVector3D pmouse, from;
    float yaw, pitch;

    /* movement parameters */
    bool u, d, l, r, f, b, down;
    float vel_y;
    float accel_y;
    bool jmp;
};

#endif // WIDGET_H
