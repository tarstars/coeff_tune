#ifndef OUR_GL_WIDGET
#define OUR_GL_WIDGET

#include <QGLWidget>

class OurGlWidget : public QGLWidget {
 Q_OBJECT

 public:

  OurGlWidget(QWidget* = 0);

  int dirX, dirY, dirZ;

 protected:
  void initializeGL();
  void resizeGL(int, int);
  void paintGL();

  public slots:
  void rotxChange(int);
  void rotyChange(int);
  void rotzChange(int);
};

#endif
