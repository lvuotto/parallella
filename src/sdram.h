#ifndef __MSG_H__
#define __MSG_H__


#include <stdint.h>


typedef struct ticks_s ticks_t;
typedef struct msg_s   msg_t;

struct ticks_s {
  double   t64;
  double   t32;
  double   t16;
  double   t8;
  double   ua64;
  double   ua32;
  double   ua16;
  double   ua8;
} __attribute__((packed));

struct msg_s {
  ticks_t  ticks[16];
  uint32_t finished;
} __attribute__((packed));


#endif /* __MSG_H__ */
