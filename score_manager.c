#include "score_manager.h"
#include <stdio.h>


void checkFileExist() {

    FILE* fp;
    fp = fopen("SOFTWAREARCADE_SCORE.txt", "r+");

    if (fp == NULL) {
        fp = fopen("SOFTWAREARCADE_SCORE.txt", "w");

        for (int i = 0; i < 10; i++) {          // ������ũ ���� ���� �ʱ�ȭ
            fputs("SNAKE 000000\n", fp);
        }
        for (int i = 0; i < 10; i++) {          // ��Ʈ���� ���� ���� �ʱ�ȭ
            fputs("TETRIS 000000\n", fp);
        }
        fputs("TICTACTOE 0 0 0\n", fp);                   // ƽ���� ���� �¸�/�й�/���º� �ʱ�ȭ
        fclose(fp);
    }
    else
        fclose(fp);

}
