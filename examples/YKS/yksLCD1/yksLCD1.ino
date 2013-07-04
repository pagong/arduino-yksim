// simple YubiKey generator for Arduino 1.0.x
//
// read AES key, counter, public and private ID from EEPROM
//
// use LCD keypad shield for keypress and display

#include "YkCore.h"
#include "YkSim.h"
#include <SoftTimer.h>

yubikey_ctx_st ctx;

char otp[YUBIKEY_OTP_MAXSIZE];
char *pos;

#define BLINKPIN	 13
#define THRESHOLD	  2

#define TIME_POLL	100	// poll keys every 100 ms
#define TIME_SEND	 10	// send kb codes every 10 ms

Task taskKey(TIME_POLL, checkKey);
Task taskKB (TIME_SEND, sendKey);

/*************************************/

#include <LiquidCrystal.h>

// Next include file defines function lcd_get_key()
// and creates an already initialized 'lcd' object 

// Select only one of these include files !!
    #include <LcdBtn_anduino.h>
//  #include <LcdBtn_dfrobot.h>
//  #include <LcdBtn_freetronics.h>

/*************************************/

#define MODE_NONE	0
#define MODE_YKSIM	1
#define MODE_STATIC	2
#define MODE_HOTP	3
#define MODE_TOTP	4
#define MODE_CHALRESP	5

//#define MAX_MODES	6
#define MAX_MODES	3

int  yks_mode = MODE_YKSIM;
char modes[6][8+1] = {
//	"01234567"
	"None    ",	// 0
	"YkSim   ",	// 1
	"Static  ",	// 2
	"HOTP    ",	// 3
	"TOTP    ",	// 4
	"ChalResp"	// 5
};

int  line_no  = 0;
int  line_max = 0;
char lcd_line[4][16+1] ;

/*************************************/

void setup() {
  Serial.begin(9600);
  pinMode(BLINKPIN, OUTPUT);

  YubikeyInit();
  yks_set_mode(MODE_YKSIM);

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd_redraw();

  SoftTimer.add(&taskKey);
}

/*************************************/

void checkKey(Task* me) {
  static int key_on = 0, key_off = 0, key_press = 0;
  static int key_btn = 0, button = 0;

  yubikey_incr_timestamp(&ctx);

  button = lcd_get_key();
  if (button > 0) {
    key_off = 0;
    key_press = 0;
    key_on += 1;
    digitalWrite(BLINKPIN, HIGH);
    key_btn = button;
  } else {
    if (key_on > THRESHOLD) key_press = key_on;
    key_on = 0;
    key_off += 1;
    digitalWrite(BLINKPIN, LOW);
  }

  if ((key_press > 0) && (key_off > THRESHOLD)) {
    switch (key_btn) {
      case btnSELECT:
	payload(yks_mode);
	break;
      case btnUP:
	if (line_no > 0) line_no--;
	break;
      case btnDOWN:
	if (line_no < line_max) line_no++;
	break;
      case btnLEFT:
	if (line_no == 0) yks_set_mode(yks_mode-1);
	break;
      case btnRIGHT:
	if (line_no == 0) yks_set_mode(yks_mode+1);
	break;
      default:
        // do nothing
	break;
    }
    lcd_redraw();
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

void payload(int mode) {
  line_no = 0;
  switch (mode) {
    case MODE_YKSIM:
	gen_token();
	line_max = 2;
	strncpy(lcd_line[1], otp, 16);
	strncpy(lcd_line[2], (otp+16), 16);
	strncpy(lcd_line[3], (otp+32), 12);
	break;
    case MODE_STATIC:
	gen_static();
	line_max = 1;
	strncpy((lcd_line[1]), otp, 16);
	strncpy((lcd_line[2]), (otp+16), 16);
	break;
    default:
	*otp = '\0';
	line_max = 0;
	clear_line(1);
	clear_line(2);
	clear_line(3);
	break;
  }

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
  yubikey_simulate(otp, &ctx);
  yubikey_incr_usage(&ctx);
}

/*************************************/

void gen_static(void) {
  char buffer[16];

  yubikey_eeget_static ((uint8_t *) buffer);
  yubikey_modhex_encode (otp, buffer, 16);
}

/*************************************/

void yks_set_mode(int mode) {
  line_no  = 0;
  line_max = 0;

  clear_line(0);
  clear_line(1);
  clear_line(2);
  clear_line(3);

  if (mode < 0) yks_mode = 0;
  else yks_mode = mode;
  if (mode >= MAX_MODES) yks_mode = MAX_MODES-1;

  strncpy(lcd_line[0],"Mode:", 5);
  strncpy((lcd_line[0]+6), modes[yks_mode], 8);
}

/*************************************/

void clear_line(int num) {
  strcpy(lcd_line[num],	"                ");
}

/*************************************/

void lcd_redraw() {
  lcd.setCursor(0, 0);
  lcd.print(lcd_line[line_no]);
  lcd.setCursor(0, 1);
  lcd.print(lcd_line[line_no+1]);
}

/*************************************/

void YubikeyInit() {
  unsigned long time1, time2;
  
  uint32_t seed         = analogRead(3);

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

