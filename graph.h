#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <ostream>
#include <queue>
#include <random>
#include <string>
#include <sys/types.h>
#include <utility>
#include <vector>

const double INF = std::numeric_limits<double>::infinity();

std::string MakeParentString(const std::vector<int> &parent, int finish) {
    std::vector<int> invparent;
    int i = finish;
    while (i != -1) {
        invparent.push_back(i);
        i = parent[i];
    }
    std::string str;
    for (int k = invparent.size() - 1; k >= 0; k--) {
        str += std::to_string(invparent[k] + 1);
        if (k != 0)
            str += "->";
    }
    return str;
}

class Graph {
    protected:
        int n;
        std::vector<int> V;
        std::vector<std::vector<bool>> adj_matr;
        std::vector<std::vector<std::pair<int, double>>> adj_list;

    public:
        virtual int AddVertex() = 0;
        virtual void AddEdge(int i, int j) = 0;
        virtual void DeleteVertex(int num) = 0;
        virtual void DeleteEdge(int i, int j) = 0;
        virtual void BuildLists() = 0;
        virtual void Print() = 0;
};
class NorGraph : public Graph {
    protected:
        int n;
        std::vector<int> V;
        std::vector<std::vector<bool>> adj_matr;
        std::vector<std::vector<std::pair<int, double>>> adj_list;

    public:
        NorGraph(int number)
            : n(number),
              V(number),
              adj_matr(number, std::vector<bool>(number)) {
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = 0; j < n; j++)
                    adj_matr[i][j] = 0;
            }
        }
        NorGraph()
            : n(0),
              V(0),
              adj_matr(0) {}

        NorGraph(int number, double p)
            : n(number),
              V(number),
              adj_matr(number, std::vector<bool>(number)) {

            std::uniform_real_distribution<double> unif(0, 1);
            std::default_random_engine re;
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = i + 1; j < n; j++) {
                    if (unif(re) < p) {
                        AddEdge(i + 1, j + 1);
                    }
                }
            }
        }
        int AddVertex() override {
            n++;
            V.push_back(n);
            for (int i = 0; i < n - 1; i++)
                adj_matr[i].push_back(0);
            adj_matr.push_back(std::vector<bool>(n, 0));

            return n;
        }

        void AddEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = 1;
            adj_matr[j][i] = 1;
        }

        void DeleteVertex(int num) override {
            adj_matr.erase(adj_matr.begin() + num - 1);
            n--;
            for (int i = 0; i < n; i++) {
                adj_matr[i].erase(adj_matr[i].begin() + num - 1);
            }
        }
        void DeleteEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = 0;
            adj_matr[j][i] = 0;
        }

        void Print() override {
            std::cout << "===============\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    std::cout << adj_matr[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "===============\n";
        }
        void BuildLists() override {
            std::pair<int, double> a;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (adj_matr[i][j] == 1) {
                        a.first = j;
                        a.second = 1;
                        adj_list[i].push_back(a);
                    }
                }
            }
        }
};
class OrGraph : public Graph {
    private:
        int n;
        std::vector<int> V;
        std::vector<std::vector<bool>> adj_matr;
        std::vector<std::vector<std::pair<int, double>>> adj_list;

    public:
        OrGraph(int number)
            : n(number),
              V(number),
              adj_matr(number, std::vector<bool>(number)) {
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = 0; j < n; j++)
                    adj_matr[i][j] = 0;
            }
        }
        OrGraph()
            : n(0),
              V(0),
              adj_matr(0) {}
        OrGraph(int number, double p)
            : n(number),
              V(number),
              adj_matr(number, std::vector<bool>(number)) {

            std::uniform_real_distribution<double> unif(0, 1);
            std::default_random_engine re;
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = i + 1; j < n; j++) {
                    if (unif(re) < p) {
                        AddEdge(i + 1, j + 1);
                    }
                }
            }
        }

        int AddVertex() override {
            n++;
            V.push_back(n);
            for (int i = 0; i < n - 1; i++)
                adj_matr[i].push_back(0);
            adj_matr.push_back(std::vector<bool>(n, 0));

            return n;
        }

        void AddEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = 1;
        }

        void DeleteVertex(int num) override {
            adj_matr.erase(adj_matr.begin() + num - 1);
            n--;
            for (int i = 0; i < n; i++) {
                adj_matr[i].erase(adj_matr[i].begin() + num - 1);
            }
        }
        void DeleteEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = 0;
        }
        void Print() override {
            std::cout << "===============\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    std::cout << adj_matr[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "===============\n";
        }
        void BuildLists() override {
            std::pair<int, double> a;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (adj_matr[i][j] == 1) {
                        a.first = j;
                        a.second = 1;
                        adj_list[i].push_back(a);
                    }
                }
            }
        }
};

class WOrGraph : public OrGraph {
    private:
        int n;
        std::vector<int> V;
        std::vector<std::vector<double>> adj_matr;
        std::vector<std::vector<std::pair<int, double>>> adj_list;

    public:
        WOrGraph(int number)
            : n(number),
              V(number),
              adj_matr(number, std::vector<double>(number)) {
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = 0; j < n; j++)
                    adj_matr[i][j] = INF;
                adj_matr[i][i] = 0;
            }
        }
        WOrGraph()
            : n(0),
              V(0),
              adj_matr(0) {}

        WOrGraph(int number, double p, int begin, int fin)
            : n(number),
              V(number),
              adj_matr(number, std::vector<double>(number)) {

            std::uniform_real_distribution<double> unif(0, 1);
            std::uniform_real_distribution<double> random(begin, fin);
            std::default_random_engine re;
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = 0; j < n; j++) {
                    if (i == j) {
                        adj_matr[i][j] = 0;
                    } else {
                        if (unif(re) < p) {
                            AddEdge(i + 1, j + 1, random(re));
                        } else {
                            adj_matr[i][j] = INF;
                        }
                    }
                }
            }
        }

        int AddVertex() override {
            n++;
            V.push_back(n);
            for (int i = 0; i < n - 1; i++)
                adj_matr[i].push_back(INF);
            adj_matr.push_back(std::vector<double>(n, INF));
            adj_matr[n - 1][n - 1] = 0;
            return n;
        }

        void AddEdge(int i, int j, double w) {
            i--;
            j--;
            adj_matr[i][j] = w;
        }

        void DeleteVertex(int num) override {
            adj_matr.erase(adj_matr.begin() + num - 1);
            n--;
            for (int i = 0; i < n; i++) {
                adj_matr[i].erase(adj_matr[i].begin() + num - 1);
            }
        }
        void DeleteEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = INF; // if i != j
        }
        void Print() override {
            std::cout << "===============\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    std::cout << adj_matr[i][j] << "\t";
                }
                std::cout << std::endl;
            }
            std::cout << "===============\n";
        }
        void BuildLists() override {
            std::pair<int, double> a;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (adj_matr[i][j] != INF && j != i) {
                        a.first = j;
                        a.second = adj_matr[i][j];
                        adj_list[i].push_back(a);
                    }
                }
            }
        }

        std::pair<double, std::string> Dijkstra(int s, int f) {
            std::pair<double, std::string> pair;
            std::vector<double> dist(n, INF);
            std::vector<bool> visited(n, false);
            std::vector<int> parent(n, -1);
            std::priority_queue<std::pair<double, int>,
                                std::vector<std::pair<double, int>>,
                                std::greater<std::pair<double, int>>>
                pq;
            if (s >= 1 && s <= n && f >= 1 && f <= n) {
                int start = s - 1;
                int finish = f - 1;
                dist[start] = 0;
                pq.push({0, start});

                while (!pq.empty()) {
                    int u = pq.top().second;
                    pq.pop();

                    if (visited[u])
                        continue;
                    visited[u] = true;
                    if (u == finish) {
                        pair.first = dist[finish];
                        pair.second = MakeParentString(parent, finish);
                        return pair;
                    }
                    for (int i = 0; i < n; i++) {
                        if (adj_matr[u][i] != INF) {
                            if (dist[i] > dist[u] + adj_matr[u][i]) {
                                dist[i] = dist[u] + adj_matr[u][i];
                                parent[i] = u;
                                pq.push({dist[i], i});
                            }
                        }
                    }
                }
                pair.first = dist[finish];
                pair.second = MakeParentString(parent, finish);
                return pair;
            } else {
                std::cerr << "entered vertexes are not in graph\n";
                pair.first = INF;
                pair.second = "";
                return pair;
            }
        }
        std::vector<std::vector<double>> FullDijkstra() {
            std::vector<std::vector<double>> matr_routes;
            for (int i = 0; i < n; i++) {
                matr_routes.push_back(std::vector<double>(n, INF));

                for (int j = 0; j < n; j++) {
                    if (i == j) {
                        matr_routes[i][j] = 0;
                    } else {
                        matr_routes[i][j] = Dijkstra(i + 1, j + 1).first;
                    }
                }
            }
            return matr_routes;
        }
        void
        PrintFullDijkstra(const std::vector<std::vector<double>> &matr_routes) {
            std::cout << "===============\n" << "\t FullDijkstra:\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    std::cout << matr_routes[i][j] << "\t";
                }
                std::cout << std::endl;
            }
            std::cout << "===============\n";
        }
        std::vector<std::vector<double>> FloidUorshal() {
            std::vector<std::vector<double>> matr_routes;
            for (int f = 0; f < n; f++) {
                matr_routes.push_back(std::vector<double>(n, INF));
                for (int g = 0; g < n; g++) {
                    matr_routes[f][g] = adj_matr[f][g];
                }
            }
            for (int k = 0; k < n; k++) {
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (i == j) {
                            matr_routes[i][j] = 0;
                        } else {
                            matr_routes[i][j] =
                                std::min(matr_routes[i][j],
                                         matr_routes[i][k] + matr_routes[k][j]);
                        }
                    }
                }
            }

            return matr_routes;
        }
        void
        PrintFloidUorshal(const std::vector<std::vector<double>> &matr_routes) {
            std::cout << "===============\n" << "\t\t FloidUorshala: \n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    std::cout << matr_routes[i][j] << "\t";
                }
                std::cout << std::endl;
            }
            std::cout << "===============\n";
        }
};

class WNorGraph : public NorGraph {
    private:
        int n;
        std::vector<int> V;
        std::vector<std::vector<double>> adj_matr;
        std::vector<std::vector<std::pair<int, double>>> adj_list;

    public:
        WNorGraph(int number)
            : n(number),
              V(number),
              adj_matr(number, std::vector<double>(number)) {
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = 0; j < n; j++)
                    adj_matr[i][j] = INF;
                adj_matr[i][i] = 0;
            }
        }
        WNorGraph()
            : n(0),
              V(0),
              adj_matr(0) {}

        WNorGraph(int number, double p, int begin, int fin)
            : n(number),
              V(number),
              adj_matr(number, std::vector<double>(number)) {

            std::uniform_real_distribution<double> unif(0, 1);
            std::uniform_real_distribution<double> random(begin, fin);
            std::default_random_engine re;
            for (int i = 0; i < n; i++) {
                V[i] = i + 1;
                for (int j = i + 1; j < n; j++) {
                    if (unif(re) < p) {
                        AddEdge(i + 1, j + 1, random(re));
                    } else {
                        adj_matr[i][j] = INF;
                        adj_matr[j][i] = INF;
                    }
                }
            }
        }
        int AddVertex() override {
            n++;
            V.push_back(n);
            for (int i = 0; i < n - 1; i++)
                adj_matr[i].push_back(0);
            adj_matr.push_back(std::vector<double>(n, 0));

            return n;
        }

        void AddEdge(int i, int j, double w) {
            i--;
            j--;
            adj_matr[i][j] = w;
            adj_matr[j][i] = w;
        }

        void DeleteVertex(int num) override {
            adj_matr.erase(adj_matr.begin() + num - 1);
            n--;
            for (int i = 0; i < n; i++) {
                adj_matr[i].erase(adj_matr[i].begin() + num - 1);
            }
        }
        void DeleteEdge(int i, int j) override {
            i--;
            j--;
            adj_matr[i][j] = INF;
            adj_matr[j][i] = INF;
        }
        void Print() override {
            std::cout << "===============\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {

                    std::cout << adj_matr[i][j] << " ";
                }
                std::cout << std::endl;
            }
            std::cout << "===============\n";
        }
        void BuildLists() override {
            std::pair<int, double> a;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (adj_matr[i][j] != INF && j != i) {
                        a.first = j;
                        a.second = adj_matr[i][j];
                        adj_list[i].push_back(a);
                    }
                }
            }
        }
};
