#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <cstdlib> 
#include <conio.h> 
#include <windows.h>
#include <mmsystem.h>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <chrono>
#include <thread>
#pragma comment(lib, "winmm.lib")

using namespace std;

void clearScreen() {
#ifdef _WIN32
	system("CLS");
#else
	system("clear");
#endif
}

class Sprite {
protected:
	int x, y;
	char shape;
public:
	Sprite(int x, int y, char shape) : x(x), y(y), shape(shape) {}
	virtual ~Sprite() {}
	virtual void move(char d) = 0;
	char getShape() { return shape; }
	int getX() { return x; }
	int getY() { return y; }
	bool checkCollision(Sprite* other) {
		return (x == other->getX() && y == other->getY());
	}
};

class Board {
	char* board;
	char* originalBoard; // enemy 이동 때 사용할 보드 백업
	int width, height;
public:
	Board(int w, int h) : width(w), height(h) {
		board = new char[width * height];
		generateMaze();

		// 보드 백업 생성
		originalBoard = new char[width * height];
		memcpy(originalBoard, board, width * height * sizeof(char));
	}

	~Board() {
		delete[] board;
		delete[] originalBoard;
	}

	void setValue(int r, int c, char shape) {
		board[r * width + c] = shape;
	}

	char getValue(int r, int c) {
		return board[r * width + c];
	}

	void printBoard() {
		for (int i = 0; i < height; i++) {
			cout << "\t";
			for (int j = 0; j < width; j++) {
				char symbol = board[i * width + j];
				if (symbol == '_') {
					cout << "#"; // 벽
				}
				else if (symbol == '.') {
					cout << " "; // 빈 공간
				}
				else {
					cout << symbol; // 스프라이트 요소 (H, T, E)
				}
			}
			cout << endl;
		}
	}

	void clearBoard() {
		// 보드를 초기화
		memcpy(board, originalBoard, width * height * sizeof(char));
	}

	void generateMaze() {
		srand(static_cast<unsigned int>(time(NULL)));

		// 초기에는 모든 칸을 벽(_)으로 설정
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				board[i * width + j] = '_';
			}
		}

		// 방향 설정
		int directions[4][2] = {
			{-2, 0},  // 위로 이동
			{2, 0},   // 아래로 이동
			{0, -2},  // 왼쪽으로 이동
			{0, 2}    // 오른쪽으로 이동
		};

		// 방향을 섞어주는 헬퍼 함수
		auto shuffleDirections = [&]() {
			for (int i = 3; i > 0; --i) {
				int j = rand() % (i + 1);
				std::swap(directions[i], directions[j]);
			}
			};

		// 재귀 백트래킹 함수
		std::function<void(int, int)> carvePath = [&](int r, int c) {
			board[r * width + c] = '.'; // 현재 칸을 열린 상태로 표시
			shuffleDirections(); // 탐색 순서를 랜덤화

			for (const auto& dir : directions) {
				int newRow = r + dir[0];
				int newCol = c + dir[1];

				// 범위를 벗어나지 않고, 새 칸이 벽으로 둘러싸인 경우만 처리
				if (newRow > 0 && newRow < height - 1 && newCol > 0 && newCol < width - 1 &&
					board[newRow * width + newCol] == '_') {

					// 현재 칸과 다음 칸 사이의 벽을 열기
					board[(r + newRow) / 2 * width + (c + newCol) / 2] = '.';

					// 새 칸으로 재귀 호출
					carvePath(newRow, newCol);
				}
			}
			};

		// 좌상단에서 시작하여 미로 생성
		carvePath(1, 1);

		// 시작 지점과 목표 지점은 항상 열려있게 설정
		board[1 * width + 1] = '.'; // 시작점
		board[(height - 2) * width + (width - 2)] = '.'; // 목표점

		// 미로가 연결되도록 모든 벽을 확인하며 연결되지 않은 부분 열기
		for (int i = 1; i < height - 1; i += 2) {
			for (int j = 1; j < width - 1; j += 2) {
				if (board[i * width + j] == '_') {
					board[i * width + j] = '.';
					int direction = rand() % 4;
					int connectRow = i + directions[direction][0] / 2;
					int connectCol = j + directions[direction][1] / 2;
					if (connectRow > 0 && connectRow < height - 1 && connectCol > 0 && connectCol < width - 1) {
						board[connectRow * width + connectCol] = '.';
					}
				}
			}
		}
	}
};

class Hero : public Sprite {
private:
	int boardWidth, boardHeight;
	int score;
	Board& board;
public:
	Hero(int x, int y, int boardWidth, int boardHeight, Board& board)
		: Sprite(x, y, 'H'), boardWidth(boardWidth), boardHeight(boardHeight), board(board), score(0) {}

	void move(char d) override {
		int newX = x, newY = y;

		if (d == 'a' && x > 0) { newX -= 1; }      // Left
		else if (d == 'w' && y > 0) { newY -= 1; } // Up
		else if (d == 's' && y < boardHeight - 1) { newY += 1; } // Down
		else if (d == 'd' && x < boardWidth - 1) { newX += 1; }  // Right

		// 벽에 닿았는지 확인
		if (board.getValue(newY, newX) != '_') {
			x = newX;
			y = newY;
		}
	}

	void increaseScore() {
		score++;
	}

	int getScore() const {
		return score;
	}
};

class Treasure : public Sprite {
public:
	Treasure(int x, int y) : Sprite(x, y, 'T') {}
	void move(char d) override {}
};

class Enemy : public Sprite {
private:
	int boardWidth, boardHeight;
	Board& board;
public:
	Enemy(int x, int y, int boardWidth, int boardHeight, Board& board)
		: Sprite(x, y, 'E'), boardWidth(boardWidth), boardHeight(boardHeight), board(board) {}

	void move(char d) override {
		int direction = d - '0';
		int newX = x, newY = y;

		// 이동
		if (direction == 0 && x > 0) { newX -= 1; }      // Left
		else if (direction == 1 && y > 0) { newY -= 1; } // Up
		else if (direction == 2 && y < boardHeight - 1) { newY += 1; } // Down
		else if (direction == 3 && x < boardWidth - 1) { newX += 1; }  // Right

		// x, y 업데이트
		x = newX;
		y = newY;
	}
};

// 스페이스바 입력 대기
void waitForSpaceBar() {
	while (true) {
		if (_getch() == ' ') break;
	}
	cout << endl;
}

void drawLine(char x, int n) {
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << x;
	}
	cout << endl;
}

// 시작 화면 메서드
void displayStartScreen() {
	system("cls");
	drawLine('*', 120);
	cout << setw(140) << "" << R"(
                                 ____  ______   ________  ______  _____  _   _  
                                |  _ `| _   `  / /  __  `| ____ ||  _  || | | |
                                | | | | | | ` V /| |  | || |__   | | | ||  `| |
                                | | | | | | |> < | |  | ||  __|  | | | || `   |
                                | |_| | |_| / . `| |__| || |____ | |_| || | ` |
                                |____/|____/_/ `_`_____/ |______||_____||_| |_|
                                                 
    )";

	cout << setw(130) << "" << R"(
                                       ____   ______   __  __  ______ 
                                      / ___| |  __  | |  |/  ||  ____|
                                     | |  _  | |__| | | |  / || |__   
                                     | | | | |  __  | | ||/| ||  __|  
                                     | |_| | | |  | | | |  | || |____ 
                                     |_____| |_|  |_| |_|  |_||______| 
                                      
    )" << endl;
	cout << setw(75) << "Press [ENTER] to Start Your Adventure!" << endl;
	drawLine('*', 120);
	cout << "\n";
	cout << setw(20) << "" << "Goal: Reach the treasure without bumping into traps (T) or enemies (E).\n";
	cout << setw(40) << "" << "Use the keys to move: \n";
	cout << setw(40) << "" << "  - 'a' (left)\n";
	cout << setw(40) << "" << "  - 'd' (right)\n";
	cout << setw(40) << "" << "  - 's' (down)\n";
	cout << setw(40) << "" << "  - 'w' (up)\n";
	drawLine('*', 120);
}

void displayWinScreen() {
	system("cls");
	drawLine('*', 120);
	cout << setw(140) << "" << R"(
                     ____  ______   ________  ______  _____  _   _            ____   ______   __  __  ______ 
                    |  _ `| _   `  / /  __  `| ____ ||  _  || | | |          / ___| |  __  | |  |/  ||  ____|
                    | | | | | | ` V /| |  | || |__   | | | ||  `| |         | |  _  | |__| | | |  / || |__ 
                    | | | | | | |> < | |  | ||  __|  | | | || `   |         | | | | |  __  | | ||/| ||  __|  
                    | |_| | |_| / . `| |__| || |____ | |_| || | ` |         | |_| | | |  | | | |  | || |____ 
                    |____/|____/_/ `_`_____/ |______||_____||_| |_|         |_____| |_|  |_| |_|  |_||______| 
                                                 
    )";

	cout << setw(130) << "" << R"(

                                                     __        __  _   _   _ 
                                                     ` `      / / | | | | | |
                                                      ` ` /` / /  | | |  `| |
                                                       ` V  V /   | | | |`  |
                                                        `_/`_/    |_| |_| `_|
  



                                      
    )" << endl;
	cout << "\n";
	cout << setw(55) << "" << "Press [ENTER] to return to main menu." << endl;
	drawLine('*', 120);

	while (true) {
		if (_getch() == 13) break; // 엔터키 입력 대기
	}
}


void displayGameOverScreen() {
	system("cls");
	drawLine('*', 120);
	cout << setw(140) << "" << R"(
                     ____  ______   ________  ______  _____  _   _            ____   ______   __  __  ______ 
                    |  _ `| _   `  / /  __  `| ____ ||  _  || | | |          / ___| |  __  | |  |/  ||  ____|
                    | | | | | | ` V /| |  | || |__   | | | ||  `| |         | |  _  | |__| | | |  / || |__ 
                    | | | | | | |> < | |  | ||  __|  | | | || `   |         | | | | |  __  | | ||/| ||  __|  
                    | |_| | |_| / . `| |__| || |____ | |_| || | ` |         | |_| | | |  | | | |  | || |____ 
                    |____/|____/_/ `_`_____/ |______||_____||_| |_|         |_____| |_|  |_| |_|  |_||______| 
                                                 
    )";
	cout << setw(130) << "" << R"(
                                                     _        ____    _____  _____ 
                                                    | |      / __ `  / ____|| ____|
                                                    | |     | |  | || (___  | |__  
                                                    | |     | |  | | `___ ` |  __| 
                                                    | |____ | |__| | ____) || |____
                                                    |______| `____/ |______/|______|

  
                                      
    )" << endl;
	cout << "\n";
	cout << setw(55) << "" << "Press [ENTER] to return to main menu." << endl;
	drawLine('*', 120);

	while (true) {
		if (_getch() == 13) break; // 엔터키 입력 대기
	}
}

int main() {
	PlaySound(TEXT("OST.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

	vector<Sprite*> list;

	srand(static_cast<unsigned int>(time(NULL)));
	int width = rand() % 10 + 70;
	int height = rand() % 10 + 10;

	Board board(width, height);
	list.push_back(new Hero(1, 1, width, height, board));

	// Treasure 위치를 미로의 빈 공간에 배치
	int treasureX, treasureY;
	do {
		treasureX = rand() % (width - 2) + 1;
		treasureY = rand() % (height - 2) + 1;
	} while (board.getValue(treasureY, treasureX) != '.'); // 빈 공간 확인
	list.push_back(new Treasure(treasureX, treasureY));
	int Enum = rand() % 5 + 1;
	for (int i = 0; i < Enum; i++)
		list.push_back(new Enemy(rand() % width, rand() % height, width, height, board));

	displayStartScreen();
	waitForSpaceBar();

	// 메인 루프
	while (true) {
		clearScreen();

		// 보드 초기화
		board.clearBoard();

		// 각 요소 표시
		for (auto& e : list) {
			board.setValue(e->getY(), e->getX(), e->getShape());
		}

		board.printBoard();

		// 입력 대기 및 적 움직임 타이머
		auto startTime = std::chrono::steady_clock::now();
		bool heroMoved = false;

		// 1초 동안 사용자 입력을 받음
		while (std::chrono::steady_clock::now() - startTime < std::chrono::seconds(1)) {
			if (_kbhit()) { // 사용자가 키를 누르면
				char direction = _getch();

				// 히어로 이동
				if (direction == 'a' || direction == 's' || direction == 'w' || direction == 'd') {
					list[0]->move(direction);
					heroMoved = true;
					break;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		// 적 이동 (1초에 한 번)
		for (size_t i = 2; i < list.size(); ++i) {
			list[i]->move(rand() % 4 + '0'); // 랜덤 방향으로 이동
		}

		// 충돌 검사
		if (list[0]->checkCollision(list[1])) {
			// 현재 음악 종료
			PlaySound(NULL, 0, 0);

			// 승리 음악 재생
			PlaySound(TEXT("WIN.wav"), NULL, SND_FILENAME | SND_ASYNC);

			// 보물 획득 화면 표시
			displayWinScreen();
			break; // 종료
		}

		for (int i = 2; i < (int)list.size(); ++i) {
			if (list[0]->checkCollision(list[i])) {
				// 현재 음악 종료
				PlaySound(NULL, 0, 0);

				// 패배 음악 재생
				PlaySound(TEXT("LOSE.wav"), NULL, SND_FILENAME | SND_ASYNC);

				// 게임 오버 화면 표시
				displayGameOverScreen();

				// 종료
				for (auto& e : list) delete e;
				list.clear();
				return 0;
			}
		}
	}

	for (auto& e : list) {
		delete e;
	}
	list.clear();
	return 0;
}