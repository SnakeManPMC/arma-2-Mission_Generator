#include <QtCore/QCoreApplication>
#include "mission_generator.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	// parameter needs to be PATH only :)
	Mission_Generator gObj;
	gObj.setDescription("PMC Rockabilly Rulez Okay!");
	gObj.setName("PMC Rulez Mission!");
	gObj.Do_Mission("d:/coding/test_files/temp-sqm/");

	return 0;
}
