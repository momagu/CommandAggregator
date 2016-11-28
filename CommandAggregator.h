/*
 * InterbusDefinitions.h
 *
 *  Created on: 07.10.2016
 *      Author: moritz
 */

#ifndef UTILS_COMMANDAGGREGATOR_H_
#define UTILS_COMMANDAGGREGATOR_H_

#include <stdlib.h>

typedef struct {
	char identifier;
	int length;
} AggregatorCommand_t;

typedef struct{
	void (*proccessCommand)(char,char*);
	const AggregatorCommand_t *commands;
	short command_count;
	//These variables are used for the aggregation process.
	char _cmd;
	int _argCounter;
	int _argLength;
	char* _argBuf;
} CommandAggregator_t;


void setupCommandAggregator(CommandAggregator_t *aggregator, const AggregatorCommand_t *availableCommands, short maxargcount, void (*proccessFunc)(char,char*) );

void aggregateCommandByte(CommandAggregator_t *aggregator, char data);


//States





#endif /* UTILS_COMMANDAGGREGATOR_H_ */
