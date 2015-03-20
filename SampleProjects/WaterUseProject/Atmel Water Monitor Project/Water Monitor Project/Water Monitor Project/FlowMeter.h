/*
 * FlowMeter.h
 *
 * Created: 2/18/2014 1:49:22 PM
 *  Author: Magnum Laptop1
 */ 


#ifndef FLOWMETER_H_
#define FLOWMETER_H_

// Flow meter pin
 #define FLOW_SENSOR_PIN 	PB0

// Macros
#define FLOWSIG_RD (PINB&(1<<FLOW_SENSOR_PIN))

// Constants
#define K_FACTOR 550
#define INCREMENT_TIMEOUT 10			// The number of minutes it takes for the device to inrement cycle count after
									// the flow meter runs
// Prototype Functions
void FLOW_init(void);
void check_FLOW(void);

// Global Bit Field structures
typedef struct
{
	// threshold_met indicates when the threshold has been met
	// FLOW_active holds the past 4 values for the activity of the flow meter
	// This is so that transitions may be sensed
	// transistion_flag is set when a transitions is sensed
	// active_toggle1s toggles every 1 second while the flow meter is active
	// incrementcyclesflag indicates whether or not to increment the cycles counter
	// after a cycle has occurred
	unsigned threshold_met	: 1;
	unsigned active_toggle1s: 1;
	unsigned state			: 1;
	unsigned incrementcyclesflag:1;
}flowFlags;

// Globals
volatile uint16_t FLOW_pcount;		// pulse count	
volatile uint16_t FLOW_freq;		// Frequency that the flow meter is spinning 
volatile float FLOW_gals;			// gallons counted 
volatile uint8_t FLOW_idlecount;	// count seconds that the flow meter is idle


uint16_t FLOW_idlecount_mins;		// keep track of minutes
float FLOW_gallonThreshold;			// gallon threshold
float FLOW_DIgalThreshold;			// Threshold for DI tank
float FLOW_KYgalThreshold;			// Threshold for Kyzen tank
float FLOW_DIgals;
float FLOW_KYgals;
int	FLOW_DIcycles;
int FLOW_KYcycles;
flowFlags FLOW_indicator;
	
#endif /* FLOWMETER_H_ */