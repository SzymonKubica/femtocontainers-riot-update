#include "bpf/bpfapi/helpers.h"
#include <stdint.h>
#include <string.h>

int temp_read(void *ctx) {
  (void)ctx;

  char *message =
      "This is a test message for the Fletcher32 checksum algorithm.\n";

  uint16_t *data = (uint16_t *)message;

  // Algorithm needs the length in words
  uint32_t len = strlen(message) / 2;

  uint32_t c0 = 0;
  uint32_t c1 = 0;

  /* We similarly solve for n > 0 and n * (n+1) / 2 * (2^16-1) < (2^32-1)
   * here.
   */
  /* On modern computers, using a 64-bit c0/c1 could allow a group size of
   * 23726746. */
  for (c0 = c1 = 0; len > 0;) {
    uint32_t blocklen = len;
    if (blocklen > 360 * 2) {
      blocklen = 360 * 2;
    }
    len -= blocklen;
    for (uint32_t i = 0; i < blocklen; i += 2) {
      char c = *(data);
      c0 = c0 + c;
      c1 = c1 + c0;
    }
    c0 = c0 % 65535;
    c1 = c1 % 65535;
  }

  uint32_t checksum = (c1 << 16 | c0);

  return checksum;

}
