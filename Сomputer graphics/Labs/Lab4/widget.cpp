#include "widget.h"

Widget::Widget(QOpenGLWidget *parent):
	QOpenGLWidget(parent),
	fps_start(QTime::currentTime()),
	fps_frames(0),
	yaw(0), pitch(0), dist(30)
{
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
	fps_start = QTime::currentTime();
	initializeOpenGLFunctions();

	qDebug("OpenGL version: %s", glGetString(GL_VERSION));
	qDebug("OpenGL vendor: %s", glGetString(GL_VENDOR));
	qDebug("OpenGL renderer: %s", glGetString(GL_RENDERER));
	qDebug("OpenGL shading language version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

	myShader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/simple.vert");
	myShader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/simple.frag");
    myShader.link();

	init();

	refresh.setInterval(30);
	connect(&refresh, SIGNAL(timeout()), this, SLOT(update()));
	refresh.start();
}

void Widget::init()
{
    GLfloat vertices[] = {
        // top
        0.0, -0.5, 1.0,
        -0.5, 0.0, 1.0,
        0.0, 0.0, 1.0,
        // bottom
        0.0, -0.5, 0.0,
        -0.5, 0.0, 0.0,
        0.0, 0.0, 0.0
    };
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLfloat colors[] = {
        // top
        0.4, 0.0, 0.2,
        0.6, 0.2, 1.0,
        0.6, 1.0, 1.0,
        // bottom
        0.4, 0.0, 0.2,
        0.6, 0.2, 1.0,
        0.6, 1.0, 1.0
    };
    glGenBuffers(1, &vbo_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLushort faces[] = {
        0, 1, 2,
        0, 1, 3,
        1, 3, 4,
        1, 5, 4,
        1, 2, 5,
        2, 0, 5,
        0, 3, 5,
        3, 4, 5
    };
    glGenBuffers(1, &ibo_faces);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_faces);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces), faces, GL_STATIC_DRAW);

	attr_coord3d = myShader.attributeLocation("coord3d");
	attr_v_color = myShader.attributeLocation("v_color");
	glEnableVertexAttribArray(attr_coord3d);
	glEnableVertexAttribArray(attr_v_color);
}

void Widget::draw(QOpenGLShaderProgram *prog)
{
	QMatrix4x4 anim;
	anim.rotate(yaw, QVector3D(0, 1, 0));
	anim.rotate(pitch, QVector3D(1, 0, 0));

	QMatrix4x4 model;
	model.translate(QVector3D(0.0, 0.0, 3.0));
	QMatrix4x4 view;
	view.lookAt(QVector3D(0.0, 1.0, 0.0), QVector3D(0.0, 0.0, 3.0), QVector3D(0.0, 1.0, 0.0));
	QMatrix4x4 projection;
	projection.perspective(dist, float(width())/height(), 0.1f, 10.0f);

	QMatrix4x4 mvp = projection * view * model * anim;
	prog->setUniformValue("mvp", mvp);

	glEnableVertexAttribArray(attr_coord3d);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer(attr_coord3d, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(attr_v_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glVertexAttribPointer(attr_v_color, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_faces);
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(attr_coord3d);
	glDisableVertexAttribArray(attr_v_color);
}

void Widget::paintGL()
{
	makeCurrent();

    glClearColor(.839, .6, .862, 2.);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

    myShader.bind();
	draw(&myShader);
	myShader.release();

	doneCurrent();
	measureFps();
}

void Widget::measureFps()
{
	fps_frames++;
	int delta_t = (QTime::currentTime().msecsSinceStartOfDay() - fps_start.msecsSinceStartOfDay());
	if(delta_t > 1000)
	{
          this->setWindowTitle(QString("Cherygova-cg16 Lab4. FPS: %1").arg(1000. * fps_frames / delta_t));
		  fps_frames = 0;
		  fps_start = QTime::currentTime();
	}
}

void Widget::mousePressEvent(QMouseEvent *e)
{
	if(e->button())
    {
        pmouse[0] = e->x();
        pmouse[1] = e->y();
	}
}

void Widget::wheelEvent(QWheelEvent *e)
{
	if(e->delta() < 0)
        dist += 1.0;
	else if(dist > 1.0)
        dist -= 1.0;

	paintGL();
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
	if(e->buttons())
    {
		yaw +=(e->x() - pmouse[0]);
		pitch -=(e->y() - pmouse[1]);
    }

    pmouse[0] = e->x();
    pmouse[1] = e->y();
    paintGL();
}
