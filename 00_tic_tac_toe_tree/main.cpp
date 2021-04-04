#include <stdio.h>
#include <string>
#include <iostream>

class Node {
 public:
  Node * next;
  Node(Node * next);
  void placeX(Node * root, int position);
  void placeO(Node * root, int position);
  void printBoard(int position);
  char board[9];
};

Node::Node(Node * next) {
  this-> next = next;
  for (int i = 0; i < 9; i++){
    board[i] = ' ';
  }
}

void Node::placeX(Node * node, int position){
  while (node->next != NULL){
    node = node->next;
  }

  node->board[position] = 'X';

}

void Node::placeO(Node * node, int position){
  while (node->next != NULL){
    node = node->next;
  }

  node->board[position] = 'O';
}

void Node::printBoard(int position) {
  for (int i = 0; i < 9; i++){
    if (i == position){
      std::cout << "_, ";
    }else{
      std::cout << board[i] << ", ";
    }      
  }
  std::cout << std::endl;
}

void displayPossibilities(Node * node){
  while (node->next != NULL){
    node = node->next;
  }

  for (int i = 0; i < 9; i++){
    if (node->board[i] == ' '){
      std::cout << "Position " << std::to_string(i) <<": ";
      node->printBoard(i);
    }
  }
}

int main() {
  Node * root;
  root = new Node(NULL);
  bool x_turn = true;
  int position = 0;
  
  while(true){
    if (x_turn){
      std::cout << "Select a position to place the X: "<< std::endl;
      displayPossibilities(root);
      std::cin >> position;
      root->placeX(root,position);
      x_turn = false;

    }else{
      std::cout << "Select a position to place the O: "<< std::endl;
      displayPossibilities(root);
      std::cin >> position;
      root->placeO(root,position);
      x_turn = true;
    }
  }
  return 0;
}