#include <stdio.h>
#include <string>
#include <iostream>

class Node {
 public:
  Node * next_node, * previous_node;
  Node(Node * next_node, Node * previous_node);
  Node *placeX(int position);
  Node *placeO(int position);
  void printBoard();
 private:
  char board[9];
};

Node::Node(Node * next_node, Node * previous_node) {
  this-> next_node = next_node;
  this-> previous_node = previous_node;
  for (int i = 0; i < 9; i++){
    board[i] = i + '0';
  }
}

void Node::printBoard() {
  for (int i = 0; i < 3; i++){
      std::cout << board[i];
  }
  std::cout << std::endl;
  for (int i = 3; i < 6; i++){
      
      std::cout << board[i];
  }
  std::cout << std::endl;
  for (int i = 6; i < 9; i++){
      std::cout << board[i];
  }
  std::cout << std::endl;
}

void createTree(Node * root) {

}

int main() {
  Node * root;
  root = new Node(NULL, NULL);

  root->printBoard();
  createTree(root);

  return 0;
}