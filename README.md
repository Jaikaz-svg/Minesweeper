# Minesweeper Classic

A classic puzzle game where you need to avoid hidden mines.

This program is writen by russian student Popov AV

# Game Features

- When opening a cell, all adjacent 3x3 cells are automatically revealed (except those containing mines)
- Attempting to open an already revealed cell will be ignored
## Game Control
- To revial cell enter coordinates (x, y) followed by ANY number (except 1):
    > 3 4 0
- To place a flag enter coordinates (x, y) followed by number 1:
    > 5 2 1
- If you want to revial demine cell, simply enter its coords
- **Simple Rules**: 
  - `?` - Unexplored cell
  - `#` - Flagged cell (suspected mine)
  - `1-8` - Number of adjacent mines
  - `*` - Mine (revealed when triggered)

# Developer Notes

I welcome all feedback and suggestions! Please feel free to open issues or contribute to the project. There is more information about program structure in spec-ation.cpp file

I'm planning to Qt-based GUI implementation

I hope you enjoy the game! :)
