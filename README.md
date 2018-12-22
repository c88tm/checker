# Checker Game

## Usage:
Use server.cpp like:
```
.\server.exe <AI1> <AI2>
```
Both AI.exes should be kept within the same folder
Server will call **AI#**.exe with `<AI#>.exe <player_num>`
Where **player_num** is the number that indicates the player on chess board
In each round, player should read inputs from `board.txt` and outputs to **AI#**.txt
return 0;