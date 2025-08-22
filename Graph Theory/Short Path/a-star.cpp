#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <array>
#include <climits>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
int moves[] = {-1, 0, 1, 0, -1};

// Heuristic function: Manhattan distance
int manhattanDistance(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

// Heuristic function: Chebyshev distance
int chebyshevDistance(int x1, int y1, int x2, int y2)
{
    return max(abs(x2 - x1), abs(y2 - y1));
}

// Heuristic function: Euclidean distance
double euclideanDistance(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int findShortestPath_Dijkstra(const vector<vector<int>> &grid, int startX, int startY, int targetX, int targetY)
{
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0)
    {
        return -1;
    }
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> distance(n, vector<int>(m, INT_MAX));
    distance[startX][startY] = 1;
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    auto comp = [](const array<int, 3> &a, const array<int, 3> &b)
    {
        return a[2] > b[2];
    };
    priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(comp)> pq(comp);

    pq.push({startX, startY, 1});
    while (!pq.empty())
    {
        array<int, 3> current = pq.top();
        pq.pop();
        int x = current[0];
        int y = current[1];

        if (visited[x][y])
        {
            continue;
        }
        visited[x][y] = true;

        if (x == targetX && y == targetY)
        {
            return distance[x][y];
        }

        for (int i = 0; i < 4; ++i)
        {
            int nextX = x + moves[i];
            int nextY = y + moves[i + 1];

            if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < m &&
                grid[nextX][nextY] == 1 && !visited[nextX][nextY] &&
                distance[x][y] + 1 < distance[nextX][nextY])
            {
                distance[nextX][nextY] = distance[x][y] + 1;
                pq.push({nextX, nextY, distance[nextX][nextY]});
            }
        }
    }
    return -1;
}

int findShortestPath_AStar(const vector<vector<int>> &grid, int startX, int startY, int targetX, int targetY)
{
    if (grid[startX][startY] == 0 || grid[targetX][targetY] == 0)
    {
        return -1;
    }
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> distance(n, vector<int>(m, INT_MAX));
    distance[startX][startY] = 1;
    vector<vector<bool>> visited(n, vector<bool>(m, false));

    auto comp = [](const array<int, 3> &a, const array<int, 3> &b)
    {
        return a[2] > b[2];
    };
    priority_queue<array<int, 3>, vector<array<int, 3>>, decltype(comp)> pq(comp);

    int h_cost = manhattanDistance(startX, startY, targetX, targetY);
    pq.push({startX, startY, 1 + h_cost});

    while (!pq.empty())
    {
        array<int, 3> current = pq.top();
        pq.pop();
        int x = current[0];
        int y = current[1];

        if (visited[x][y])
        {
            continue;
        }
        visited[x][y] = true;

        if (x == targetX && y == targetY)
        {
            return distance[x][y];
        }

        for (int i = 0; i < 4; ++i)
        {
            int nextX = x + moves[i];
            int nextY = y + moves[i + 1];

            if (nextX >= 0 && nextX < n && nextY >= 0 && nextY < m &&
                grid[nextX][nextY] == 1 && !visited[nextX][nextY] &&
                distance[x][y] + 1 < distance[nextX][nextY])
            {
                distance[nextX][nextY] = distance[x][y] + 1;
                int new_h_cost = manhattanDistance(nextX, nextY, targetX, targetY);
                pq.push({nextX, nextY, distance[nextX][nextY] + new_h_cost});
            }
        }
    }
    return -1;
}

vector<vector<int>> randomGrid(int size)
{
    vector<vector<int>> grid(size, vector<int>(size));
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            grid[i][j] = ((rand() / (double)RAND_MAX) < 0.3) ? 0 : 1;
        }
    }
    return grid;
}

int main()
{
    srand(time(0));
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cout << "--- Functional Test Started ---" << endl;
    int correctnessTestSize = 100;
    int correctnessTestRuns = 10000;
    for (int i = 0; i < correctnessTestRuns; i++)
    {
        int n = (rand() % correctnessTestSize) + 2;
        vector<vector<int>> grid = randomGrid(n);
        int startX = rand() % n;
        int startY = rand() % n;
        int targetX = rand() % n;
        int targetY = rand() % n;
        int ans1 = findShortestPath_Dijkstra(grid, startX, startY, targetX, targetY);
        int ans2 = findShortestPath_AStar(grid, startX, startY, targetX, targetY);
        if (ans1 != ans2)
        {
            cout << "Error: Mismatch found!" << endl;
        }
    }
    cout << "--- Functional Test Finished ---" << endl;

    cout << "\n--- Performance Test Started ---" << endl;
    int perfTestSize = 4000;
    vector<vector<int>> perfGrid = randomGrid(perfTestSize);
    int startX_perf = 0, startY_perf = 0;
    int targetX_perf = 3900, targetY_perf = 3900;

    auto start = chrono::high_resolution_clock::now();
    int ans1 = findShortestPath_Dijkstra(perfGrid, startX_perf, startY_perf, targetX_perf, targetY_perf);
    auto end = chrono::high_resolution_clock::now();
    long long duration1 = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Dijkstra result: " << ans1 << ", Time (ms): " << duration1 << endl;

    start = chrono::high_resolution_clock::now();
    int ans2 = findShortestPath_AStar(perfGrid, startX_perf, startY_perf, targetX_perf, targetY_perf);
    end = chrono::high_resolution_clock::now();
    long long duration2 = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "A* Search result: " << ans2 << ", Time (ms): " << duration2 << endl;
    cout << "--- Performance Test Finished ---" << endl;

    return 0;
}