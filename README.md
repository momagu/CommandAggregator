# CommandAggregator
A C Lib to decode a serial stream (i.e. UART, RS232) byte by byte into predefined commands. This was implemented to run on AVR devices, but it should run on every system witch supports C. 
## Command Structure
This lib will decode Commands wich look like this:
```
[ComandIdentifier][arg0][arg1]...[argn]
```
When a command is complete a callback function of type `void (*proccessFunc)(char, char*)` will be called.

## Usage

```C

#include "CommandAggregator.h"

CommandAggregator_t cmdAggregator;
static AggregatorCommand_t commands[] = {
		{ 'r', 0},    // Command identified by 'r', no arguments 
		{ 0x02, 6 },  // Command identified by 0x02, this one has 6 arguments
};

int main(void){
		
    setupCommandAggregator(&cmdAggregator, commands, sizeof(interbusCommands) / sizeof(interbusCommands[0]),
				&exec_cmd);
				
		//Just an example. Usally aggregateCommandByte would be called from some interrupt. 
		// This example would result in one call to exec_cmd
		//Command 0x02 with 6 arguments
		char[] cmd = {0x02, 'a', 'r', 'g', 's', '0', '1'};
		for (int i=0; i<7; i++)
			aggregateCommandByte(cmdAggregator, cmd[i]);
}

void exec_cmd(char cmd, char* args) {
	switch (cmd) {
	case 'r':
		//Do the thing that 'r' should do
		break;
	case IB_S_DETECTED_KNOWN:
		char arg4 = args[4];
		// Do whatever you want with the args
		break;
	default:
		break;
	}
}

//######################### AVR ISR USART Example

// USARTC0 should be correctly initialized before!
ISR(USARTC0_RXC_vect){
	// Get data from USART
	unsigned char data = USARTC0.DATA;
	// Give it to the cmdAggregator 
	aggregateCommandByte(cmdAggregator, data);

}
```

You can use mutliple Aggregators at the same time.

Be aware that this is _no_ soluion for instable connections and has no Timeout!
