// Crappy code written to quickly that should be rewritten!
#include <iostream>
#include <fstream>
#include "ActionsRecorder.h"
#include "Robot.h"

ActionsRecorder::ActionsRecorder() {
	updateCounter = 0;
	recorderStatus = ActionsRecorder::disabled;
}

ActionsRecorder::~ActionsRecorder() {
	Clear();
}



void ActionsRecorder::Clear()
{
	recordList.clear();
	updateCounter = 0;
}

// Record a sequence
void ActionsRecorder::StartRecord()
{
	Clear();
	recorderStatus = ActionsRecorder::recordInProgress;
}

// Stop the record
void ActionsRecorder::StopRecord()
{
	recorderStatus = ActionsRecorder::disabled;
}

void ActionsRecorder::StartPlay()
{
	updateCounter = 0;
	itList = recordList.begin();
	recorderStatus = ActionsRecorder::playInProgress;
}

void ActionsRecorder::StopPlay()
{
	recorderStatus = ActionsRecorder::disabled;
}

bool ActionsRecorder::SaveFile(const char* fileName)
{
	// Cannot save a file while recording or playing
	if (recorderStatus!=disabled)
		return false;

	std::ofstream file (fileName, std::ofstream::binary);
	if (!file.is_open())
	{
		perror ("Error creating file");
		return false;
	}

	int recordNumber = (int) recordList.size();
	cout << "number of record = " << recordNumber << endl;

	// Save the number of record
	file.write((char*) &recordNumber, sizeof(int));

	for (std::list<std::shared_ptr<Record>>::iterator it = recordList.begin(); it!=recordList.end(); ++it)
	{
		file.write((char*) (*it).get(), sizeof(Record));
//		file << (*it)->tickCounter;
//		file << (*it)->funcID;
//		file << (*it)->double1;
//		file << (*it)->double2;
	}

	file.close();
	return true;
}


bool ActionsRecorder::LoadFile(const char* fileName)
{
	// Cannot load a file while recording or playing
	if (recorderStatus!=disabled)
		return false;

	// We flush everyting
	Clear();

	ifstream file (fileName, ios::in | ios::binary);
	if (!file.is_open())
	{
		perror ("Error opening file");
		return false;
	}

	// Read the number of records saved in the file
	int numberOfRecord;
	file.read((char*) &numberOfRecord, sizeof(int));
	Record tmpRecord;

	cout << "number of record = " << numberOfRecord << endl;

	for (int it=0; it<numberOfRecord; it++)
	{
		file.read((char*) &tmpRecord, sizeof(Record));
//		file >> tmpRecord.tickCounter;
//		file >> tmpRecord.funcID;
//		file >> tmpRecord.double1;
//		file >> tmpRecord.double2;

		//file.read((char*) &tmpRecord, sizeof(tmpRecord));

		std::shared_ptr<Record> pRecord(new Record(tmpRecord));
		recordList.push_back(pRecord);
	}

	file.close();
	return true;

}

Record* ActionsRecorder::GetCurrentAction()
{
	cout << "Size = " << recordList.size();

	if (itList == recordList.end())
		return NULL;

	return (*itList).get();
}

void ActionsRecorder::IterateNextAction()
{
	itList++;
}

// Record a command without parameters
void ActionsRecorder::RecordCommand(unsigned int funcID)
{
	// If we don't record it's not necessary to save the information
	if (recorderStatus!=recordInProgress)
		return;

	std::shared_ptr<Record> pRecord(new Record(updateCounter, funcID));
	recordList.push_back(pRecord);

	//size_type big = recordList.size();
	cout << "Size = " << recordList.size() << "\n";
}

// Record a command with parameters
void ActionsRecorder::RecordCommand(unsigned int funcID, double val1, double val2)
{
	// If we don't record it's not necessary to save the information
	if (!recorderStatus!=recordInProgress)
		return;

	std::shared_ptr<Record> pRecord(new Record(updateCounter, funcID, val1, val2));
	recordList.push_back(pRecord);
}

// Update the recorder
void ActionsRecorder::Update()
{
	// nothing to do if we don't record or don't play
	if (recorderStatus == disabled)
		return;

	// If we are recording we only increase the update counter
	if (recorderStatus == recordInProgress)
	{
		updateCounter++;
		return;
	}

	/////////////////////////////////////////////////////
	// Playing mode...
	Record* pRecord = GetCurrentAction();

	// If the list of records is empty (there is nothing to play)
	if (pRecord == nullptr)
	{
		StopPlay();
		return;
	}

	// If we have an action to play and in synchro with the current updateCounter
	while ((pRecord != nullptr) &&
		   (pRecord->updateCounter == updateCounter))
	{
		PlaySpecificRecord(pRecord);

		// We are looking for the next action
		IterateNextAction();
		pRecord = GetCurrentAction();
	}

	updateCounter++;
}

void ActionsRecorder::PlaySpecificRecord(const Record* pRecord)
{
	if (pRecord == nullptr)
		return;

	// Depending the funcID we will call the right function on a specific subsystem
	switch(pRecord->funcID)
	{
	case FUNC_VEHICLE_MOVE:
		(Robot::vehicle.get())->Move(pRecord->double1, pRecord->double2);
		break;

	case FUNC_VEHICLE_STOP:
		(Robot::vehicle.get())->Stop();
		break;

	case FUNC_CATAPULT_SETROTATIONSPEED:
		(Robot::catapult.get())->SetRotationSpeed(pRecord->double1, pRecord->double2);
		break;

	case FUNC_CATAPULT_STOP:
		(Robot::catapult.get())->Stop();
		break;

	}

}

