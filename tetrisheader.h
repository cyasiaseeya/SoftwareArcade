#pragma once
#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>
#include "BlockModel.h"

int posX, posY; // Ŀ�� ��ġ
#define GBOARD_WIDTH 10   // ���� ������ �ʺ�
#define GBOARD_HEIGHT 20  // ���� ������ ����
#define GBOARD_ORIGIN_X 4 // ���� ������ x��
#define GBOARD_ORIGIN_Y 2 // ���� ������ y��

#define LEFT 75   // LEFT Ű
#define RIGHT 77  // RIGHT Ű
#define UP 72 // UP Ű
#define DOWN 80 // DOWN Ű
#define SPACE 32 // SPACE Ű

int block_id;
int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2]; // ���� ���� ����
void ShowBlock(char blockInfo[4][4]);   // ����� ȭ�鿡 ǥ���ϴ� �Լ�                      
void DeleteBlock(char blockInfo[4][4]); // ȭ�鿡�� ����� ����� �Լ�                      
void DrawGameBoard(); // ���� ���带 �׸��� �Լ�
int DetectCollision(int PosX, int PosY, char blockModel[4][4]); // �浹�� �����ϴ� �Լ� 
void ShiftRight(void); // ����� ���������� �̵���Ű�� �Լ�
void ShiftLeft(void);  // ����� �������� �̵���Ű�� �Լ�
int BlockDown();       // ����� �Ʒ��� �� ĭ �̵���Ű�� �Լ�
void RotateBlock();    // ����� ȸ����Ű�� �Լ�
void SpaceDown();      // ����� �ٴڱ��� �� ���� ������ �Լ�

int speed; //  �ӵ�
void ProcessKeyInput(); // Ű �Է��� ó���ϴ� �Լ�
int IsGameOver(void); // ���� ���� ���θ� Ȯ���ϴ� �Լ�
void RedrawBlocks(void); // ���� ���带 �ٽ� �׸��� �Լ�
void AddBlockToBoard(void); // ���� ����� ���� ���忡 �߰��ϴ� �Լ�
void RemoveFillUpLine(void); // ���� �� ���� �����ϴ� �Լ�

int score = 0, best_score = 0; // ���� ����, �ְ� ����
char* gameName = "TETRIS";

void ShowBlock(char blockInfo[4][4]) // ����� ȭ�鿡 ǥ���ϴ� �Լ�
{
	int x, y;
	COORD curPos = getCurrentCursorPos2(); // ���� Ŀ�� ��ġ
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			setCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y); // �ش� ��ǥ�� Ŀ�� �̵�
			if (blockInfo[y][x] == 1) // ����� ������
				printf("��");          // ��� ǥ��
		}
	}
	setCurrentCursorPos(curPos.X, curPos.Y); // ���� ��ġ�� Ŀ�� �̵�
}
void DeleteBlock(char blockInfo[4][4]) // ȭ�鿡�� ����� ����� �Լ�
{
	int x, y;
	COORD curPos = getCurrentCursorPos2(); // ���� Ŀ�� ��ġ
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			setCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y); // �ش� ��ǥ�� Ŀ�� �̵�
			if (blockInfo[y][x] == 1) // ����� ������
				printf(" ");          // ��� ����
		}
	}
	setCurrentCursorPos(curPos.X, curPos.Y); // ���� ��ġ�� Ŀ�� �̵�
}
void DrawGameBoard() { // ���� ���带 �׸��� �Լ�
	int x, y;
	for (y = 0; y <= GBOARD_HEIGHT; y++) {
		setCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);
		if (y == GBOARD_HEIGHT)
			printf("��"); // ���� �Ʒ� �𼭸�
		else
			printf("��"); // ���� ��
	}
	for (y = 0; y <= GBOARD_HEIGHT; y++) {
		setCurrentCursorPos(GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2, GBOARD_ORIGIN_Y + y);
		if (y == GBOARD_HEIGHT)
			printf("��"); // ������ �Ʒ� �𼭸�
		else
			printf("��"); // ������ ��
	}
	for (x = 1; x < GBOARD_WIDTH + 1; x++) {
		setCurrentCursorPos(GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);
		printf("��"); // �Ʒ� ��
	}
	setCurrentCursorPos(GBOARD_ORIGIN_X + GBOARD_WIDTH, 0);

	// ���� ���� �迭 �ʱ�ȭ
	for (x = 0; x < GBOARD_WIDTH + 2; x++) {
		gameBoardInfo[GBOARD_HEIGHT][x] = 2; // �ٴ��� 2�� ����
	}
	for (y = 0; y < GBOARD_HEIGHT; y++) {
		gameBoardInfo[y][0] = 2;				// ���� ���� 2�� ����
		gameBoardInfo[y][GBOARD_WIDTH + 1] = 2; // ������ ���� 2�� ����
	}

	// ���� ����, ���� ����
	setCurrentCursorPos(34, 9);  printf("      SCORE : %6d", score);       // ���� ����
	setCurrentCursorPos(34, 12); printf(" BEST SCORE : %6d", best_score);  // �ְ� ����
	setCurrentCursorPos(34, 15); printf("  ��   : ��� �ٲٱ�");
	setCurrentCursorPos(34, 16); printf("��   �� : ��� �̵�");
	setCurrentCursorPos(34, 17); printf("  ��   : Soft Drop");
	setCurrentCursorPos(34, 18); printf("SPACE : Hard Drop");
}


int DetectCollision(int PosX, int PosY, char blockModel[4][4]) // �浹�� �����ϴ� �Լ�
{
	int X, Y;
	int arrX = (PosX - GBOARD_ORIGIN_X) / 2;
	int arrY = PosY - GBOARD_ORIGIN_Y;
	for (X = 0; X < 4; X++)
	{
		for (Y = 0; Y < 4; Y++)
		{
			if (blockModel[Y][X] == 1 && gameBoardInfo[arrY + Y][arrX + X] == 2)
				return 0; // �浹�ϸ� 0 ��ȯ
		}
	}
	return 1; // �浹���� ������ 1 ��ȯ
}
void ShiftRight(void) // ����� ���������� �̵���Ű�� �Լ�
{
	if (DetectCollision(posX + 2, posY, blockModel[block_id]) == 0) { // ������ �̵� �������� Ȯ��
		return; // �浹�ϸ� �̵����� ����
	}
	DeleteBlock(blockModel[block_id]); // ���� ��� ����
	posX += 2;
	setCurrentCursorPos(posX, posY); // Ŀ�� �̵�
	ShowBlock(blockModel[block_id]); // ��� �׸���
}
void ShiftLeft(void) // ����� �������� �̵���Ű�� �Լ�
{
	if (DetectCollision(posX - 2, posY, blockModel[block_id]) == 0) { // ���� �̵� �������� Ȯ��
		return; // �浹�ϸ� �̵����� ����
	}
	DeleteBlock(blockModel[block_id]); // ���� ��� ����
	posX -= 2;
	setCurrentCursorPos(posX, posY); // Ŀ�� �̵�
	ShowBlock(blockModel[block_id]); // ��� �׸���
}
int BlockDown() // ����� �Ʒ��� �� ĭ �̵���Ű�� �Լ�
{
	if (!DetectCollision(posX, posY + 1, blockModel[block_id])) { // �Ʒ� �̵� ���� Ȯ��
		return 0;
	}
	DeleteBlock(blockModel[block_id]); // ���� ��� ����
	posY += 1;
	setCurrentCursorPos(posX, posY); // Ŀ�� �̵�
	ShowBlock(blockModel[block_id]); // ��� �׸���
	return 1; // �̵� ���� �� 1 ��ȯ
}
void RotateBlock()  // ����� ȸ����Ű�� �Լ�
{
	int block_base;
	block_base = block_id - block_id % 4;
	int block_rotated = block_base + (block_id + 1) % 4;
	if (!DetectCollision(posX, posY, blockModel[block_rotated])) { // ȸ���� �� �ִ��� Ȯ��
		return 0; // �浹�ϸ� ȸ������ ����
	}
	DeleteBlock(blockModel[block_id]); // ���� ��� ����
	block_id = block_rotated;
	ShowBlock(blockModel[block_id]); // ȸ���� ����� �׸�
}
void SpaceDown()  // ����� �ٴڱ��� �� ���� ������ �Լ�
{
	while (BlockDown()); // ����� �� �̻� ������ �� ���� ������ ��� ����
}

void ProcessKeyInput() // Ű �Է��� ó���ϴ� �Լ�
{
	int i, key;
	for (i = 0; i < 20; i++)
	{
		if (_kbhit() != 0) // Ű �Է��� �ִ��� Ȯ��
		{
			key = _getch(); // Ű �Է��� �޾ƿ�
			switch (key)
			{
			case LEFT:  // ���� 
				ShiftLeft();  // ��� ���� �̵�
				break;
			case RIGHT: // ������
				ShiftRight(); // ��� ������ �̵�
				break;
			case UP:    // ��
				RotateBlock(); // ��� ȸ��
				break;
			case DOWN:  // �Ʒ�
				if (DetectCollision(posX, posY + 1, blockModel[block_id])) // ����� �� ĭ �Ʒ��� �̵� �������� Ȯ��
				{
					DeleteBlock(blockModel[block_id]); // ���� ��ġ�� ��� ����
					posY += 1; // ����� Y ��ġ�� �� ĭ �Ʒ��� �̵�
					setCurrentCursorPos(posX, posY); // Ŀ���� ���ο� ��� ��ġ�� �̵�
					ShowBlock(blockModel[block_id]); // ���ο� ��ġ�� ����� ǥ��
				}
				break;
			case SPACE: // �����̽���
				SpaceDown();   // ��� �ϵ� ���
				break;
			}
		}
		Sleep(speed);
	}
}
int IsGameOver(void) // ���� ���� ���θ� Ȯ���ϴ� �Լ�
{
	if (DetectCollision(posX, posY, blockModel[block_id]) == 1) // �浹���� ������
	{
		return 1; // ���� ����
	}
	else return 0; // �浹�ϸ� ���� ����
}
void RedrawBlocks(void) // ���� ���带 �ٽ� �׸��� �Լ�
{
	int x, y;
	int cursX, cursY;
	for (y = 0; y < GBOARD_HEIGHT; y++)
	{
		for (x = 1; x < GBOARD_WIDTH + 1; x++)
		{
			cursX = x * 2 + GBOARD_ORIGIN_X;
			cursY = y + GBOARD_ORIGIN_Y;
			setCurrentCursorPos(cursX, cursY); // Ŀ�� �̵�
			if (gameBoardInfo[y][x] == 2)
			{
				printf("��"); // ��� �׸���
			}
			else { printf("  "); } // �� ���� �׸���
		}
	}
}
void AddBlockToBoard(void) // ���� ����� ���� ���忡 �߰��ϴ� �Լ�
{
	int x, y, arrCurX, arrCurY;
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)

		{
			arrCurX = (posX - GBOARD_ORIGIN_X) / 2;
			arrCurY = posY - GBOARD_ORIGIN_Y;

			if (blockModel[block_id][y][x] == 1) // ����� �ִ� �κ���
				gameBoardInfo[arrCurY + y][arrCurX + x] = 2; // ���� ���忡 �߰�
		}
	}
}
void RemoveFillUpLine(void) // ���� �� ���� �����ϴ� �Լ�
{
	int line, x, y;
	for (y = GBOARD_HEIGHT - 1; y > 0; y--) {
		for (x = 1; x < GBOARD_WIDTH + 1; x++) {
			if (gameBoardInfo[y][x] != 2) // ���� �� �ٿ� �� ĭ�� ������
				break; // �˻� �ߴ�
		}
		if (x == (GBOARD_WIDTH + 1)) { // �� ���� ���� �� ���
			score += 10;
			for (line = 0; y - line > 0; line++) {
				// �Ʒ��������� ���� ��ܿ�
				memcpy(&gameBoardInfo[y - line][1],
					&gameBoardInfo[(y - line) - 1][1], GBOARD_WIDTH * sizeof(int)); // ����

			}
			y++; // �˻��� ���� �ٽ� �˻�
		}
	}
	// ��� ID�� 28�� ���(����)
	if (block_id == 28) {
		int x, y;
		int arrCurX = (posX - GBOARD_ORIGIN_X) / 2;
		int arrCurY = posY - GBOARD_ORIGIN_Y;
		for (y = arrCurY; y < arrCurY + 4; y++) {
			for (x = 0; x < 4; x++) {
				gameBoardInfo[y][arrCurX + x] = 0; // ����� �������� ����
			}
		}
	}
	RedrawBlocks(); // ���� ���� �ٽ� �׸�
}