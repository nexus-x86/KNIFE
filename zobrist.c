#include "zobrist.h"
#include "types.h"

uint64_t ZOBRIST_PIECES[12][64];
uint64_t ZOBRIST_EP_KEYS[64];
uint64_t ZOBRIST_CASTLE_KEYS[16];
uint64_t ZOBRIST_SIDE_KEY;

void InitZobristKeys() {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j <
