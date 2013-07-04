/*
**	Key reading functions for LCD shield:
**	Anduino ARD LCD216
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
// actual values for ARD LCD216 (+ approx. 30 safety margin)
int adc_values[NUM_KEYS] =  {30, 290, 530, 710, 890 };

int buttons[NUM_KEYS] = {btnSELECT, btnRIGHT, btnUP, btnDOWN, btnLEFT };


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
