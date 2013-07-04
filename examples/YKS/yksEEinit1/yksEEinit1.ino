// simple YubiKey generator for Arduino 1.0.x
//
// initialize EEPROM of Yubikey: set AES key and counter
// private and public ID, and static password

#include "YkCore.h"
#include "YkSim.h"

void setup() {
  unsigned long time1, time2;
  Serial.begin(19200);

  uint8_t *ptr, len;

  uint16_t counter	= 0x0000;
  uint8_t buffer[20];

  Serial.println("Resetting EEPROM of YubiKeySim ...");
  time1 = micros();

  memset (&buffer, 0, 20);
  yubikey_modhex_decode ((char *) &buffer, "gutenbergdrucktebuecherundbibeln", 16);
  yubikey_eeset_aeskey(buffer);

  ptr = (uint8_t *) &counter;
  yubikey_eeset_counter(ptr);

  memset (&buffer, 0, 20);
  yubikey_modhex_decode ((char *) &buffer, "geilerkeiler", 6);
  yubikey_eeset_private(buffer);

  memset (&buffer, 0, 20);
  yubikey_modhex_decode ((char *) &buffer, "luftundliebe", 6);
  yubikey_eeset_public(buffer, 6);

  memset (&buffer, 0, 20);
  yubikey_modhex_decode ((char *) &buffer, "richtlinientreueteichgrundbieber", 16);
  yubikey_eeset_static(buffer, 16);

  time2 = micros();
  Serial.print("done in ");
  Serial.print(time2-time1);
  Serial.println(" micros");

  Serial.print(EEpos_aeskey);
  Serial.print(": ");
  Serial.println(EElen_aeskey);

  Serial.print(EEpos_counter);
  Serial.print(": ");
  Serial.println(EElen_counter);

  Serial.print(EEpos_private);
  Serial.print(": ");
  Serial.println(EElen_private);

  Serial.print(EEpos_public);
  Serial.print(": ");
  Serial.println(EElen_public);

  Serial.print(EEpos_static);
  Serial.print(": ");
  Serial.println(EElen_static);

  Serial.print(EEpos_keylen);
  Serial.print(": ");
  Serial.print(EElen_keylen);
  yubikey_eeget_keylen(&len);
  Serial.print("> ");
  Serial.println(len);

  Serial.print(EEpos_ctrlen);
  Serial.print(": ");
  Serial.print(EElen_ctrlen);
  yubikey_eeget_ctrlen(&len);
  Serial.print("> ");
  Serial.println(len);

  Serial.print(EEpos_prvlen);
  Serial.print(": ");
  Serial.print(EElen_prvlen);
  yubikey_eeget_prvlen(&len);
  Serial.print("> ");
  Serial.println(len);

  Serial.print(EEpos_publen);
  Serial.print(": ");
  Serial.print(EElen_publen);
  yubikey_eeget_publen(&len);
  Serial.print("> ");
  Serial.println(len);

  Serial.print(EEpos_statlen);
  Serial.print(": ");
  Serial.print(EElen_statlen);
  yubikey_eeget_statlen(&len);
  Serial.print("> ");
  Serial.println(len);
}

void loop() {
}

