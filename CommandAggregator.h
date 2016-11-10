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


#if !defined(IB_DRIVER_MAX_ARGS)
#define IB_DRIVER_MAX_ARGS 3
#endif

// Command structure

// Master to Slave

// Start the Analyze Phase
#define IB_M_ANALYSE_PHASE 's'
#define IB_M_ANALYSE_PHASE_ARGS 0

// Set the 16 bit bus address to (args[0] args[1]);
#define IB_M_SET_ADDRESS 'a'
#define IB_M_SET_ADDRESS_ARGS 2

// Completes the analyze phase, device should enter the ConfiguredIdle phase.
#define IB_M_ANALYSE_COMPLETE 'c'
#define IB_M_ANALYSE_COMPLETE_ARGS 0

// Tells the device to set knock on a specific side
// Args[0][1]: The Address
// Args[2]   : The side to knock on
#define IB_M_KNOCK_ON_SIDE_ON 'o'
#define IB_M_KNOCK_ON_SIDE_ON_ARGS 3

// Tells the device to set knock on a specific side
// Args[0][1]: The Address
// Args[2]   : The side to knock off
#define IB_M_KNOCK_ON_SIDE_OFF 'f'
#define IB_M_KNOCK_ON_SIDE_OFF_ARGS 3

// Slave to Master

// Tells master about detection while having no bus address.
//Args [0]: side on witch the knock was detected
//Args [1]: SmartDevicetype (Source|Detector)
#define IB_S_DETECTED_UNKNOWN 'n'
#define IB_S_DETECTED_UNKNOWN_ARGS 1

// Tells master about detection while having a bus address.
// Args[2]   : Side on witch the knock was detected
// Args[0][1]: Bus address
#define IB_S_DETECTED_KNOWN 'z'
#define IB_S_DETECTED_KNOWN_ARGS 3

#define ARGS_TO_ADDR(ARGS)  ((uint16_t)ARGS[1] + (uint16_t)(ARGS[0] << 0x08))



void setupCommandAggregator(CommandAggregator_t *aggregator, const AggregatorCommand_t *availableCommands, short maxargcount, void (*proccessFunc)(char,char*) );

void aggregateCommandByte(CommandAggregator_t *aggregator, char data);


//States





#endif /* UTILS_COMMANDAGGREGATOR_H_ */
