#include"PovrayMaker.h"
#include<cmath>


PovrayMaker::PovrayMaker()
{
	dnum=0;
	fileName=QString("Demo");
	file=new QFile(fileName+QString("%1.pov").arg(dnum));
	fileINI=new QFile(fileName+QString("%1.ini").arg(dnum));
	init();
}


PovrayMaker::PovrayMaker(QString name)
{
	dnum=0;
	fileName=name;
	file=new QFile(fileName+QString("%1.pov").arg(dnum));
	fileINI=new QFile(fileName+QString("%1.ini").arg(dnum));
	init();
}

void PovrayMaker::init()
{
	if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
	{
		printf("%s\n",QString("Файл %1 не открыт").arg(fileName+QString("%1.pov").arg(dnum)));
		dnum++;
		delete file;
		file=new QFile(fileName+QString("%1.pov").arg(dnum));
	}
	textOut.setDevice(file);

	textOut<<"#include \"colors.inc\""<<"\n"
		   <<"#include \"stones.inc\""<<"\n"
		   <<"\n";


	textOut
		<<QString("camera")<<"\n"
		<<QString("{")<<"\n"
		<<QString("	 location <%1*cos(2*pi*clock),%1,%1*sin(2*pi*clock)>").arg(2)<<"\n"
//		<<QString("	 location <0,1,1>").arg(2)<<"\n"
		<<QString("	 look_at  <0, 0,  0>")<<"\n"
		<<QString("}")<<"\n"
		<<"\n";

	addLightSource(2, 4, -3);

	addCylinder(0, 0,0,2, 0,0, 0.05,1);
	addCylinder(0, 0,0,0, 2,0, 0.05,2);
	addCylinder(0, 0,0,0, 0,2, 0.05,3);
}

void PovrayMaker::filmINI(int Nframes)
{
	if (!fileINI->open(QIODevice::WriteOnly | QIODevice::Text))
	{
		printf("%s\n",QString("Файл %1 не открыт").arg(fileName+QString("%1.pov").arg(dnum)));
	}
	textOutINI.setDevice(fileINI);

	textOutINI
		<<QString("Initial_Frame = 1")<<"\n"
		<<QString("Final_Frame = %1").arg(Nframes)<<"\n"
		<<"\n"
		<<QString("Initial_Clock = 0")<<"\n"
		<<QString("Final_Clock = 1")<<"\n"
		<<"\n"
		<<QString("Input_File_Name = \"")+fileName+QString("%1.pov").arg(dnum)+QString("\"")<<"\n"
		<<"\n";
	fileINI->close();
}

void PovrayMaker::pigment(double R, double G,double B)
{
	textOut
		<<QString("  texture")<<"\n"
		<<QString("  {")<<"\n"
		<<QString("    pigment { color rgb <%1, %2, %3> }").arg(R).arg(G).arg(B)<<"\n"
 		<<QString("  }")<<"\n"
		<<QString("}")<<"\n"
		<<"\n";
}

void PovrayMaker::pigment(double c)
{
	double R=(c-2)*(c-3)/2;
	double G=(c-1)*(c-3)/(-1);
	double B=(c-1)*(c-2)/2;
	pigment(R, G, B);
}

void PovrayMaker::addSphere(double x, double y,double z, double r, double c)
{
	textOut
		<<QString("sphere")<<"\n"
		<<QString("{")<<"\n"
		<<QString("  <%1, %2, %3>, %4").arg(x).arg(y).arg(-z).arg(r)<<"\n";
	if(c)
		pigment(c);

}
void PovrayMaker::addSphere(double *vec, double r, double c)
{
	addSphere(vec[0], vec[1],vec[2], r, c);
}

void PovrayMaker::addCylinder(double x, double y,double z,double x1, double y1,double z1, double r, double c, int open)
{
  	textOut
		<<QString("cylinder")<<"\n"
		<<QString("{")<<"\n"
    	<<QString("  <%1, %2, %3>").arg(x).arg(z).arg(y)<<"\n"
    	<<QString("  <%1, %2, %3>").arg(x1).arg(z1).arg(y1)<<"\n"
    	<<QString("  %1").arg(r)<<"\n";
	if(open)
  		textOut<<QString("  %1").arg(open)<<"\n";           // Remove end caps
	if(c)
		pigment(c);

}

void PovrayMaker::addCone(double x, double y,double z,double r,double x1, double y1,double z1, double r1, double c, int open)
{
	textOut
		<<QString("cone")<<"\n"
		<<QString("{")<<"\n"
		<<QString("  <%1, %2, %3>, %4").arg(x).arg(y).arg(-z).arg(r)<<"\n"
		<<QString("  <%1, %2, %3>, %4").arg(x1).arg(y1).arg(-z1).arg(r1)<<"\n";
	if(open)
  		textOut<<QString("  %1").arg(open)<<"\n";           // Remove end caps
	if(c)
		pigment(c);

}

void PovrayMaker::addRadial(double r, double phi,double theta, double c)
{
	double x1=r*cos(phi)*sin(theta);
	double y1=r*sin(phi)*sin(theta);
	double z1=r*cos(theta);
	addCone(0,0,0,0,x1, y1, z1, 1, c);
}
void PovrayMaker::codeLine(QString line)
{
	textOut<<line<<"\n";
}

void PovrayMaker::addLightSource(double x, double y,double z, double c)
{
	double R=1,G=1,B=1;
	textOut
		<<QString("light_source { <%1, %2, %3> color rgb <%4, %5, %6>}").arg(x).arg(y).arg(-z).arg(R).arg(G).arg(B)<<"\n"
		<<"\n";

}

int PovrayMaker::render()
{
	if (file->isOpen())
		file->close();

	QFile iniFile(fileName+QString("%1.ini").arg(dnum));

	QString processor("D:\\Program\" \"Files\\POVRAY\\bin\\pvengine /RENDER ");
//	QString processor("notepad ");

	if(iniFile.exists())
		Povray.start(processor+fileName+QString("%1.ini").arg(dnum));
	else
		Povray.start(processor+fileName+QString("%1.pov").arg(dnum));

     if (!Povray.waitForStarted())
         return 1;
     if (!Povray.waitForFinished(-1))
         return 2;

	 if(!file->open(QIODevice::Append  | QIODevice::Text))
		 return 3;
	textOut.setDevice(file);
	 return 0;
}