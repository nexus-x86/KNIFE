#ifndef ZOBRIST_H
#define ZOBRIST_H

#include "board.h"
#include "types.h"

extern uint64_t ZOBRIST_PIECES[12][64];
extern uint64_t ZOBRIST_EP_KEYS[64];
extern uint64_t ZOBRIST_CASTLE_KEYS[16];
extern uint64_t ZOBRIST_SIDE_KEY;

void InitZobristKeys();
uint64_t Zobrist(Board *board);
uint64_t PawnZobrist(Board *board);

static inline uint64_t KeyAfter(Board *board, const Move move) {
  if (!move) {
    return board->zobrist ^ ZOBRIST_SIDE_KEY;
  }
  
  const int from = From(move);
  const int to = To(move);
  const int moving = Moving(move);

  uint64_t newKey = board->zobrist ^ ZOBRIST_SIDE_KEY ^ ZOBRIST_PIECES[moving][from] ^ ZOBRIST_PIECES[moving][to];
  
  if (board->squares[to] != NO_PIECE) {
    newKey ^= ZOBRIST_PIECES[board->squares[to]][to];
  }

  return newKey;
}

#endif
