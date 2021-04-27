#include "window.h"
#include <cstdlib>

Window::Window(QWidget *parent):
	QOpenGLWidget(parent),
	frame(0),
    particles(1000)//
{
	for(int i = 0; i < particles; ++i)
		v.push_back(float(i));
}

void Window::initializeGL()
{
	initializeOpenGLFunctions();

	ps.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/particle.vert");
	ps.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/particle.frag");
	ps.link();

	vao.create();
	vao.bind();

	buf.create();
	buf.setUsagePattern(QOpenGLBuffer::StaticDraw);
	buf.bind();
    buf.allocate(v.data(), v.size() * sizeof(v[0]));//закидываем точки в буфер на видеокарту

    texture = new QOpenGLTexture(QImage(":/particle.png"));

    timer.setInterval(15);
	timer.setSingleShot(false);
	QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start();
}

void Window::paintGL()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_POINT_SPRITE);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glPointSize(20);

//	vao.bind();
	ps.bind();

//    timer2.start();

	texture->bind();
    ps.setUniformValue("time", float(frame));
//       ps.setUniformValue("time", timer2.remainingTime());
	ps.setUniformValue("alpha", 1.0f);
	ps.setUniformValue("sampler", 0);

	GLuint att_vertex = ps.attributeLocation("vertex");
	glEnableVertexAttribArray(att_vertex);
	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_POINTS, 0, v.size());

	ps.release();
//	vao.release();

	frame = (frame + 1) % 1000;
}

Window::~Window()
{

}
