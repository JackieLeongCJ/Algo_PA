// graph.cpp
#include "graph.h"
#include <functional>
#include <queue>
#include <stdexcept>
#include <utility>

Graph::Graph() = default;

Graph::Graph(int numVertices) {
    resize(numVertices);
}

void Graph::resize(int numVertices) {
    adj_.assign(numVertices, {});
}

void Graph::addEdge(int u, int v, int baseCost) {
    // TODO: add edge (u, v) between GCell u and v with baseCosts to the graph
}

std::vector<int> dijkstra(
    const Graph &g,
    int source,
    std::vector<int> *outPrev
) {
    const int n = g.numVertices();
    std::vector<int> dist(n, INF);
    std::vector<int> prev(n, -1);

    // TODO: implement Dijkstra's algorithm to compute shortest paths from source

    return dist;
}
