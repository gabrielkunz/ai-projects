#include <stdio.h>
#include <string>
#include <iostream>

class Node {
 public:
  Node();
  char node_board[9];
  Node ** children;
  int child_count;
};

class Game {
 public:
  Game();
  void placeX(int position);
  void placeO(int position);
  void printBoard();
  int getRemainingMoves();
 private:
  char board[9];
  int remaining_moves;
};

Node::Node() {
  for (int i = 0; i < 9; i++){
    node_board[i] = ' ';
  }
}

Game::Game() {
  for (int i = 0; i < 9; i++){
    board[i] = i + 48;
  }
  remaining_moves = 9;
}

void Game::placeX(int position) {
  board[position] = 'X';
  remaining_moves--;
}

void Game::placeO(int position) {
  board[position] = 'O';
  remaining_moves--;
}

void Game::printBoard() {
  for (int i = 0; i < 3; i++){
    if (i == 2){
      std::cout << board[i];
    }else{
      std::cout << board[i] << " | ";
    }
  }      
  std::cout << std::endl;
  std::cout << "-   -   -";
  std::cout << std::endl;
  for (int i = 3; i < 6; i++){
    if (i == 5){
      std::cout << board[i];
    }else{
      std::cout << board[i] << " | ";
    }
  }      
  std::cout << std::endl;
  std::cout << "-   -   -";
  std::cout << std::endl;
  for (int i = 6; i < 9; i++){
    if (i == 8){
      std::cout << board[i];
    }else{
      std::cout << board[i] << " | ";
    }
  }      
  std::cout << std::endl;
}

int Game::getRemainingMoves() {
  return remaining_moves;
}

Node * createTree(Game * game){
  Node * node = new Node();
  node->child_count = game->getRemainingMoves();
  return node;
}

int main() {
  bool x_turn = true;
  int position = 0;
  Game * game = new Game();
  Node * root;
  root = createTree(game);
  
  while(game->getRemainingMoves() != 0){
    if (x_turn){
      std::cout << "Select a position to place the X: "<< std::endl;
      game->printBoard();
      std::cin >> position;
      game->placeX(position);
      x_turn = false;
    }else{
      std::cout << "Select a position to place the O: "<< std::endl;
      game->printBoard();
      std::cin >> position;
      game->placeO(position);
      x_turn = true;
    }
    std::cout << "\033[2J\033[1;1H";
  }

  std::cout << "Game Over" << std::endl;
  game->printBoard();
  printf("%d /n",game->getRemainingMoves());

  return 0;
}