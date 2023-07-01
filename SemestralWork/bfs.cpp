#include <iostream>
#include <vector>
#include <queue>
#include <set>
using namespace std;

typedef pair<int, int> Position;

Position findNextMove(const vector<vector<int>>& mapMatrix, const Position& enemyPos, const Position& playerPos, const vector<int>& allowedBlocks) {
    queue<Position> queue;
    vector<vector<Position>> parent(mapMatrix.size(), vector<Position>(mapMatrix[0].size(), {-1, -1}));

    queue.push(enemyPos);

    while (!queue.empty()) {
        Position currentPos = queue.front();
        queue.pop();

        if (currentPos == playerPos) {
            // Shortest path found
            break;
        }

        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        for (const auto& direction : directions) {
            Position nextPos = make_pair(currentPos.first + direction.first, currentPos.second + direction.second);

            if (nextPos.first >= 0 && nextPos.first < mapMatrix.size() &&
                nextPos.second >= 0 && nextPos.second < mapMatrix[0].size() &&
                find(allowedBlocks.begin(), allowedBlocks.end(), mapMatrix[nextPos.first][nextPos.second]) != allowedBlocks.end() &&
                parent[nextPos.first][nextPos.second] == make_pair(-1, -1)) {

                queue.push(nextPos);
                parent[nextPos.first][nextPos.second] = currentPos;
            }
        }
    }

    // Determine next move based on the parent positions
    Position currentPos = playerPos;
    while (parent[currentPos.first][currentPos.second] != enemyPos) {
        currentPos = parent[currentPos.first][currentPos.second];
    }

    return currentPos;
}

int main() {
    vector<vector<int>> mapMatrix = {
            {1, 1, 0, 1, 0},
            {1, 0, 0, 1, 1},
            {1, 1, 1, 1, 1},
            {1, 1, 0, 0, 0},
            {0, 0, 0, 1, 0}
    };

    Position enemyPos = make_pair(2, 3);
    Position playerPos = make_pair(5, 5);
    vector<int> allowedBlocks = {0, 1};  // Example allowed block types

    Position nextMove = findNextMove(mapMatrix, enemyPos, playerPos, allowedBlocks);
    cout << "Next move: (" << nextMove.first << ", " << nextMove.second << ")" << endl;

    return 0;
}