#ifndef MESH_H
#define MESH_H

#include <QVector3D>
#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

struct Vertex
{
public:
	QVector3D p;
	QVector3D n;

	Vertex(){}
	Vertex(const Vertex &v): p(v.p), n(v.n){}
	Vertex(const QVector3D &p, const QVector3D &n): p(p), n(n){}
	Vertex(float x, float y, float z): p(x, y, z){}

};

class Mesh
{
private:
	QVector<Vertex> vertices;
	QOpenGLTexture *texture;

public:
	Mesh() { texture = 0; }
	~Mesh(){}

	void loadRawTriangles(QString fileName);
	void setTexture(QOpenGLTexture *t);
	void draw(QOpenGLFunctions *funcs, QOpenGLShaderProgram *prog);

};


#endif // MESH_H
