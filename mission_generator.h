#ifndef MISSION_GENERATOR_H
#define MISSION_GENERATOR_H

#include "QTextStream"

class Mission_Generator
{
public:
	Mission_Generator(QString filename);

private:
	void Do_Mission(QString filename);
	void Header(QTextStream &stream, int randomSeed, float startWeather, float forecastWeather, int year, int month, int day, int hour, int minute);
	void InitSQF(QString filename);
	void DescriptionExt(QString filename);
};

#endif // MISSION_GENERATOR_H
