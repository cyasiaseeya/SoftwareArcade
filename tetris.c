#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include "tetrisheader.h"

// gameBoardinfo[21][12];

int tetris() {
    
    posX = 12;
    posY = 0;
    speed = 30; // ��� �̵� �ӵ�
    score = 0;
    block_id = 0;
    
    int i, j;
    for (i = 0; i < 21; i++) {
        for (j = 0; j < 12; j++) {
            gameBoardInfo[i][j] = 0;
        }
    }

    srand((unsigned int)time(NULL)); // ���� ����
    removeCursor();  // Ŀ�� ����
    DrawGameBoard(); // ���� ���� �׸���

    // ���� ���� ����
    while (1) {
        if (IsGameOver() == 0) { // ���� ���� Ȯ��
            break;
        }
        while (1)
        {
            if (BlockDown() == 0) // ����� �� �̻� ������ �� ���� ���
            {
                AddBlockToBoard();  // ����� ���� ���忡 �߰�
                RemoveFillUpLine(); // ���� �� �� ����
                DrawGameBoard(); // ���� ���� �׸���
                break;
            }
            ProcessKeyInput(); // Ű �Է� ó��
        }
        // ���ο� ��� ���� ��ġ
        posX = 6; posY = 2;
        block_id = (rand() % 7) * 4; // ���ο� ��� ���� ����
    }
    // ���� ���� �޽��� ���
    setCurrentCursorPos(11, 1);
    puts("GameOver");

    checkScore(tetrisGameName, score);

    Sleep(100);
    return -1;
}