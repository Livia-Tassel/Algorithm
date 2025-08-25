#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
#include <set>
#include <numeric> 

namespace generator
{
    static std::mt19937 gen(std::time(nullptr));
    /**
     * @brief random int vector
     * @param size
     * @param minVal
     * @param maxVal
     * @return vector<int>
     */
    std::vector<int> generateVector(int size, int minVal, int maxVal)
    {
        std::vector<int> vec(size);
        std::uniform_int_distribution<int> dist(minVal, maxVal);
        for (int i = 0; i < size; ++i)
        {
            vec[i] = dist(gen);
        }
        return vec;
    }

    /**
     * @brief random long long vector
     */
    std::vector<long long> generateVector(int size, long long minVal, long long maxVal)
    {
        std::vector<long long> vec(size);
        std::uniform_int_distribution<long long> dist(minVal, maxVal);
        for (int i = 0; i < size; ++i)
        {
            vec[i] = dist(gen);
        }
        return vec;
    }

    /**
     * @brief random double vector
     */
    std::vector<double> generateVector(int size, double minVal, double maxVal)
    {
        std::vector<double> vec(size);
        std::uniform_real_distribution<double> dist(minVal, maxVal);
        for (int i = 0; i < size; ++i)
        {
            vec[i] = dist(gen);
        }
        return vec;
    }

    /**
     * @brief random int matrix
     */
    std::vector<std::vector<int>> generateMatrix(int rows, int cols, int minVal, int maxVal)
    {
        std::vector<std::vector<int>> matrix(rows);
        for (int i = 0; i < rows; ++i)
        {
            matrix[i] = generateVector(cols, minVal, maxVal);
        }
        return matrix;
    }

    /**
     * @brief random {startTime, endTime}
     * @param n
     * @param timeMax [0, timeMax-1]
     * @return vector<vector<int>>, {startTime, endTime}
     */
    std::vector<std::vector<int>> generateIntervals(int n, int timeMax)
    {
        std::vector<std::vector<int>> ans(n, std::vector<int>(2));
        std::uniform_int_distribution<> dist(0, timeMax - 1);
        for (int i = 0; i < n; ++i)
        {
            int a = dist(gen);
            int b = dist(gen);
            if (a == b)
            {
                ans[i][0] = a;
                ans[i][1] = a + 1;
            }
            else
            {
                ans[i][0] = std::min(a, b);
                ans[i][1] = std::max(a, b);
            }
        }
        return ans;
    }

    /**
     * @brief random string
     * @param maxLen [1, maxLen]
     * @param charKinds (a to z)
     * @return string
     */
    std::string generateString(int maxLen, int charKinds)
    {
        std::uniform_int_distribution<> len_dist(1, maxLen);
        int len = len_dist(gen);
        std::string s(len, ' ');
        std::uniform_int_distribution<> char_dist(0, charKinds - 1);
        for (int i = 0; i < len; ++i)
        {
            s[i] = (char)('a' + char_dist(gen));
        }
        return s;
    }

    /**
     * @brief random string vector
     * @param n
     * @param maxStrLen
     * @param charKinds
     * @return vector<string>
     */
    std::vector<std::string> generateStringVector(int n, int maxStrLen, int charKinds)
    {
        std::vector<std::string> ans(n);
        for (int i = 0; i < n; ++i)
        {
            ans[i] = generateString(maxStrLen, charKinds);
        }
        return ans;
    }

    /**
     * @brief random permutation from [0, n-1]
     * @param n
     * @return vector<int>
     */
    std::vector<int> generatePermutation(int n)
    {
        std::vector<int> p(n);
        std::iota(p.begin(), p.end(), 0);
        std::shuffle(p.begin(), p.end(), gen);
        return p;
    }

    /**
     * @brief random tree edges
     * @param n
     * @return vector<vector<int>>, {u, v}
     */
    std::vector<std::vector<int>> generateTreeEdges(int n)
    {
        if (n <= 1)
            return {};
        std::vector<std::vector<int>> edges;
        for (int i = 1; i < n; ++i)
        {
            std::uniform_int_distribution<> dist(0, i - 1);
            int parent = dist(gen);
            edges.push_back({parent, i});
        }
        std::shuffle(edges.begin(), edges.end(), gen);
        return edges;
    }

    /**
     * @brief random simple graph edges
     * @param n
     * @param m
     * @return vector<vector<int>>, {u, v}
     */
    std::vector<std::vector<int>> generateSimpleGraphEdges(int n, int m)
    {
        if (n <= 1)
            return {};
        long long max_edges = (long long)n * (n - 1) / 2;
        if (m > max_edges)
            m = max_edges;

        std::set<std::pair<int, int>> edge_set;
        std::uniform_int_distribution<> dist(0, n - 1);

        while (edge_set.size() < m)
        {
            int u = dist(gen);
            int v = dist(gen);
            if (u == v)
                continue;
            if (u > v)
                std::swap(u, v);
            edge_set.insert({u, v});
        }

        std::vector<std::vector<int>> edges;
        for (const auto &p : edge_set)
        {
            edges.push_back({p.first, p.second});
        }
        std::shuffle(edges.begin(), edges.end(), gen);
        return edges;
    }

} // namespace generator

signed main()
{
    using namespace generator;

    auto vec_int = generateVector(8, 1, 100);
    auto vec_ll = generateVector(5, 1LL, 2000000000LL);
    auto vec_double = generateVector(6, 0.0, 1.0);
    auto matrix = generateMatrix(3, 4, -10, 10);
    auto intervals = generateIntervals(5, 30);
    auto str_vec = generateStringVector(4, 10, 5);
    auto p = generatePermutation(9);
    auto tree = generateTreeEdges(7);
    auto graph = generateSimpleGraphEdges(6, 8);

    return 0;
}