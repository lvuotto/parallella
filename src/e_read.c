#include "e-lib.h"
#include "sdram.h"


#define E_ROWS e_group_config.group_rows
#define E_COLS e_group_config.group_cols
#define VECES                      10000
#define DUMMY_WAIT                  5000
#define MEM_ALINEADA              0x7000
#define MEM_NO_ALINEADA           0x7003


int main()
{
  msg_t *m = (msg_t *) 0x4000;
  uint64_t d64;
  uint32_t d32;
  uint16_t d16;
  uint8_t  d8;
  unsigned int dt;
  for (unsigned int row = 0; row < E_ROWS; row++) {
    for (unsigned int col = 0; col < E_COLS; col++) {
      unsigned int tcore = row * E_COLS + col;

      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_read(&e_group_config, &d64,
               row, col,
               (uint64_t *) MEM_ALINEADA, sizeof(d64));
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t64 = (dt - DUMMY_WAIT) / (double) VECES;

      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_read(&e_group_config, &d32,
               row, col,
               (uint32_t *) MEM_ALINEADA, sizeof(d32));
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t32 = (dt - DUMMY_WAIT) / (double) VECES;

      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_read(&e_group_config, &d16,
               row, col,
               (uint16_t *) MEM_ALINEADA, sizeof(d16));
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t16 = (dt - DUMMY_WAIT) / (double) VECES;

      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_read(&e_group_config, &d8,
               row, col,
               (uint8_t *) MEM_ALINEADA, sizeof(d8));
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t8 = (dt - DUMMY_WAIT) / (double) VECES;

      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_read(&e_group_config, &d64,
               row, col,
               (uint64_t *) MEM_NO_ALINEADA, sizeof(d64));
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].ua64 = (dt - DUMMY_WAIT) / (double) VECES;

      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_read(&e_group_config, &d32,
               row, col,
               (uint32_t *) MEM_NO_ALINEADA, sizeof(d32));
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].ua32 = (dt - DUMMY_WAIT) / (double) VECES;

      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_read(&e_group_config, &d16,
               row, col,
               (uint16_t *) MEM_NO_ALINEADA, sizeof(d16));
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].ua16 = (dt - DUMMY_WAIT) / (double) VECES;

      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_read(&e_group_config, &d8,
               row, col,
               (uint8_t *) MEM_NO_ALINEADA, sizeof(d8));
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].ua8 = (dt - DUMMY_WAIT) / (double) VECES;
    }
  }
  m->finalizado = E_TRUE;

  return 0;
}
