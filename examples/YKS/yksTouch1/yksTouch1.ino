// simple YubiKey generator for Arduino 1.0.x
//
// read AES key, counter, public and private ID from EEPROM
// use touch sensor on Pin 7 as key press

#include "YkCore.h"
#include "YkSim.h"
#include <SoftTimer.h>

yubikey_ctx_st ctx;

char otp[YUBIKEY_OTP_MAXSIZE];
char *pos;

#define BLINKPIN	 13
#define TOUCHPIN	  7
#define THRESHOLD	  2

#define	TIME_POLL	100	// poll "key" every 100 ms
#define	TIME_SEND	 10	// send kb codes every 10 ms

Task taskKey(TIME_POLL, checkKey);
Task taskKB (TIME_SEND, sendKey);

/*************************************/

void setup() {
  Serial.begin(9600);
  pinMode(BLINKPIN, OUTPUT);

  YubikeyInit();

  SoftTimer.add(&taskKey);
}

/*************************************/

void checkKey(Task* me) {
  static int key_on = 0, key_off = 0, key_press = 0;

  yubikey_incr_timestamp(&ctx);

  if (readCapacitivePin(TOUCHPIN) > 1) {
    key_off = 0;
    key_press = 0;
    key_on += 1;
    digitalWrite(BLINKPIN, HIGH);
  } else {
    if (key_on > THRESHOLD) key_press = key_on;
    key_on = 0;
    key_off += 1;
    digitalWrite(BLINKPIN, LOW);
  }

  if ((key_press > 0) && (key_off > THRESHOLD)) {
    payload(key_press);
    key_press = 0;
  }
}

/*************************************/

void sendKey(Task* me) {
  if (*pos) {
    Keyboard.write(*pos);
    pos++;
  } else {
    Keyboard.write('\n');
    Keyboard.end();
    SoftTimer.remove(&taskKB);
    SoftTimer.add(&taskKey);
  }
}

/*************************************/

void payload(int duration) {
  *otp = '\0';
  if (duration <= 10) gen_token();
  if (duration >= 15) gen_static();

/*
  Keyboard.begin();
  Keyboard.println(otp);
  Keyboard.end();
*/

  pos = otp;
  Keyboard.begin();
  SoftTimer.remove(&taskKey);
  SoftTimer.add(&taskKB);
}

/*************************************/

void gen_token(void) {
  unsigned long time1, time2;

  yubikey_simulate(otp, &ctx);
  yubikey_incr_usage(&ctx);
}

/*************************************/

void gen_static(void) {
  unsigned long time1, time2;
  char buffer[16];

  yubikey_eeget_static ((uint8_t *) buffer);
  yubikey_modhex_encode (otp, buffer, 16);
}

/*************************************/

/*	
**	Following code is from
**	http://playground.arduino.cc/Code/CapacitiveSensor
*/

// readCapacitivePin
//  Input: Arduino pin number
//  Output: A number, from 0 to 17 expressing
//  how much capacitance is on the pin
//  When you touch the pin, or whatever you have
//  attached to it, the number will get higher

uint8_t readCapacitivePin(int pinToMeasure) {
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;

  // Here we translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  //  and which bit of those registers we care about.
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  uint8_t bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));

  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  byte cycles = 17;
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  // Now see how long the pin needs to get pulled up
  for(uint8_t i = 0; i < 16; i++){
    if (*pin & bitmask){
      cycles = i;
      break;
    }
  }

  // Discharge the pin again by setting it low and output
  //  It's important to leave the pins low if you want to 
  //  be able to touch more than 1 sensor at a time - if
  //  the sensor is left pulled high, when you touch
  //  two sensors, your body will transfer the charge between
  //  sensors.
  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}

/*************************************/

void YubikeyInit() {
  unsigned long time1, time2;
  
  uint32_t seed         = analogRead(0);

  uint8_t aeskey[16];
  uint8_t privID[6];
  uint8_t pubID[16];
  uint16_t counter;
  uint8_t *ptr;

  char public_id[32+1];
  char private_id[12+1];

  uint32_t time = 0x010203;

  Serial.println("Initializing YubiKey ...");
  time1 = micros();

  ptr = aeskey;
  yubikey_eeget_aeskey(ptr);

  ptr = (uint8_t*) &counter;
  yubikey_eeget_counter(ptr);

  ptr = privID;
  yubikey_eeget_private(ptr);
  yubikey_hex_encode(private_id, (char *)privID, 6);

  ptr = pubID;
  yubikey_eeget_public(ptr);
  yubikey_hex_encode(public_id, (char *)pubID, 6);

  yubikey_init(&ctx, aeskey, public_id, private_id, counter, time, seed);
  yubikey_incr_counter(&ctx);

  ptr = (uint8_t*) &(ctx.counter);
  yubikey_eeset_counter(ptr);

  time2 = micros();
  Serial.print("done in ");
  Serial.print(time2-time1);
  Serial.println(" micros");
}

/*************************************/

