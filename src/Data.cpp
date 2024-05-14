#include "Data.h"

Data::Data() : graph(Graph()), realGraph(false), tourismToyGraph(false), extraGraph(false) {
    report = {0, 0, 0, 0,0,0,0,0, 0, 0};
    haversineReport = {0, 0, 0, 0,0,0,0,0, 0, 0};
}

Graph Data::getGraph() {return graph;}
bool Data::getRealGraph() const {return realGraph;}
bool Data::getExtraGraph() const {return extraGraph;}
bool Data::getTourismToyGraph() const {return tourismToyGraph;}

void Data::readRealGraphs(int graphNumber) {
    realGraph = true;
    ifstream nodes("../datasets/Real-World-Graphs/graph" + to_string(graphNumber) + "/nodes.csv");
    ifstream edges("../datasets/Real-World-Graphs/graph" + to_string(graphNumber) + "/edges.csv");
    string textLine;

    getline(nodes, textLine);
    getline(edges, textLine);

    while (getline(nodes, textLine)) {
        stringstream input(textLine);
        string Id, Longitude, Latitude;

        getline(input, Id, ',');
        getline(input, Longitude, ',');
        getline(input, Latitude, '\r');

        graph.addNode(stoi(Id), stod(Longitude), stod(Latitude));
    }
    while (getline(edges, textLine)) {
        stringstream input(textLine);
        string Origin, Destination, Distance;

        getline(input, Origin, ',');
        getline(input, Destination, ',');
        getline(input, Distance, '\r');

        graph.addEdge(stoi(Origin), stoi(Destination), stof(Distance), Distance);
    }
}

void Data::readToyGraphs(const string& graphName) {
    ifstream edges("../datasets/Toy-Graphs/" + graphName + ".csv");
    string textLine;

    getline(edges, textLine);
    string Origin, Destination, Distance;

    if (graphName == "tourism") {
        tourismToyGraph = true;
        while (getline(edges, textLine)) {
            stringstream input(textLine);
            string OriginName, DestinationName;

            getline(input, Origin, ',');
            getline(input, Destination, ',');
            getline(input, Distance, ',');
            getline(input, OriginName, ',');
            getline(input, DestinationName, '\r');

            graph.addNode(stoi(Origin), 0, 0);
            graph.addNode(stoi(Destination), 0, 0);
            graph.addEdge(stoi(Origin), stoi(Destination), stof(Distance), Distance);

            graph.getNodes().find(stoi(Origin))->second->name = OriginName;
            graph.getNodes().find(stoi(Destination))->second->name = DestinationName;
        }
    } else {
        while (getline(edges, textLine)) {
            stringstream input(textLine);

            getline(input, Origin, ',');
            getline(input, Destination, ',');
            getline(input, Distance, '\r');

            graph.addNode(stoi(Origin), 0, 0);
            graph.addNode(stoi(Destination), 0, 0);
            graph.addEdge(stoi(Origin), stoi(Destination), stof(Distance), Distance);
        }
    }
}

void Data::readExtraGraphs(int graphNumber) {
    extraGraph = true;
    ifstream edges("../datasets/Extra_Fully_Connected_Graphs/edges_" + to_string(graphNumber) + ".csv");
    string textLine;

    getline(edges, textLine);

    while (getline(edges, textLine)) {
        stringstream input(textLine);
        string Origin, Destination, Distance;

        getline(input, Origin, ',');
        getline(input, Destination, ',');
        getline(input, Distance, '\r');

        graph.addNode(stoi(Origin), 0, 0);
        graph.addNode(stoi(Destination), 0, 0);
        graph.addEdge(stoi(Origin), stoi(Destination), stof(Distance), Distance);
    }
}
