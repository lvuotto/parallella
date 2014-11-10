#include "e-lib.h"
#include "sdram.h"
#include <string.h>


#define E_ROWS e_group_config.group_rows
#define E_COLS e_group_config.group_cols
#define VECES                      10000
#define DUMMY_WAIT                  1000
#define MEM_ALINEADA              0x6000


void opt_read(void *dst, const void *src, size_t n);


int main()
{
  msg_t *m = (msg_t *) 0x4000;
  uint64_t d64;
  uint32_t d32;
  uint16_t d16;
  uint8_t  d8;
  unsigned int dt;
  void *da;
  for (unsigned int row = 0; row < E_ROWS; row++) {
    for (unsigned int col = 0; col < E_COLS; col++) {
      unsigned int tcore = row * E_COLS + col;

      da = e_get_global_address(row, col, (void *) MEM_ALINEADA);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        opt_read(&d64, da, sizeof(d64));
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t64 = (dt - DUMMY_WAIT) / (double) VECES;

      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        opt_read(&d32, da, sizeof(d32));
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t32 = (dt - DUMMY_WAIT) / (double) VECES;

      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        opt_read(&d16, da, sizeof(d16));
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t16 = (dt - DUMMY_WAIT) / (double) VECES;

      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        opt_read(&d8, da, sizeof(d8));
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t8 = (dt - DUMMY_WAIT) / (double) VECES;
    }
  }
  m->finalizado = E_TRUE;

  return 0;
}


void opt_read(void *dst, const void *src, size_t n)
{
  if (n == 0) return;
  __asm__(
    "mov r4, %0\n\t"
    "mov r5, %1\n\t"
    "mov r6, %2\n\t"
    ".read_loop:\n\t"
    "ldrb r7, [r5], #1\n\t"
    "strb r7, [r4], #1\n\t"
    "sub r6, r6, #1\n\t"
    "bne .read_loop\n\t"
    : /* no output */
    : "r"(dst), "r"(src), "r"(n)
    : "memory", "r4", "r5", "r6", "r7"
  );
}
