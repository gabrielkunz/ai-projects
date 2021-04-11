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
Tic Tac Toe game where a tree containing all possible boards is generated after each move. Both players enter the move on the terminal and the program will display the total number of possible boards in the tree. The tree is untrimmed, which means that it contains boards that are not possible because one of the player could have won the game already in a previous node.

The tree is created based on the following structure:

![alt text](https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2F1.bp.blogspot.com%2F-LsJinVrVFz8%2FWHoAy4WBz_I%2FAAAAAAAA6qY%2FoKyq9vlydMAH27zxhIlMxMfHCf5B0n8tQCLcB%2Fs1600%2FOXO-search-tree.jpg&f=1&nofb=1)

Starting at the root level 1 (with the empty board), we have the following combinations:

Level 1 = 9 + 9\*8 + 9\*8\*7 + 9\*8\*7\*6 + 9\*8\*7\*6\*5 + 9\*8\*7\*6\*5\*4 + 9\*8\*7\*6\*5\*4\*3 + 9\*8\*7\*6\*5\*4\*3\*2 + 9\*8\*7\*6\*5\*4\*3\*2\*1 = 986.409 possible boards

Level 2 = 8 + 8\*7 + 8\*7\*6 + 8\*7\*6\*5 + 8\*7\*6\*5\*4 + 8\*7\*6\*5\*4\*3 + 8\*7\*6\*5\*4\*3\*2 + 8\*7\*6\*5\*4\*3\*2\*1 = 109.600 possible boards

Level 3 = 7 + 7\*6 + 7\*6\*5 + 7\*6\*5\*4 + 7\*6\*5\*4\*3 + 7\*6\*5\*4\*3\*2 + 7\*6\*5\*4\*3\*2\*1 = 13.699 possible boards

Level 4 = 6 + 6\*5 + 6\*5\*4 + 6\*5\*4\*3 + 6\*5\*4\*3\*2 + 6\*5\*4\*3\*2\*1 = 1,956 possible boards

Level 5 = 5 + 5\*4 + 5\*4\*3 + 5\*4\*3\*2 + 5\*4\*3\*2\*1 = 325 possible boards

Level 6 = 4 + 4\*3 + 4\*3\*2 + 4\*3\*2\*1 = 64 possible boards

Level 7 = 3 + 3\*2 + 3\*2\*1 = 15 possible boards

Level 8 = 2 + 2\*1 = 4 possible boards

Level 9 = 1 possible board
