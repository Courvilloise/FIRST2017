/*
 * ActionsRecorder.h
 *
 *  Created on: Feb 13, 2017
 *      Author: franc
 */

#ifndef SRC_ACTIONSRECORDER_H_
#define SRC_ACTIONSRECORDER_H_
#include <string>
#include <list>
#include <memory>
#include "subsystems/Geargate.h"
using namespace std;


class ActionsRecorder;
class Record;
class Geargate;

//////////////////////////////////////////////////////////////////////
//  BUG: IF A TRACK RECORDER IS LONGER THAN 15 SEC (THE AUTONMOUS MODE)
// THE ROBOT WILL STAY JAMMED AND THE MANUAL MODE WILL NOT SWITCH!
// YOU CAN USE THE "PRATICE"

class Record
{
public:
	Record() : updateCounter(0), funcID(0), double1(0.0f), double2(0.0f){}

	Record(const Record& other)
	{
		updateCounter = other.updateCounter;
		funcID = other.funcID;
		double1 = other.double1;
		double2 = other.double2;
		gatePosition = other.gatePosition;
	}

	Record(long tick, unsigned int ID) : updateCounter(tick), funcID(ID){}
	Record(long tick, unsigned int ID, double val1, double val2) : updateCounter(tick), funcID(ID), double1(val1), double2(val2){}
	Record(long tick, unsigned int ID, Geargate::gatePosition pos) : updateCounter(tick), funcID(ID), gatePosition(pos){}
	~Record (){}

	unsigned long updateCounter;
	unsigned int funcID;
	double double1;
	double double2;
	Geargate::gatePosition gatePosition;
};

class ActionsRecorder {
public:
	enum recorderMode {recordInProgress, playInProgress, autonoumousInProgress, disabled};

private:
	// To block all new instance! It's a singleton
	ActionsRecorder();
	// To block all instance copies! It's a singleton
	ActionsRecorder(ActionsRecorder const&); // Don't Implement
    void operator=(ActionsRecorder const&);  // Don't implement

    void PlaySpecificRecord(const Record* pRecord);

    // Count the update from a start record to a stop record
    unsigned long updateCounter;
    // To know the current status of the instance
    recorderMode recorderStatus;

    // To store all calls made during a record session
    std::list<std::shared_ptr<Record>> recordList;
    // To iterate through the list and replay the actions
    std::list<std::shared_ptr<Record>>::iterator itList;

public:
	virtual ~ActionsRecorder();

	// It's a singleton (only one instance)
	static ActionsRecorder* GetInstance()
	{
		static ActionsRecorder singletonInstance;
		return &singletonInstance;
	}

	void StartRecord();
	void StopRecord();
	void StartPlay();
	void StopPlay();
	void StartAutonoumous();
	void StopAutonoumous();
	void Clear();										// Clear all commands recorded;
	void Update();
	void AutonoumousUpdate();
	long GetUpdateCounter(){return updateCounter;}
	recorderMode GetStatus(){return recorderStatus;}	// Get current status

	bool SaveFile(const char* fileName);						// To save the record sequence in a file
	bool LoadFile(const char* fileName);						// To reload the record squenec from a file

	Record* GetCurrentAction();
	void IterateNextAction();

	// Used to record calls
	void RecordCommand(unsigned int funcID);
	void RecordCommand(unsigned int funcID, double val1, double val2);
	void RecordCommand(unsigned int funcID, Geargate::gatePosition pos);
};

#endif /* SRC_ACTIONSRECORDER_H_ */
