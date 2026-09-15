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
            std::cout << i+1 << std::endl;
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

};



int main(){

    ChessBoard game;
    game.displayBoardWhiteSide();
    std::cout << "\n\n------------------------------------------\n\n";
    game.displayBoardBlackSide();
    
    return 0;
}