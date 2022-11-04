#pragma once

#include <stdint.h>

typedef uint8_t byte;

typedef enum {
  I32, F64, EXTERNREF
} wasm_type_t;

typedef enum {
  FUNC, GLOBAL, TABLE, MEMORY
} wasm_import_kind_t;

typedef struct {
  wasm_type_t tag;
  union {
    uint32_t i32;
    double f64;
    void* ref;
  } val;
} wasm_value_t;

typedef struct {
  int32_t length; // < 0 indicates a trap or error
  wasm_value_t* vals;
} wasm_values;

wasm_value_t parse_wasm_value(char* string);
void print_wasm_value(wasm_value_t val);
void trace_wasm_value(wasm_value_t val);

wasm_value_t wasm_i32_value(int32_t val);
wasm_value_t wasm_f64_value(double val);
wasm_value_t wasm_ref_value(void* val);

typedef struct {
  uint32_t initial;
  uint32_t max;
  unsigned has_max : 1;
} wasm_limits_t;

typedef struct {
  const char* mod_name;
  const char* member_name;
  wasm_import_kind_t kind;
  uint32_t index;
} wasm_import_decl_t;

typedef struct {
  uint8_t intrinsic;
  uint32_t sig_index;
  uint32_t code_start;
  uint32_t code_end;
} wasm_func_decl_t;

typedef struct {
  uint32_t num_params;
  wasm_type_t* params;
  uint32_t num_results;
  wasm_type_t* results;
} wasm_sig_decl_t;

typedef struct {
  wasm_limits_t limits;
} wasm_table_decl_t;

typedef struct {
  wasm_type_t type;
  unsigned mutable : 1;
  wasm_value_t init;
} wasm_global_decl_t;

typedef struct {
  uint32_t mem_offset;
  uint32_t bytes_start;
  uint32_t bytes_end;
} wasm_data_decl_t;

typedef struct {
  uint32_t table_offset;
  uint32_t length;
  uint32_t* func_indexes;
} wasm_elems_decl_t;

typedef struct {
  const byte* bytes_start;
  const byte* bytes_end;
  
  wasm_limits_t mem_limits;
  wasm_table_decl_t* table;
  
  uint32_t num_sigs;
  wasm_sig_decl_t* sigs;

  uint32_t num_imports;
  wasm_import_decl_t* imports;
  
  uint32_t num_funcs;
  wasm_func_decl_t* funcs;

  uint32_t num_globals;
  wasm_global_decl_t* globals;
  
  uint32_t num_data;
  wasm_data_decl_t* data;

  uint32_t num_elems;
  wasm_elems_decl_t* elems;

  int32_t start_func;
  int32_t main_func;
} wasm_module_t;

typedef struct {
  wasm_module_t* module;
  
  byte* mem_start;
  byte* mem_end;

  uint32_t* table;
  uint32_t table_size;

  wasm_value_t* globals;
} wasm_instance_t;

void init_wasm_module(wasm_module_t* module);

void rewrite_brs(byte* start, byte* end);
