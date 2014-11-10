#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <e-hal.h>

#include "sdram.h"


/*
static inline uint32_t rdtsc32 (void) {
#if defined(__GNUC__) && defined(__ARM_ARCH_7A__)
  uint32_t r = 0;
  asm volatile("mrc p15, 0, %0, c9, c13, 0" : "=r"(r) );
  return r;
#else
# error Unsupported architecture/compiler!
#endif
}
*/


void benchmark_r(e_platform_t *platform,
                 e_epiphany_t *device,
                 char *srec);
void benchmark_w(e_platform_t *platform,
                 e_epiphany_t *device,
                 char *srec);


int main()
{
  e_platform_t platform;

  e_init(NULL);
  e_reset_system();
  e_get_platform_info(&platform);

  e_epiphany_t device;
  e_open(&device, 0, 0, platform.rows, platform.cols);

  benchmark_r(&platform, &device, "e_read.srec");
  puts("---------------------------------------------------------");
  benchmark_r(&platform, &device, "e_read_dma.srec");
  puts("---------------------------------------------------------");
  benchmark_r(&platform, &device, "e_read_asm.srec");
  puts("---------------------------------------------------------");
  benchmark_w(&platform, &device, "e_write.srec");
  
  e_close(&device);
  e_finalize();

  return 0;
}


void benchmark_r(e_platform_t *platform,
                 e_epiphany_t *device,
                 char *srec)
{
  msg_t msg;
  memset(&msg, 0, sizeof(msg));

  e_write(device, 0, 0, 0x4000, &msg, sizeof(msg));

  e_reset_group(device);
  if (e_load(srec, device, 0, 0, E_TRUE) != E_OK) {
    fprintf(stderr, "Hubo un error al cargar.\n");
    exit(1);
  }

  do {
    e_read(device, 0, 0, 0x4000, &msg, sizeof(msg));
    fprintf(stderr,
            "[%"PRIx32", %"PRIx32", %"PRIx32", %"PRIx32"], finalizado = %u\n",
            msg.v[0], msg.v[1], msg.v[2], msg.v[3], msg.finalizado);
  } while (!msg.finalizado);

  for (unsigned int row = 0; row < platform->rows; row++) {
    for (unsigned int col = 0; col < platform->cols; col++) {
      unsigned int tcore = row * platform->cols + col;
      printf("  tcore#%x:  t64: %.3f,  t32: %.3f,  t16: %.3f,  t8: %.3f,\n"
             "           ua64: %.3f, ua32: %.3f, ua16: %.3f, ua8: %.3f,\n"
             "            c64: %.3f,  c32: %.3f,  c16: %.3f,  c8: %.3f,\n"
             "           v[0]: %"PRIx32", v[1]: %"PRIx32", v[2]: %"PRIx32", v[3]: %"PRIx32"\n",
             tcore,
             msg.ticks[tcore].t64,  msg.ticks[tcore].t32,
             msg.ticks[tcore].t16,  msg.ticks[tcore].t8,
             msg.ticks[tcore].ua64, msg.ticks[tcore].ua32,
             msg.ticks[tcore].ua16, msg.ticks[tcore].ua8,
             msg.ticks[tcore].c64, msg.ticks[tcore].c32,
             msg.ticks[tcore].c16, msg.ticks[tcore].c8,
             msg.v[0], msg.v[1], msg.v[2], msg.v[3]);
    }
  }
}


void benchmark_w(e_platform_t *platform,
                 e_epiphany_t *device,
                 char *srec)
{
  msg_t msg;
  memset(&msg, 0, sizeof(msg));

  e_write(device, 0, 0, 0x4000, &msg, sizeof(msg));

  e_reset_group(device);
  if (e_load(srec, device, 0, 1, E_TRUE) != E_OK) {
    fprintf(stderr, "Hubo un error al cargar.\n");
    exit(1);
  }
  if (e_load(srec, device, 0, 0, E_TRUE) != E_OK) {
    fprintf(stderr, "Hubo un error al cargar.\n");
    exit(1);
  }

  do {
    e_read(device, 0, 0, 0x4000, &msg, sizeof(msg));
    fprintf(stderr,
            "[%"PRIx32", %"PRIx32", %"PRIx32", %"PRIx32"], finalizado = %u\n",
            msg.v[0], msg.v[1], msg.v[2], msg.v[3], msg.finalizado);
  } while (!msg.finalizado);

  for (unsigned int row = 0; row < platform->rows; row++) {
    for (unsigned int col = 0; col < platform->cols; col++) {
      unsigned int tcore = row * platform->cols + col;
      printf("  tcore#%x:  t64: %.3f,  t32: %.3f,  t16: %.3f,  t8: %.3f,\n"
             "           ua64: %.3f, ua32: %.3f, ua16: %.3f, ua8: %.3f,\n"
             "            c64: %.3f,  c32: %.3f,  c16: %.3f,  c8: %.3f,\n"
             "           v[0]: %"PRIx32", v[1]: %"PRIx32", v[2]: %"PRIx32", v[3]: %"PRIx32"\n",
             tcore,
             msg.ticks[tcore].t64,  msg.ticks[tcore].t32,
             msg.ticks[tcore].t16,  msg.ticks[tcore].t8,
             msg.ticks[tcore].ua64, msg.ticks[tcore].ua32,
             msg.ticks[tcore].ua16, msg.ticks[tcore].ua8,
             msg.ticks[tcore].c64, msg.ticks[tcore].c32,
             msg.ticks[tcore].c16, msg.ticks[tcore].c8,
             msg.v[0], msg.v[1], msg.v[2], msg.v[3]);
    }
  }
}
