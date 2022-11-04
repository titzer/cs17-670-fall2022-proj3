#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "common.h"
#include "disass.h"
#include "vm.h"
#include "test.h"
#include "weewasm.h"
#include "illegal.h"
#include "ir.h"

// Disassembles and runs a wasm module.
wasm_values run(const byte* start, const byte* end, wasm_values* args);

// Main function.
// Parses arguments and either runs the tests or runs a file with arguments.
//  -trace: enable tracing to stderr
//  -disassemble: disassemble sections and code while parsing
//  -test: run internal tests
int main(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];
    if (strcmp(arg, "-test") == 0) return run_tests();
    if (strcmp(arg, "-trace") == 0) {
      g_trace = 1;
      continue;
    }
    if (strcmp(arg, "-disassemble") == 0) {
      g_disassemble = 1;
      continue;
    }
    
    byte* start = NULL;
    byte* end = NULL;
    ssize_t r = load_file(arg, &start, &end);
    if (r >= 0) {
      TRACE("loaded %s: %ld bytes\n", arg, r);
      wasm_values args = { argc - i - 1, NULL };
      if (args.length > 0) {
	args.vals = (wasm_value_t*)malloc(sizeof(wasm_value_t) * args.length);
	for (int j = i + 1; j < argc; j++) {
	  int a = j - i - 1;
	  args.vals[a] = parse_wasm_value(argv[j]);
	  TRACE("args[%d] = ", a);
	  trace_wasm_value(args.vals[a]);
	  TRACE("\n");
	}
      }
      wasm_values result = run(start, end, &args);
      unload_file(&start, &end);
      if (result.length < 0) {
        printf("!trap\n");
        exit(1);
        return 1;
      } else {
        for (int i = 0; i < result.length; i++) {
          if (i > 0) printf(" ");
          print_wasm_value(result.vals[i]);
        }
        printf("\n");
        exit(0);
        return 0;
      }
    } else {
      ERR("failed to load: %s\n", arg);
      return 1;
    }
  }
  return 0;
}

// Your solution here
