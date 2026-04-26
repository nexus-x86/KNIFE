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

            if (*fen != 'K' && *fen != 'k') {
                board->piecesCounts += (1ULL << (4 * piece));
            }
        } else if (*fen >= '0' && *fen <= '9') {
            int offset = *fen - '1';
            i += offset;
        } else if (*fen == '/') {
            i--;
        }

        fen++;
    }

    fen++;

    board->stm = (*fen++ == 'w' ? WHITE : BLACK);
    board->xstm = !board->stm;

    board->castling = 0;
    for (int i = 0; i < 4; i++) {
        board->cr[i] = -1;
    }
    int whiteKing = LSB(PieceBB(KING, WHITE));
    int blackKing = LSB(PieceBB(KING, BLACK));

    Bitboard whiteRooks = PieceBB(ROOK, WHITE) & RANK_1;
    Bitboard blackRooks = PieceBB(ROOK, BLACK) & RANK_8;

    while (*(++fen) != ' ') {
        if (*fen == 'K') {
            board->castling |= WHITE_KS;
            board->cr[0] = MSB(whiteRooks);
        } else if (*fen == 'Q') {
            board->castling |= WHITE_QS;
            board->cr[1] = LSB(whiteRooks);
        } else if (*fen >= 'A' && *fen <= 'H') {
            board->castling |= ((*fen - 'A') > File(whiteKing) ? WHITE_KS : WHITE_QS);
            board->cr[(*fen - 'A') > File(whiteKing) ? 0 : 1] = A1 + (*fen - 'A'); 
        } else if (*fen == 'k') {
            board->castling |= BLACK_KS;
            board->cr[2] = MSB(blackRooks);
        } else if (*fen == 'q') {
            board->castling |= BLACK_QS;
            board->cr[3] = LSB(blackRooks);
        } else if (*fen >= 'a' && *fen <= 'h') {
            board->castling |= ((*fen - 'a') > File(blackKing) ? BLACK_KS : BLACK_QS);
            board->cr[(*fen - 'a') > File(blackKing) ? 2 : 3] = A8 + (*fen - 'a');
        }
    }

    for (int i = 0; i < 64; i++) {
        board->castlingRights[i] = board->castling;

        if (i == whiteKing) {
            board->castlingRights[i] ^= (WHITE_KS | WHITE_QS);
        } else if (i == blackKing) {
            board->castlingRights[i] ^= (BLACK_KS | BLACK_QS);
        } else if (i == board->cr[0]) {
            board->castlingRights[i] ^= WHITE_KS;
        } else if (i == board->cr[1]) {
            board->castlingRights[i] ^= WHITE_QS;
        } else if (i == board->cr[2]) {
            board->castlingRights[i] ^= BLACK_KS;
        } else if (i == board->cr[3]) {
            board->castlingRights[i] ^= BLACK_QS;
        }
    }

    fen++;

    if (*fen != '-') {
        int f = fen[0] - 'a';
        int r = 8 - (fen[1] - '0');

        board->epSquare = r * 8 + f;
    } else {
        board->epSquare = 0;
    }

    while (*fen && *fen != ' ') {
        fen++;
    }

    sscanf(fen, " %d %d", &board->fmr, &board->moveNo);

    OccBB(WHITE) = OccBB(BLACK) = OccBB(BOTH) = 0;
    for (int i = WHITE_PAWN; i <= BLACK_KING; i++) {
        OccBB(i & 1) |= board->pieces[i];
    }
    OccBB(BOTH) = OccBB(WHITE) | OccBB(BLACK);

    SetSpecialPieces(board);
    SetThreats(board);

    board->zobrist = Zobrist(board);
    board->pawnZobrist = PawnZobrist(board);
}

void BoardToFen(char *fen, Board *board) {
    for (int r = 0; r < 8; r++) {
        int c = 0;
        for (int f = 0; f < 8; f++) {
            int sq = 8 * r + f;
            int piece = board->squares[sq];
            if (piece != NO_PIECE) {
                if (c) {
                    *fen++ = c + '0';
                }
                *fen++ = PIECE_TO_CHAR[piece];
                c = 0;
            } else {
                c++;
            }
        }

        if (c) {
            *fen++ = c + '0';
        }
        *fen++ = (r == 7) ? ' ' : '/';
    }

    *fen++ = board->stm ? 'b' : 'w';
    *fen++ = ' ';

    if (board->castling) {
        if (board->castling & 0x8) {
            *fen++ = 'K';
        }
        if (board->castling & 0x4) {
            *fen++ = 'Q';
        }
        if (board->castling & 0x2) {
            *fen++ = 'k';
        }
        if (board->castling & 0x1) {
            *fen++ = 'q';
        }
    } else {
        *fen++ = '-';
    }

    *fen++ = ' ';

    sprintf(fen, "%s %d %d", board->epSquare ? SQ_TO_COMBO[board->epSquare] : "-", board->fmr, board->moveNo);
}

void PrintBoard(Board *board) {
    static char fenBuffer[120];
    for (int r = 0; r < 8; r++) {
        printf("+-------+-------+-------+-------+-------+-------+-------+-------+\n");
        printf("|");
        for (int f = 0; f < 16; f++) {
            if (f == 8) {
                printf("\n|");
            }
            
            int sq = r * 8 + (f > 7 ? f - 8 : f);

            if (f < 8) {
                if (board->squares[sq] == NO_PIECE) {
                    printf("       |");
                } else {
                    printf("   %c   |", PIECE_TO_CHAR[board->squares[sq]]);
                }
            } else {
                printf("       |");
            }
        }
        printf("\n");
    }
    printf("+-------+-------+-------+-------+-------+-------+-------+-------+\n");
    BoardToFen(fenBuffer, board);
    printf("\n FEN: %s\n\n", fenBuffer);
}

// Special pieces are those giving check, and those that are pinned
inline void SetSpecialPieces(Board *board) {

}

void SetThreats(Board *board);

int DoesMoveCheck(Move move, Board *board);
int IsDraw(Board *board, int ply);
int IsRepetition(Board *board, int ply);
int IsMaterialDraw(Board *board);
int IsFiftyMoveRule(Board *board);

void MakeNullMove(Board *board);
void UndoNullMove(Board *board);

void MakeMove(Move move, Board *board) {
    MakeMoveUpdate(move, board, 1);
}

void MakeMoveUpdate(Move move, Board *board, int update) {
    int from = From(move);
    int to = To(move);
    int piece = Moving(move);
    int captured = IsEP(move) ? Piece(PAWN, board->xstm) : board->squares[to]; 

    memcpy(&board->history[board->histPly], board, offsetof(Board, stm));
    board->history[board->histPly].capture = captured;

    board->fmr++;
    board->nullply++;

    FlipBits()
}

void UndoMove(Move move, Board *board);

int IsPseudoLegal(Move move, Board *board);
int IsLegal(Move move, Board *board);