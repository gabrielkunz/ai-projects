# AI Projects
 
## Usage
Compile:
```console
foo@bar ~ % g++ main.cpp <executable_name>.out
```
Execute:
```console
foo@bar ~ % ./<executable_name>.out
```

## Program 1: 00_tic_tac_toe_tree/
Tic Tac Toe game where a tree containing all possible boards is generated after each move. Both players enter the move on the terminal and the program will display the total number of possible boards in the tree. The tree is untrimmed, which means that it contains boards that are no possible because one of the player could have won the game in a previous node.

