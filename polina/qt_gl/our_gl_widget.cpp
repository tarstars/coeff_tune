#include "main_dialog.h"
#include <cmath>
#include <iostream>

#include "our_gl_widget.h"

using namespace std;

OurGlWidget::OurGlWidget(QWidget* parent): QGLWidget(parent), dirX(0), dirY(0), dirZ(0) {
  
}

void
OurGlWidget::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glEnable(GL_SMOOTH);
  glEnable(GL_COLOR_MATERIAL);

  glEnable(GL_LIGHTING);

  {
    glEnable(GL_LIGHT0);

    GLfloat ambientLight[] = {0, 1, 0, 1};
    GLfloat diffuseReflection[] = {.2, .7, .7, 1};
    GLfloat specularLight[] = {.5, .5, .5, 1.0};
    GLfloat pos[] = {2, 2, 8, 1};
    GLfloat dir[] = {0, 0, 1};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseReflection);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
  }

  cout << "initialize" << endl;
}

void
OurGlWidget::resizeGL(int w, int h) {
  int s = qMin(w, h);
  glViewport((w - h) / 2, (h - s) / 2, s, s);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-.5, .5, -.5, .5, 4, 12);
  glMatrixMode(GL_MODELVIEW);

  cout << "resize: " << w << " " << h << endl;
}

void drawCube(double x, double y, double z, double sz) {
  glTranslated(x,y,z);

  glBegin (GL_QUADS);
  glNormal3d (0, 0, 1);
  glVertex3f (sz, sz, sz);
  glVertex3f (-sz, sz, sz);
  glVertex3f (-sz, -sz, sz);
  glVertex3f (sz, -sz, sz);
  glEnd();

 glBegin (GL_QUADS);
  glNormal3d (0, 0, -1);
  glVertex3f (sz, sz, -sz);
  glVertex3f (sz, -sz, -sz);
  glVertex3f (-sz, -sz, -sz);
  glVertex3f (-sz, sz, -sz);
  glEnd();

 glBegin (GL_QUADS);
  glNormal3d (-1, 0, 0);
  glVertex3f (-sz, sz, sz);
  glVertex3f (-sz, sz, -sz);
  glVertex3f (-sz, -sz, -sz);
  glVertex3f (-sz, -sz, sz);
  glEnd();

 glBegin (GL_QUADS);
  glNormal3d (0, 1, 0);
  glVertex3f (sz, sz, sz);
  glVertex3f (sz, -sz, sz);
  glVertex3f (sz, -sz, -sz);
  glVertex3f (sz, sz, -sz);
  glEnd();

 glBegin (GL_QUADS);
  glNormal3d (0, 1, 0);
  glVertex3f (-sz, sz, -sz);
  glVertex3f (-sz, sz, sz);
  glVertex3f (sz, sz, sz);
  glVertex3f (sz, sz, -sz);
  glEnd();

 glBegin(GL_QUADS);
  glNormal3d (0, -1, 0);
  glVertex3f (-sz, -sz, -sz);
  glVertex3f (sz, -sz, -sz);
  glVertex3f (sz, -sz, sz);
  glVertex3f (-sz, -sz, sz);
  glEnd();

 glTranslated(-x,-y,-z);
}

void
OurGlWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  glTranslated(0, 0, -7);

  glRotated(dirX, 1, 0, 0);
  glRotated(dirY, 0, 1, 0);
  glRotated(dirZ, 0, 0, 1);

  glBegin(GL_LINES);{
    glNormal3d(1, 0, 0);
    glColor3f(0.0, 3.0, 0.0);
    glVertex3f(-0.3, 0.0, 0.0);
    glVertex3f(1, 0.0, 0.0);
  } glEnd();

  glBegin(GL_LINES);{
    glNormal3d(0, 0, 1);
    glColor3f(3.0, 0.0, 0.0);
    glVertex3f(0.0, -0.3, 0.0);
    glVertex3f(0.0, 1, 0.0);
  } glEnd();

  glBegin(GL_LINES);{
    glNormal3d(0, 1, 0);
    glColor3f(0.0, 0.0, 3.0);
    glVertex3f(0.0, 0.0, -0.3);
    glVertex3f(0.0, 0.0, 1);
  } glEnd();

  for(double phi = 0; phi < 2 * M_PI; phi += 0.01) {
    double x = 0.3*sin(2*phi);
    double y = 0.3*sin(3*phi);
    double z = phi/6 -0.5; //0.3*sin(4*phi);

    drawCube(x, y, z, 0.023);
  }
}

void
OurGlWidget::rotxChange(int rx) {
  dirX = rx;
  update();
}

void
OurGlWidget::rotyChange(int ry) {
  dirY = ry;
  update();
}

void
OurGlWidget::rotzChange(int rz) {
  dirX = rz;
  update();
}
