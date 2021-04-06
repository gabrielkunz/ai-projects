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

Node * createTree(int remaining_moves, char board[9], int depth){
  Node * node = new Node();
  bool x_turn = true;

  node->child_count = remaining_moves;

  if (depth > 0 && node->child_count > 0){
    node->children = new Node * [node->child_count];

    for (int i = 0; i != node->child_count; ++i){
      if (x_turn){
        node->placeX(i);
        node->children[i] = createTree(depth - 1,node->node_board, depth - 1);
        x_turn = false;
        total_children++;
      }else{
        node->placeO(i);
        node->children[i] = createTree(depth - 1,node->node_board, depth - 1);
        x_turn = true;
        total_children++;
      }        
    }
  }else{
    node->children = NULL;
  }

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
  Game * game = new Game();
  
  while(game->getRemainingMoves() != 0){
    Node * root;
    root = createTree(game->getRemainingMoves(), game->board, 9);
    printf("%d",total_children);
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
  }

  std::cout << "Game Over" << std::endl;
  game->printBoard();
  printf("%d /n",game->getRemainingMoves());

  return 0;
}