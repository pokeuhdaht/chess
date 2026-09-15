#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>


//using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif

enum Color {
    WHITE,
    BLACK,
    NONE
};

enum PieceType {
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    EMPTY
};

struct Position {
    int row;
    int col;
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

struct Piece {
    PieceType type;
    Color color;
    char symbol;
};

/* 
    //Black Pieces
        {"King", "Black", "♚"};
        {"Queen", "Black", "♛"};
        {"Rook", "Black", "♜"};
        {"Bishop", "Black", "♝"};
        {"Knight", "Black", "♞"};
        {"Pawn", "Black", "♟"};

    //White Pieces
        {"King", "White", "♔"};
        {"Queen", "White", "♕"};
        {"Rook", "White", "♖"};
        {"Bishop", "White", "♗"};
        {"Knight", "White", "♘"};
        {"Pawn", "White", "♙"};

*/



class ChessBoard {
private:
   Piece board[8][8];
   Color currentTurn;

    void setupBoard() {
        for (int row = 2; row < 6; ++row) {
            for (int col = 0; col < 8; ++col) {
                board[row][col] = {EMPTY, NONE, ' '}; // Empty squares
            }
        }

        for (int col = 0; col < 8; ++col) {
            board[1][col] = {PAWN, BLACK, 'p'}; // Black pawns
            board[6][col] = {PAWN, WHITE, 'P'}; // White pawns
        }

        char blackPieces[] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
        char whitePieces[] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
        PieceType pieceTypes[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};

        for (int col = 0; col < 8; ++col) {
            board[0][col] = {pieceTypes[col], BLACK, blackPieces[col]}; // Black pieces
            board[7][col] = {pieceTypes[col], WHITE, whitePieces[col]}; // White pieces
        }
    }

    bool isPathClear(Position from, Position to) {
        int rowStep = (to.row - from.row) == 0 ? 0 : (to.row - from.row) / std::abs(to.row - from.row);
        int colStep = (to.col - from.col) == 0 ? 0 : (to.col - from.col) / std::abs(to.col - from.col);

        int currentRow = from.row + rowStep;
        int currentCol = from.col + colStep;

        while (currentRow != to.row || currentCol != to.col) {
            if (board[currentRow][currentCol].type != EMPTY) {
                return false; // Path is blocked
            }
            currentRow += rowStep;
            currentCol += colStep;
        }
        return true; // Path is clear
    }
    

    

public: 
    ChessBoard() : currentTurn(WHITE) {
        setupBoard();
    }

    void display(){
        std::cout << "   a   b   c   d   e   f   g   h\n";
        std::cout << " +---+---+---+---+---+---+---+---+\n";
        for (int row = 0; row < 8; ++row) {
            std::cout << 8 - row << "|";
            for (int col = 0; col < 8; ++col) {
                std::cout << " " << board[row][col].symbol << " |";
            }
            std::cout << " " << 8 - row << "\n";
            std::cout << " +---+---+---+---+---+---+---+---+\n";
        }
    }

    Color getCurrentTurn() {
        return currentTurn;
    }

    bool validateMove(Position from, Position to) {
        if (from.row < 0 || from.row >= 8 || from.col < 0 || from.col >= 8 ||
            to.row < 0 || to.row >= 8 || to.col < 0 || to.col >= 8) {
            return false; // Out of bounds
        }

        Piece movingPiece = board[from.row][from.col];
        Piece targetPiece = board[to.row][to.col];

        if (movingPiece.type == EMPTY || movingPiece.color != currentTurn) {
            return false; // No piece to move or wrong turn
        }

        if (targetPiece.color == currentTurn) {
            return false; // Cannot capture own piece
        }

        // Check if the path is clear for pieces that require it
        if (movingPiece.type == ROOK || movingPiece.type == BISHOP || movingPiece.type == QUEEN) {
            if (!isPathClear(from, to)) {
                return false; // Path is blocked
            }
        }

        // Additional movement rules for each piece type can be added here

        return true; // Move is valid
    }



};







int main(){

    

    return 0;
}