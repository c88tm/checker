# Checker Game

## Introduction

This is a chinese checkers program written in cpp, where the program itself is devided into two parts:

### Server

Server holds the board of the game, executing clients for next thier move.\

### Client

Client reads the board and outputs its results with file IO

## I/O

Server will dump `board.txt` each time before executing a client.\
It is a 17x17 array looks something like this:

```txt
0 0 0 0 0 0 0 0 0 0 0 0 2 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 2 2 0 0 0 0
0 0 0 0 0 0 0 0 0 0 2 2 2 0 0 0 0
0 0 0 0 0 0 0 0 0 2 2 2 2 0 0 0 0
0 0 0 0 1 1 1 1 2 2 2 2 2 1 1 1 1
0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 1 0
0 0 0 0 1 1 1 1 1 1 1 1 1 1 1 0 0
0 0 0 0 1 1 1 1 1 1 1 1 1 1 0 0 0
0 0 0 0 1 1 1 1 1 1 1 1 1 0 0 0 0
0 0 0 1 1 1 1 1 1 1 1 1 1 0 0 0 0
0 0 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0
0 1 1 1 1 1 1 1 1 1 1 1 1 0 0 0 0
1 1 1 1 3 3 3 3 3 1 1 1 1 0 0 0 0
0 0 0 0 3 3 3 3 0 0 0 0 0 0 0 0 0
0 0 0 0 3 3 3 0 0 0 0 0 0 0 0 0 0
0 0 0 0 3 3 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 3 0 0 0 0 0 0 0 0 0 0 0 0
```

where 0 is void, 1 is empty spaces, 2 and above are different colors of checkers.

Client will reads this text file in, then outputs another text file with the same filename as your executable.\
First line of the output should have one number $n$, as total jumps you make in this move.\
Then the next $n+1$ lines contains two numbers $X_i, Y_i$, your peice of checker should be able to jump from $X_0, Y_0$ and stops at $X_n, Y_n$.

## Usage

Use server.cpp like:

```cmd
.\server.exe <AI1> <AI2>
```

Both AI.exes should be kept within the same folder\
Server will call **AI#**.exe with `<AI#>.exe <player_num>`\
Where **player_num** is the number that indicates the player on chess board\
In each round, player should read inputs from `board.txt` and outputs to **AI#**.txt

Server will execute client like:

```cmd
.\s1071226.exe 3
```

client should read from `board.txt` and outputs its move to `s1071226.txt` within a minute.