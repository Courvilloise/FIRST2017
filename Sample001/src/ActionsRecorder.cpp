/*
 * ActionsRecorder.cpp
 *
 *  Created on: Feb 13, 2017
 *      Author: franc
 */

#include "ActionsRecorder.h"

ActionsRecorder::ActionsRecorder() {
	tickCounter = 0;
	recordInProgress = false;
}

ActionsRecorder::~ActionsRecorder() {
	Clear();
}

void ActionsRecorder::Clear()
{
	recordList.clear();
	tickCounter = 0;
}

// Record a sequence
void ActionsRecorder::StartRecord()
{
	recordInProgress = true;
}

// Stop the record
void ActionsRecorder::StopRecord()
{
	recordInProgress = false;
}

// Record a command without parameters
void ActionsRecorder::RecordCommand(std::string& funcName)
{
	// If we don't record it's not necessary to save the information
	if (!recordInProgress)
		return;

	std::shared_ptr<Record> pRecord(new Record(tickCounter, funcName));
	recordList.push_back(pRecord);
}

// Record a command with parameters
void ActionsRecorder::RecordCommand(std::string& funcName, double val1, double val2)
{
	// If we don't record it's not necessary to save the information
	if (!recordInProgress)
		return;

	std::shared_ptr<Record> pRecord(new Record(tickCounter, funcName, val2, val2));
	recordList.push_back(pRecord);
}

