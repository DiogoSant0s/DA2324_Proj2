#ifndef DA2_DATA_H
#define DA2_DATA_H

#include <fstream>
#include <sstream>
#include "Graph.h"

/**
 * @details The Data class is responsible for reading all the provided data and connecting the Menu class to the Graph class
 */
class Data {
private:
    /**
     * The graph
     */
    Graph graph;
    /**
     * Bool used to know if the graph is one of the Real World Graphs
     */
    bool realGraph;
    /**
     * Bool used to know if the graph is the Tourism Toy Graph, the only graph whose nodes have names
     */
    bool tourismToyGraph;
    /**
     * Bool used to know if the graph is one of the Extra Fully Connected Graphs
     */
    bool extraGraph;
public:
    /**
     * Struct to store the results of the algorithms
     */
    struct Report {
        /**
         * Time taken by the Backtrack algorithm
         */
        double timeBacktrack;
        /**
         * Time taken by prim's MST algorithm
         */
        double timeMST;
        /**
         * Time taken by prim's MST2 algorithm
         */
        double timeMST2;
        /**
         * Time taken by the Nearest Neighbor algorithm
         */
        double timeNearNeighbor;
        /**
         * Time taken by the Minimum Distance Recursive Traversal algorithm
         */
        double timeMDRT;
        /**
         * Distance of the path found by the Backtrack algorithm
         */
        double distBacktrack;
        /**
         * Distance of the path found by prim's MST algorithm
         */
        double distMST;
        /**
         * Distance of the path found by prim's MST2 algorithm
         */
        double distMST2;
        /**
         * Distance of the path found by the Nearest Neighbor algorithm
         */
        double distNearNeighbor;
        /**
         * Distance of the path found by the Minimum Distance Recursive Traversal algorithm
         */
        double distMDRT;
    };
    /**
     * Normal report
     */
    Report report{};
    /**
     * Haversine report
     */
    Report haversineReport{};
    /**
     * Data class constructor
     * @details Calls the Graph constructor for the graph in this class and initializes all variables
     */
    Data();
    /**
     * Reads the data in the nodes and edges files from the real graph corresponding to the given graphNumber and stores it in the correct structures
     * @details Time Complexity - O(V * E)
     * @details With V being the amount of nodes and E being the amount of edges of the graph
     * @param graphNumber Number of the graph to be read
     */
    void readRealGraphs(int graphNumber);
    /**
     * Reads the data in the edges file from the toy graph corresponding to the given graphName and stores it in the correct structures
     * @details Time Complexity - O(E)
     * @details With E being the amount of edges of the graph
     * @param graphName Name of the graph to be read
     */
    void readToyGraphs(const string& graphName);
    /**
     * Reads the data in the edges file from the extra graph corresponding to the given graphNumber and stores it in the correct structures
     * @details Time Complexity - O(E)
     * @details With E being the amount of edges of the graph
     * @param graphNumber Number of the graph to be read
     */
    void readExtraGraphs(int graphNumber);
    /**
     * Graph method to get the Graph graph
     * @details Time Complexity - O(1)
     * @return graph
     */
    Graph getGraph();
    /**
     * Bool method to get the boolean realGraph
     * @details Time Complexity - O(1)
     * @return realGraph
     */
    bool getRealGraph() const;
    /**
     * Bool method to get the boolean extraGraph
     * @details Time Complexity - O(1)
     * @return extraGraph
     */
    bool getExtraGraph() const;
    /**
     * Bool method to get the boolean tourismToyGraph
     * @details Time Complexity - O(1)
     * @return tourismToyGraph
     */
    bool getTourismToyGraph() const;
};

#endif //DA2_DATA_H
