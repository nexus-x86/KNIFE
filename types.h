#ifndef TYPES_H
#define TYPES_H

#define BuildMove(from, to, piece, flags) (from) | 
#define From(move) (((int) (move) & 0x0003f) >> 0)
#define To(move) (((int) (move) & 0x00fc0) >> 6)
#define Moving(move) (((int) (move) & 0x0f000) >> 12)

enum {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum {
    WHITE_PAWN,
    BLACK_PAWN,
    WHITE_KNIGHT,
    BLACK_KNIGHT,
    WHITE_BISHOP,
    BLACK_BISHOP,
    WHITE_ROOK,
    BLACK_ROOK,
    WHITE_QUEEN,
    BLACK_QUEEN,
    WHITE_KING,
    BLACK_KING,
    NO_PIECE,
},

enum {
  A8,
  B8,
  C8,
  D8,
  E8,
  F8,
  G8,
  H8,
  A7,
  B7,
  C7,
  D7,
  E7,
  F7,
  G7,
  H7,
  A6,
  B6,
  C6,
  D6,
  E6,
  F6,
  G6,
  H6,
  A5,
  B5,
  C5,
  D5,
  E5,
  F5,
  G5,
  H5,
  A4,
  B4,
  C4,
  D4,
  E4,
  F4,
  G4,
  H4,
  A3,
  B3,
  C3,
  D3,
  E3,
  F3,
  G3,
  H3,
  A2,
  B2,
  C2,
  D2,
  E2,
  F2,
  G2,
  H2,
  A1,
  B1,
  C1,
  D1,
  E1,
  F1,
  G1,
  H1,
};

extern const int CHAR_TO_PIECE[];
extern const char* PIECE_TO_CHAR;
extern const char* SQ_TO_COORD;

enum {
    WHITE,
    BLACK,
    BOTH
};

typedef uint64_t Bitboard;
typedef uint32_t Move;

typedef struct {
    int castling;
    int ep;
    int fmr;
    int nullply;
    uint64_t zobrist;
    uint64_t pawnZobrist;
    Bitboard checkers;
    Bitboard pinned;
    Bitboard threatened;
    Bitboard threatenedBy[6];
    int capture;
} BoardHistory;

typedef struct {
    int castling;
    int epSquare;
    int fmr;
    int nullply;
    uint64_t zobrist;
    uint64_t pawnZobrist;
    Bitboard checkers;
    Bitboard pinned;
    Bitboard threatened;
    Bitboard threatenedBy[6];
    int stm;
    int xstm;
    int histPly;
    int moveNo;
    uint64_t piecesCounts;
    int squares[64];
    Bitboard occupancies[3];
    Bitboard pieces[12];
    int cr[4];
    int castlingRights[64];
    BoardHistory history[300]; // random constant
} Board;


#endif
