#include "chess.cpp"
#include <iostream>

int main() {
    std::cout << "Testing..." << std::endl;
    ChessBoard testBoard;

    testBoard.displayBoardWhiteSide();
    std::cout << "----------------------" << std::endl;
    testBoard.displayBoardBlackSide();

    return 0;
}
