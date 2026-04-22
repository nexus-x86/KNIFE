#ifndef BOARD_H
#define BOARD_H

#include "types.h"

#define A_FILE 0x0101010101010101ULL
#define B_FILE 0x0202020202020202ULL
#define C_FILE 0x0404040404040404ULL
#define D_FILE 0x0808080808080808ULL
#define E_FILE 0x1010101010101010ULL
#define F_FILE 0x2020202020202020ULL
#define G_FILE 0x4040404040404040ULL
#define H_FILE 0x8080808080808080ULL

#define RANK_1 0xFF00000000000000ULL
#define RANK_2 0x00FF000000000000ULL
#define RANK_3 0x0000FF0000000000ULL
#define RANK_4 0x000000FF00000000ULL
#define RANK_5 0x00000000FF000000ULL
#define RANK_6 0x0000000000FF0000ULL
#define RANK_7 0x000000000000FF00ULL
#define RANK_8 0x00000000000000FFULL

#define DARK_SQS 0x55AA55AA55AA55AAULL

#define WHITE_KS 0x8
#define WHITE_QS 0x4
#define BLACK_KS 0x2
#define BLACK_QS 0x1

#define File(sq) ((sq) & 7)

#define Piece(pc, c)   (((pc) << 1) + c)
#define PieceType(pc)  ((pc) >> 1)
#define PPieceBB(pc)   (board->pieces[pc])
#define PieceBB(pc, c) (board->pieces[Piece(pc, (c))])
#define LSB(bb)                (__builtin_ctzll(bb))
#define MSB(bb)                (63 ^ __builtin_clzll(bb))

void ClearBoard(Board *board);
void ParseFen(char *fen, Board *board);
void BoardToFen(char *fen, Board *board);
void PrintBoard(Board *board);

void SetSpecialPieces(Board *board);
void SetThreats(Board *board);

int DoesMoveCheck(Move move, Board *board);
int IsDraw(Board *board, int ply);
int IsRepetition(Board *board, int ply);
int IsMaterialDraw(Board *board);
int IsFiftyMoveRule(Board *board);

void MakeNullMove(Board *board);
void UndoNullMove(Board *board);
void MakeMove(Move move, Board *board);
void MakeMoveUpdate(Move move, Board *board, int update);
void UndoMove(Move move, Board *board);

int IsPseudoLegal(Move move, Board *board);
int IsLegal(Move move, Board *board);

#endif