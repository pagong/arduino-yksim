/*
**	Key reading functions for LCD shield:
**	DFRobot Keypad Shield
*/

#include <Arduino.h>

#define	PIN_RS	8
#define	PIN_EN	9
#define	PIN_KEY	0

#define	PIN_D0	4
#define	PIN_D1	5
#define	PIN_D2	6
#define	PIN_D3	7

#define btnNONE   0
#define btnLEFT   1
#define btnUP     2
#define btnDOWN   3
#define btnRIGHT  4
#define btnSELECT 5

#define	NUM_KEYS  5

/*
**	analog values for different buttons
*/
// int adc_values[NUM_KEYS] = {30, 150, 360, 535, 760 };	// DFRobot sample code 1
// int adc_values[NUM_KEYS] = {50, 195, 380, 555, 790 };	// DFRobot sample code 2

// actual values for my DFRobot LCD shield (+ approx 30 safety margin)
int adc_values[NUM_KEYS] =  {30, 130, 300, 440, 670 };

int buttons[NUM_KEYS] = {btnRIGHT, btnUP, btnDOWN, btnLEFT, btnSELECT };


/**************************/

// Convert ADC value to key number
int lcd_get_key() {
    int input = analogRead(PIN_KEY);
    for (int k = 0; k < NUM_KEYS; k++) {
        if (input < adc_values[k]) {
	    return buttons[k];
	}
    }
    // No valid key pressed
    return btnNONE;
}

/**************************/

// select the pins used on the LCD panel
LiquidCrystal lcd (PIN_RS, PIN_EN,
		   PIN_D0, PIN_D1, PIN_D2, PIN_D3);
