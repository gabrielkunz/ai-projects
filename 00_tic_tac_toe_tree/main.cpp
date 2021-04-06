#include <stdio.h>
#include <string>
#include <iostream>

int total_children = 0;

class Node {
 public:
  Node();
  void placeX(int position);
  void placeO(int position);
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
  char board[9];
 private:
  int remaining_moves;
};

Node::Node() {
  for (int i = 0; i < 9; i++){
    node_board[i] = ' ';
  }
}

void Node::placeX(int position) {
  node_board[position] = 'X';
}

void Node::placeO(int position) {
  node_board[position] = 'O';
}

Game::Game() {
  for (int i = 0; i < 9; i++){
    board[i] = ' ';
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
      if (board[i] == ' '){
        std::cout << i;
      }else{
        std::cout << board[i];
      }
    }else{
      if (board[i] == ' '){
        std::cout << i << " | ";
      }else{
        std::cout << board[i] << " | ";
      }
    }
  }      
  std::cout << std::endl;
  std::cout << "-   -   -";
  std::cout << std::endl;
  for (int i = 3; i < 6; i++){
    if (i == 5){
      if (board[i] == ' '){
        std::cout << i;
      }else{
        std::cout << board[i];
      }
    }else{
      if (board[i] == ' '){
        std::cout << i << " | ";
      }else{
        std::cout << board[i] << " | ";
      }
    }
  }      
  std::cout << std::endl;
  std::cout << "-   -   -";
  std::cout << std::endl;
  for (int i = 6; i < 9; i++){
    if (i == 8){
      if (board[i] == ' '){
        std::cout << i;
      }else{
        std::cout << board[i];
      }
    }else{
      if (board[i] == ' '){
        std::cout << i << " | ";
      }else{
        std::cout << board[i] << " | ";
      }
    }
  }      
  std::cout << std::endl;
}

int Game::getRemainingMoves() {
  return remaining_moves;
}

Node * createTree(int remaining_moves, char board[9], int depth){
  Node * node = new Node();

  node->child_count = remaining_moves;

  if (depth > 0 && node->child_count > 0){
    node->children = new Node * [node->child_count];

    for (int i = 0; i != node->child_count; ++i){
      node->placeX(i);
      node->children[i] = createTree(depth - 1,node->node_board, depth - 1);
      total_children++;
    }
  }else{
    node->children = NULL;
  }

  // for (int i = 0; i < 9; ++i) {
  //   std::cout << node->node_board[i] << "  ";
  // }
  // std::cout << std::endl;

  return node;
}

void deleteTree(Node * node)
{
    for (int i = 0; i != node->child_count; ++i)
        deleteTree(node->children[i]);
    delete [] node->children; // deleting NULL is OK
    delete node;
    total_children = 0;
}

int main() {
  bool x_turn = true;
  int position = 0;
  int depth = 9;
  Game * game = new Game();
  
  while(game->getRemainingMoves() != 0){
    Node * root;
    root = createTree(game->getRemainingMoves(), game->board, depth);

    printf("Possible boards: %d", total_children);
    std::cout << std::endl;

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

    deleteTree(root);
    depth--;
  }

  std::cout << "Remaining Moves: " << game->getRemainingMoves();
  std::cout << " - Game Over" << std::endl;
  game->printBoard();

  return 0;
}