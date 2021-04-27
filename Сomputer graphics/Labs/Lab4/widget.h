#ifndef WIDGET_H
#define WIDGET_H

#include <cmath>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include <QVector3D>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

#include <QTime>
#include <QDebug>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

class Widget: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
    
public:
	explicit Widget(QOpenGLWidget *parent = 0);
	~Widget();
    
private:
	QTimer refresh;
	QOpenGLShaderProgram myShader;
	QVector3D pmouse;

	QTime fps_start;
	int fps_frames;
    float yaw, pitch, dist;

    /* OpenGL stuff */
    GLint attr_coord3d, attr_v_color, unif_mvp;
	GLuint vbo_vertices, vbo_colors, ibo_faces;

	void initializeGL();
	void paintGL();
	void measureFps();

	void init();
	void draw(QOpenGLShaderProgram *prog);

    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
};

#endif // WIDGET_H
