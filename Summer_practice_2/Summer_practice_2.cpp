#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <chrono>

using namespace std;

const int w = 800;
const int h = 600;
const int capitalSpeed = 5;
const int woodenSpeed = 3;

struct Building {
    int x, y;
    int destX, destY;
    bool isMoving;

    Building(int startX, int startY, int endX, int endY)
        : x(startX), y(startY), destX(endX), destY(endY), isMoving(true) {}
};

vector<Building> capitalBuildings;
vector<Building> woodenBuildings;

void moveBuilding(Building& building, int speed) {
    int dx = building.destX - building.x;
    int dy = building.destY - building.y;
    float length = sqrt(dx * dx + dy * dy);

    if (length > speed) {
        building.x += int(speed * dx / length);
        building.y += int(speed * dy / length);
    }
    else {
        building.x = building.destX;
        building.y = building.destY;
        building.isMoving = false;
    }
}

void capitalBuildingThread() {
    while (true) {
        for (auto& building : capitalBuildings) {
            if (building.isMoving) {
                moveBuilding(building, capitalSpeed);
            }
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void woodenBuildingThread() {
    while (true) {
        for (auto& building : woodenBuildings) {
            if (building.isMoving) {
                moveBuilding(building, woodenSpeed);
            }
        }
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void printBuildings() {
    while (true) {
        system("cls");
        cout << "Capital Buildings:" << endl;
        for (const auto& building : capitalBuildings) {
            cout << "Position: (" << building.x << ", " << building.y << "), Destination: ("
                << building.destX << ", " << building.destY << ")" << endl;
        }
        cout << endl << "Wooden Buildings:" << endl;
        for (const auto& building : woodenBuildings) {
            cout << "Position: (" << building.x << ", " << building.y << "), Destination: ("
                << building.destX << ", " << building.destY << ")" << endl;
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < 5; ++i) {
        int capitalStartX = rand() % (w / 2);
        int capitalStartY = rand() % (h / 2);
        int capitalEndX = rand() % (w / 2);
        int capitalEndY = rand() % (h / 2);
        capitalBuildings.emplace_back(capitalStartX, capitalStartY, capitalEndX, capitalEndY);

        int woodenStartX = w / 2 + rand() % (w / 2);
        int woodenStartY = h / 2 + rand() % (h / 2);
        int woodenEndX = w / 2 + rand() % (w / 2);
        int woodenEndY = h / 2 + rand() % (h / 2);
        woodenBuildings.emplace_back(woodenStartX, woodenStartY, woodenEndX, woodenEndY);
    }

    thread t1(capitalBuildingThread);
    thread t2(woodenBuildingThread);
    thread t3(printBuildings);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
