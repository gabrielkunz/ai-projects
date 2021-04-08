#include <stdio.h>
#include <string>
#include <iostream>

class Node {
 public:
  Node();
  char board[9];
  int child_count;
  Node * children[9];
  Node * father;
};

class Game {
 public:
  Game();
  void placeX(int position);
  void placeO(int position);
  void printBoard();
  int getRemainingMoves();
  char getWinner();
  bool checkMove(int position);
  char checkWinner();
  void removePosition(int position);
  char board[9];
 private:
  int remaining_moves;
  int available_positions[9];
  char winner;
};

Node::Node() {
  for (int i = 0; i < 9; i++)
    board[i] = '_';
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
  winner = checkWinner();
}

void Game::placeO(int position) {
  board[position] = 'O';
  remaining_moves--;
  removePosition(position);
  winner = checkWinner();
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

char Game::getWinner() {
  return winner;
}

// This function returns true if the move entered is inside the board
// (valid) or if it wasn't played before
bool Game::checkMove(int position) {
  int * find_result =
    std::find(available_positions, available_positions+9, position);

  if (position < 0 || position > 8 || find_result == available_positions + 9) {
    return false;
  } else {
    return true;
  }
}

// This functions returns 'X' or 'O' if someone has won the game, or '_'
// if the game is still going. The check starts already after the first move.
char Game::checkWinner() {
  // Check rows
  if (board[0] == board[1] && board[0] == board[2] && board[0] != '_') {
    remaining_moves = 0;
    return board[0];
  } else if (board[3] == board[4] && board[3] == board[5] && board[3] != '_') {
    remaining_moves = 0;
    return board[3];
  } else if (board[6] == board[7] && board[6] == board[8] && board[6] != '_') {
    remaining_moves = 0;
    return board[6];

  // Check columns
  } else if (board[0] == board[3] && board[0] == board[6] && board[0] != '_') {
    remaining_moves = 0;
    return board[0];
  } else if (board[1] == board[4] && board[1] == board[7] && board[1] != '_') {
    remaining_moves = 0;
    return board[1];
  } else if (board[2] == board[5] && board[5] == board[8] && board[2] != '_') {
    remaining_moves = 0;
    return board[2];

  // Check diagonals
  } else if (board[0] == board[4] && board[0] == board[8] && board[0] != '_') {
    remaining_moves = 0;
    return board[0];
  } else if (board[2] == board[4] && board[2] == board[6] && board[2] != '_') {
    remaining_moves = 0;
    return board[2];
  } else {
    // Game still going
    return '_';
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
Node * createTree(int remaining_moves, char game_board[9], Node * father) {
  Node * node = new Node();

  node->child_count = remaining_moves;
  node->father = father;

  if (node->child_count > 0) {
    for (int i = 0; i != node->child_count; i++) {
      node->children[i] = new Node();
      node->children[i] = createTree(remaining_moves - 1, game_board, node);
    }
  } else {
    node->children[0] = NULL;
  }

  return node;
}

// This function deletes the entire tree. The input is the
// root node. The function starts deleting its children and
// then deletes itself.
void deleteTree(Node * node) {
    for (int i = 0; i != node->child_count; i++)
        deleteTree(node->children[i]);
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
  std::cout << node->board << std::endl;
  for (int i = 0; i != node->child_count; i++) {
    printNodeBoards(node->children[i]);
  }
}

int main() {
  bool x_turn = true;
  int position = 9;
  Game * game = new Game();

  // Loop for the game input. The loop will alternate between X's and O's turns.
  // If an invalid position is entered (smaller than 0 or greater than 8), the
  // input is requested again.
  while (game->getRemainingMoves() != 0) {
    std::cout << "Remaining Moves: " << game->getRemainingMoves() << std::endl;
    Node * root;
    root = createTree(game->getRemainingMoves(), game->board, NULL);

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
  }

  std::cout << "Game Over: ";
  if (game->getWinner() == '_') {
    std::cout << "Draw" << std::endl;
  } else {
    std::cout << "Player " << game->getWinner() << " won"<< std::endl;
  }
  game->printBoard();

  return 0;
}
