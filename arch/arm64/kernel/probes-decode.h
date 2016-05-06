/*
 * arch/arm64/kernel/probes-decode.h
 *
 * Copyright (C) 2013 Linaro Limited.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#ifndef _ARM_KERNEL_PROBES_DECODE_H
#define _ARM_KERNEL_PROBES_DECODE_H

/*
 * The following definitions and macros are used to build instruction
 * decoding tables.
 */
enum decode_type {
	DECODE_TYPE_END,
	DECODE_TYPE_SINGLESTEP,
	DECODE_TYPE_SIMULATE,
	DECODE_TYPE_TABLE,
	DECODE_TYPE_REJECT,
};

struct aarch64_decode_item;

struct aarch64_decode_header {
	enum decode_type type;
	u32 mask;
	u32 val;
};

struct aarch64_decode_actions {
	kprobes_prepare_t *prepare;
	kprobes_handler_t *handler;
};

struct aarch64_decode_table {
	const struct aarch64_decode_item *tbl;
};

union aarch64_decode_handler {
	struct aarch64_decode_actions actions;
	struct aarch64_decode_table table;
};

struct aarch64_decode_item {
	struct aarch64_decode_header header;
	union aarch64_decode_handler decode;
};

#define decode_get_type(_entry)	 ((_entry).header.type)

#define decode_table_end(_entry)		\
	((_entry).header.type == DECODE_TYPE_END)

#define decode_table_hit(_entry, insn)		\
	((insn & (_entry).header.mask) == (_entry).header.val)

#define decode_prepare_fn(_entry)	((_entry).decode.actions.prepare)
#define decode_handler_fn(_entry)	((_entry).decode.actions.handler)
#define decode_sub_table(_entry)	((_entry).decode.table.tbl)

#define DECODE_ADD_HEADER(_type, _val, _mask)	\
	.header = {				\
		.type = _type,			\
		.mask = _mask,			\
		.val = _val,			\
	},

#define DECODE_ADD_ACTION(_prepare, _handler)	\
	.decode = {				\
		.actions = {			\
			.prepare = _prepare,	\
			.handler = _handler,	\
		}				\
	},

#define DECODE_ADD_TABLE(_table)		\
	.decode = {				\
		.table = {.tbl = _table}	\
	},

#define DECODE_REJECT(_v, _m)					\
	{ DECODE_ADD_HEADER(DECODE_TYPE_REJECT, _v, _m) }

#define DECODE_SINGLESTEP(_v, _m)				\
	{ DECODE_ADD_HEADER(DECODE_TYPE_SINGLESTEP, _v, _m) }

#define DECODE_SIMULATE(_v, _m, _p, _h)				\
	{ DECODE_ADD_HEADER(DECODE_TYPE_SIMULATE, _v, _m)	\
	  DECODE_ADD_ACTION(_p, _h) }

#define DECODE_TABLE(_v, _m, _table)				\
	{ DECODE_ADD_HEADER(DECODE_TYPE_TABLE, _v, _m)		\
	  DECODE_ADD_TABLE(_table) }

#define DECODE_LITERAL(_v, _m, _p, _h)	DECODE_SIMULATE(_v, _m, _p, _h)
#define DECODE_BRANCH(_v, _m, _p, _h)	DECODE_SIMULATE(_v, _m, _p, _h)

/* should be the last element in decode structure */
#define DECODE_END	{ .header = {.type = DECODE_TYPE_END, } }

#endif /* _ARM_KERNEL_PROBES_DECODE_H */
