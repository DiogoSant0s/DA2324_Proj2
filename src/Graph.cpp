#include "Graph.h"

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
    return value * M_PI / 180;
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
    double aux = pow(sin(convertToRad(nodes[destination]->latitude - nodes[origin]->latitude) / 2), 2) + cos(convertToRad(nodes[origin]->latitude)) *
            cos(convertToRad(nodes[destination]->latitude)) * pow(sin(convertToRad(nodes[destination]->longitude - nodes[origin]->longitude) / 2), 2);
    return 6371 * 2.0 * atan2(sqrt(aux), sqrt(1.0 - aux));
}

void Graph::backtrackingApproach(double &shortestDistance, int *shortestCycle, bool distanceType) {
    for (auto& pair : nodes) {
        pair.second->visited = false;
    }
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

vector<int> Graph::nearestNeighbor(int startNode, double &totalDistance, bool distanceType) {
    vector<int> path;
    unordered_set<int> visitedNodes;
    int currentNode = startNode;
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
    path.push_back(startNode);
    for (int i = 0; i < path.size() - 1; i++) {
        totalDistance += distanceBetweenNodes(path[i], path[i + 1], distanceType);
    }
    return path;
}

void Graph::minimumDistanceRec(Node *node, double& distance, vector<int> &path, unsigned int count, bool& valid, bool distanceType) {
    if (!valid) return;
    double minDist = numeric_limits<double>::infinity();
    Edge* e = nullptr;
    for (auto edge : node->edgesOut) {
        if (count == nodes.size() - 1) {
            if (edge->dest == 0) {
                distance += distanceBetweenNodes(node->Id, edge->dest, distanceType);
                return;
            }
        }
        else {
            double edgeDistance = distanceBetweenNodes(node->Id, edge->dest, distanceType);
            if (edgeDistance < minDist && !nodes.find(edge->dest)->second->visited) {
                minDist = edgeDistance;
                e = edge;
            }
        }
    }
    if (!e) {
        valid = false;
        minimumDistanceRec(nullptr, distance, path, count + 1, valid, distanceType);
    }
    else {
        nodes.find(e->dest)->second->visited = true;
        path.push_back(e->dest);
        distance += minDist;
        minimumDistanceRec(nodes.find(e->dest)->second, distance, path, count + 1, valid, distanceType);
    }
}

double Graph::minimumDistance(vector<int>& path, bool distanceType) {
    double distance = 0;
    unsigned int count = 0;
    bool validApproximation = true;
    for (auto& v : nodes) {
        v.second->visited = false;
    }
    auto root = nodes.find(0);
    root->second->visited = true;
    path.push_back(root->first);
    minimumDistanceRec(root->second, distance, path, count, validApproximation, distanceType);
    return distance;
}
