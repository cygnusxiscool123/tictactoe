#define VR_X A0
#define VR_Y A1
#define SW 2

#include <TicTacToeDisplay.h>

TicTacToeDisplay display; 
int cursorPos = 0;  //tracks the selected square (0-8)
bool isXturn = true;  //X starts first
char board[9] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};  // Board state: ' ' for empty, 'X', 'O'

void setup() {

  display.begin();
  display.drawBoard();
  delay(500);  

  Serial.begin(9600);
  pinMode(VR_X, INPUT);
  pinMode(VR_Y, INPUT);
  pinMode(SW, INPUT_PULLUP);
}


void loop() {
  // put your main code here, to run repeatedly:
  //Read analog values of VR_X and VR_Y
  int vrxValue = analogRead(VR_X);
  int vryValue = analogRead(VR_Y);
  //Read digital value of SW
  int swValue = digitalRead(SW);

  if (vryValue < 200 && cursorPos >= 3) {
    moveCursor(-3);
    delay(300);
  }
  if (vryValue > 900 && cursorPos <= 5) {
    moveCursor(3);
    delay(300);
  }
  if (vrxValue < 200 && cursorPos >= 1) {
    moveCursor(-1);
    delay(300);
  }
  if (vrxValue > 900 && cursorPos <= 7) {
    moveCursor(1);
    delay(300);
  }
  if (swValue == 0) {
    placePiece();
    delay(300);
  }
}

void moveCursor(int step) {
  display.deselectSquare(cursorPos);
  cursorPos = cursorPos + step;
  display.selectSquare(cursorPos);
}

void placePiece() {
  if (board[cursorPos] != ' ' || playerHasWon() == true) {
    return;
  }
  if (isXturn) {
    board[cursorPos] = 'X';
    display.drawX(cursorPos);
    }
  if (!isXturn) {
  board[cursorPos] = 'O';
  display.drawO(cursorPos);
    }
    if (!playerHasWon()) {
      isXturn = !isXturn;
    }
}


bool playerHasWon() {

  //Vertical win
  for (int i = 0; i < 3; i ++) {
    if (board[i] == 'X' 
    && board[i + 3] == 'X' 
    && board[i + 6] == 'X') {
      display.drawSmallText("Player X    has won!");
      display.drawVictoryLine(i, i + 6);
      display.flashScreen();
      delay(500);
      return true;
    }
  }
  for (int i = 0; i < 3; i ++) {
    if (board[i] == 'O' 
    && board[i + 3] == 'O' 
    && board[i + 6] == 'O') {
      display.drawSmallText("Player O    has won!");
      display.drawVictoryLine(i, i + 6);
      display.flashScreen();
      delay(500);
      return true;
    }  
  }

  //Horizontal win
  for (int i = 0; i < 7; i+= 3) {
    if (board[i] == 'X' 
    && board[i + 1] == 'X' 
    && board[i + 2] == 'X') {
      display.drawSmallText("Player X    has won!");
      display.drawVictoryLine(i, i + 2);
      display.flashScreen();
      delay(500);
      return true;
    }
  }
  for (int i = 0; i < 7; i +=3) {
    if (board[i] == 'O' 
    && board[i + 1] == 'O' 
    && board[i + 2] == 'O') {
      display.drawSmallText("Player O    has won!");
      display.drawVictoryLine(i, i + 2);
      display.flashScreen();
      delay(500);
      return true;
    }  
  }

  //Diagonal win
  if (board[2] == 'X' 
    && board[4] == 'X' 
    && board[6] == 'X') {
      display.drawSmallText("Player X    has won!");
      display.drawVictoryLine(2, 6);
      display.flashScreen();
      delay(500);
      return true;
    }

  if (board[2] == 'O' 
    && board[4] == 'O' 
    && board[6] == 'O') {
      display.drawSmallText("Player O    has won!");
      display.drawVictoryLine(2, 6);
      display.flashScreen();
      delay(500);
      return true;
    }

  if (board[0] == 'X' 
    && board[4] == 'X' 
    && board[8] == 'X') {
      display.drawSmallText("Player X    has won!");
      display.drawVictoryLine(0, 8);
      display.flashScreen();
      delay(500);
      return true;
    }

  if (board[0] == 'O' 
    && board[4] == 'O' 
    && board[8] == 'O') {
      display.drawSmallText("Player O    has won!");
      display.drawVictoryLine(0, 8);
      display.flashScreen();
      delay(500);
      return true;
    }

  return false;
}