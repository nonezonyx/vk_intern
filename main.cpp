#include <fstream>
#include <iostream>
#include <istream>
#include <queue>
#include <vector>

class graph {
public:
    friend std::istream &operator>>(std::istream &is, graph &g) {
        g.data.clear();
        long long n = 0, m = 0;
        is >> n >> m;
        g.data.resize(n);
        for (long long i = 0; i < m; ++i) {
            long long u = 0, v = 0;
            is >> u >> v;
            g.data[u].push_back(v);
            g.data[v].push_back(u);
        }
        return is;
    }

    std::vector<long long> distances_from(long long v) {
        std::queue<long long> q;
        q.push(v);
        std::vector<long long> distances(data.size(), -1);
        distances[v] = 0;
        while (!q.empty()) {
            v = q.front();
            q.pop();
            for (auto neighbor : data[v]) {
                if (distances[neighbor] == -1) {
                    distances[neighbor] = distances[v] + 1;
                    q.push(neighbor);
                }
            }
        }
        return distances;
    }

private:
    std::vector<std::vector<long long>> data;
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage:\n"
                     "\t"
                  << argv[0] << " graph.txt --- file with graph\n";
        return 0;
    }
    std::ifstream f(argv[1]);
    graph g;
    long long query;
    f >> g >> query;
    auto distances = g.distances_from(query);
    for (long long distance : distances) {
        std::cout << distance << '\n';
    }
    std::cout << std::endl;
}
