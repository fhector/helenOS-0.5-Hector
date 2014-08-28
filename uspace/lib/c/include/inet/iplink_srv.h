/*
 * Copyright (c) 2012 Jiri Svoboda
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * - The name of the author may not be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/** @addtogroup libc
 * @{
 */
/** @file
 */

#ifndef LIBC_INET_IPLINK_SRV_H_
#define LIBC_INET_IPLINK_SRV_H_

#include <async.h>
#include <fibril_synch.h>
#include <bool.h>
#include <sys/types.h>

struct iplink_ops;

typedef struct {
	fibril_mutex_t lock;
	bool connected;
	struct iplink_ops *ops;
	void *arg;
	async_sess_t *client_sess;
} iplink_srv_t;

typedef struct {
	uint32_t ipv4;
} iplink_srv_addr_t;

/** IP link Service Data Unit */
typedef struct {
	/** Local source address */
	iplink_srv_addr_t lsrc;
	/** Local destination address */
	iplink_srv_addr_t ldest;
	/** Serialized IP packet */
	void *data;
	/** Size of @c data in bytes */
	size_t size;
} iplink_srv_sdu_t;

typedef struct iplink_ops {
	int (*open)(iplink_srv_t *);
	int (*close)(iplink_srv_t *);
	int (*send)(iplink_srv_t *, iplink_srv_sdu_t *);
	int (*get_mtu)(iplink_srv_t *, size_t *);
	int (*addr_add)(iplink_srv_t *, iplink_srv_addr_t *);
	int (*addr_remove)(iplink_srv_t *, iplink_srv_addr_t *);
} iplink_ops_t;

extern void iplink_srv_init(iplink_srv_t *);

extern int iplink_conn(ipc_callid_t, ipc_call_t *, void *);
extern int iplink_ev_recv(iplink_srv_t *, iplink_srv_sdu_t *);

#endif

/** @}
 */
