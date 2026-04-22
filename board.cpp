#include "board.h"

#include <string.h>

void ClearBoard(Board *board) {
    memset(board->pieces, 0, sizeof(board->pieces));
    memset(board->occupancies, 0, sizeof(board->occupancies));
    memset(board->history, 0, sizeof(board->history));

    for (int i = 0; i < 64; i++) {
        board->squares[i] = NO_PIECE;
    }

    board->piecesCounts = 0ULL;
    board->zobrist = 0ULL;
    board->pawnZobrist = 0ULL;

    board->stm = WHITE;
    board->xstm = BLACK;

    board->epSquare = 0;
    board->castling = 0;
    board->histPly = 0;
    board->moveNo = 1;
    board->fmr = 0;
    board->nullply = 0;
}

void ParseFen(char *fen, Board *board) {
    ClearBoard(board);

    for (int i = 0; i < 64; i++) {
        if ((*fen >= 'a' && *fen <= 'z') || (*fen >= 'A' && *fen <= 'Z')) {
            int piece = CHAR_TO_PIECE[(int) *fen];
            board->pieces[piece] |= (1ULL << (i)); // Set it on the bitboard
            board->squares[i] = piece;
        }
    }
}

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