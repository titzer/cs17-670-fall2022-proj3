#pragma once

#define WASM_MAGIC 0x6d736100u
#define WASM_VERSION 1

// Section constants
#define WASM_SECT_TYPE 1
#define WASM_SECT_IMPORT 2
#define WASM_SECT_FUNCTION 3
#define WASM_SECT_TABLE 4
#define WASM_SECT_MEMORY 5
#define WASM_SECT_GLOBAL 6
#define WASM_SECT_EXPORT 7
#define WASM_SECT_START 8
#define WASM_SECT_ELEMENT 9
#define WASM_SECT_CODE 10
#define WASM_SECT_DATA 11

// Opcode constants
#define WASM_OP_UNREACHABLE		0x00 /* "unreachable" */
#define WASM_OP_NOP			0x01 /* "nop" */
#define WASM_OP_BLOCK			0x02 /* "block" BLOCKT */
#define WASM_OP_LOOP			0x03 /* "loop" BLOCKT */
#define WASM_OP_END			0x0B /* "end" */
#define WASM_OP_BR			0x0C /* "br" LABEL */
#define WASM_OP_BR_IF			0x0D /* "br_if" LABEL */
#define WASM_OP_BR_TABLE		0x0E /* "br_table" LABELS */
#define WASM_OP_RETURN			0x0F /* "return" */
#define WASM_OP_CALL			0x10 /* "call" FUNC */
#define WASM_OP_CALL_INDIRECT		0x11 /* "call_indirect" SIG_TABLE */
#define WASM_OP_DROP			0x1A /* "drop" */
#define WASM_OP_SELECT			0x1B /* "select" */
#define WASM_OP_LOCAL_GET		0x20 /* "local.get" LOCAL */
#define WASM_OP_LOCAL_SET		0x21 /* "local.set" LOCAL */
#define WASM_OP_LOCAL_TEE		0x22 /* "local.tee" LOCAL */
#define WASM_OP_GLOBAL_GET		0x23 /* "global.get" GLOBAL */
#define WASM_OP_GLOBAL_SET		0x24 /* "global.set" GLOBAL */
#define WASM_OP_I32_LOAD		0x28 /* "i32.load" MEMARG */
#define WASM_OP_F64_LOAD		0x2B /* "f64.load" MEMARG */
#define WASM_OP_I32_LOAD8_S		0x2C /* "i32.load8_s" MEMARG */
#define WASM_OP_I32_LOAD8_U		0x2D /* "i32.load8_u" MEMARG */
#define WASM_OP_I32_LOAD16_S		0x2E /* "i32.load16_s" MEMARG */
#define WASM_OP_I32_LOAD16_U		0x2F /* "i32.load16_u" MEMARG */
#define WASM_OP_I32_STORE		0x36 /* "i32.store" MEMARG */
#define WASM_OP_F64_STORE		0x39 /* "f64.store" MEMARG */
#define WASM_OP_I32_STORE8		0x3A /* "i32.store8" MEMARG */
#define WASM_OP_I32_STORE16		0x3B /* "i32.store16" MEMARG */
#define WASM_OP_I32_CONST		0x41 /* "i32.const" I32 */
#define WASM_OP_F64_CONST		0x44 /* "f64.const" F64 */
#define WASM_OP_I32_EQZ			0x45 /* "i32.eqz" */
#define WASM_OP_I32_EQ			0x46 /* "i32.eq" */
#define WASM_OP_I32_NE			0x47 /* "i32.ne" */
#define WASM_OP_I32_LT_S		0x48 /* "i32.lt_s" */
#define WASM_OP_I32_LT_U		0x49 /* "i32.lt_u" */
#define WASM_OP_I32_GT_S		0x4A /* "i32.gt_s" */
#define WASM_OP_I32_GT_U		0x4B /* "i32.gt_u" */
#define WASM_OP_I32_LE_S		0x4C /* "i32.le_s" */
#define WASM_OP_I32_LE_U		0x4D /* "i32.le_u" */
#define WASM_OP_I32_GE_S		0x4E /* "i32.ge_s" */
#define WASM_OP_I32_GE_U		0x4F /* "i32.ge_u" */
#define WASM_OP_F64_EQ			0x61 /* "f64.eq" */
#define WASM_OP_F64_NE			0x62 /* "f64.ne" */
#define WASM_OP_F64_LT			0x63 /* "f64.lt" */
#define WASM_OP_F64_GT			0x64 /* "f64.gt" */
#define WASM_OP_F64_LE			0x65 /* "f64.le" */
#define WASM_OP_F64_GE			0x66 /* "f64.ge" */
#define WASM_OP_I32_CLZ			0x67 /* "i32.clz" */
#define WASM_OP_I32_CTZ			0x68 /* "i32.ctz" */
#define WASM_OP_I32_POPCNT		0x69 /* "i32.popcnt" */
#define WASM_OP_I32_ADD			0x6A /* "i32.add" */
#define WASM_OP_I32_SUB			0x6B /* "i32.sub" */
#define WASM_OP_I32_MUL			0x6C /* "i32.mul" */
#define WASM_OP_I32_DIV_S		0x6D /* "i32.div_s" */
#define WASM_OP_I32_DIV_U		0x6E /* "i32.div_u" */
#define WASM_OP_I32_REM_S		0x6F /* "i32.rem_s" */
#define WASM_OP_I32_REM_U		0x70 /* "i32.rem_u" */
#define WASM_OP_I32_AND			0x71 /* "i32.and" */
#define WASM_OP_I32_OR			0x72 /* "i32.or" */
#define WASM_OP_I32_XOR			0x73 /* "i32.xor" */
#define WASM_OP_I32_SHL			0x74 /* "i32.shl" */
#define WASM_OP_I32_SHR_S		0x75 /* "i32.shr_s" */
#define WASM_OP_I32_SHR_U		0x76 /* "i32.shr_u" */
#define WASM_OP_I32_ROTL		0x77 /* "i32.rotl" */
#define WASM_OP_I32_ROTR		0x78 /* "i32.rotr" */
#define WASM_OP_F64_ADD			0xA0 /* "f64.add" */
#define WASM_OP_F64_SUB			0xA1 /* "f64.sub" */
#define WASM_OP_F64_MUL			0xA2 /* "f64.mul" */
#define WASM_OP_F64_DIV			0xA3 /* "f64.div" */
#define WASM_OP_I32_TRUNC_F64_S		0xAA /* "i32.trunc_f64_s" */
#define WASM_OP_I32_TRUNC_F64_U		0xAB /* "i32.trunc_f64_u" */
#define WASM_OP_F64_CONVERT_I32_S	0xB7 /* "f64.convert_i32_s" */
#define WASM_OP_F64_CONVERT_I32_U	0xB8 /* "f64.convert_i32_u" */
#define WASM_OP_I32_EXTEND8_S		0xC0 /* "i32.extend8_s" */
#define WASM_OP_I32_EXTEND16_S		0xC1 /* "i32.extend16_s" */

#define WASM_OP_JMP                     0xF0 /* "jmp" */
#define WASM_OP_JMP_IF                  0xF1 /* "jmp_if */
#define WASM_OP_JMP_TABLE               0xF2 /*  jmp_table */

#define WEEWASM_INTRINSIC_PUTI 0x01
#define WEEWASM_INTRINSIC_PUTD 0x02
#define WEEWASM_INTRINSIC_PUTS 0x03
