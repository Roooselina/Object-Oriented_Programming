#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <cstdlib>
#include <ctime>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 800;
const int WORLD_SIZE = 2000;
const int CELL_SIZE = 50;
const int GRID_SIZE = WORLD_SIZE / CELL_SIZE;
const int PLAYER_SIZE = 20;
const int MONSTER_SIZE = 20;

struct Entity {
    sf::Vector2f position;
    sf::Vector2f size;
    float speed;
};

struct Wall {
    sf::FloatRect rect;
};

struct Cell {
    int x, y;
    bool walkable;
    float gCost;
    float hCost;
    float fCost;
    Cell* parent;
};

class Game {
public:
    Game();
    void run();
private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void resetGame();
    void generateRandomMaze();
    bool checkCollision(const sf::Vector2f& nextPos, const Entity& entity);
    std::vector<sf::Vector2f> findPath(const sf::Vector2f& startPos, const sf::Vector2f& endPos);
    std::vector<Cell*> getNeighbors(Cell* cell);
    float heuristic(Cell* a, Cell* b);
    Cell* getCellAtPosition(const sf::Vector2f& pos);
    void applyWallsToGrid();
    bool doesWallOverlap(const Wall& newWall);
    bool isGoalPositionValid(const sf::Vector2f& goalPos);

    sf::RenderWindow window;
    sf::View view;
    Entity player;
    Entity monster;
    sf::Vector2f goal;
    std::vector<Wall> walls;
    Cell grid[GRID_SIZE][GRID_SIZE];
    std::vector<sf::Vector2f> monsterPath;
    float frameCount;
    int score;
    bool gameStarted;
    bool playerWon;
    bool monsterRecalculatePath;
    sf::Font font;
    sf::Text startMessage;
    sf::Text gameOverMessage;
    sf::Text winMessage;
    sf::Text scoreText;
    sf::SoundBuffer footstepBuffer;
    sf::Sound footstepSound;
    sf::SoundBuffer monsterFootstepBuffer;
    sf::Sound monsterFootstepSound;
    sf::Music mazeMusic;
    bool startMazeAudio;
};

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Maze Game"),
frameCount(0), score(0), gameStarted(false), playerWon(false), monsterRecalculatePath(false), startMazeAudio(false)
{
    window.setFramerateLimit(60);
    view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    view.setCenter(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    player.position = sf::Vector2f(400.f, 400.f);
    player.size = sf::Vector2f(PLAYER_SIZE, PLAYER_SIZE);
    player.speed = 5.f;

    monster.position = sf::Vector2f(std::rand() % WORLD_SIZE, std::rand() % WORLD_SIZE);
    monster.size = sf::Vector2f(MONSTER_SIZE, MONSTER_SIZE);
    monster.speed = 3.f;

    goal = sf::Vector2f(std::rand() % (1800 - 200 + 1) + 200, std::rand() % (1800 - 200 + 1) + 200);

    if (!font.loadFromFile("Arial.ttf")) {
        // 폰트 로드 실패 시 처리
    }

    startMessage.setFont(font);
    startMessage.setString("PRESS SPACE TO START");
    startMessage.setCharacterSize(40);
    startMessage.setFillColor(sf::Color::White);
    startMessage.setPosition(WINDOW_WIDTH / 2 - startMessage.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2);

    gameOverMessage.setFont(font);
    gameOverMessage.setString("GAME OVER");
    gameOverMessage.setCharacterSize(48);
    gameOverMessage.setFillColor(sf::Color::White);
    gameOverMessage.setPosition(WINDOW_WIDTH / 2 - gameOverMessage.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2);

    winMessage.setFont(font);
    winMessage.setString("YOU WIN!");
    winMessage.setCharacterSize(48);
    winMessage.setFillColor(sf::Color::White);
    winMessage.setPosition(WINDOW_WIDTH / 2 - winMessage.getGlobalBounds().width / 2, WINDOW_HEIGHT / 2);

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    if (!footstepBuffer.loadFromFile("FootStep.wav")) {
        // 사운드 로드 실패 시 처리
    }
    footstepSound.setBuffer(footstepBuffer);
    footstepSound.setLoop(true);

    if (!monsterFootstepBuffer.loadFromFile("MonsterFootStep.wav")) {
        // 사운드 로드 실패 시 처리
    }
    monsterFootstepSound.setBuffer(monsterFootstepBuffer);
    monsterFootstepSound.setLoop(true);

    if (!mazeMusic.openFromFile("MazeMusic.wav")) {
        // 음악 로드 실패 시 처리
    }
    mazeMusic.setLoop(true);

    generateRandomMaze();
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();
        if (gameStarted && !playerWon) {
            update(deltaTime);
        }
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (!gameStarted && event.key.code == sf::Keyboard::Space) {
                gameStarted = true;
                if (!startMazeAudio) {
                    mazeMusic.setVolume(50);
                    mazeMusic.play();
                    startMazeAudio = true;
                }
            }

            if (playerWon && event.key.code == sf::Keyboard::Space) {
                window.close();
            }
        }
    }
}

void Game::update(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);
    bool isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movement.y -= player.speed;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        movement.y += player.speed;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movement.x -= player.speed;
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movement.x += player.speed;
        isMoving = true;
    }

    sf::Vector2f nextPos = player.position + movement * deltaTime * 60.f;
    if (!checkCollision(nextPos, player)) {
        player.position = nextPos;
    }

    if (isMoving) {
        if (footstepSound.getStatus() != sf::Sound::Playing)
            footstepSound.play();
    }
    else {
        footstepSound.stop();
    }

    // 몬스터 업데이트
    frameCount += deltaTime * 60.f;
    if (frameCount >= 20.f) {
        monsterRecalculatePath = true;
        frameCount = 0.f;
    }

    if (monsterPath.empty() || monsterRecalculatePath) {
        monsterPath = findPath(monster.position, player.position);
        monsterRecalculatePath = false;
    }

    if (!monsterPath.empty()) {
        sf::Vector2f nextPos = monsterPath.front();
        sf::Vector2f dir = nextPos - monster.position;
        float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (distance > 0.f) {
            dir /= distance;
            monster.position += dir * monster.speed * deltaTime * 60.f;
        }
        if (std::abs(monster.position.x - nextPos.x) < 1.f && std::abs(monster.position.y - nextPos.y) < 1.f) {
            monsterPath.erase(monsterPath.begin());
        }
    }
    else {
        sf::Vector2f dir = player.position - monster.position;
        float distance = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (distance > 0.f) {
            dir /= distance;
            sf::Vector2f nextPos = monster.position + dir * monster.speed * deltaTime * 60.f;
            if (!checkCollision(nextPos, monster)) {
                monster.position = nextPos;
            }
        }
    }

    // Goal 충돌 검사
    if (std::abs(player.position.x - goal.x) < 20.f && std::abs(player.position.y - goal.y) < 20.f) {
        score++;
        if (score >= 3) {
            playerWon = true;
            mazeMusic.stop();
        }
        else {
            resetGame();
        }
    }

    // 플레이어와 몬스터 충돌 검사
    if (player.position.x < monster.position.x + MONSTER_SIZE &&
        player.position.x + PLAYER_SIZE > monster.position.x &&
        player.position.y < monster.position.y + MONSTER_SIZE &&
        player.position.y + PLAYER_SIZE > monster.position.y) {
        // 게임 오버 처리
        gameStarted = false;
        mazeMusic.stop();
        footstepSound.stop();
        monsterFootstepSound.stop();
    }

    // 뷰 업데이트
    view.setCenter(player.position);
    window.setView(view);
}

void Game::render() {
    window.clear(sf::Color::Black);

    if (!gameStarted) {
        window.draw(startMessage);
    }
    else {
        // 벽 그리기
        sf::RectangleShape wallShape;
        wallShape.setFillColor(sf::Color::Black);
        for (const auto& wall : walls) {
            wallShape.setPosition(wall.rect.left, wall.rect.top);
            wallShape.setSize(sf::Vector2f(wall.rect.width, wall.rect.height));
            window.draw(wallShape);
        }

        // Goal 그리기
        sf::CircleShape goalShape(10.f);
        goalShape.setFillColor(sf::Color::Yellow);
        goalShape.setPosition(goal.x - 10.f, goal.y - 10.f);
        window.draw(goalShape);

        // 플레이어 그리기
        sf::RectangleShape playerShape;
        playerShape.setSize(player.size);
        playerShape.setFillColor(sf::Color::Blue);
        playerShape.setPosition(player.position);
        window.draw(playerShape);

        // 몬스터 그리기
        sf::RectangleShape monsterShape;
        monsterShape.setSize(monster.size);
        monsterShape.setFillColor(sf::Color::Red);
        monsterShape.setPosition(monster.position);
        window.draw(monsterShape);

        // 점수 표시
        scoreText.setString("Score: " + std::to_string(score));
        window.setView(window.getDefaultView()); // HUD를 그리기 위해 뷰 리셋
        window.draw(scoreText);
        window.setView(view); // 다시 게임 뷰로 설정

        // 플레이어 승리 시 메시지 표시
        if (playerWon) {
            window.draw(winMessage);
        }
    }

    window.display();
}

void Game::resetGame() {
    player.position = sf::Vector2f(400.f, 400.f);
    monster.position = sf::Vector2f(std::rand() % WORLD_SIZE, std::rand() % WORLD_SIZE);
    generateRandomMaze();
}

void Game::generateRandomMaze() {
    walls.clear();

    // 경계 벽 추가
    walls.push_back({ sf::FloatRect(0.f, 0.f, WORLD_SIZE, 20.f) });
    walls.push_back({ sf::FloatRect(0.f, 0.f, 20.f, WORLD_SIZE) });
    walls.push_back({ sf::FloatRect(WORLD_SIZE - 20.f, 0.f, 20.f, WORLD_SIZE) });
    walls.push_back({ sf::FloatRect(0.f, WORLD_SIZE - 20.f, WORLD_SIZE, 20.f) });

    // 랜덤 벽 생성
    for (int i = 0; i < 50; ++i) {
        Wall wall;
        bool isVertical = std::rand() % 2 == 0;
        float wallLength = CELL_SIZE * (2 + std::rand() % 6);

        if (isVertical) {
            wall.rect.left = std::rand() % GRID_SIZE * CELL_SIZE;
            wall.rect.top = std::rand() % (GRID_SIZE - (int)(wallLength / CELL_SIZE)) * CELL_SIZE;
            wall.rect.width = 20.f;
            wall.rect.height = wallLength;
        }
        else {
            wall.rect.left = std::rand() % (GRID_SIZE - (int)(wallLength / CELL_SIZE)) * CELL_SIZE;
            wall.rect.top = std::rand() % GRID_SIZE * CELL_SIZE;
            wall.rect.width = wallLength;
            wall.rect.height = 20.f;
        }

        if (wall.rect.left < 20.f || wall.rect.top < 20.f ||
            wall.rect.left + wall.rect.width > WORLD_SIZE - 20.f ||
            wall.rect.top + wall.rect.height > WORLD_SIZE - 20.f) {
            continue;
        }

        if (!doesWallOverlap(wall)) {
            walls.push_back(wall);
        }
    }

    applyWallsToGrid();

    // Goal 위치 재설정
    do {
        goal.x = std::rand() % (1800 - 200 + 1) + 200;
        goal.y = std::rand() % (1800 - 200 + 1) + 200;
    } while (!isGoalPositionValid(goal));
}

bool Game::doesWallOverlap(const Wall& newWall) {
    for (const auto& wall : walls) {
        if (newWall.rect.intersects(wall.rect)) {
            return true;
        }
    }
    return false;
}

bool Game::isGoalPositionValid(const sf::Vector2f& goalPos) {
    for (const auto& wall : walls) {
        if (wall.rect.contains(goalPos)) {
            return false;
        }
    }
    return true;
}

bool Game::checkCollision(const sf::Vector2f& nextPos, const Entity& entity) {
    sf::FloatRect entityRect(nextPos.x, nextPos.y, entity.size.x, entity.size.y);
    for (const auto& wall : walls) {
        if (entityRect.intersects(wall.rect)) {
            return true;
        }
    }
    return false;
}

std::vector<sf::Vector2f> Game::findPath(const sf::Vector2f& startPos, const sf::Vector2f& endPos) {
    std::vector<sf::Vector2f> path;
    // A* 알고리즘 구현
    Cell* startCell = getCellAtPosition(startPos);
    Cell* endCell = getCellAtPosition(endPos);

    if (!startCell || !endCell || !startCell->walkable || !endCell->walkable) {
        return path;
    }

    std::priority_queue<std::pair<float, Cell*>, std::vector<std::pair<float, Cell*>>, std::greater<>> openList;
    bool closedList[GRID_SIZE][GRID_SIZE] = { false };

    startCell->gCost = 0.f;
    startCell->hCost = heuristic(startCell, endCell);
    startCell->fCost = startCell->gCost + startCell->hCost;
    startCell->parent = nullptr;

    openList.emplace(startCell->fCost, startCell);

    while (!openList.empty()) {
        Cell* current = openList.top().second;
        openList.pop();

        if (current == endCell) {
            // 경로 생성
            Cell* curr = current;
            while (curr != nullptr) {
                path.push_back(sf::Vector2f(curr->x * CELL_SIZE + CELL_SIZE / 2.f, curr->y * CELL_SIZE + CELL_SIZE / 2.f));
                curr = curr->parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedList[current->y][current->x] = true;

        for (Cell* neighbor : getNeighbors(current)) {
            if (!neighbor->walkable || closedList[neighbor->y][neighbor->x])
                continue;

            float tentativeGCost = current->gCost + 1.f;

            if (tentativeGCost < neighbor->gCost) {
                neighbor->gCost = tentativeGCost;
                neighbor->hCost = heuristic(neighbor, endCell);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = current;
                openList.emplace(neighbor->fCost, neighbor);
            }
        }
    }

    return path;
}

std::vector<Cell*> Game::getNeighbors(Cell* cell) {
    std::vector<Cell*> neighbors;
    int dx[] = { -1, 1, 0, 0 };
    int dy[] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; ++i) {
        int nx = cell->x + dx[i];
        int ny = cell->y + dy[i];

        if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE) {
            neighbors.push_back(&grid[ny][nx]);
        }
    }

    return neighbors;
}

float Game::heuristic(Cell* a, Cell* b) {
    return std::abs(a->x - b->x) + std::abs(a->y - b->y);
}

Cell* Game::getCellAtPosition(const sf::Vector2f& pos) {
    int x = pos.x / CELL_SIZE;
    int y = pos.y / CELL_SIZE;
    if (x >= 0 && x < GRID_SIZE && y >= 0 && y < GRID_SIZE) {
        return &grid[y][x];
    }
    return nullptr;
}

void Game::applyWallsToGrid() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            grid[i][j].x = j;
            grid[i][j].y = i;
            grid[i][j].walkable = true;
            grid[i][j].gCost = FLT_MAX;
            grid[i][j].hCost = 0.f;
            grid[i][j].fCost = 0.f;
            grid[i][j].parent = nullptr;
        }
    }

    for (const auto& wall : walls) {
        int startX = wall.rect.left / CELL_SIZE;
        int endX = (wall.rect.left + wall.rect.width) / CELL_SIZE;
        int startY = wall.rect.top / CELL_SIZE;
        int endY = (wall.rect.top + wall.rect.height) / CELL_SIZE;

        for (int i = startY; i < endY; ++i) {
            for (int j = startX; j < endX; ++j) {
                if (i >= 0 && i < GRID_SIZE && j >= 0 && j < GRID_SIZE) {
                    grid[i][j].walkable = false;
                }
            }
        }
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    Game game;
    game.run();
    return 0;
}