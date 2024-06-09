#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

// size of gameboard
#define GBOARD_WIDTH 12
#define GBOARD_HEIGHT 12

// starting point of gameboard
#define GBOARD_ORIGIN_X 18
#define GBOARD_ORIGIN_Y 8


//GameState
#define COMPUTERWIN 3
#define PLAYERWIN 2
#define DRAW 1
#define PROGRESS 0

void initializeBoard(char board[]);
int getInputNumber();

void displayInputRetryMessage();
void displayDrawMessage();
void displayPlayerWinMessage();
void displayComputerWinMessage();

void computerTurn();
int checkGameState();
void clearScreen();
void printBoard();

void moveAndPrintChar(int x, int y, int col, char* c);
void gotoxycol(int x, int y, int col, char* s);
void gotoxytic(int x, int y);

char board[9] = { '1', '2', '3','4', '5', '6','7', '8', '9' };

int tictactoe() {
    
    int inputNumber;
    int isGameRunning = 1;
    int checkState;

    while (isGameRunning) {
        printBoard();
        gotoxytic(48, 14);
        printf("                                                                ");
        gotoxytic(55, 14);
        printf(" ���ڸ� �Է����ּ���: ");

        inputNumber = getInputNumber();
        gotoxytic(78, 14);
        printf("%d", inputNumber);
        Sleep(500);


        if (board[inputNumber - 1] != 'X' && board[inputNumber - 1] != 'O') {

            board[inputNumber - 1] = 'X';

            checkState = checkGameState();

            if (checkState == DRAW) {
                displayDrawMessage();
                updateTicTacToeScore("TICTACTOE", 2);
                break;
            }
            else if (checkState == PLAYERWIN) {
                displayPlayerWinMessage();
                updateTicTacToeScore("TICTACTOE", 0);
                break;
            }
            else if (checkState == COMPUTERWIN) {
                displayComputerWinMessage();
                updateTicTacToeScore("TICTACTOE", 1);
                break;
            }

        }
        else {
            displayInputRetryMessage();
            continue;
        }

        computerTurn();

        checkState = checkGameState();


        if (checkState == DRAW) {
            displayDrawMessage();
            updateTicTacToeScore("TICTACTOE", 2);
            break;
        }

        else if (checkState == PLAYERWIN) {
            displayPlayerWinMessage();
            updateTicTacToeScore("TICTACTOE", 0);
            break;
        }

        else if (checkState == COMPUTERWIN) {
            displayComputerWinMessage();
            updateTicTacToeScore("TICTACTOE", 1);
            break;
        }

    }

    initializeBoard(board);

    return -1;
}


//board[]�� �ʱ�ȭ�ϴ� �Լ� 
void initializeBoard(char board[]) {
    for (int i = 0; i < 9; i++) {
        board[i] = '1' + i; 
    }
}



//���� �Է¹޴� �Լ�
int getInputNumber() {
    while (1) {
        while (!_kbhit());

        char ch = _getch();

        if (ch >= '0' && ch <= '9') {
            return ch - '0';
        }
    }
}


//�̹� �Էµ� ���ڸ� �Է¹޾��� �� ȭ�鿡 ���� �Լ�
void displayInputRetryMessage() {

    printBoard();
    gotoxytic(48, 14);
    printf("�̹� �Էµ� �����Դϴ�. ��� ��ٷȴٰ� �ٽ��Է����ּ���.\n");
    Sleep(500);
}


//Player�� �̰��� �� ȭ�鿡 ���� �Լ�
void displayPlayerWinMessage() {
    printBoard();
    gotoxytic(55, 14);
    printf("Player�� �̰���ϴ�!\n");
    Sleep(500);
}


//Computer�� �̰��� �� ȭ�鿡 ���� �Լ�
void displayComputerWinMessage() {
    printBoard();
    gotoxytic(55, 14);
    printf("Computer�� �̰���ϴ�!\n");
    Sleep(500);
}


//����� �� ȭ�鿡 ���� �Լ�
void displayDrawMessage() {
    printBoard();
    gotoxytic(48, 14);
    printf("                                                                ");
    gotoxytic(55, 14);
    printf("�����ϴ�!\n");
    Sleep(500);
}


//x,y��ǥ ���ϴ� �Լ� 
void gotoxytic(int x, int y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}


//ȭ�� ���� �Ŀ� ���� ���ӻ�Ȳ�� �ݿ��� Board�� ȭ�鿡 �Խ��ϴ� �Լ�
void printBoard() {

    clearScreen();

    // game title
    gotoxycol(45, 2, 14, "�� Tic Tac Toe ��");
    // draw game board
    for (int y = 0; y <= GBOARD_HEIGHT; y++) {
        if (y == 0) gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "��");
        else if (y == GBOARD_HEIGHT) gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "��");
        else {
            gotoxycol(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y, 14, "��");
            gotoxycol(GBOARD_ORIGIN_X + 9, GBOARD_ORIGIN_Y + y, 14, "|");
            gotoxycol(GBOARD_ORIGIN_X + 18, GBOARD_ORIGIN_Y + y, 14, "|");
        }

        if (y == 0) gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "��");
        else if (y == GBOARD_HEIGHT) gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "��");
        else gotoxycol(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y, 14, "��");
    }
    for (int x = 1; x < GBOARD_WIDTH + 1; x++) {
        gotoxycol(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y, 14, "��");
        gotoxycol(GBOARD_ORIGIN_X + x * 2, 12, 14, "-");
        gotoxycol(GBOARD_ORIGIN_X + x * 2, 16, 14, "-");
        gotoxycol(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT, 14, "��");
    }


    moveAndPrintChar(GBOARD_ORIGIN_X + 4, GBOARD_ORIGIN_Y + 2, 14, board[0]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 13, GBOARD_ORIGIN_Y + 2, 14, board[1]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 22, GBOARD_ORIGIN_Y + 2, 14, board[2]);

    moveAndPrintChar(GBOARD_ORIGIN_X + 4, GBOARD_ORIGIN_Y + 6, 14, board[3]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 13, GBOARD_ORIGIN_Y + 6, 14, board[4]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 22, GBOARD_ORIGIN_Y + 6, 14, board[5]);

    moveAndPrintChar(GBOARD_ORIGIN_X + 4, GBOARD_ORIGIN_Y + 10, 14, board[6]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 13, GBOARD_ORIGIN_Y + 10, 14, board[7]);
    moveAndPrintChar(GBOARD_ORIGIN_X + 22, GBOARD_ORIGIN_Y + 10, 14, board[8]);

}


//char ��ġ ���ؼ� ȭ�鿡 ����ϴ� �Լ�
void moveAndPrintChar(int x, int y, int col, char* c) {
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), col);
    printf("%c", c);
}


//computer ������ �� ����Ǵ� �Լ�
void computerTurn() {


    if ((board[1] == 'X' && board[2] == 'X' || board[3] == 'X' && board[6] == 'X' || board[4] == 'X' && board[8] == 'X') &&
        board[0] != 'X' && board[0] != 'O') {
        board[0] = 'O';
    }
    else if ((board[0] == 'X' && board[2] == 'X' || board[4] == 'X' && board[7] == 'X') &&
        board[1] != 'X' && board[1] != 'O') {
        board[1] = 'O';
    }
    else if ((board[0] == 'X' && board[1] == 'X' || board[4] == 'X' && board[6] == 'X' || board[5] == 'X' && board[8] == 'X') &&
        board[2] != 'X' && board[2] != 'O') {
        board[2] = 'O';
    }
    else if ((board[0] == 'X' && board[6] == 'X' || board[4] == 'X' && board[5] == 'X') &&
        board[3] != 'X' && board[3] != 'O') {
        board[3] = 'O';
    }
    else if ((board[0] == 'X' && board[8] == 'X' || board[2] == 'X' && board[6] == 'X' || board[1] == 'X' && board[7] == 'X' || board[3] == 'X' && board[5] == 'X') &&
        board[4] != 'X' && board[4] != 'O') {
        board[4] = 'O';
    }
    else if ((board[3] == 'X' && board[4] == 'X' || board[2] == 'X' && board[8] == 'X') &&
        board[5] != 'X' && board[5] != 'O') {
        board[5] = 'O';
    }
    else if ((board[0] == 'X' && board[3] == 'X' || board[2] == 'X' && board[4] == 'X' || board[7] == 'X' && board[8] == 'X') &&
        board[6] != 'X' && board[6] != 'O') {
        board[6] = 'O';
    }
    else if ((board[1] == 'X' && board[4] == 'X' || board[6] == 'X' && board[8] == 'X') &&
        board[7] != 'X' && board[7] != 'O') {
        board[7] = 'O';
    }
    else if ((board[0] == 'X' && board[4] == 'X' || board[2] == 'X' && board[5] == 'X' || board[6] == 'X' && board[7] == 'X') &&
        board[8] != 'X' && board[8] != 'O') {
        board[8] = 'O';
    }
    else {

        while (1) {
            int randomNubmer = rand() % 8;
            if (board[randomNubmer] != 'X' && board[randomNubmer] != 'O') {
                board[randomNubmer] = 'O';
                break;
            }
        }

    }

}


//���ӻ�Ȳ�� ��Ÿ���� �Լ�
int checkGameState() {

    int i = 0;

    for (i = 0;i < 9;i += 3) {
        if (board[i] == board[i + 1] && board[i + 1] == board[i + 2]) {
            if (board[i] == 'X') {
                return PLAYERWIN;
            }
            return COMPUTERWIN;
        }
    }

    for (i = 0;i < 9;i++) {
        if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
            if (board[i] == 'X') {
                return PLAYERWIN;
            }
            return COMPUTERWIN;
        }
    }


    if ((board[0] == board[4] && board[4] == board[8]) ||
        (board[2] == board[4] && board[4] == board[6])) {
        if (board[4] == 'X') {
            return PLAYERWIN;
        }
        return COMPUTERWIN;
    }


    for (int i = 0;i < 9;i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            return PROGRESS;
        }
    }

    return DRAW;
}

