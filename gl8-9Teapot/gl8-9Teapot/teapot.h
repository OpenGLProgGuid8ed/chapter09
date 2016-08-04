#ifndef TEAPOT_H
#define TEAPOT_H

#include <QtWidgets/QWidget>
#include "ui_teapot.h"
#include "mat.h"
#include "LoadShaders.h"
#include "vmath.h"
#include "data.h"
#include <qgl.h>
#include <QKeyEvent>
class Teapot : public QGLWidget
{
	Q_OBJECT

public:
	Teapot(QGLWidget *parent = 0);
	~Teapot();
	void initializeGL();
	void paintGL();
	void resizeGL(int w,int h);
	void timerEvent(QTimerEvent*);
	void keyPressEvent(QKeyEvent* e);
private:
	Ui::TeapotClass ui;
	float aspect;
	GLuint program;
	GLuint  PLoc;  // Projection matrix
	GLuint  InnerLoc;  // Inner tessellation paramter
	GLuint  OuterLoc;  // Outer tessellation paramter
	GLuint object_mat_mvp_loc;
	GLfloat  Inner;
	GLfloat  Outer;
};

#endif // TEAPOT_H
