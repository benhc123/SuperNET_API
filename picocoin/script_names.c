/* Copyright 2012 exMULTI, Inc.
 * Distributed under the MIT/X11 software license, see the accompanying
 * file COPYING or http://www.opensource.org/licenses/mit-license.php.
 */
#include "picocoin-config.h"

#include <ccoin/script.h>
#include <ccoin/util.h>

static const char *opnames[256] = {
	[OP_0] = "OP_0",
	[OP_PUSHDATA1] = "OP_PUSHDATA1",
	[OP_PUSHDATA2] = "OP_PUSHDATA2",
	[OP_PUSHDATA4] = "OP_PUSHDATA4",
	[OP_1NEGATE] = "OP_1NEGATE",
	[OP_RESERVED] = "OP_RESERVED",
	[OP_1] = "OP_1",
	[OP_2] = "OP_2",
	[OP_3] = "OP_3",
	[OP_4] = "OP_4",
	[OP_5] = "OP_5",
	[OP_6] = "OP_6",
	[OP_7] = "OP_7",
	[OP_8] = "OP_8",
	[OP_9] = "OP_9",
	[OP_10] = "OP_10",
	[OP_11] = "OP_11",
	[OP_12] = "OP_12",
	[OP_13] = "OP_13",
	[OP_14] = "OP_14",
	[OP_15] = "OP_15",
	[OP_16] = "OP_16",

	[OP_NOP] = "OP_NOP",
	[OP_VER] = "OP_VER",
	[OP_IF] = "OP_IF",
	[OP_NOTIF] = "OP_NOTIF",
	[OP_VERIF] = "OP_VERIF",
	[OP_VERNOTIF] = "OP_VERNOTIF",
	[OP_ELSE] = "OP_ELSE",
	[OP_ENDIF] = "OP_ENDIF",
	[OP_VERIFY] = "OP_VERIFY",
	[OP_RETURN] = "OP_RETURN",

	[OP_TOALTSTACK] = "OP_TOALTSTACK",
	[OP_FROMALTSTACK] = "OP_FROMALTSTACK",
	[OP_2DROP] = "OP_2DROP",
	[OP_2DUP] = "OP_2DUP",
	[OP_3DUP] = "OP_3DUP",
	[OP_2OVER] = "OP_2OVER",
	[OP_2ROT] = "OP_2ROT",
	[OP_2SWAP] = "OP_2SWAP",
	[OP_IFDUP] = "OP_IFDUP",
	[OP_DEPTH] = "OP_DEPTH",
	[OP_DROP] = "OP_DROP",
	[OP_DUP] = "OP_DUP",
	[OP_NIP] = "OP_NIP",
	[OP_OVER] = "OP_OVER",
	[OP_PICK] = "OP_PICK",
	[OP_ROLL] = "OP_ROLL",
	[OP_ROT] = "OP_ROT",
	[OP_SWAP] = "OP_SWAP",
	[OP_TUCK] = "OP_TUCK",

	[OP_CAT] = "OP_CAT",
	[OP_SUBSTR] = "OP_SUBSTR",
	[OP_LEFT] = "OP_LEFT",
	[OP_RIGHT] = "OP_RIGHT",
	[OP_SIZE] = "OP_SIZE",

	[OP_INVERT] = "OP_INVERT",
	[OP_AND] = "OP_AND",
	[OP_OR] = "OP_OR",
	[OP_XOR] = "OP_XOR",
	[OP_EQUAL] = "OP_EQUAL",
	[OP_EQUALVERIFY] = "OP_EQUALVERIFY",
	[OP_RESERVED1] = "OP_RESERVED1",
	[OP_RESERVED2] = "OP_RESERVED2",

	[OP_1ADD] = "OP_1ADD",
	[OP_1SUB] = "OP_1SUB",
	[OP_2MUL] = "OP_2MUL",
	[OP_2DIV] = "OP_2DIV",
	[OP_NEGATE] = "OP_NEGATE",
	[OP_ABS] = "OP_ABS",
	[OP_NOT] = "OP_NOT",
	[OP_0NOTEQUAL] = "OP_0NOTEQUAL",

	[OP_ADD] = "OP_ADD",
	[OP_SUB] = "OP_SUB",
	[OP_MUL] = "OP_MUL",
	[OP_DIV] = "OP_DIV",
	[OP_MOD] = "OP_MOD",
	[OP_LSHIFT] = "OP_LSHIFT",
	[OP_RSHIFT] = "OP_RSHIFT",

	[OP_BOOLAND] = "OP_BOOLAND",
	[OP_BOOLOR] = "OP_BOOLOR",
	[OP_NUMEQUAL] = "OP_NUMEQUAL",
	[OP_NUMEQUALVERIFY] = "OP_NUMEQUALVERIFY",
	[OP_NUMNOTEQUAL] = "OP_NUMNOTEQUAL",
	[OP_LESSTHAN] = "OP_LESSTHAN",
	[OP_GREATERTHAN] = "OP_GREATERTHAN",
	[OP_LESSTHANOREQUAL] = "OP_LESSTHANOREQUAL",
	[OP_GREATERTHANOREQUAL] = "OP_GREATERTHANOREQUAL",
	[OP_MIN] = "OP_MIN",
	[OP_MAX] = "OP_MAX",

	[OP_WITHIN] = "OP_WITHIN",

	[OP_RIPEMD160] = "OP_RIPEMD160",
	[OP_SHA1] = "OP_SHA1",
	[OP_SHA256] = "OP_SHA256",
	[OP_HASH160] = "OP_HASH160",
	[OP_HASH256] = "OP_HASH256",
	[OP_CODESEPARATOR] = "OP_CODESEPARATOR",
	[OP_CHECKSIG] = "OP_CHECKSIG",
	[OP_CHECKSIGVERIFY] = "OP_CHECKSIGVERIFY",
	[OP_CHECKMULTISIG] = "OP_CHECKMULTISIG",
	[OP_CHECKMULTISIGVERIFY] = "OP_CHECKMULTISIGVERIFY",

	[OP_NOP1] = "OP_NOP1",
	[OP_NOP2] = "OP_NOP2",
	[OP_NOP3] = "OP_NOP3",
	[OP_NOP4] = "OP_NOP4",
	[OP_NOP5] = "OP_NOP5",
	[OP_NOP6] = "OP_NOP6",
	[OP_NOP7] = "OP_NOP7",
	[OP_NOP8] = "OP_NOP8",
	[OP_NOP9] = "OP_NOP9",
	[OP_NOP10] = "OP_NOP10",



	[OP_SMALLINTEGER] = "OP_SMALLINTEGER",
	[OP_PUBKEYS] = "OP_PUBKEYS",
	[OP_PUBKEYHASH] = "OP_PUBKEYHASH",
	[OP_PUBKEY] = "OP_PUBKEY",
};

const char *GetOpName(enum opcodetype opcode_)
{
	int idx = (int) opcode_;

	if (idx >= 0 && idx < 256) {
		const char *name = opnames[idx];
		if (name)
			return name;
	}

	return "<unknown>";
}

enum opcodetype GetOpType(const char *opname)
{
	unsigned int i;
	char tmpname[64];

	for (i = 0; i < ARRAY_SIZE(opnames); i++) {
		if (opnames[i]) {
			if (!strcmp(opname, opnames[i]))
				return (enum opcodetype) i;

			strcpy(tmpname, "OP_");
			strcat(tmpname, opname);
			if (!strcmp(tmpname, opnames[i]))
				return (enum opcodetype) i;
		}
	}

	return OP_INVALIDOPCODE;
}

