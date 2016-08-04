#include "teapot.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Teapot w;
	w.show();
	return a.exec();
}
