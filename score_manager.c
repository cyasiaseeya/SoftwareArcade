#include "score_manager.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#pragma warning(disable:4996)

void checkFileExist() {

    FILE* fp;
    fp = fopen("SOFTWAREARCADE_SCORE.txt", "r+");

    if (fp == NULL) {
        fp = fopen("SOFTWAREARCADE_SCORE.txt", "w");

        for (int i = 0; i < 10; i++) {          // ������ũ ���� ���� �ʱ�ȭ
            fputs("SNAKE 0\n", fp);
        }
        for (int i = 0; i < 10; i++) {          // ��Ʈ���� ���� ���� �ʱ�ȭ
            fputs("TETRIS 0\n", fp);
        }
        fputs("TICTACTOE 0 0 0\n", fp);         // ƽ���� ���� �¸�/�й�/���º� �ʱ�ȭ
        fclose(fp);
    }
    else
        fclose(fp);

}

void checkScore(char *gameName, int curGameScore) {
    char savedGameName[10];
    int savedGameScore;

    FILE* file = fopen("SOFTWAREARCADE_SCORE.txt", "r");
    if (file == NULL) {
        printf("score file does not exist\n");
        exit(-1);
    }

    while (fscanf(file, "%s %d", savedGameName, &savedGameScore) != EOF) {

        if (strcmp(gameName, savedGameName) == 0 && curGameScore > savedGameScore) {
            fclose(file);
            updateFile(gameName, curGameScore);
            return;
        }
    }

    fclose(file);
}

void updateFile(char *gameName, int newScore) {
    FILE* fp = fopen("SOFTWAREARCADE_SCORE.txt", "r");
    FILE* tempFile = fopen("temp.txt", "w");

    if (fp == NULL) {
        printf("Could not open file");
        exit(-1);
    }

    char buffer[256];
    char name[10];
    int score;
    int tempScore = newScore;



    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        sscanf(buffer, "%s %d", name, &score);
        if (strcmp(name, gameName) == 0) {
            if (tempScore > score) {
                fprintf(tempFile, "%s %d\n", gameName, tempScore);
                tempScore = score;
            }
            else {
                fprintf(tempFile, "%s %d\n", name, score);
            }
        }
        else {
            fprintf(tempFile, "%s", buffer);
        }
    }

    fclose(fp);
    fclose(tempFile);

    remove("SOFTWAREARCADE_SCORE.txt");
    rename("temp.txt", "SOFTWAREARCADE_SCORE.txt");
}