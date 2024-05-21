#ifndef DA2_GRAPH_H
#define DA2_GRAPH_H

#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <unordered_map>
#include <unordered_set>
#include "PQ.h"

using namespace std;

/**
 * @details The Graph class configures the attributes of a graph and the more complicated functions developed
 */
class Graph {
private:
    /**
     * Represents the edges of the graph
     */
    struct Edge {
        /**
         * Origin Node's Id
         */
        int origin;
        /**
         * Destination Node's Id
         */
        int dest;
        /**
         * Distance between the two nodes in the edge
         */
        float distance;
        /**
         * Distance between the two nodes in the edge as a string (used only by the printing function)
         */
        string distanceStr;
    };
    /**
     * Represents the content of each node
     */
    struct Node {
        /**
         * Node's Id
         */
        int Id;
        /**
         * Node's latitude
         */
        double latitude;
        /**
         * Node's longitude
         */
        double longitude;
        /**
         * Node's name (only used for the Tourism Toy Graph really)
         */
        string name;
        /**
         * List of outgoing edges, to adjacent nodes
         */
        vector<Edge*> edgesOut = {};
        /**
         * Verifies if the node has been visited on a previous search
         * @details This variable set to True means that the node has been visited and False otherwise
         */
        bool visited = false;
        /**
         * Distance from the origin node to this node
         */
        double distance = 0;
        /**
         * Index of the node in the priority queue
         */
        int queueIndex = 0;
        /**
         * Edge used to reach this node
         */
        Edge* path = nullptr;
        /**
         * Operator overload used to compare two nodes
         * @param node
         * @return
         */
        bool operator<(Node & node) const {
            return this->distance < node.distance;
        }
    };
    /**
     * A hash table
     * @details When searching the Time Complexity is O(1)
     */
    unordered_map<int, Node*> nodes;
    /**
     * Auxiliary function used to convert degrees to radians
     * @param value Value to be converted to radians
     * @details Time Complexity - O(1)
     * @return Radian equivalent to the provided degree
     */
    static double convertToRad(double value);
    /**
     * Auxiliary function used to determine the distance between to nodes using the Haversine formula
     * @param origin Id of the origin node
     * @param destination Id of the destination node
     * @param realDistances Boolean used to know if we want the real distances or the Haversine distances
     * @details Time Complexity - O(1)
     * @return Distance between the two nodes
     */
    double distanceBetweenNodes(int origin, int destination, bool realDistances);
public:
    /**
     * Graph class constructor
     * @details Creates a default Graph
     */
    Graph();
    /**
     * Add a node to the Graph
     * @param id The node's id
     * @param lon The node's longitude
     * @param lat The node's latitude
     * @details Time Complexity - O(1)
     */
    void addNode(int id, double lon, double lat);
    /**
     * Add an edge from a source node to a target node
     * @param org The source node
     * @param destination The target node
     * @param dist Distance between the source and target nodes
     * @param distance Distance between the source and target nodes as a string
     * @details Time Complexity - O(1)
     */
    void addEdge(int org, int destination, float dist, const string& distance);
    /**
     * Getter for the object nodes
     * @details Time Complexity: O(1)
     * @return The object nodes
     */
    unordered_map<int, Node*> getNodes();
    /**
     * Getter for the outgoing edges of a certain node
     * @param id Id of the node that has the edges you are looking for
     * @details Time Complexity: O(1)
     * @return The object edgesOut of said node
     */
    vector<Edge*> getEdgesOut(int id);
    /**
     * Function that calls the recursive function to find the shortest path between two nodes using a backtracking algorithm
     * @param shortestDistance The shortest distance travelled
     * @param shortestCycle The shortest cycle
     * @param distanceType Boolean used to know if we want the real distances or the Haversine distances
     * @details Time Complexity - O(1)
     */
    void backtrackingApproach(double &shortestDistance, int *shortestCycle, bool distanceType);
    /**
     * Finds the shortest path between two nodes using a backtracking algorithm recursively
     * @param distance The current distance travelled
     * @param shortestDistance The shortest distance travelled
     * @param currentIndex The current node's index
     * @param n The number of nodes
     * @param cycle The current cycle
     * @param shortestCycle The shortest cycle
     * @param distanceType Boolean used to know if we want the real distances or the Haversine distances
     * @details Time Complexity - O(V^2)
     * @details V is the number of nodes
     */
    void backtrackingApproachRec(double distance, double &shortestDistance, int currentIndex, int n, int cycle[], int shortestCycle[], bool distanceType);
    /**
     * Finds the minimum spanning tree of a graph using Prim's algorithm
     * @param distanceType Boolean used to know if we want the real distances or the Haversine distances
     * @param totalDistance The total distance travelled in the MST
     * @details Time Complexity - O(V * E)
     * @details V is the number of nodes and E is the number of edges
     * @return The visitedVertices vector that contains the MST
     */
    vector<int> primMST(bool distanceType, double &totalDistance);
    /**
     * Auxiliar function to Prim's algorithm
     * @param nodeId The node's id
     * @param primVisit The vector with all nodes and sorted by prim's algorithm
     * @param preOrder The vector with all nodes after ordering
     * @param distanceType Boolean used to know if we want the real distances or the Haversine distances
     * @details Time Complexity - O(V)
     * @details V is the number of nodes
     * @return The total distance travelled in the MST
     */
    double orderMST(int nodeId, vector<int> &primVisit, vector<int>& preOrder, bool distanceType);
    /**
     * Finds the minimum spanning tree of a graph using Prim's algorithm but with a worse 2-approximation algorithm while being faster for larger graphs
     * @param distanceType Boolean used to know if we want the real distances or the Haversine distances
     * @param totalDistance The total distance travelled in the MST
     * @details Time Complexity - O(V * E)
     * @details V is the number of nodes and E is the number of edges
     * @return The visitedVertices vector that contains the MST
     */
    vector<int> primMST2(bool distanceType, double &totalDistance);
    /**
     * Auxiliar function to Prim's algorithm but with a worse 2-approximation algorithm while being faster for larger graphs
     * @param nodeId The node's id
     * @param primVisit The vector with all nodes and sorted by prim's algorithm
     * @param preOrder The vector with all nodes after ordering
     * @param mst The graph representing the MST after Prim's algorithm
     * @param distanceType Boolean used to know if we want the real distances or the Haversine distances
     * @details Time Complexity - O(V)
     * @details V is the number of nodes
     * @return The total distance travelled in the MST
     */
    double orderMST2(int nodeId, vector<int> &primVisit, vector<int> &preOrder, Graph *mst, bool distanceType);
    /**
     * Auxiliar function to perform the order
     * @param node The current node's id
     * @param preOrder The vector with all nodes after ordering
     * @param mst The graph representing the MST after Prim's algorithm
     * @details Time Complexity - O(E)
     * @details E is the number of edges
     */
    void helper(int node, vector<int> &preOrder, Graph *mst);
    /**
     * Nearest Neighbor algorithm to find the shortest path between all nodes
     * @param startNode The node where the algorithm starts
     * @param totalDistance The total distance travelled
     * @param distanceType Boolean used to know if we want the real distances or the Haversine distances
     * @details Time Complexity - O(V^2)
     * @details V is the number of nodes
     * @return The shortest path between all nodes
     */
    vector<int> nearestNeighbor(int startNode, double &totalDistance, bool distanceType);
    /**
     * Function that calls the recursive function to find the shortest path between all nodes using a minimum distance algorithm
     * @param path The shortest path between all nodes
     * @param distanceType Boolean used to know if we want the real distances or the Haversine distances
     * @details Time Complexity - O(V^2)
     * @details V is the number of nodes
     * @return The total distance travelled
     */
    double minimumDistance(vector<int> &path, bool distanceType);
    /**
     * Minimum distance recursive algorithm to find the shortest path between all nodes recursively
     * @param node The current node
     * @param distance The current distance travelled
     * @param path The shortest path between all nodes
     * @param count The number of nodes visited
     * @param valid Boolean used to know if the path is valid
     * @param distanceType Boolean used to know if we want the real distances or the Haversine distances
     * @details Time Complexity - O(E)
     * @details E is the number of edges of each node
     */
    void minimumDistanceRec(Node *node, double &distance, vector<int> &path, unsigned int count, bool &valid, bool distanceType);
};

#endif //DA2_GRAPH_H
