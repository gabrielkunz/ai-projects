#include <stdio.h>
#include <string>
#include <iostream>

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
  bool checkMove(int position);
  void removePosition(int position);
  char board[9];
 private:
  int remaining_moves;
  int available_positions[9];
};

Node::Node() {
  for (int i = 0; i < 9; i++) {
    node_board[i] = '_';
  }
}

void Node::placeX(int position) {
  node_board[position] = 'X';
}

void Node::placeO(int position) {
  node_board[position] = 'O';
}

Game::Game() {
  for (int i = 0; i < 9; i++) {
    board[i] = '_';
    available_positions[i] = i;
  }
  remaining_moves = 9;
}

void Game::placeX(int position) {
  board[position] = 'X';
  remaining_moves--;
  removePosition(position);
}

void Game::placeO(int position) {
  board[position] = 'O';
  remaining_moves--;
  removePosition(position);
}

void Game::printBoard() {
  for (int i = 0; i < 3; i++) {
    if (i == 2) {
      if (board[i] == '_') {
        std::cout << i;
      } else {
        std::cout << board[i];
      }
    } else {
      if (board[i] == '_') {
        std::cout << i << " | ";
      } else {
        std::cout << board[i] << " | ";
      }
    }
  }
  std::cout << std::endl;
  std::cout << "-   -   -";
  std::cout << std::endl;
  for (int i = 3; i < 6; i++) {
    if (i == 5) {
      if (board[i] == '_') {
        std::cout << i;
      } else {
        std::cout << board[i];
      }
    } else {
      if (board[i] == '_') {
        std::cout << i << " | ";
      } else {
        std::cout << board[i] << " | ";
      }
    }
  }
  std::cout << std::endl;
  std::cout << "-   -   -";
  std::cout << std::endl;
  for (int i = 6; i < 9; i++) {
    if (i == 8) {
      if (board[i] == '_') {
        std::cout << i;
      } else {
        std::cout << board[i];
      }
    } else {
      if (board[i] == '_') {
        std::cout << i << " | ";
      } else {
        std::cout << board[i] << " | ";
      }
    }
  }
  std::cout << std::endl;
}

int Game::getRemainingMoves() {
  return remaining_moves;
}

// This function returns true if the move entered is inside the board
// or if it wasn't played before
bool Game::checkMove(int position) {
  int * find_result =
    std::find(available_positions, available_positions+9, position);

  std::cout << find_result << std::endl;
  std::cout << available_positions+9 << std::endl;

  if (position < 0 || position > 8 || find_result == available_positions + 9) {
    return false;
  } else {
    return true;
  }
}

// This function sets a position already entered as 9 in the postition array.
// This way the user cannot enter the same position twice. The function is
// called after each move on the board.
void Game::removePosition(int position) {
  for (int i = 0; i < 9; i++) {
    if (i == position) {
      available_positions[i] = 9;
    }
  }
}

// This function creates the tree with all the possible boards for the
// game. The root node should always contain the most up to date board.
Node * createTree(int remaining_moves, char game_board[9], int depth) {
  Node * node = new Node();

  node->child_count = remaining_moves;

  if (depth > 0 && node->child_count > 0) {
    node->children = new Node * [node->child_count];

    for (int i = 0; i != node->child_count; ++i) {
      for (int j = 0; j < 9; j++) {
        node->node_board[j] = game_board[j];
      }
      node->children[i] = createTree(depth - 1, node->node_board, depth - 1);
    }

  } else {
    node->children = NULL;
  }
  return node;
}

// This function deletes the entire tree. The input is the
// root node. The function starts deleting its children and
// then deletes itself.
void deleteTree(Node * node) {
    for (int i = 0; i != node->child_count; ++i)
        deleteTree(node->children[i]);
    delete [] node->children;
    delete node;
}

int countNodes(Node * node) {
  int total_nodes = 0;

  if (node == NULL) {
    return 0;
  }

  total_nodes = 1;
  for (int i = 0; i < node->child_count; i++) {
    total_nodes = total_nodes + countNodes(node->children[i]);
  }

  return total_nodes;
}

void printNodeBoards(Node * node) {
  std::cout << node->node_board << std::endl;
  for (int i = 0; i != node->child_count; i++) {
    printNodeBoards(node->children[i]);
  }
}

int main() {
  bool x_turn = true;
  int position = 9;
  int depth = 9;
  Game * game = new Game();

  // Loop for the game input. The loop will alternate between X's and O's turns.
  // If an invalid position is entered (smaller than 0 or greater than 8), the
  // input is requested again.
  while (game->getRemainingMoves() != 0) {
    std::cout << "Remaining Moves: " << game->getRemainingMoves() << std::endl;
    std::cout << "Depth: " << depth << std::endl;
    Node * root;
    root = createTree(game->getRemainingMoves(), game->board, depth);

    printf("Possible boards: %d", countNodes(root) - 1);
    std::cout << std::endl;

    // printNodeBoards(root);

    if (x_turn) {
      std::cout << "Select a position to place the X: "<< std::endl;
      game->printBoard();
      std::cin >> position;

      // Check if the position entered is valid
      while (!(game->checkMove(position))) {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Error: Invalid position"<< std::endl;
        std::cout << "Select a position to place the X: "<< std::endl;
        game->printBoard();
        std::cin >> position;
      }

      game->placeX(position);
      x_turn = false;
    } else {
      std::cout << "Select a position to place the O: "<< std::endl;
      game->printBoard();
      std::cin >> position;

      // Check if the position entered is valid
      while (!(game->checkMove(position))) {
        std::cout << "\033[2J\033[1;1H";
        std::cout << "Error: Invalid position"<< std::endl;
        std::cout << "Select a position to place the O: "<< std::endl;
        game->printBoard();
        std::cin >> position;
      }

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
