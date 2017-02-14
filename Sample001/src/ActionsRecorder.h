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
class ActionsRecorder;

class Record
{
public:
	Record(long tick, std::string func) : tickCounter(tick), funcName(func){}
	Record(long tick, std::string func, double val1, double val2) : tickCounter(tick), funcName(func), double1(val1), double2(val2){}

	long tickCounter;
	std::string funcName;
	double double1;
	double double2;
};

class ActionsRecorder {
private:
	// To block all new instance! It's a singleton
	ActionsRecorder();
	// To block all instance copies! It's a singleton
	ActionsRecorder(ActionsRecorder const&); // Don't Implement
    void operator=(ActionsRecorder const&);  // Don't implement

    // Count the tick from a start record to a stop record
    unsigned long tickCounter;
    // To know the current status of the instance
    bool recordInProgress;
    // To store all calls made during a record session
    std::list<std::shared_ptr<Record>> recordList;

public:
	virtual ~ActionsRecorder();

	// It's a singleton (only one instance)
	static ActionsRecorder* GetInstance()
	{
		static ActionsRecorder singletonInstance;
		return &singletonInstance;
	}

	// Clear all command recorded;
	void Clear();

	// Increment the tick;
	void Tick()
	{
		tickCounter++;
	}

	// Record a sequence
	void StartRecord();
	// Stop the record
	void StopRecord();
	// To know if a record is in progress
	bool RecordInProgress()
	{
		return recordInProgress;
	}

	void RecordCommand(std::string& funcName);
	void RecordCommand(std::string& funcName, double val1, double val2);
};

#endif /* SRC_ACTIONSRECORDER_H_ */
