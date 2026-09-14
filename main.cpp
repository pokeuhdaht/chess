#include <stdio.h>
#include <iostream>

using namespace std;

#ifdef _WIN32
#include <windows.h>
#endif


int main(){
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif
    

    const char* whiteKing   = "♔";
    const char* whiteQueen  = "♕";
    const char* whiteRook   = "♖";
    const char* whiteBishop = "♗";
    const char* whiteKnight = "♘";
    const char* whitePawn   = "♙";

    const char* blackKing   = "♚";
    const char* blackQueen  = "♛";
    const char* blackRook   = "♜";
    const char* blackBishop = "♝";
    const char* blackKnight = "♞";
    const char* blackPawn   = "♟";




    cout << "White Row: " << whiteRook << " " << whiteKnight << " " << whiteBishop << " " << whiteQueen << " " << whiteKing << " " << whitePawn << "\n";
    cout << "Black Row: " << blackRook << " " << blackKnight << " " << blackBishop << " " << blackQueen << " " << blackKing << " " << blackPawn << "\n";

    return 0;
}