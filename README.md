# dots_and_boxes_minimax
## Rules  
Dots and boxes is a classic, 2-player combinatorial strategy game. The game starts with an empty m×n grid. During each turn, a player draws a line joining two adjacent dots. The line must either be horizontal or vertical. If a player draws a line which completes a square, then the player earns points. If a square is completed by any player, then one more move needs to be completed by the same player. The goal of each player is to complete as many boxes as possible and earn maximum amount of points. This continues until no more moves can be made.  
## Game board implementation  
```
BOARD 3x3 (5x5 actually) -> 2*rows - 1, 2*cols - 1

           0 1 2 3 4	-> actual coordinates
           0   1   2	-> coordinates for player
          ___________
    0  0 | *   *   *
    1    |
    2  1 | *   *   *
    3    |
    4  2 | *   *   *

DOTS:  -> i and j are even numbers -> 0 (*)

LINES: -> i is odd, j is even      -> 0 for Free, 1 for Line
          or i is even, j is odd

BOXES: -> i and j are odd numbers  -> 0 for Free, 1 for Player1, 2 for Player2
```
## Minimax algorithm with alpha beta pruning  
A node is terminal when:
- depth = 0
- the number of free lines on the board = 0  

Heuristic value for a node consists of:
- remaining free lines / 2
- number of boxes that have been taken
