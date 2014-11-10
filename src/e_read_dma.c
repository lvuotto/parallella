#include "e-lib.h"
#include "sdram.h"


#define E_ROWS e_group_config.group_rows
#define E_COLS e_group_config.group_cols
#define VECES                      10000
#define DUMMY_WAIT                  5000
#define MEM_ALINEADA              0x6000
#define MEM_NO_ALINEADA           0x6003
#define MEM_A_CABALLO             0x5fff


int main()
{
  msg_t *m = (msg_t *) 0x4000;
  uint64_t d64;
  uint32_t d32;
  uint16_t d16;
  uint8_t  d8;
  unsigned int dt;
  void *da, *dua, *dc;
  for (unsigned int row = 0; row < E_ROWS; row++) {
    for (unsigned int col = 0; col < E_COLS; col++) {
      if (row == 0 && col == 0) continue;
      unsigned int tcore = row * E_COLS + col;

      da = e_get_global_address(row, col, (void *) MEM_ALINEADA);
      dua = e_get_global_address(row, col, (void *) MEM_NO_ALINEADA);
      dc = e_get_global_address(row, col, (void *) MEM_A_CABALLO);

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d64, da, sizeof(d64));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t64 = (dt - DUMMY_WAIT) / (double) VECES;

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d32, da, sizeof(d32));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t32 = (dt - DUMMY_WAIT) / (double) VECES;

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d16, da, sizeof(d16));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t16 = (dt - DUMMY_WAIT) / (double) VECES;

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d8, da, sizeof(d8));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].t8 = (dt - DUMMY_WAIT) / (double) VECES;

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d64, dua, sizeof(d64));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].ua64 = (dt - DUMMY_WAIT) / (double) VECES;

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d32, dua, sizeof(d32));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].ua32 = (dt - DUMMY_WAIT) / (double) VECES;

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d16, dua, sizeof(d16));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].ua16 = (dt - DUMMY_WAIT) / (double) VECES;

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d8, dua, sizeof(d8));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].ua8 = (dt - DUMMY_WAIT) / (double) VECES;

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d64, dua, sizeof(d64));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].c64 = (dt - DUMMY_WAIT) / (double) VECES;

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d32, dc, sizeof(d32));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].c32 = (dt - DUMMY_WAIT) / (double) VECES;

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d16, dc, sizeof(d16));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].c16 = (dt - DUMMY_WAIT) / (double) VECES;

      e_dma_wait(E_DMA_1);
      e_ctimer_set(E_CTIMER_0, E_CTIMER_MAX);
      e_ctimer_start(E_CTIMER_0, E_CTIMER_CLK);
      for (int i = 0; i < VECES; i++)
        e_dma_copy(&d8, dc, sizeof(d8));
      e_dma_wait(E_DMA_1);
      e_wait(E_CTIMER_1, DUMMY_WAIT);
      e_ctimer_stop(E_CTIMER_0);
      dt = E_CTIMER_MAX - e_ctimer_get(E_CTIMER_0);
      m->ticks[tcore].c8 = (dt - DUMMY_WAIT) / (double) VECES;
    }
  }
  m->finalizado = E_TRUE;

  return 0;
}
