#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>


//using namespace std;


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

struct Piece {
    PieceType type;
    Color color;
    char symbol;
    int moves;

};



class ChessBoard {
private:
   Piece board[8][8];
   Color currentTurn;
   
   void boardSetup(){
        //this created the empty board with no pieces on it.
        for(int i = 2; i < 6; i++){
            for(int j = 0; j < 8; j++){
                board[i][j]= {EMPTY, NONE, ' ', 0};
                
            }
        }

        for (int i = 0; i < 8; i++){
            board[1][i]= {PAWN, BLACK, 'p', 0};
            board[6][i]= {PAWN, WHITE, 'P', 0};
        }

        char backRowSymbolsBlack[8] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'l'};
        char backRowSymbolsWhite[8] = {'L', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
        PieceType backRowTypes[8] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};

        for (int i = 0; i < 8; i++){
            board[0][i]= {backRowTypes[i], BLACK, backRowSymbolsBlack[i], 0};
            board[7][i]= {backRowTypes[i], WHITE, backRowSymbolsWhite[i], 0};
        }
    }
    

public: 
    ChessBoard() {
        currentTurn = WHITE;
        boardSetup();
    }
    
    void displayBoardWhiteSide() {
        std::cout << "    a   b   c   d   e   f   g   h" << std::endl;
        std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << 8 - i << " | ";
            for (int j = 0; j < 8; j++) {
                std::cout << board[i][j].symbol << " | ";
            };
            std::cout << 8 - i << std::endl;
            std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
        }
        std::cout << "    a   b   c   d   e   f   g   h"<< std::endl;
    }
    
    void displayBoardBlackSide() {
        std::cout << "    h   g   f   e   d   c   b   a" << std::endl;
        std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
        for (int i = 7; i >= 0; i--) {
            std::cout << i+1 << " | ";
            for (int j = 7; j >= 0; j--) {
                std::cout << board[i][j].symbol << " | ";
            }
            std::cout << i + 1 << std::endl;
            std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
        }
        std::cout << "    h   g   f   e   d   c   b   a"<< std::endl;
    }

    Color getCurrentTurn() const {
        return currentTurn;
    }
    void setCurrentTurn(){
        if (getCurrentTurn() == WHITE) {
            currentTurn = BLACK;
        } else {
            currentTurn = WHITE;
        }
        return;
    }

    //get the piece at a specific position on the board
    Piece getPieceAt(int row, int col) const {
        return board[row][col];
    }
    //sets the new position of a piece on the board
    void setPieceAt(int row, int col, Piece piece) {
        board[row][col] = piece;
    }


    /*
    // will need to adjust this function to work based on user input.
    // User input  s h o u l d  look like this: "e2e4" or "g1f3" or "b8c6"
    void movePiece(char[4] move) {
        SWITCH (move[0]) {
            CASE 'a': startCol = 0; BREAK;
            CASE 'b': startCol = 1; BREAK;
            CASE 'c': startCol = 2; BREAK;
            CASE 'd': startCol = 3; BREAK;
            CASE 'e': startCol = 4; BREAK;
            CASE 'f': startCol = 5; BREAK;
            CASE 'g': startCol = 6; BREAK;
            CASE 'h': startCol = 7; BREAK;
        }
        SWITCH (move[1]) {
            CASE '1': startRow = 7; BREAK;
            CASE '2': startRow = 6; BREAK;
            CASE '3': startRow = 5; BREAK;
            CASE '4': startRow = 4; BREAK;
            CASE '5': startRow = 3; BREAK;
            CASE '6': startRow = 2; BREAK;
            CASE '7': startRow = 1; BREAK;
            CASE '8': startRow = 0; BREAK;
        }
        SWITCH (move[2]) {
            CASE 'a': endCol = 0; BREAK;
            CASE 'b': endCol = 1; BREAK;
            CASE 'c': endCol = 2; BREAK;
            CASE 'd': endCol = 3; BREAK;
            CASE 'e': endCol = 4; BREAK;
            CASE 'f': endCol = 5; BREAK;
            CASE 'g': endCol = 6; BREAK;
            CASE 'h': endCol = 7; BREAK;
        }
        SWITCH (move[3]) {
            CASE '1': endRow = 7; BREAK;
            CASE '2': endRow = 6; BREAK;
            CASE '3': endRow = 5; BREAK;
            CASE '4': endRow = 4; BREAK;
            CASE '5': endRow = 3; BREAK;
            CASE '6': endRow = 2; BREAK;
            CASE '7': endRow = 1; BREAK;
            CASE '8': endRow = 0; BREAK;
        }
        Piece pieceToMove = getPieceAt(startRow, startCol);
        setPieceAt(endRow, endCol, pieceToMove);
        setPieceAt(startRow, startCol, {EMPTY, NONE, ' ', 0});
        setCurrentTurn();
    }
    */


};



int main(){

    ChessBoard game;
    game.displayBoardWhiteSide();
    std::cout << "\n\n------------------------------------------\n\n";
    game.displayBoardBlackSide();
    
    return 0;
}