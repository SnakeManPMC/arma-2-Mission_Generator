#include <QtCore/QCoreApplication>
#include "../include/mission_generator.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// parameter needs to be PATH only :)
	Mission_Generator("d:/coding/test_files/temp-sqm/");

	return 0;
}
