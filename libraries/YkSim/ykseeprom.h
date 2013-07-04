/* ykseeprom.h --- adaption of libyubikey for Arduino 1.0.x
**
**  msd, 25-sep-2012:	EEPROM functions
*/

/*
 * Written by Michael Doerr.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef YKS_EEPROM_H
#define YKS_EEPROM_H

#ifdef __cplusplus
extern "C"
{
#endif


#define EEpos_aeskey	0
#define EElen_aeskey	16
#define EEpos_counter	(EEpos_aeskey + EElen_aeskey)
#define EElen_counter	2
#define EEpos_private	(EEpos_counter + EElen_counter)
#define EElen_private	6
#define EEpos_public	(EEpos_private + EElen_private)
#define EElen_public	16
#define EEpos_static	(EEpos_public + EElen_public)
#define EElen_static	16

extern int  yubikey_eeget_aeskey (uint8_t *ptr);
extern void yubikey_eeset_aeskey (uint8_t *ptr);

extern int  yubikey_eeget_counter (uint8_t *ptr);
extern void yubikey_eeset_counter (uint8_t *ptr);

extern int  yubikey_eeget_private (uint8_t *ptr);
extern void yubikey_eeset_private (uint8_t *ptr);

extern int  yubikey_eeget_public (uint8_t *ptr);
extern void yubikey_eeset_public (uint8_t *ptr, int len);

extern int  yubikey_eeget_static (uint8_t *ptr);
extern void yubikey_eeset_static (uint8_t *ptr, int len);


#define EEpos_keylen	(EEpos_static + EElen_static)
#define EElen_keylen	1
#define EEpos_ctrlen	(EEpos_keylen + EElen_keylen)
#define EElen_ctrlen	1
#define EEpos_prvlen	(EEpos_ctrlen + EElen_ctrlen)
#define EElen_prvlen	1
#define EEpos_publen	(EEpos_prvlen + EElen_prvlen)
#define EElen_publen	1
#define EEpos_statlen	(EEpos_publen + EElen_publen)
#define EElen_statlen	1

extern int  yubikey_eeget_keylen (uint8_t *ptr);
extern void yubikey_eeset_keylen (uint8_t *ptr);

extern int  yubikey_eeget_ctrlen (uint8_t *ptr);
extern void yubikey_eeset_ctrlen (uint8_t *ptr);

extern int  yubikey_eeget_prvlen (uint8_t *ptr);
extern void yubikey_eeset_prvlen (uint8_t *ptr);

extern int  yubikey_eeget_publen (uint8_t *ptr);
extern void yubikey_eeset_publen (uint8_t *ptr);

extern int  yubikey_eeget_statlen (uint8_t *ptr);
extern void yubikey_eeset_statlen (uint8_t *ptr);


#ifdef __cplusplus
}
#endif
#endif

