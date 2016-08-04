#include "teapot.h"
#include <iostream>
using namespace std;
#define BUFFER_OFFSET(x)  ((const void*) (x))

Teapot::Teapot(QGLWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);
	startTimer(100);
	Inner = 1.0;
	Outer = 1.0;
}

Teapot::~Teapot()
{
	glUseProgram(0);
}

void Teapot::initializeGL()
{
	if(glewInit())
	{
		cout<<"Unable to Init glew!"<<endl;
		exit(EXIT_FAILURE);
	}
	 // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    enum { ArrayBuffer, ElementBuffer, NumVertexBuffers };
    GLuint buffers[NumVertexBuffers];
    glGenBuffers( NumVertexBuffers, buffers );
    glBindBuffer( GL_ARRAY_BUFFER, buffers[ArrayBuffer] );
    glBufferData( GL_ARRAY_BUFFER, sizeof(TeapotVertices),
		  TeapotVertices, GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, buffers[ElementBuffer] );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(TeapotIndices),
                  TeapotIndices, GL_STATIC_DRAW );

	 // Load shaders and use the resulting shader program
    ShaderInfo  shaders[] = {
	{ GL_VERTEX_SHADER,          "teapot.vert" },
	{ GL_TESS_CONTROL_SHADER,    "teapot.cont" },
 	{ GL_TESS_EVALUATION_SHADER, "teapot.eval" },
 	{ GL_FRAGMENT_SHADER,        "teapot.frag" },
	{ GL_NONE, NULL }
    };
    program = LoadShaders( shaders );
    glUseProgram( program );

	 // set up vertex arrays
    GLuint vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 3, GL_DOUBLE, GL_FALSE, 0,
			   BUFFER_OFFSET(0) );

	object_mat_mvp_loc = glGetUniformLocation(program, "mat_mvp");
    PLoc = glGetUniformLocation( program, "P" );
    InnerLoc = glGetUniformLocation( program, "Inner" );
    OuterLoc = glGetUniformLocation( program, "Outer" );

    glUniform1f( InnerLoc, Inner );
    glUniform1f( OuterLoc, Outer );
    
	mat4  modelview = Translate( -0.2625f, -1.575f, -1.0f );
	modelview *= Translate( 0.0f, 0.0f, -7.5f );
    glUniformMatrix4fv( glGetUniformLocation( program, "MV" ),
			1, GL_TRUE, modelview );

    glPatchParameteri( GL_PATCH_VERTICES, NumTeapotVerticesPerPatch );
    
    glClearColor( 0.0, 0.0, 0.0, 1.0 );
}

void Teapot::paintGL()
{


	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glUseProgram(program);
	static const unsigned int start_time = GetTickCount();
    float t = float((GetTickCount() - start_time)) / float(0x3FFF);
    static const vmath::vec3 X(1.0f, 0.0f, 0.0f);
    static const vmath::vec3 Y(0.0f, 1.0f, 0.0f);
    static const vmath::vec3 Z(0.0f, 0.0f, 1.0f);

	vmath::mat4 tc_matrix = vmath::translate(vmath::vec3(0.0f, 0.0f, -4.0f)) *
                vmath::rotate(70.0f * 3.0f * t, Y);
	tc_matrix = vmath::perspective(35.0f, 1.0f / aspect, 0.1f, 100.0f) * tc_matrix;
	glUniformMatrix4fv(object_mat_mvp_loc, 1, GL_FALSE, tc_matrix);
	glDrawElements( GL_PATCHES, NumTeapotVertices,
		    GL_UNSIGNED_INT, BUFFER_OFFSET(0) );
}

void Teapot::resizeGL(int w,int h)
{
	if(0 == h)
		h = 1;
	aspect = GLfloat(w)/h;

    mat4  projection = Perspective( 60.0, aspect, 5, 10 );
    glUniformMatrix4fv( PLoc, 1, GL_TRUE, projection );
	glViewport(0,0,w,h);
	glLoadIdentity();
}

void Teapot::timerEvent(QTimerEvent*)
{
	updateGL();
}

void Teapot::keyPressEvent(QKeyEvent *e)
{
	switch (e->key())
	{
	case Qt::Key_Up:
		Inner++;
	    if ( Inner > 64 )  Inner = 128.0;
	    glUniform1f( InnerLoc, Inner );
	    break;
	case Qt::Key_Down:
		Inner--;
	    if ( Inner < 1.0 )  Inner = 1.0;
	    glUniform1f( InnerLoc, Inner );
	    break;
	case Qt::Key_Left:
		Outer--;
	    if ( Outer < 1.0 )  Outer = 1.0;
	    glUniform1f( OuterLoc, Outer );
	    break;
	case Qt::Key_Right:
		Outer++;
	    if ( Outer > 64 )  Outer = 128.0;
	    glUniform1f( OuterLoc, Outer );
	    break;
	case Qt::Key_Space:
		 Inner = 1.0;
	    Outer = 1.0;
	    glUniform1f( InnerLoc, Inner );
	    glUniform1f( OuterLoc, Outer );
	    break;
	case Qt::Key_Escape: {
	    static GLenum mode = GL_FILL;
	    mode = ( mode == GL_FILL ? GL_LINE : GL_FILL );
	    glPolygonMode( GL_FRONT_AND_BACK, mode );
	} break;
	default:
		break;
	}
}