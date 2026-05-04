#include "zobrist.h"
#include "types.h"

uint64_t ZOBRIST_PIECES[12][64];
uint64_t ZOBRIST_EP_KEYS[64];
uint64_t ZOBRIST_CASTLE_KEYS[16];
uint64_t ZOBRIST_SIDE_KEY;

static inline int PopLSB(Bitboard *bb) {
  int sq = LSB(*bb);
  *bb &= *bb - 1;
  return sq;
}

void InitZobristKeys() {
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 64; j++) {
       ZOBRIST_PIECES[i][j] = RandomUInt64();
    }
  }

  for (int i = 0; i < 64; i++) {
    ZOBRIST_EP_KEYS[i] = RandomUInt64();
  }

  for (int i = 0; i < 16; i++) {
    ZOBRIST_CASTLE_KEYS[i] = RandomUInt64();
  }

  ZOBRIST_SIDE_KEY = RandomUInt64();
}

uint64_t Zobrist(Board* board) {
  uint64_t hash = 0ULL;

  for (int piece = WHITE_PAWN; piece <= BLACK_KING; piece++) {
    Bitboard pcs = board->pieces[piece];
    while (pcs) {
      hash ^= ZOBRIST_PIECES[piece][PopLSB(&pcs)];
    }
  }

  if (board->epSquare) {
    hash ^= ZOBRIST_EP_KEYS[board->epSquare];
  }

  hash ^= ZOBRIST_CASTLE_KEYS[board->castling];

  if (board->stm) {
    hash ^= ZOBRIST_SIDE_KEY;
  }

  return hash;
}

uint64_t PawnZobrist(Board *board) {
  uint64_t hash = 0ULL;

  for (int piece = WHITE_PAWN; piece <= BLACK_PAWN; piece++) {
    Bitboard pcs = board->pieces[piece];
    while (pcs) {
      hash ^= ZOBRIST_PIECES[piece][PopLSB(&pcs)];
    }
  }

  if (board->stm) {
    hash ^= ZOBRIST_SIDE_KEY;
  }

  return hash;
}
