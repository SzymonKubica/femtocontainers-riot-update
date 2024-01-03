#include "bpf/bpfapi/helpers.h"
#include <stdint.h>

int temp_read(void *ctx) {
  (void)ctx;
  unsigned type = 0x42; /* Temperature sensor */
  bpf_saul_reg_t *sensor;
  phydat_t measurement;

  /* Find temp sensor */
  sensor = bpf_saul_reg_find_type(type);

  if (!sensor || (bpf_saul_reg_read(sensor, &measurement) < 0)) {
    return 2790; /* random temperature to simulate */
  }

  char *message =
      "This is a test message for the Fletcher32 checksum algorithm.\n";

  uint16_t *data = (uint16_t *)message;

  // Algorithm needs the length in words
  size_t len = strlen(message) / 2;

  uint32_t c0 = 0;
  uint32_t c1 = 0;

  /* We similarly solve for n > 0 and n * (n+1) / 2 * (2^16-1) < (2^32-1)
   * here.
   */
  /* On modern computers, using a 64-bit c0/c1 could allow a group size of
   * 23726746. */
  for (c0 = c1 = 0; len > 0;) {
    size_t blocklen = len;
    if (blocklen > 360 * 2) {
      blocklen = 360 * 2;
    }
    len -= blocklen;
    for (size_t i = 0; i < blocklen; i += 2) {
      bpf_trace_printk("", 20, *data);
      char c = *(data);
      c0 = c0 + c;
      c1 = c1 + c0;
    }
    c0 = c0 % 65535;
    c1 = c1 % 65535;
  }

  uint32_t checksum = (c1 << 16 | c0);

  return checksum;

  /** format */
  return measurement.val[0] * 100;
}
