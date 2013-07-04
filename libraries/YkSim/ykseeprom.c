/* ykseeprom.c --- adaption of libyubikey for Arduino 1.0.x
**
**  msd, 25-sep-2012:	read/write persistent values from/to EEPROM
*/

#include <Arduino.h>
#include <avr/eeprom.h>
#include "ykseeprom.h"

/*********************************/

void yubikey_eeget_common(
	uint8_t	*ptr,
	int	addr,
	int	len)
{
    while (len--) {
	*ptr++ = eeprom_read_byte(addr++);
    }
}

void yubikey_eeset_common(
	uint8_t	*ptr,
	int	addr,
	int	len)
{
    while (len--) {
	eeprom_write_byte(addr++, *ptr++);
    }
}

/*********************************/
/*********************************/

int yubikey_eeget_keylen (uint8_t *ptr) {
    yubikey_eeget_common(ptr, EEpos_keylen, EElen_keylen);
    return EElen_keylen;
}
void yubikey_eeset_keylen (uint8_t *ptr) {
    yubikey_eeset_common(ptr, EEpos_keylen, EElen_keylen);
}

/*********************************/

int yubikey_eeget_ctrlen (uint8_t *ptr) {
    yubikey_eeget_common(ptr, EEpos_ctrlen, EElen_ctrlen);
    return EElen_ctrlen;
}
void yubikey_eeset_ctrlen (uint8_t *ptr) {
    yubikey_eeset_common(ptr, EEpos_ctrlen, EElen_ctrlen);
}

/*********************************/

int yubikey_eeget_prvlen (uint8_t *ptr) {
    yubikey_eeget_common(ptr, EEpos_prvlen, EElen_prvlen);
    return EElen_prvlen;
}
void yubikey_eeset_prvlen (uint8_t *ptr) {
    yubikey_eeset_common(ptr, EEpos_prvlen, EElen_prvlen);
}

/*********************************/

int yubikey_eeget_publen (uint8_t *ptr) {
    yubikey_eeget_common(ptr, EEpos_publen, EElen_publen);
    return EElen_publen;
}
void yubikey_eeset_publen (uint8_t *ptr) {
    yubikey_eeset_common(ptr, EEpos_publen, EElen_publen);
}

/*********************************/

int yubikey_eeget_statlen (uint8_t *ptr) {
    yubikey_eeget_common(ptr, EEpos_statlen, EElen_statlen);
    return EElen_statlen;
}
void yubikey_eeset_statlen (uint8_t *ptr) {
    yubikey_eeset_common(ptr, EEpos_statlen, EElen_statlen);
}

/*********************************/
/*********************************/

int yubikey_eeget_aeskey (uint8_t *ptr) {
    uint8_t length;
    yubikey_eeget_keylen(&length);
    if (length != EElen_aeskey) return 0;
    yubikey_eeget_common(ptr, EEpos_aeskey, EElen_aeskey);
    return EElen_aeskey;
}
void yubikey_eeset_aeskey (uint8_t *ptr) {
    yubikey_eeset_common(ptr, EEpos_aeskey, EElen_aeskey);
    uint8_t length = EElen_aeskey;
    yubikey_eeset_keylen(&length);
}

/*********************************/

int yubikey_eeget_counter (uint8_t *ptr) {
    uint8_t length;
    yubikey_eeget_ctrlen(&length);
    if (length != EElen_counter) return 0;
    yubikey_eeget_common(ptr, EEpos_counter, EElen_counter);
    return EElen_counter;
}
void yubikey_eeset_counter (uint8_t *ptr) {
    yubikey_eeset_common(ptr, EEpos_counter, EElen_counter);
    uint8_t length = EElen_counter;
    yubikey_eeset_ctrlen(&length);
}

/*********************************/

int yubikey_eeget_private (uint8_t *ptr) {
    uint8_t length;
    yubikey_eeget_prvlen(&length);
    if (length != EElen_private) return 0;
    yubikey_eeget_common(ptr, EEpos_private, EElen_private);
    return EElen_private;
}
void yubikey_eeset_private (uint8_t *ptr) {
    yubikey_eeset_common(ptr, EEpos_private, EElen_private);
    uint8_t length = EElen_private;
    yubikey_eeset_prvlen(&length);
}

/*********************************/

int yubikey_eeget_public (uint8_t *ptr) {
    uint8_t length;
    yubikey_eeget_publen(&length);
    int size = (int) length;
    if (size > EElen_public) size = EElen_public;
    yubikey_eeget_common(ptr, EEpos_public, size);
    return size;
}
void yubikey_eeset_public (uint8_t *ptr, int size) {
    if (size > EElen_public) size = EElen_public;
    yubikey_eeset_common(ptr, EEpos_public, size);
    uint8_t length = (uint8_t) size;
    yubikey_eeset_publen(&length);
}

/*********************************/

int yubikey_eeget_static (uint8_t *ptr) {
    uint8_t length;
    yubikey_eeget_statlen(&length);
    int size = (int) length;
    if (size > EElen_static) size = EElen_static;
    yubikey_eeget_common(ptr, EEpos_static, size);
    return size;
}
void yubikey_eeset_static (uint8_t *ptr, int size) {
    if (size > EElen_static) size = EElen_static;
    yubikey_eeset_common(ptr, EEpos_static, size);
    uint8_t length = (uint8_t) size;
    yubikey_eeset_statlen(&length);
}

/*********************************/
/*********************************/

