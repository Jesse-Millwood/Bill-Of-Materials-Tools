/*
 * Encoder.h
 *
 * Created: 2/14/2014 9:42:38 AM
 *  Author: Magnum Laptop1
 */ 

/*
	Note about this Encoder Library:
	---------------------------------
	Much of the functionality of the built in switch
	is defined and addressed in other files. It is kept
	separate from this library in an effort to make this
	library more portable and usable with encoders that do
	not have switches built in
*/

#ifndef ENCODER_H_
#define ENCODER_H_
 
 // Define Pins of Encoder
 #define ENC_CH_A			PD2
 #define ENC_CH_B			PD1
 #define ENC_SW				PD0
// Macros
// Read and store state of the rotary encoder 
//(only works for CHA on Pin PD2 and CHB on Pin PD1)
// The intended value of ENC_RD is something like:
// ENC_RD = 0b(CHA State)(CHB State) ( a two bit binary number)
#define ENC_RD (((PIND&(1<<ENC_CH_A))>>1)|((PIND&(1<<ENC_CH_B))>>1))
// Read and store state of Encoder Switch
#define ENC_SW_RD (PIND&(1<<ENC_SW)) 

// global bit field structure
typedef struct  
{
	unsigned turnRight : 1;
	unsigned turnLeft  : 1;
}encoderFlags;


// Function Prototypes
void Encoder_init(void);

// Globals
encoderFlags ENC;

#endif /* ENCODER_H_ */