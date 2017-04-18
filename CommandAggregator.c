/*
 * InterbusDriver.c
 *
 *      Author: Moritz Morawietz
 */

#include "CommandAggregator.h"

// This is set to 0 to begin with to avoid early calls to processIbByte to cause problems.

/*
 * Setup the Driver with a commandset and callback function
 */
void setupCommandAggregator(CommandAggregator_t *aggregator,
		const AggregatorCommand_t *availableCommands, short commandCount,
		void (*proccessFunc)(char, char*)) {
	aggregator->proccessCommand = proccessFunc;
	aggregator->commands = availableCommands;
	aggregator->command_count = commandCount;
	aggregator->_argCounter = 0;
	aggregator->_argLength = 0;
	aggregator->_cmd = '\0';
	// Allocate enough space for the argument buffer
	int maxArgs = 0;
	for (int i = 0; i < commandCount; i++) {
		if (availableCommands[i].length > maxArgs)
			maxArgs = availableCommands[i].length;
	}
	aggregator->_argBuf = malloc(sizeof(char) * maxArgs);

}

/*
 * Processes a byte from the interbus. This method will wait for commands and all its arguments.
 * If a Command is received completely it is given to
 * the function set by setupCommandDriver(..., processfunc);
 *
 */
void aggregateCommandByte(CommandAggregator_t *aggregator, char data) {
	// These static variables are only initialized once!

	if (aggregator->_argCounter == 0 && aggregator->_cmd == '\0') { // Start of a new Command

	//Search for the command
		int i = 0;
		while (aggregator->commands[i].identifier != data
				&& i < aggregator->command_count) {
			i++;
		};

		// abort on unknown command
		if (i == aggregator->command_count)
			return;

		// Command found. Set command and argument length.
		aggregator->_cmd = data;
		aggregator->_argLength = aggregator->commands[i].length;
	} else { // Another argument byte, maybe the last one
		aggregator->_argBuf[aggregator->_argCounter] = data;
		aggregator->_argCounter++;
	}

	if (aggregator->_argCounter == aggregator->_argLength) { // All argument bytes received
		aggregator->proccessCommand(aggregator->_cmd, aggregator->_argBuf);
		aggregator->_cmd = '\0';
		aggregator->_argCounter = 0;
	}
}
