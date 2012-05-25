#include <QImage>

int main(int, char **){
  int n = 600;

  QImage img(n, n, QImage::Format_ARGB32_Premultiplied);

  for(int p = 0; p < n; ++p){
    for(int q = 0; q < n; ++q){
      int t = (p & q) ? 1 : 0;
      img.setPixel(q, p, qRgb(t * 255, t * 255, 0));
    }
  }

  img.save("square.png");

  return 0;
}
