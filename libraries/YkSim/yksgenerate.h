/* yksgenerate.h --- adaption of libyubikey for Arduino 1.0.x
**
**  msd, 13-sep-2012:	based on code from https://github.com/Yubico/yubico-c
*/

/*
 * Written by Simon Josefsson <simon@josefsson.org>.
 * Copyright (c) 2006-2012 Yubico AB
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

#ifndef YKS_GENERATE_H
#define YKS_GENERATE_H

#include <YkCore.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define	YUBIKEY_PUB_SIZE	16
#define YUBIKEY_OTP_MAXSIZE	((YUBIKEY_BLOCK_SIZE + YUBIKEY_PUB_SIZE) * 2 + 1)

typedef struct {
	uint8_t		key[YUBIKEY_KEY_SIZE];
	uint8_t		prv[YUBIKEY_UID_SIZE];
	uint8_t		pub[YUBIKEY_PUB_SIZE];
	uint8_t		publen;
	uint8_t		usage;
	uint16_t	counter;
	uint32_t	timestamp;
} yubikey_ctx_st;

typedef yubikey_ctx_st *yubikey_ctx_t;

#define EXIT_FAILURE	1
#define EXIT_SUCCESS	0

extern void yubikey_init(
	yubikey_ctx_t	ctx,
	uint8_t		*aeskey,
	char		*yk_pubid,
	char		*yk_prvid,
	uint16_t	yk_counter,
	uint32_t	yk_time,
	uint32_t	seed);

extern void yubikey_simulate(
        char		*otp,
	yubikey_ctx_t	ctx);

#define MAX_counter	0x7fff
extern void yubikey_incr_timestamp (yubikey_ctx_t ctx);
extern int  yubikey_incr_counter   (yubikey_ctx_t ctx);
extern int  yubikey_incr_usage     (yubikey_ctx_t ctx);

#ifdef __cplusplus
}
#endif
#endif

