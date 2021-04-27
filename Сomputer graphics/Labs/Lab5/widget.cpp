#include "widget.h"

Widget::Widget(QWidget *parent):
	QOpenGLWidget(parent)
{
    u = d = l = r = f = b = down = false;
    vel_y = 0, accel_y = 0.4, jmp = false;
    yaw = M_PI;
    pitch = 0;
    from = QVector3D(0, 20, 7);
    this->setWindowTitle("Cherygova-cg16 Lab5");
}

void Widget::initializeGL()
{
	initializeOpenGLFunctions();

	qDebug("%s\n%s\n%s\n", glGetString(GL_VERSION), glGetString(GL_VENDOR), glGetString(GL_RENDERER));

	myShader.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/ground.vert");
	myShader.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/ground.frag");
    myShader.link();

	groundTexture = new QOpenGLTexture(QImage(":/textures/ground.jpg"));
    sphereTexture = new QOpenGLTexture(QImage(":/textures/sphere.jpg"));
    ladderTexture = new QOpenGLTexture(QImage(":/textures/ladder.jpg"));

	groundMesh.loadRawTriangles(":/raw/ground.raw");
	groundMesh.setTexture(groundTexture);

    sphereMesh.loadRawTriangles(":/raw/sphere.raw");
    sphereMesh.setTexture(sphereTexture);

    ladderMesh.loadRawTriangles(":/raw/ladder.raw");
    ladderMesh.setTexture(ladderTexture);

	timer.setInterval (30);
	QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
	timer.start();
}

void Widget::move()
{
	if (f) from += QVector3D(sin(yaw)*cos(pitch), cos(yaw)*cos(pitch), 0);
	if (b) from -= QVector3D(sin(yaw)*cos(pitch), cos(yaw)*cos(pitch), 0);
	if (l) from -= QVector3D(cos(yaw), -sin(yaw), 0);
	if (r) from += QVector3D(cos(yaw), -sin(yaw), 0);
    if (u)
    {
        if (!jmp)
        {
            vel_y = 3;
            jmp = true;
        }
    }

    if (jmp)
    {
        vel_y -= accel_y;
        if (from.z() + vel_y > 7)
            from += QVector3D (0, 0, vel_y);
        else
        {
            vel_y = 0;
            jmp = false;
            from = QVector3D (from.x(), from.y(), 7);
        }
    }

    if (from.z() <= 5 and not down)
        from = QVector3D (from.x(), from.y(), 7);

    if (d)
    {
        if (!down)
        {
            from -= QVector3D (0, 0, 4.5);
            down = true;
        }
    } else down = false;
}

void Widget::paintGL()
{
    glClearColor(.9, .9, .7, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

	myShader.bind();

	QMatrix4x4 modelview;
	modelview.perspective(70, 1.0 * this->width() / this->height(), 0.1, 100);

	QVector3D to = QVector3D(sin(yaw) * cos(pitch), cos(yaw) * cos(pitch), sin(pitch));
    move();
	modelview.lookAt(from, from + to, QVector3D(0, 0, 1));

	myShader.setUniformValue("mvp", modelview);
    groundMesh.draw(this, &myShader);

    ladderMesh.draw(this, &myShader);

    myShader.setUniformValue("mvp", modelview);
    sphereMesh.draw(this, &myShader);

    myShader.release();
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons())
    {
        yaw += (e->x() - pmouse.x())*0.01;
        pitch -= (e->y() - pmouse.y())*0.01;
        pitch = (pitch < -M_PI/2) ? -M_PI/2 : (pitch > M_PI/2) ? M_PI/2 : pitch;
    }

	pmouse.setX(e->x());
	pmouse.setY(e->y());
    repaint();
}

void Widget::keyPressEvent (QKeyEvent *e)
{
	if(e->key() == Qt::Key_Up || e->key() == Qt::Key_W)
        f = true;

	else if(e->key() == Qt::Key_Down || e->key() == Qt::Key_S)
        b = true;

	else if(e->key() == Qt::Key_Left || e->key() == Qt::Key_A)
        l = true;

	else if(e->key() == Qt::Key_Right || e->key() == Qt::Key_D)
        r = true;

	else if(e->key() == Qt::Key_Q)
        this->close();

	else if(e->key() == Qt::Key_Space)
        u = true;

	else if(e->key() == Qt::Key_Control)
        d = true;

	else if(e->key() == Qt::Key_R)
        from = QVector3D(0, 20, 7);
}

void Widget::keyReleaseEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Up or e->key() == Qt::Key_W)
        f = false;

    else if (e->key() == Qt::Key_Down or e->key() == Qt::Key_S)
        b = false;

    else if (e->key() == Qt::Key_Left or e->key() == Qt::Key_A)
        l = false;

    else if (e->key() == Qt::Key_Right or e->key() == Qt::Key_D)
        r = false;

    else if (e->key() == Qt::Key_Space)
        u = false;

    else if (e->key() == Qt::Key_Control)
        d = false;
}
