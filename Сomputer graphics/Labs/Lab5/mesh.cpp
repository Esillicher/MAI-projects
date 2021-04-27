#include "mesh.h"

void Mesh::loadRawTriangles(QString fileName)
{
	QFile file(fileName);
	QVector<float> floats;
	if (!file.open(QIODevice::ReadOnly))
		throw QString("Can't open file ") + fileName;

	QTextStream in(&file);
	while(!in.atEnd())
	{
		QString line = in.readLine();
		QStringList values = line.split(" ", QString::SkipEmptyParts);

		if(values.empty())
			continue;
		else if(values[0] == "#")
			continue;
		else if(values.size() == 9)
		{
			QTextStream stream(&line);
			for (int i = 0; i < 9; ++i)
			{
				float f;
				stream >> f;
				floats.push_back(f);
			}

			QVector3D A(floats[0], floats[1], floats[2]);
			QVector3D B(floats[3], floats[4], floats[5]);
			QVector3D C(floats[6], floats[7], floats[8]);
			QVector3D N = QVector3D::crossProduct(A-B, A-C).normalized();

			vertices.push_back(Vertex(A, N));
			vertices.push_back(Vertex(B, N));
			vertices.push_back(Vertex(C, N));
			floats.clear();
		} else
			qDebug() << values.size() << "Warning: bad line " << line;
	}
}

void Mesh::setTexture(QOpenGLTexture *t)
{
	texture = t;
}

void Mesh::draw(QOpenGLFunctions *funcs, QOpenGLShaderProgram *prog)
{
	int qt_vertex = prog->attributeLocation("qt_Vertex");
	int qt_normal = prog->attributeLocation("qt_Normal");

	funcs->glEnableVertexAttribArray(qt_vertex);
	funcs->glEnableVertexAttribArray(qt_normal);

	funcs->glVertexAttribPointer(qt_vertex, 3, GL_FLOAT, false, 6 * sizeof(float), &vertices[0].p);
	funcs->glVertexAttribPointer(qt_normal, 3, GL_FLOAT, false, 6 * sizeof(float), &vertices[0].n);

	if(texture)
	{
		prog->setUniformValue("sampler", 0);
		texture->bind();
	}

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	if(texture)
		texture->release();
}
