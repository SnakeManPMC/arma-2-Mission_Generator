#include <QtCore/QCoreApplication>
#include "mission_generator.h"
//#include "create_units.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

// constructor
Mission_Generator::Mission_Generator(QString filename)
{
	Do_Mission(filename);
	InitSQF(filename);
	DescriptionExt(filename);
}

// write mission.sqm
void Mission_Generator::Do_Mission(QString filename)
{
	QString currentSide, currentClass, currentRank;
	QString sensorActivationBy, missionName, missionDescription, sensorActivationType;
	QString sensorType, sensorAge, sensorText;
	QString onActivation;
	int amountSensors = 1, currentSensor = 0, sensorPosX = 123;
	int sensorPosZ = 456, currentSensonSizeA = 123, currentSensonSizeB = 123;
	int missionVersion = 11, randomSeed = 14958083, groupItems = 0, currentItem = 0;
	int vehicleItems = 0, currentVehicleItem = 0;
	int sensorTimeoutMin = 3, sensorTimeoutMid = 5, sensorTimeoutMax = 7, sensorInterruptable = 1;
	int resistanceAffil = 1, amountMarkers = 0; // waypointX = 123, waypointZ = 123,
	int x = 111, z = 222, id = 0, leader = 1, currentSkill = 0.333;
	int currentMarker = 0, year = 1985, month = 6, day = 15, hour = 12, minute = 30;
	float startWeather = 0.5, forecastWeather = 0.5;
	bool playerCommander = false;

	// put in some initial values
	currentSide.append("WEST");
	currentClass.append("USMC_soldier");
	currentRank.append("CAPTAIN");
	sensorActivationBy.append("EAST");
	sensorActivationType.append("NOT PRESENT");
	sensorType.append("END1");
	sensorAge.append("UNKNOWN");
	missionName.append("PMC mission generator made mission");
	missionDescription.append("PMC mission generator made description");
	//waypointX = 0;
	//waypointZ = 0;

	// open mission.sqm file for writing
	QString missionsqm(filename);

	// this for some reason doesnt work straight up append("\\" + "mission.sqm"); huh?
	missionsqm.append("\\");
	missionsqm.append("mission.sqm");

	QFile file (missionsqm);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		// error
        	qDebug() << "There was error on" << missionsqm;
        	exit(1);
	}
	QTextStream stream(&file);

	// mission start

	// mission header
	stream << "version=" << missionVersion << ";\nclass Mission\n{\n\trandomSeed=" << randomSeed;
	stream << ";\n\tclass Intel\n\t{\n\t\tbriefingName=\"" << missionName;
	stream << "\";\n\t\tbriefingDescription=\"" << missionDescription;
	stream << "\";\n\t\tresistanceWest=" << resistanceAffil;
	stream << ";\n\t\tstartWeather=" << startWeather << ";\n\t\tforecastWeather=" << forecastWeather;
	stream << ";\n\t\tyear=" << year << ";\n\t\tmonth=" << month;
	stream << ";\n\t\tday=" << day << ";\n\t\thour=" << hour << ";\n" << "\t\tminute=" << minute << ";\n\t};\n";

	// finish the header, prepare for groups.
	groupItems = 3;
	vehicleItems = 4;
	x = 2700;
	z = 2700;
	stream << "\n";
	stream << "\tclass Groups\n\t{\n\t\titems=" << groupItems << ";\n";

	// groups
	// this is LOOP 1, how many groups?
	for (int i = 0; i < groupItems; i++)
	{ // start loop 1 <- bullshit, it starts with 0 !?

		// group items
		stream << "\t\tclass Item" << currentItem << "\n\t\t{\n\t\t\tside=\"" << currentSide << "\";\n\t\t\t";
		currentItem++;

		// hmm? :)
		stream << "class Vehicles\n";
		stream << "\t\t\t{\n\t\t\t\titems=" << vehicleItems << ";\n";

		// vehicles
		// this is LOOP 2, how many soldiers / vehicles / etc?
		currentVehicleItem = 0;
		// mark old positions.
		x = x + 100;
		float pos_x = x, pos_z = z;
		for (int vx = 0; vx < vehicleItems; vx++)
		{
			stream << "\t\t\t\tclass Item" << currentVehicleItem << "\n\t\t\t\t{\n\t\t\t\t\t";

			// vehicle details of vehicle, position, id, type, etc.
			stream << "position[]={" << pos_x << ", 0, " << pos_z << "};\n\t\t\t\t\tid=" << id << ";\n\t\t\t\t\t";
			id++;

			stream << "side=\"" << currentSide << "\";\n\t\t\t\t\tvehicle=\"" << currentClass << "\";\n";
			stream << "\t\t\t\t\t";

            // if we have the FIRST group ever then make the character player
            if (i == 0 && !playerCommander)
            {
                stream << "player=\"PLAYER COMMANDER\";\n\t\t\t\t\t";
                playerCommander = true;
            }
            // else we make everyone playable :)
            else
            {
                stream << "player=\"PLAY CDG\";\n\t\t\t\t\t";
            }
			// if we have a leader
			if (currentVehicleItem == 0)
			{
				stream << "leader=" << leader << ";\n\t\t\t\t\t";
				// more next vehicle bit to the side.
				pos_x = pos_x - 13;
				pos_z = pos_z - 3;
			}
			currentVehicleItem++;
			// and now start to bring the new vehicles 3m to the right :)
			pos_x = pos_x + 3;

			stream << "rank=\"" << currentRank << "\";\n\t\t\t\t\tskill=" << currentSkill << ";\n\t\t\t\t};\n";
		} // end loop 2.

		// reset vehicle item.
		currentVehicleItem = 0;
		// end vehicles part
		stream << "\t\t\t};\n";

		// this is for groups? :)
		stream << "\t\t};\n";
	} // end loop 1
	stream << "\t};\n";

	// markers
	stream << "\tclass Markers\n\t{\n\t\titems=" << amountMarkers << ";\n\t\tclass Item" << currentMarker << "\n\t\t{\n\t\t\t";

	// rest of the marker stuff.
	stream << "\n\t\t};\n\t};\n\t";

	/*
		class Markers
		{
			items=11;
			class Item0
			{
				position[]={6982.182617,241.738663,6205.911133};
				name="killbox1";
				markerType="RECTANGLE";
				type="mil_flag";
				colorName="ColorRedAlpha";
				a=5000.000000;
				b=5000.000000;
			};
	*/

	// sensors (triggers)
	// temporary fake values before nice random functions are added.
	amountSensors = 2;
	currentSensor = 0;
	currentSensonSizeA = 150;
	currentSensonSizeB = 150;
	//sensorActivationBy.append("EAST");
	//sensorActivationType.append("NOT PRESENT");
	sensorText.append("PMC_opfordead1");
	onActivation.append("PMC_opfordead1 = true; publicVariable \"\"pmc_opfordead1\"\";");
	sensorPosX = 2900;
	sensorPosZ = 2700;

	stream << "class Sensors\n\t{\n";
	stream << "\t\titems=" << amountSensors << ";\n";

	// this is not working, you can to sensors like this, you have to make
	// sensor creating function and pass parameters to it to create
	// opfordead -> end1 sensor "link".

	// sensors loop
	for (int i = 0; i < amountSensors; i++)
	{
		stream << "\t\tclass Item" << currentSensor << "\n\t\t{\n\t\t\t";
		currentSensor++;
		sensorPosX = sensorPosX + 100; // one nudge left
		sensorPosZ = sensorPosZ - 100; // one nudge down

		// sensor details
		stream << "position[]={" << sensorPosX << ", 0, " << sensorPosZ << "};\n\t\t\t";

		stream << "a=" << currentSensonSizeA << ";\n\t\t\tb=" << currentSensonSizeB << ";\n\t\t\t";

		stream << "activationBy=\"" << sensorActivationBy << "\";\n\t\t\tactivationType=\"" << sensorActivationType << "\";\n\t\t\t";

		stream << "timeoutMin=" << sensorTimeoutMin << ";\n\t\t\ttimeoutMid=" << sensorTimeoutMid << ";\n\t\t\ttimeoutMax=" << sensorTimeoutMax << ";\n\t\t\tinterruptable=" << sensorInterruptable << ";\n\t\t\t";

		stream << "type=\"" << sensorType << "\";\n\t\t\tage=\"" << sensorAge << "\";\n\t\t\ttext=\"" << sensorText << "\";\n\t\t\t";

		stream << "expActiv=\"" << onActivation << "\";\n\t\t\t";
		//expCond="opfordead1";
		//expActiv="opfordead1 = true;";

		stream << "class Effects\n\t\t\t{\n\t\t\t};\n\t\t};\n";
	// end of sensors loop
	}
	stream << "\t};\n";

	// mission end
	stream << "};\n\n";

	// the end

	// intro start

	// intro cutscene
	stream << "class Intro\n{\n\t";

	// intro header
	Header(stream, randomSeed, startWeather, forecastWeather, year, month, day, hour, minute);
	stream << "};\n\n";
	// intro end

	// outro start

	// outro win cutscene
	stream << "class OutroWin\n{\n\t";

	// outro header
	Header(stream, randomSeed, startWeather, forecastWeather, year, month, day, hour, minute);
	stream << "};\n\n";
	// outro end

	// outro loose cutscene
	stream << "class OutroLoose\n{\n\t";

	// outro loose header
	Header(stream, randomSeed, startWeather, forecastWeather, year, month, day, hour, minute);
	stream << "};\n";

	/*
	// waypoints
	// not used now
	stream << "\tclass Waypoints\n\t{\n\t\titems=" << items << ";\n\t\tclass Item" << currentItem << "\n\t\t{\n\t\t\tposition[]={" << waypointX << ", 0, " << waypointZ << "};\n";
	stream << "\t\t\tclass Effects\n\t\t\t{\n\t\t\t};\n\t\t\tshowWP=\"NEVER\";\n\t\t};\n\t};\n";

	this goes for the vehicle which you want to be player controlled.
	player="PLAYER COMMANDER";
	others are I think:
	player="PLAYER CDG"; commander driver gunner??
	*/

	// close mission.sqm file
	file.close();
}

void Mission_Generator::Header(QTextStream &stream, int randomSeed, float startWeather, float forecastWeather, int year, int month, int day, int hour, int minute)
{
	stream << "randomSeed=" << randomSeed << ";\n\tclass Intel\n\t{\n";
	stream << "\t\tstartWeather=" << startWeather << ";\n\t\tforecastWeather=" << forecastWeather;
	stream << ";\n\t\tyear=" << year << ";\n\t\tmonth=" << month;
	stream << ";\n\t\tday=" << day << ";\n\t\thour=" << hour << ";\n" << "\t\tminute=" << minute << ";\n\t};\n";
}

// creates init.sqf file in mission dir
void Mission_Generator::InitSQF(QString filename)
{
	// this for some reason doesnt work straight up append("\\" + "mission.sqm"); huh?
	filename.append("\\");
	filename.append("init.sqf");

	QString missionsqm(filename);
	QFile file (missionsqm);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		// error
	}
	QTextStream stream(&file);

	stream << "// if run on server\nif (isServer) then\n{\n\t//[] execVM ""PMC\\PMC_init.sqf"";\n}\nelse\n{\n\t// client stuff\n\t// set our weather using multiplayer parameter array\n";
	stream << "\t//[] execVM \"PMC\\PMC_weather_with_mp_parameter.sqf\";\n\tplayer setVariable [\"BIS_noCoreConversations\", true];\n};\n";

	file.close();
}


void Mission_Generator::DescriptionExt(QString filename)
{
	// this for some reason doesnt work straight up append("\\" + "mission.sqm"); huh?
	filename.append("\\");
	filename.append("description.ext");

	QString missionsqm(filename);
	QFile file (missionsqm);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		// error
	}
	QTextStream stream(&file);

	stream << "/*\n\n*/\n\nrespawn = GROUP;\nrespawndelay = 5;\nonLoadMission = \"PMC Campaign Mission\";\nOnLoadIntro = \"PMC Campaign Mission\";\nOnLoadIntroTime = true;\nOnLoadMissionTime = true;\n";
	stream << "ShowGPS = true;\n";

	file.close();
}
