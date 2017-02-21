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
}

// Record a sequence
void ActionsRecorder::StartRecord()
{
	Clear();
	updateCounter = 0;
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

void ActionsRecorder::StartAutonoumous()
{
	updateCounter = 0;
	itList = recordList.begin();
	recorderStatus = ActionsRecorder::autonoumousInProgress;
}

void ActionsRecorder::StopAutonoumous()
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

	// Save the number of record
	file.write((char*) &recordNumber, sizeof(int));

	for (std::list<std::shared_ptr<Record>>::iterator it = recordList.begin(); it!=recordList.end(); ++it)
	{
		file.write((char*) (*it).get(), sizeof(Record));
	}

	file.close();
	cout << "File Saved successfully! Number of record = " << recordNumber << endl;
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

		std::shared_ptr<Record> pRecord(new Record(tmpRecord));
		recordList.push_back(pRecord);
	}

	file.close();
	cout << "File Loaded successfully! Number of record = " << numberOfRecord << endl;
	return true;

}

Record* ActionsRecorder::GetCurrentAction()
{
	if (itList == recordList.end())
		return nullptr;

	return (*itList).get();
}

void ActionsRecorder::IterateNextAction()
{
	++itList;
}

// Record a command without parameters
void ActionsRecorder::RecordCommand(unsigned int funcID)
{
	// If we don't record it's not necessary to save the information
	if (recorderStatus!=recordInProgress)
		return;

	std::shared_ptr<Record> pRecord(new Record(updateCounter, funcID));
	recordList.push_back(pRecord);
}

// Record a command with parameters
void ActionsRecorder::RecordCommand(unsigned int funcID, double val1, double val2)
{
	// If we don't record it's not necessary to save the information
	if (recorderStatus!=recordInProgress)
		return;

	std::shared_ptr<Record> pRecord(new Record(updateCounter, funcID, val1, val2));
	recordList.push_back(pRecord);
}

void ActionsRecorder::RecordCommand(unsigned int funcID, Geargate::gatePosition pos)
{
	// If we don't record it's not necessary to save the information
	if (recorderStatus!=recordInProgress)
		return;

	std::shared_ptr<Record> pRecord(new Record(updateCounter, funcID, pos));
	recordList.push_back(pRecord);

}

// Update the recorder! This function will be called by the gamepad even in the autonmous mode
// We need more more time to refactor...
void ActionsRecorder::Update()
{
	// If we are in autonoumous mode we cannot update by this function!
	if (recorderStatus == ActionsRecorder::autonoumousInProgress)
		return;

	updateCounter++;

	if (recorderStatus != playInProgress)
		return;

	/////////////////////////////////////////////////////
	// Playing mode...
	Record* pRecord = GetCurrentAction();

	// If the list of records is empty (there is nothing to play)
	if (pRecord == nullptr)
	{
		StopPlay();
		return;
	}

	//printf("pRecord->updateCounter = %u, updateCounter = %u\n", (unsigned int) pRecord->updateCounter, (unsigned int) updateCounter );

	// If we have an action to play and it's synchro with the current updateCounter
	while ((pRecord != nullptr) &&
		   (pRecord->updateCounter == updateCounter))
	{
		PlaySpecificRecord(pRecord);

		// We are looking for the next action
		IterateNextAction();
		pRecord = GetCurrentAction();
	}
}

void ActionsRecorder::AutonoumousUpdate()
{
	// We need to be in the autonoumous mode
	if (recorderStatus != ActionsRecorder::autonoumousInProgress)
		return;

	updateCounter++;

	/////////////////////////////////////////////////////
	// Playing mode...
	Record* pRecord = GetCurrentAction();

	// If the list of records is empty (there is nothing to play)
	if (pRecord == nullptr)
	{
		StopAutonoumous();
		return;
	}

	//printf("pRecord->updateCounter = %u, updateCounter = %u\n", (unsigned int) pRecord->updateCounter, (unsigned int) updateCounter );

	// If we have an action to play and it's synchro with the current autonoumousUpdateCounter
	while ((pRecord != nullptr) &&
		   (pRecord->updateCounter == updateCounter))
	{
		PlaySpecificRecord(pRecord);

		// We are looking for the next action
		IterateNextAction();
		pRecord = GetCurrentAction();
	}
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

	case FUNC_GEARGATE_SETGATEPOSITION:
		(Robot::geargate.get())->SetGatePosition(pRecord->gatePosition);
		break;
	}

}

