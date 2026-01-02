// This was a bit more complicated then i thought it wuld be so this is mainly ai but still a pretty cool program :)

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>

// --- CROSS PLATFORM INPUT (BLOCKING) ---
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
void clearScreen() { system("cls"); }
char getCharBlocking() { return _getch(); }
#else
#include <termios.h>
#include <unistd.h>
void clearScreen() { system("clear"); }
char getCharBlocking() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

// --- CONSTANTS ---
const double G_CONST = 0.5;  
const double TIME_STEP = 0.2; 
const int GRID_W = 50;
const int GRID_H = 30;

// --- CLASS ---
class GameItem {
public:
    int id;
    double x, y, z;
    double vx, vy, vz;
    double mass;
    char symbol;

    GameItem(int _id, double _x, double _y, double _z, double _mass)
        : id(_id), x(_x), y(_y), z(_z), mass(_mass), vx(0), vy(0), vz(0) {
        if (mass > 80) symbol = '@';
        else if (mass > 40) symbol = 'O';
        else symbol = '.';
    }
};

// --- PHYSICS ENGINE ---
void UpdatePhysics(std::vector<GameItem>& items) {
    struct Vec3 { double x, y, z; };
    std::vector<Vec3> totalForces(items.size(), { 0, 0, 0 });

    for (size_t i = 0; i < items.size(); i++) {
        for (size_t j = 0; j < items.size(); j++) {
            if (i == j) continue;

            double dx = items[j].x - items[i].x;
            double dy = items[j].y - items[i].y;
            double dz = items[j].z - items[i].z;

            double distSq = (dx * dx) + (dy * dy) + (dz * dz);
            double dist = std::sqrt(distSq);

            if (dist < 5.0) dist = 5.0;
            distSq = dist * dist;

            double force = G_CONST * (items[i].mass * items[j].mass) / distSq;

            totalForces[i].x += force * (dx / dist);
            totalForces[i].y += force * (dy / dist);
            totalForces[i].z += force * (dz / dist);
        }
    }

    // 2. Apply Movement
    for (size_t i = 0; i < items.size(); i++) {
        double ax = totalForces[i].x / items[i].mass;
        double ay = totalForces[i].y / items[i].mass;
        double az = totalForces[i].z / items[i].mass;

        items[i].vx += ax * TIME_STEP;
        items[i].vy += ay * TIME_STEP;
        items[i].vz += az * TIME_STEP;

        // --- FIX 2: DAMPING (Friction) ---
        // We multiply velocity by 0.98 every tick. 
        // This removes energy from the system, forcing them to settle 
        // into a clump rather than orbiting wildly forever.
        items[i].vx *= 0.98;
        items[i].vy *= 0.98;
        items[i].vz *= 0.98;

        items[i].x += items[i].vx * TIME_STEP;
        items[i].y += items[i].vy * TIME_STEP;
        items[i].z += items[i].vz * TIME_STEP;
    }
}

// --- RENDER ENGINE ---
void DrawUniverse(const std::vector<GameItem>& galaxy, double viewX, double viewY, double scale, long totalTicks, std::string statusMsg) {
    clearScreen();

    char displayGrid[GRID_H][GRID_W];
    int densityGrid[GRID_H][GRID_W];

    for (int y = 0; y < GRID_H; y++) {
        for (int x = 0; x < GRID_W; x++) {
            densityGrid[y][x] = 0;
            if (x == GRID_W / 2 && y == GRID_H / 2) displayGrid[y][x] = '+';
            else displayGrid[y][x] = ' ';
        }
    }

    for (const auto& obj : galaxy) {
        int screenX = (int)((obj.x - viewX) / scale) + (GRID_W / 2);
        int screenY = (int)((obj.y - viewY) / scale) + (GRID_H / 2);

        if (screenX >= 0 && screenX < GRID_W && screenY >= 0 && screenY < GRID_H) {
            densityGrid[screenY][screenX]++;
            displayGrid[screenY][screenX] = obj.symbol;
        }
    }

    for (int y = 0; y < GRID_H; y++) {
        for (int x = 0; x < GRID_W; x++) {
            int count = densityGrid[y][x];
            if (count > 1) {
                if (count <= 9) displayGrid[y][x] = '0' + count;
                else if (count <= 35) displayGrid[y][x] = 'a' + (count - 10);
                else displayGrid[y][x] = '*';
            }
        }
    }

    std::cout << "--- GRAVITY CLUMP SIMULATOR --- [Paused]" << std::endl;
    std::cout << "Objects: " << galaxy.size() << " | Ticks: " << totalTicks << std::endl;
    std::cout << "View: " << (int)viewX << "," << (int)viewY << " | Zoom: " << scale << " | Msg: " << statusMsg << std::endl;

    for (int i = 0; i < GRID_W + 2; i++) std::cout << "#";
    std::cout << std::endl;

    for (int y = 0; y < GRID_H; y++) {
        std::cout << "#";
        for (int x = 0; x < GRID_W; x++) {
            std::cout << displayGrid[y][x];
        }
        std::cout << "#" << std::endl;
    }

    for (int i = 0; i < GRID_W + 2; i++) std::cout << "#";
    std::cout << std::endl;
    std::cout << "[WASD] Move | [1/2] Zoom | [3-7] Run Simulation" << std::endl;
}

// --- MAIN ---
int GalaxyStart() {
    srand((unsigned)time(0));

    std::vector<GameItem> galaxy;
  
    for (int i = 0; i < 1000; i++) {
        double rx = (rand() % 600) - 300; 
        double ry = (rand() % 600) - 300;
        double rz = (rand() % 10) - 5;
        double mass = (rand() % 90) + 10;
        galaxy.emplace_back(i, rx, ry, rz, mass);
    }

    double viewX = 0, viewY = 0;
    double scale = 1.5;
    long totalTicks = 0;
    std::string msg = "Ready";

    DrawUniverse(galaxy, viewX, viewY, scale, totalTicks, msg);

    while (true) {
        char key = getCharBlocking();

        int ticksToRun = 0;
        msg = "Ready";

        if (key == 'w') viewY -= 5 * scale;
        else if (key == 's') viewY += 5 * scale;
        else if (key == 'a') viewX -= 5 * scale;
        else if (key == 'd') viewX += 5 * scale;
        else if (key == '1') { scale -= 0.5; if (scale < 0.5) scale = 0.5; }
        else if (key == '2') { scale += 0.5; }
        else if (key == '3') ticksToRun = 10;
        else if (key == '4') ticksToRun = 50;
        else if (key == '5') ticksToRun = 100;
        else if (key == '6') ticksToRun = 1000;
        else if (key == '7') ticksToRun = 10000;

        if (ticksToRun > 0) {
            for (int t = 0; t < ticksToRun; t++) {
                UpdatePhysics(galaxy);
            }
            totalTicks += ticksToRun;
            msg = "Done " + std::to_string(ticksToRun) + " ticks.";
        }

        DrawUniverse(galaxy, viewX, viewY, scale, totalTicks, msg);
    }

    return 0;
}