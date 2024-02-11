#include <stdio.h>
#include <stdlib.h>
#include <threads.h>
#include <unistd.h>

#define WIDTH 10
#define HIGHT 10
#define MAX_SNAKE_SIZE 10

#define CLEAR "\e[1;1H\e[2J"

typedef struct {
  int x, y;
} point;

typedef struct {
  point head[MAX_SNAKE_SIZE];
} snake;

enum DIRECTION { NODIR, UP, DOWN, LEFT, RIGHT };

const point UP_DIR = {0, -1};
const point DOWN_DIR = {0, 1};
const point LEFT_DIR = {-1, 0};
const point RIGHT_DIR = {1, 0};
const point NO_DIR = {0, 0};

void drawBoardToConsole(char arr[WIDTH][HIGHT]) {

  printf(CLEAR);
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HIGHT; j++) {
      printf("%c", arr[i][j]);
    }
    printf("\n");
  }
}

void initBoard(char arr[WIDTH][HIGHT]) {

  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HIGHT; j++) {
      arr[i][j] = '*';
    }
  }
}

int checkEdge(point p) {

  int dir = NODIR;
  //  printf("checking %d,%d", p.x, p.y);

  if (p.x == -1)
    dir = LEFT;
  if (p.y == -1)
    dir = UP;
  if (p.x == WIDTH)
    dir = RIGHT;
  if (p.y == HIGHT)
    dir = DOWN;

  return dir;
}

point mapDirEnumToDir(int dirEnum) {

  switch (dirEnum) {
  case UP:
    return UP_DIR;
  case DOWN:
    return DOWN_DIR;
  case LEFT:
    return LEFT_DIR;
  case RIGHT:
    return RIGHT_DIR;
  }
  return NO_DIR;
}

void addPointToBoard(char arr[WIDTH][HIGHT], char pix, point e) {
  arr[e.y][e.x] = pix;
}

int updateAndDisplayBoard(char board[WIDTH][HIGHT], point head) {
  if (checkEdge(head) != 0) {
    printf("You loose!");
    return 1;
  } else {
    addPointToBoard(board, 'x', head);
    drawBoardToConsole(board);
  }
  return 0;
}

int main() {

  char board[WIDTH][HIGHT];

  point head;
  int direction = UP;
  head.x = 3;
  head.y = 5;

  initBoard(board);
  updateAndDisplayBoard(board, head);

  // game loop

  int flag = 0;

  while (1) {
    sleep(1);
    initBoard(board);

    flag++;
    if (flag == 3) {
      flag = 0;
      if (direction == 4) {
        direction = 1;
      } else {
        direction++;
      }
    }

    point dir = mapDirEnumToDir(direction);
    printf("%d", head.y);
    head.x += dir.x;
    head.y += dir.y;

    if (updateAndDisplayBoard(board, head)) {
      break;
    }
  }

  return 0;
}
