#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <e-hal.h>

#include "msg.h"


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


void benchmark(e_platform_t *platform,
               e_epiphany_t *device,
               char *wrfn,
               char *rdfn);


int main()
{
  e_platform_t platform;

  e_init(NULL);
  e_reset_system();
  e_get_platform_info(&platform);

  e_epiphany_t device;
  e_open(&device, 0, 0, platform.rows, platform.cols);
  
  puts("Epiphany plano");
  puts("--------------");
  benchmark(&platform, &device, "e_write.srec", "e_read.srec");
  
  puts("");
  puts("Assembler inline");
  puts("----------------");
  benchmark(&platform, &device, "e_write_asm.srec", "e_read_asm.srec");
  
  e_close(&device);
  e_finalize();

  return 0;
}


void benchmark(e_platform_t *platform,
               e_epiphany_t *device,
               char *wrfn,
               char *rdfn)
{
  int status;
  unsigned int tcore;
  static msg_t msg;
  e_mem_t mem;
  
  memset(&msg, 0, sizeof(msg));
  e_alloc(&mem, BMMI_ADDRESS, sizeof(msg));
  e_write(&mem, 0, 0, 0, &msg, sizeof(msg));
 
  e_reset_group(device);
  status = e_load(wrfn, device, 0, 0, E_TRUE);

  if (status != E_OK) {
    fprintf(stderr, "Hubo un error al cargar.\n");
    exit(1);
  }

  do {
    e_read(&mem, 0, 0, 0, &msg, sizeof(msg));
  } while (!msg.finished);

  puts("  WR");
  for (unsigned int row = 0; row < platform->rows; row++) {
    for (unsigned int col = 0; col < platform->cols; col++) {
      tcore = row*platform->cols + col;
      printf("  tcore#%-2u: t32=%.3f, t16=%.3f, t8=%.3f\n",
             tcore,
             msg.ticks[tcore].t32,
             msg.ticks[tcore].t16,
             msg.ticks[tcore].t8);
    }
  }

  e_reset_group(device);
  memset(&msg, 0, sizeof(msg));
  status = e_load(rdfn, device, 0, 0, E_TRUE);

  if (status != E_OK) {
    fprintf(stderr, "Hubo un error al cargar.\n");
    exit(1);
  }

  nano_wait(0, 10000000);

  do {
    e_read(&mem, 0, 0, 0, &msg, sizeof(msg));
  } while (!msg.finished);
  
  puts("");
  puts("  RD");
  for (unsigned int row = 0; row < platform->rows; row++) {
    for (unsigned int col = 0; col < platform->cols; col++) {
      tcore = row*platform->cols + col;
      printf("  tcore#%-2u: t32=%.3f, t16=%.3f, t8=%.3f\n",
             tcore,
             msg.ticks[tcore].t32,
             msg.ticks[tcore].t16,
             msg.ticks[tcore].t8);
    }
  }

  e_free(&mem);
}
