#include <inttypes.h>
#include <stdio.h>

void echo(int64_t value) { printf("%" PRId64 "\n", value); }

int64_t read() {
  int64_t value;
  scanf("%" SCNd64, &value);
  return value;
}
