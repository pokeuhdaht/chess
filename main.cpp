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
    bool inCheck;

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

        char backRowSymbolsBlack[8] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'};
        char backRowSymbolsWhite[8] = {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};
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
            std::cout << 8-i << " | ";
            for (int j = 7; j >= 0; j--) {
                std::cout << board[i][j].symbol << " | ";
            }
            std::cout << 8-i << std::endl;
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

    void exitGame(){
        std::cout << "Are you sure you want to close the game? (Y/N): ";
        char yesno;
        std::cin >> yesno; 
        if(yesno == 'Y' || yesno == 'y'){
            exit(0);
        }
    }

    //get the piece at a specific position on the board
    Piece getPieceAt(int row, int col) const {
        return board[row][col];
    }
    //sets the new position of a piece on the board
    void setPieceAt(int row, int col, Piece piece) {
        board[row][col] = piece;
    }

    void getUserMove() {
        bool validMove = false;
        while (!validMove) {
            std::string move;
            std::cout << "Enter your move: ";
            std::cin >> move;
            if (move.length() != 4) {
                std::cout << "Invalid move format. Please enter a move like 'e2e4'." << std::endl;
                continue; // Prompt the user again
            }
            validMove = viableMoveCheck(move.c_str());
            if (!validMove) {
                std::cout << "Invalid move. Please try again." << std::endl;
            }
        }
        //movePiece(startRow, startCol, endRow, endCol);
    }

    void movePiece(int startRow, int startCol, int endRow, int endCol) {
        Piece pieceToMove = getPieceAt(startRow, startCol);
        pieceToMove.moves += 1; // Increment the move count for the piece
        setPieceAt(endRow, endCol, pieceToMove);
        setPieceAt(startRow, startCol, {EMPTY, NONE, ' ', 0, false}); // Clear the starting position
        setCurrentTurn();
    }

    bool inWayCheck(int startRow, int startCol, int endRow, int endCol) {
        int rowDirection = (endRow - startRow) > 0 ? 1 : -1;
        int colDirection = (endCol - startCol) > 0 ? 1 : -1;

        if (startRow == endRow) { // Horizontal move
            for (int col = startCol + colDirection; col != endCol; col += colDirection) {
                if (board[startRow][col].type != EMPTY) {
                    return true; // There is a piece in the way
                }
            }
        } else if (startCol == endCol) { // Vertical move
            for (int row = startRow + rowDirection; row != endRow; row += rowDirection) {
                if (board[row][startCol].type != EMPTY) {
                    return true; // There is a piece in the way
                }
            }
        } else if (abs(endRow - startRow) == abs(endCol - startCol)) { // Diagonal move
            int row = startRow + rowDirection;
            int col = startCol + colDirection;
            while (row != endRow && col != endCol) {
                if (board[row][col].type != EMPTY) {
                    return true; // There is a piece in the way
                }
                row += rowDirection;
                col += colDirection;
            }
        }

        return false; // No pieces in the way
    }

    
    // will need to adjust this function to work based on user input.
    // User input  s h o u l d  look like this: "e2e4" or "g1f3" or "b8c6"
    bool viableMoveCheck(const char* move) {
        int startRow, startCol, endRow, endCol;

        if(move[0]=='e'&&move[1]=='x'&&move[2]=='i'&&move[3]=='t'){
            exitGame();
        }
        if(move[0]=='E'&&move[1]=='X'&&move[2]=='I'&&move[3]=='T'){
            exitGame();
        }


        switch (move[0]) {
            case 'A': 
            case 'a': startCol = 0; break;
            case 'B':
            case 'b': startCol = 1; break;
            case 'C':
            case 'c': startCol = 2; break;
            case 'D':
            case 'd': startCol = 3; break;
            case 'E':
            case 'e': startCol = 4; break;
            case 'F':
            case 'f': startCol = 5; break;
            case 'G':
            case 'g': startCol = 6; break;
            case 'H':
            case 'h': startCol = 7; break;
            default: return false;
        }
        switch (move[1]) {
            case '1': startRow = 7; break;
            case '2': startRow = 6; break;
            case '3': startRow = 5; break;
            case '4': startRow = 4; break;
            case '5': startRow = 3; break;
            case '6': startRow = 2; break;
            case '7': startRow = 1; break;
            case '8': startRow = 0; break;
            default: return false;
        }
        switch (move[2]) {
            case 'A':
            case 'a': endCol = 0; break;
            case 'B':
            case 'b': endCol = 1; break;
            case 'C':
            case 'c': endCol = 2; break;
            case 'D':
            case 'd': endCol = 3; break;
            case 'E':
            case 'e': endCol = 4; break;
            case 'F':
            case 'f': endCol = 5; break;
            case 'G':
            case 'g': endCol = 6; break;
            case 'H':
            case 'h': endCol = 7; break;
            default: return false;
        }
        switch (move[3]) {
            case '1': endRow = 7; break;
            case '2': endRow = 6; break;
            case '3': endRow = 5; break;
            case '4': endRow = 4; break;
            case '5': endRow = 3; break;
            case '6': endRow = 2; break;
            case '7': endRow = 1; break;
            case '8': endRow = 0; break;
            default: return false;
        }

        switch (board[startRow][startCol].type)
        {
            case PAWN: 
                //does not allow for diagonal or side movement               
                if(startCol != endCol){
                    return false;
                }
                if(board[startRow][startCol].moves == 0){
                    if(abs(startRow-endRow)>2){
                        return false;
                    }
                }else {
                    if(abs(endRow-startRow)!=1){
                        return false;
                    }
                }
                
                
                
                break;
            case BISHOP:
                if (abs(startRow - endRow) != abs(startCol - endCol)) {
                    std::cout << "Invalid bishop move!" << std::endl;
                    return false;
                }
                if(inWayCheck(startRow, startCol, endRow, endCol)){
                    std::cout << "There is a piece in the way!" << std::endl;
                    return false;
                }
                break;  
            case KNIGHT:
                if (!((abs(startRow - endRow) == 2 && abs(startCol - endCol) == 1) || (abs(startRow - endRow) == 1 && abs(startCol - endCol) == 2))) {
                    std::cout << "Invalid knight move!" << std::endl;
                    return false;
                }
                break;
            case ROOK:
                if (startRow != endRow && startCol != endCol) {
                    std::cout << "Invalid rook move!" << std::endl;
                    return false;
                }
                if(inWayCheck(startRow, startCol, endRow, endCol)){
                    std::cout << "There is a piece in the way!" << std::endl;
                    return false;
                }
                break;
            case KING:
                if (abs(startRow - endRow) > 1 || abs(startCol - endCol) > 1) {
                    std::cout << "Invalid king move!" << std::endl;
                    return false;
                }
                break;
            case QUEEN:
                if (startRow != endRow && startCol != endCol && abs(startRow - endRow) != abs(startCol - endCol)) {
                    std::cout << "Invalid queen move!" << std::endl;
                    return false;
                }
                if(inWayCheck(startRow, startCol, endRow, endCol)){
                    std::cout << "There is a piece in the way!" << std::endl;
                    return false;
                }
                break;
            case EMPTY:
                std::cout << "Not a valid piece!" << std::endl;
                return false;
        
        }



        if (board[startRow][startCol].color != currentTurn) {
            std::cout << "Wrong Piece!" << std::endl;
            return false;
        }
        if (board[endRow][endCol].color == currentTurn) {
            std::cout << "Cannot capture your own piece!" << std::endl;
            return false;
        }




        movePiece(startRow, startCol, endRow, endCol);
        return true;
    }

                        //Checks if a winner has been found. this is basic that just checks if a check is in place.
                        //I will want to change how this function works in the future.
    bool winnerCheck(){
        for(int i=0; i<8;i++){
            for(int j=0; j<8;j++){
                if(board[i][j].inCheck==true){
                    return true;
                }
            }
        }
        return false;
    }

    void gameStart(){
        Color winner = NONE;
        while(winner==NONE){
            if(currentTurn==WHITE) displayBoardWhiteSide();
            else displayBoardBlackSide();

            getUserMove();    
            winnerCheck();
        }
        return;
    }




};



int main(){

    ChessBoard game;
    game.gameStart();



    
    return 0;
}