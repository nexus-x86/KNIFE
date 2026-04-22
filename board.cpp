#include "board.h"

void ClearBoard(Board *board) {
    
}

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