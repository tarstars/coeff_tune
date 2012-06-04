#ifndef POVRAYMAKER_H
#define POVRAYMAKER_H

#include <QFile>
#include <QList>
#include <QProcess>
#include <QString>
#include <QTextStream>
#include"stdio.h"


class PovrayMaker
{
public:
	QString fileName;
	int dnum;
	QFile *file;
	QFile *fileINI;
	QTextStream textOut;
	QTextStream textOutINI;
	QProcess Povray;
	
	PovrayMaker();
	PovrayMaker(QString);

	void init();
	void addSphere(double x, double y,double z, double r, double c=1);
	void addSphere(double *vec, double r, double c=1);
	void addCylinder(double x, double y,double z,double x1, double y1,double z1, double r, double c=1, int open=0);
	void addCone(double x, double y,double z,double r,double x1, double y1,double z1, double r1, double c=1, int open=0);
	void addRadial(double r, double phi,double theta, double c=1);
	void addLightSource(double x, double y,double z, double c=1);
	void codeLine(QString line);
	void pigment(double R, double G,double B);
	void pigment(double c);
	void filmINI(int Nframes);
	int render();
	
};

#endif