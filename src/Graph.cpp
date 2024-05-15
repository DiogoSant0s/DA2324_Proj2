#include "Graph.h"

#include <random>

Graph::Graph() = default;

void Graph::addNode(int id, double lon, double lat) {
    if (nodes.find(id) == nodes.end()) {
        nodes.insert({id, new Node{id, lon, lat}});
    }
}

void Graph::addEdge(int org, int destination, float dist, const string& distance) {
    auto itSrc = nodes.find(org);
    auto itTar = nodes.find(destination);
    if (itSrc == nodes.end() || itTar == nodes.end() || itSrc == itTar) {
        return;
    }
    itSrc->second->edgesOut.push_back(new Edge{org, destination, dist, distance});
    itTar->second->edgesOut.push_back(new Edge{destination, org, dist, distance});
}

unordered_map<int, Graph::Node*> Graph::getNodes() {
    return nodes;
}

vector<Graph::Edge*> Graph::getEdgesOut(int id) {
    return nodes.find(id)->second->edgesOut;
}

double Graph::convertToRad(double value) {
    return value * (M_PI / 180);
}

double Graph::computeTourDistance(const vector<int>& tour, bool graphType) {
    double totalDistance = 0.0;
    for (int i = 0; i < tour.size() - 1; ++i) {
        totalDistance += distanceBetweenNodes(tour[i], tour[i + 1], graphType);
    }
    totalDistance += distanceBetweenNodes(tour.back(), tour.front(), graphType);
    return totalDistance;
}

double Graph::distanceBetweenNodes(int origin, int destination, bool realDistances) {
    if (origin == destination) {
        return 0;
    }
    if (realDistances) {
        for (Edge* edge : nodes.find(origin)->second->edgesOut) {
            if (edge->dest == destination) {
                return edge->distance;
            }
        }
    }
    return 6371 * 2 * asin(sqrt(pow(sin(convertToRad(nodes[destination]->latitude - nodes[origin]->latitude) / 2), 2) +
        pow(sin(convertToRad(nodes[destination]->longitude - nodes[origin]->longitude)/ 2), 2) *
        cos(convertToRad(nodes[origin]->latitude)) *
        cos(convertToRad(nodes[destination]->latitude))));
}

void Graph::backtrackingApproach(double &shortestDistance, int *shortestCycle, bool distanceType) {
    int cycle[nodes.size()];
    cycle[0] = 0;
    nodes.find(0)->second->visited = true;
    backtrackingApproachRec(0, shortestDistance, 1, (int) nodes.size(), cycle, shortestCycle, distanceType);
}

void Graph::backtrackingApproachRec(double distance, double &shortestDistance, int currentIndex, int n, int cycle[], int shortestCycle[], bool distanceType) {
    if (currentIndex == n) {
        distance += distanceBetweenNodes(cycle[currentIndex - 1], cycle[0], distanceType);
        if (distance < shortestDistance) {
            shortestDistance = distance;
            for (unsigned i = 0; i < n; i++) {
                shortestCycle[i] = cycle[i];
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (!(nodes.find(i)->second->visited)) {
                if (distance + distanceBetweenNodes(cycle[currentIndex - 1], i, distanceType) < shortestDistance) {
                    cycle[currentIndex] = i;
                    nodes.find(i)->second->visited = true;
                    backtrackingApproachRec(distance + distanceBetweenNodes(cycle[currentIndex - 1], i, distanceType), shortestDistance, currentIndex + 1, n, cycle,shortestCycle, distanceType);
                    nodes.find(i)->second->visited = false;
                }
            }
        }
    }
}

vector<int> Graph::primMST(bool distanceType, double &totalDistance) {
    MutablePriorityQueue<Node> queue;
    vector<int> prim;
    vector<int> preOrder;
    for (auto& pair : nodes) {
        pair.second->visited = false;
        pair.second->distance = numeric_limits<double>::infinity();
        queue.insert(pair.second);
    }
    nodes.find(0)->second->distance = 0;
    nodes.find(0)->second->path = nullptr;
    nodes.find(0)->second->visited = true;
    queue.decreaseKey(nodes.find(0)->second);
    while (!queue.empty()) {
        Node* origin = queue.extractMin();
        prim.push_back(origin->Id);
        for (auto edge : origin->edgesOut) {
            if (!(nodes.find(edge->dest)->second->visited) && edge->distance < nodes.find(edge->dest)->second->distance) {
                nodes.find(edge->dest)->second->distance = edge->distance;
                nodes.find(edge->dest)->second->path = edge;
                queue.decreaseKey(nodes.find(edge->dest)->second);
            }
        }
        nodes.find(origin->Id)->second->visited = true;
    }
    for (auto& pair : nodes){
        pair.second->visited = false;
    }
    totalDistance = orderMST(0, prim, preOrder, distanceType);
    return preOrder;
}

double Graph::orderMST(int nodeId, vector<int>& primVisit, vector<int>& preOrder, bool distanceType) {
    nodes.find(nodeId)->second->visited = true;
    preOrder.push_back(nodeId);
    for (int i = 0; i < primVisit.size(); i++) {
        auto node= nodes.find(primVisit[i])->second;
        if (node->path != nullptr && node->path->origin == nodeId && !node->visited) {
            orderMST(primVisit[i], primVisit, preOrder, distanceType);
        }
    }
    double totalCost = 0.0;
    if (nodes.find(nodeId)->second->path == nullptr) {
        preOrder.emplace_back(0);
        for (int i = 0; i < preOrder.size() - 1; i++) {
            totalCost += distanceBetweenNodes(preOrder[i], preOrder[i + 1], distanceType);
        }
    }
    return totalCost;
}

vector<int> Graph::primMST2(bool distanceType, double& totalDistance) {
    auto* mst = new Graph();
    MutablePriorityQueue<Node> queue;
    vector<int> prim;
    vector<int> preOrder;
    for (auto pair : nodes) {
        pair.second->visited = false;
        pair.second->distance = numeric_limits<double>::infinity();
        queue.insert(pair.second);
    }
    nodes.find(0)->second->distance = 0;
    nodes.find(0)->second->path = nullptr;
    nodes.find(0)->second->visited = true;
    queue.decreaseKey(nodes.find(0)->second);
    while (!queue.empty()) {
        Node* origin = queue.extractMin();
        prim.push_back(origin->Id);
        for (auto edge : origin->edgesOut) {
            if (!nodes.find(edge->dest)->second->visited && edge->distance < nodes.find(edge->dest)->second->distance) {
                nodes.find(edge->dest)->second->distance = edge->dest;
                nodes.find(edge->dest)->second->path = edge;
                queue.decreaseKey(nodes.find(edge->dest)->second);
            }
        }
        nodes.find(origin->Id)->second->visited = true;
    }
    for (auto pair : nodes) {
        pair.second->visited = false;
    }
    for (auto pair : nodes) {
        auto path = pair.second->path;
        if (path!= nullptr) {
            if (mst->nodes.find(path->origin) == mst->nodes.end()) {
                Node* node = nodes.find(path->origin)->second;
                mst->nodes.emplace(node->Id, node);
            }
            if (mst->nodes.find(path->dest) == mst->nodes.end()) {
                Node* node = nodes.find(path->dest)->second;
                mst->nodes.emplace(node->Id, node);
            }
            mst->nodes.find(path->origin)->second->edgesOut.push_back(path);
        }
    }
    totalDistance = orderMST2(0, prim, preOrder, mst, distanceType);
    return preOrder;
}

void Graph::helper(int node, vector<int>& preOrder, Graph* mst) {
    mst->nodes.find(node)->second->visited = true;
    preOrder.push_back(node);
    for (auto segment : mst->nodes.find(node)->second->edgesOut) {
        if (!mst->nodes.find(segment->dest)->second->visited) {
            helper(segment->dest, preOrder, mst);
        }
    }
}

double Graph::orderMST2(int nodeId, vector<int>& primVisit, vector<int>& preOrder, Graph* mst, bool distanceType) {
    mst->nodes.find(nodeId)->second->visited = true;
    preOrder.push_back(nodeId);
    for (int i : primVisit) {
        if (!mst->nodes.find(i)->second->visited) {
            helper(i, preOrder, mst);
        }
    }
    double totalCost = 0.0;
    if (nodes.find(nodeId)->second->path == nullptr) {
        preOrder.emplace_back(0);
        for (int i = 0; i < preOrder.size() - 1; i++) {
            totalCost += distanceBetweenNodes(preOrder[i], preOrder[i + 1], distanceType);
        }
    }
    return totalCost;
}

vector<int> Graph::nearestNeighbor(double& totalDistance, bool distanceType) {
    vector<int> path;
    unordered_set<int> visitedNodes;
    int currentNode = nodes.find(0)->first;
    visitedNodes.insert(currentNode);
    path.push_back(currentNode);
    while (path.size() < nodes.size()) {
        double minDistance = numeric_limits<double>::infinity();
        int closestNode = -1;
        for (auto nodePair : nodes) {
            if (visitedNodes.find(nodePair.first) == visitedNodes.end()) {
                double distance = distanceBetweenNodes(currentNode, nodePair.first, distanceType);
                if (distance < minDistance) {
                    minDistance = distance;
                    closestNode = nodePair.first;
                }
            }
        }
        currentNode = closestNode;
        visitedNodes.insert(currentNode);
        path.push_back(currentNode);
    }
    path.push_back(nodes.find(0)->first);
    for (int i = 0; i < path.size() - 1; i++) {
        totalDistance += distanceBetweenNodes(path[i], path[i + 1], distanceType);
    }
    return path;
}

// Initialize population with random tours
void Graph::initializePopulation(vector<vector<int>>& population) {
    for (auto& tour : population) {
        vector<int> nodesIds;
        for (const auto& pair : nodes) {
            nodesIds.push_back(pair.first);
        }
        shuffle(nodesIds.begin(), nodesIds.end(), std::mt19937(std::random_device()()));
        tour = nodesIds;
    }
}

// Evaluate fitness of each tour in the population
void Graph::evaluatePopulation(const vector<vector<int>>& population, vector<pair<int, double>>& fitnessScores, bool graphType) {
    for (int i = 0; i < population.size(); ++i) {
        double distance = computeTourDistance(population[i], graphType);
        fitnessScores.emplace_back(i, distance);
    }
    sort(fitnessScores.begin(), fitnessScores.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });
}

// Perform tournament selection to select parents
vector<int> Graph::selection(const vector<vector<int>>& population, const vector<pair<int, double>>& fitnessScores) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, (int) population.size() / 2 - 1);
    int idx1 = dist(gen);
    int idx2 = dist(gen);
    return (fitnessScores[idx1].second < fitnessScores[idx2].second) ? population[fitnessScores[idx1].first] : population[fitnessScores[idx2].first];
}

// Perform partially matched crossover
vector<int> Graph::crossover(const vector<int>& parent1, const vector<int>& parent2) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, (int) parent1.size() - 1);
    int startPos = dist(gen);
    int endPos = dist(gen);
    vector<int> child(parent1.size(), -1);
    for (int i = startPos; i <= endPos; ++i) {
        child[i] = parent1[i];
    }
    for (int i : parent2) {
        if (find(child.begin(), child.end(), i) == child.end()) {
            for (int & j : child) {
                if (j == -1) {
                    j = i;
                    break;
                }
            }
        }
    }
    return child;
}

void Graph::mutation(vector<int>& tour) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, (int) tour.size() - 1);
    int idx1 = dist(gen);
    int idx2 = dist(gen);
    swap(tour[idx1], tour[idx2]);
}

vector<int> Graph::geneticAlgorithm(int populationSize, int numGenerations, bool graphType, double &totalDistance) {
    vector<vector<int>> population(populationSize);
    initializePopulation(population);
    for (int generation = 0; generation < numGenerations; ++generation) {
        vector<pair<int, double>> fitnessScores;
        evaluatePopulation(population, fitnessScores, graphType);
        vector<vector<int>> newPopulation;
        for (int i = 0; i < populationSize; ++i) {
            // Select parents and perform crossover
            vector<int> offspring = crossover(selection(population, fitnessScores), selection(population, fitnessScores));
            // Apply mutation to offspring
            mutation(offspring);
            newPopulation.push_back(offspring);
        }
        population = newPopulation;
    }
    vector<int> bestTour;
    for (const auto& tour : population) {
        double distance = computeTourDistance(tour, graphType);
        if (distance < totalDistance) {
            totalDistance = distance;
            bestTour = tour;
        }
    }
    return bestTour;
}