#ifndef TYPES_H
#define TYPES_H

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

extern const int CHAR_TO_PIECE[];

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