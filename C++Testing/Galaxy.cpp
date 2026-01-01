#include <iostream>
#include <vector>

class GameItem {
public:
    int id;
    int x;
    int z;
    int y;
    int weight;

    // Constructor for easy creation
    GameItem(int _id, int _x, int _z, int _y, int _weight)
        : id(_id), x(_x), z(_z), y(_y), weight(_weight) {
    }
};
void GalaxyStart() 
{
    // 1. Create a container (vector) to hold the objects
    std::vector<GameItem> items;

    // Optional: Reserve memory for 100 items to improve performance
    items.reserve(100);

    // 2. Loop 100 times to "spawn" them
    for (int i = 0; i < 100; i++) {
        // Create an object with some dummy data
        // For example: id is 'i', and coordinates are just '0' for now
        items.emplace_back(i, 0, 0, 0, 10);
    }

    // 3. Verify they exist
    std::cout << "Spawned " << items.size() << " items." << std::endl;
    std::cout << "Item 5 ID: " << items[5].id << std::endl;

}