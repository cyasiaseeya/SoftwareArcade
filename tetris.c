#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include "tetrisheader.h"

int tetris() {
    int i;
    srand((unsigned)time(NULL));
    removeCursor(); //커서를 숨김 
    system("cls");
    reset_main_block(); // 메인 블록 초기화
    draw_main_block(); // 메인 블록 그리기
    game_info();  // 게임 정보
	return 0;
}