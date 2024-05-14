#include "Menu.h"

Menu::Menu() : data(Data()) {
    SelectGraphMenu();
}

void Menu::printTitle() {
    cout << R"(
________________________________________________________________________________________________
  ____  ____  _  _ ___ ___  _  _  _____      ____  _    _____  ____  ____  ___ ___  _  _  _  _
  |__/  |  |  |  |  |   |   |\ |  | __       |__|  |    | __   |  |  |__/   |   |   |__|  |\/|
  |  \  |__|  |__|  |  _|_  | \|  |___|      |  |  |___ |___|  |__|  |  \  _|_  |   |  |  |  |
------------------------------------------------------------------------------------------------
    )" << "\n";
}

void Menu::Print(const string& s, int length, bool tableOrPath) {
    int spaces;
    bool uneven = false;
    if ((length - int(s.size())) % 2 == 1) uneven = true;
    spaces = (length - int(s.size())) / 2;
    if (tableOrPath) cout << "|";
    else cout << "->";
    if (spaces > 0) cout << string(spaces, ' ');
    cout << s;
    if (spaces > 0) cout << string(spaces, ' ');
    if (uneven) cout << " ";
}

void Menu::clearScreen() {
    for (int i = 0; i < 20; i++) {
        cout << "\n";
    }
}

int Menu::getUserInput(vector<int> inputs) {
    int input;
    if (!cin) {
        cin.ignore();
        cin.ignore(100,'\n');
        cin.clear();
    }
    cin >> input;
    while (cin.fail() || find(inputs.begin(), inputs.end(), input) == inputs.end()) {
        if (cin.eof()) {
            cout << "\nExiting\n\n";
            return 0;
        }
        cin.clear();
        cin.ignore();
        cerr << "\nNot a valid input, please input one of the shown options: ";
        cin >> input;
    }
    cin.ignore(100, '\n');
    return input;
}

double Menu::printElapsedTime(timeval start, timeval end) {
    double elapsed = ((end.tv_sec - start.tv_sec) * 1e6 + (end.tv_usec - start.tv_usec)) * 1e-6;
    cout << "\n\nThe time this algorithm took to finish was: " << fixed << elapsed << setprecision(6) << " seconds.";
    return elapsed;
}

void Menu::SelectGraphMenu() {
    printTitle();
    cout << "\n";
    cout << "\tSelect Menu\n";
    cout << "(1) Real Graphs\n";
    cout << "(2) Extra Graphs\n";
    cout << "(3) Toy Graphs\n";
    cout << "(0) Exit\n";
    cout << " > ";

    if (!data.getGraph().getNodes().empty()) {
        data = Data();
    }

    int input = getUserInput({0, 1, 2, 3});
    switch (input) {
        case 1:
            clearScreen();
            printTitle();
            cout << "\n";
            cout << "\tReal Graphs Menu\n";
            cout << "(1) Graph 1\n";
            cout << "(2) Graph 2\n";
            cout << "(3) Graph 3\n";
            cout << "(4) Go back\n";
            cout << "(0) Exit\n";
            cout << " > ";

            input = getUserInput({0, 1, 2, 3, 4});
            switch (input) {
                case 1:
                    data.readRealGraphs(1);
                    MainMenu();
                case 2:
                    data.readRealGraphs(2);
                    MainMenu();
                case 3:
                    data.readRealGraphs(3);
                    MainMenu();
                case 4:
                    clearScreen();
                    SelectGraphMenu();
                case 0:
                    exit(0);
                default:
                    break;
            }
        case 2:
            clearScreen();
            printTitle();
            cout << "\n";
            cout << "\t\t\tExtra Graphs Menu\n";
            cout << "(1) 25\t\t(2) 50\t\t(3) 75\t\t(4) 100\n";
            cout << "(5) 200\t\t(6) 300\t\t(7) 400\t\t(8) 500\n";
            cout << "(9) 600\t\t(10) 700\t(11) 800\t(12) 900\n\n";
            cout << "(13) Go back\t";
            cout << "(0) Exit\n";
            cout << " > ";

            input = getUserInput({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13});
            switch (input) {
                case 1:
                    data.readExtraGraphs(25);
                    MainMenu();
                case 2:
                    data.readExtraGraphs(50);
                    MainMenu();
                case 3:
                    data.readExtraGraphs(75);
                    MainMenu();
                case 4:
                    data.readExtraGraphs(100);
                    MainMenu();
                case 5:
                    data.readExtraGraphs(200);
                    MainMenu();
                case 6:
                    data.readExtraGraphs(300);
                    MainMenu();
                case 7:
                    data.readExtraGraphs(400);
                    MainMenu();
                case 8:
                    data.readExtraGraphs(500);
                    MainMenu();
                case 9:
                    data.readExtraGraphs(600);
                    MainMenu();
                case 10:
                    data.readExtraGraphs(700);
                    MainMenu();
                case 11:
                    data.readExtraGraphs(800);
                    MainMenu();
                case 12:
                    data.readExtraGraphs(900);
                    MainMenu();
                case 13:
                    clearScreen();
                    SelectGraphMenu();
                case 0:
                    exit(0);
                default:
                    break;
            }
        case 3:
            clearScreen();
            printTitle();
            cout << "\n";
            cout << "\tToy Graphs Menu\n";
            cout << "(1) Shipping\n";
            cout << "(2) Stadiums\n";
            cout << "(3) Tourism\n";
            cout << "(4) Go back\n";
            cout << "(0) Exit\n";
            cout << " > ";

            input = getUserInput({0, 1, 2, 3, 4});
            switch (input) {
                case 1:
                    data.readToyGraphs("shipping");
                    MainMenu();
                case 2:
                    data.readToyGraphs("stadiums");
                    MainMenu();
                case 3:
                    data.readToyGraphs("tourism");
                    MainMenu();
                case 4:
                    clearScreen();
                    SelectGraphMenu();
                case 0:
                    exit(0);
                default:
                    break;
            }
        case 0:
            exit(0);
        default:
            break;
    }
}

void Menu::MainMenu() {
    clearScreen();
    printTitle();
    cout << "\n";
    cout << "\tMain Menu\n";
    cout << "(1) Graph Information\n";
    cout << "(2) Backtracking Algorithm\n";
    cout << "(3) Minimum Spanning Tree (better aproximation)\n";
    cout << "(4) Minimum Spanning Tree (worse aproximation but faster for larger graphs)\n";
    cout << "(5) Nearest Neighbor Algorithm\n";
    cout << "(6) \n";
    cout << "(7) Select another graph\n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3, 4, 5, 6, 7});
    switch (input) {
        case 1:
            InfoMenu();
        case 2:
            if (!data.getGraph().getNodes().empty()) {
                cout << "\nFinding cycle in the graph using backtracking. Please wait\n";
                double distance = INT_MAX;
                int shortestCycle[data.getGraph().getNodes().size()];
                bool graphType;
                if (data.getRealGraph()) {
                    cout << "\nDo you want to use the real distances or the Haversine distances?\n";
                    cout << "(1) Real distances\n";
                    cout << "(2) Haversine distances\n";
                    cout << " > ";
                    int input1 = getUserInput({1, 2});
                    if (input1 == 1) {
                        graphType = false;
                    }
                    else {
                        graphType = true;
                    }
                }
                else {
                    graphType = true;
                }
                struct timeval start{}, end{};
                gettimeofday(&start, nullptr);
                ios_base::sync_with_stdio(false);
                data.getGraph().backtrackingApproach(distance, shortestCycle, graphType);
                gettimeofday(&end, nullptr);

                for (int i = 0; i < data.getGraph().getNodes().size(); i++) {
                    Print(to_string(shortestCycle[i]), 6, false);
                }
                cout << "\n\nThe distance the travelling salesman travels is " <<  distance;
                if (data.getRealGraph() && graphType) {
                    data.haversineReport.distBacktrack = distance;
                    data.haversineReport.timeBacktrack = printElapsedTime(start, end);
                }
                else {
                    data.report.distBacktrack = distance;
                    data.report.timeBacktrack = printElapsedTime(start, end);
                }
            }
            break;
        case 3:
            if (!data.getGraph().getNodes().empty()) {
                vector<int> path;
                double distance = 0;
                bool graphType;
                if (data.getRealGraph()) {
                    cout << "\nDo you want to use the real distances or the Haversine distances?\n";
                    cout << "(1) Real distances\n";
                    cout << "(2) Haversine distances\n";
                    cout << " > ";
                    int input1 = getUserInput({1, 2});
                    if (input1 == 1) {
                        graphType = false;
                    }
                    else {
                        graphType = true;
                    }
                }
                else {
                    graphType = true;
                }
                cout << "\nFinding cycle in the graph using Prim's algorithm. Please wait\n";
                struct timeval start{}, end{};
                gettimeofday(&start, nullptr);
                ios_base::sync_with_stdio(false);
                path = data.getGraph().primMST(graphType, distance);
                gettimeofday(&end, nullptr);

                for (int i : path) {
                    Print(to_string(i), 6, false);

                }
                cout << "\n\nThe distance the travelling salesman travels is " << distance;
                if (data.getRealGraph() && graphType) {
                    data.haversineReport.distMST = distance;
                    data.haversineReport.timeMST = printElapsedTime(start, end);
                }
                else {
                    data.report.distMST = distance;
                    data.report.timeMST = printElapsedTime(start, end);
                }
            }
            break;
        case 4:
            if (!data.getGraph().getNodes().empty()) {
                vector<int> path;
                double distance = 0;
                bool graphType;
                if (data.getRealGraph()) {
                    cout << "\nDo you want to use the real distances or the Haversine distances?\n";
                    cout << "(1) Real distances\n";
                    cout << "(2) Haversine distances\n";
                    cout << " > ";
                    int input1 = getUserInput({1, 2});
                    if (input1 == 1) {
                        graphType = false;
                    }
                    else {
                        graphType = true;
                    }
                }
                else {
                    graphType = true;
                }
                cout << "\nFinding cycle in the graph using Prim's algorithm. Please wait\n";
                struct timeval start{}, end{};
                gettimeofday(&start, nullptr);
                ios_base::sync_with_stdio(false);
                path = data.getGraph().primMST2(graphType, distance);
                gettimeofday(&end, nullptr);

                for (int i : path) {
                    Print(to_string(i), 6, false);
                }
                cout << "\n\nThe distance the travelling salesman travels is " << distance;
                data.report.distMST2 = distance;
                data.report.timeMST2 = printElapsedTime(start, end);
            }
            break;
        case 5:
            if (!data.getGraph().getNodes().empty()) {
                vector<int> path;
                double distance = 0;
                bool graphType;
                if (data.getRealGraph()) {
                    cout << "\nDo you want to use the real distances or the Haversine distances?\n";
                    cout << "(1) Real distances\n";
                    cout << "(2) Haversine distances\n";
                    cout << " > ";
                    int input1 = getUserInput({1, 2});
                    if (input1 == 1) {
                        graphType = false;
                    }
                    else {
                        graphType = true;
                    }
                }
                else {
                    graphType = true;
                }
                cout << "\nFinding cycle in the graph using the Nearest Neighbor algorithm. Please wait\n";
                struct timeval start{}, end{};
                gettimeofday(&start, nullptr);
                ios_base::sync_with_stdio(false);
                path = data.getGraph().nearestNeighbor(distance, graphType);
                gettimeofday(&end, nullptr);

                for (int i : path) {
                    Print(to_string(i), 6, false);
                }
                cout << "\n\nThe distance the travelling salesman travels is " << distance;
                if (data.getRealGraph() && graphType) {
                    data.haversineReport.distNearNeighbor = distance;
                    data.haversineReport.timeNearNeighbor = printElapsedTime(start, end);
                }
                else {
                    data.report.distNearNeighbor = distance;
                    data.report.timeNearNeighbor = printElapsedTime(start, end);
                }
            }
            break;
        case 6:
            if (!data.getGraph().getNodes().empty()) {

            }
            break;
        case 7:
            clearScreen();
            SelectGraphMenu();
        case 0:
            exit(0);
        default:
            break;
    }
    cout << "\n\n";
    cout << "Press 7 to continue\n";
    getUserInput({7});
    MainMenu();
}

void Menu::InfoMenu() {
    clearScreen();
    printTitle();
    cout << "\n";
    cout << "\tGraph Information Menu\n";
    cout << "(1) All nodes of a graph\n";
    cout << "(2) Information about a specific node of a graph\n";
    cout << "(3) Compare time and distances results of the algorithms\n";
    cout << "(4) Back to the Main Menu\n";
    cout << "(0) Exit\n";
    cout << " > ";

    int input = getUserInput({0, 1, 2, 3, 4});
    switch (input) {
        case 1:
            if (!data.getGraph().getNodes().empty()) {
                if (data.getRealGraph()) {
                    cout << "\nDue to the number of nodes of this graph, choose the amount of entries about to be shown to you from 1 to " +
                            to_string(data.getGraph().getNodes().size()) + "\n" + " > ";
                    vector<int> inputs;
                    for (int i = 1; i <= data.getGraph().getNodes().size(); i++) inputs.push_back(i);
                    int size = getUserInput(inputs);
                    cout << "\n\n";
                    for (int i = 0; i < 56; i++) cout << "-";
                    cout << "\n";
                    Print("Node Id", 10, true);
                    Print("Longitude", 21, true);
                    Print("Latitude", 21, true);
                    cout << "|\n";
                    for (int i = 0; i < 56; i++) cout << "-";
                    cout << "\n";
                    for (int i = 0; i < size; i++) {
                        Print(to_string(data.getGraph().getNodes().at(i)->Id), 10, true);
                        cout << "| " << fixed << setprecision(15) << data.getGraph().getNodes().at(i)->longitude << " ";
                        cout << "| " << fixed << setprecision(15) << data.getGraph().getNodes().at(i)->latitude << " ";
                        cout << "|\n";
                    }
                    for (int i = 0; i < 56; i++) cout << "-";
                } else if (data.getExtraGraph()) {
                    int size = (int) data.getGraph().getNodes().size();
                    if (size > 100) {
                        cout << "\nDue to the number of nodes of this graph, choose the amount of entries about to be shown to you from 1 to " +
                             to_string(data.getGraph().getNodes().size()) + "\n" + " > ";
                        vector<int> inputs;
                        for (int i = 1; i <= data.getGraph().getNodes().size(); i++) inputs.push_back(i);
                        size = getUserInput(inputs);
                    }
                    cout << "\n\n";
                    for (int i = 0; i < 12; i++) cout << "-";
                    cout << "\n";
                    Print("Node Id", 10, true);
                    cout << "|\n";
                    for (int i = 0; i < 12; i++) cout << "-";
                    cout << "\n";
                    for (int i = 0; i < size; i++) {
                        Print(to_string(data.getGraph().getNodes().at(i)->Id), 10, true);
                        cout << "|\n";
                    }
                    for (int i = 0; i < 12; i++) cout << "-";
                } else {
                    if (data.getTourismToyGraph()) {
                        cout << "\n\n";
                        for (int i = 0; i < 23; i++) cout << "-";
                        cout << "\n";
                        Print("Node Id", 9, true);
                        Print("Node Name", 11, true);
                        cout << "|\n";
                        for (int i = 0; i < 23; i++) cout << "-";
                        cout << "\n";
                        for (int i = 0; i < data.getGraph().getNodes().size(); i++) {
                            Print(to_string(data.getGraph().getNodes().at(i)->Id), 9, true);
                            Print(data.getGraph().getNodes().at(i)->name, 11, true);
                            cout << "|\n";
                        }
                        for (int i = 0; i < 23; i++) cout << "-";
                    } else {
                        cout << "\n\n";
                        for (int i = 0; i < 12; i++) cout << "-";
                        cout << "\n";
                        Print("Node Id", 10, true);
                        cout << "|\n";
                        for (int i = 0; i < 12; i++) cout << "-";
                        cout << "\n";
                        for (int i = 0; i < data.getGraph().getNodes().size(); i++) {
                            Print(to_string(data.getGraph().getNodes().at(i)->Id), 10, true);
                            cout << "|\n";
                        }
                        for (int i = 0; i < 12; i++) cout << "-";
                    }
                }
            }
            break;
        case 2:
            if (!data.getGraph().getNodes().empty()) {
                cout << "\nChoose the node id. It has to be between 0 and " + to_string(data.getGraph().getNodes().size() - 1) + "\n" + " > ";
                vector<int> inputs;
                for (int i = 0; i < data.getGraph().getNodes().size(); i++) inputs.push_back(i);
                int Id = getUserInput(inputs);
                int size = (int) data.getGraph().getEdgesOut(Id).size();
                if (size > 100) {
                    vector<int> inputs1;
                    cout << "\nDue to the number of edges of this node, choose the amount of entries about to be shown to you from 1 to " +
                            to_string(data.getGraph().getEdgesOut(Id).size()) + "\n" + " > ";
                    for (int i = 1; i <= data.getGraph().getEdgesOut(Id).size(); i++) inputs1.push_back(i);
                    size = getUserInput(inputs1);
                }
                cout << "\n\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                Print("Origin", 8, true);
                Print("Destination", 13, true);
                Print("Distance", 10, true);
                cout << "|\n";
                for (int i = 0; i < 35; i++) cout << "-";
                cout << "\n";
                for (int i = 0; i < size; i++) {
                    Print(to_string(data.getGraph().getEdgesOut(Id).at(i)->origin), 8, true);
                    Print(to_string(data.getGraph().getEdgesOut(Id).at(i)->dest), 13, true);
                    Print(data.getGraph().getEdgesOut(Id).at(i)->distanceStr, 10, true);
                    cout << "|\n";
                }
                for (int i = 0; i < 35; i++) cout << "-";
            }
            break;
        case 3:
            if (!data.getGraph().getNodes().empty()) {
                cout << "\n\n";
                for (int i = 0; i < 43; i++) cout << "-";
                if (data.getRealGraph()) {
                    for (int i = 0; i < 30; i++) cout << "-";
                }
                cout << "\n";
                Print("Real Distances", 41, true);
                if (data.getRealGraph()) {
                    Print("Haversine Distances", 29, true);
                }
                cout << "|\n";
                for (int i = 0; i < 43; i++) cout << "-";
                if (data.getRealGraph()) {
                    for (int i = 0; i < 30; i++) cout << "-";
                }
                cout << "\n";
                Print("Algorithm", 11, true);
                Print("Time", 14, true);
                Print("Distance", 14, true);
                if (data.getRealGraph()) {
                    Print("Time", 14, true);
                    Print("Distance", 14, true);
                }
                cout << "|\n";
                for (int i = 0; i < 43; i++) cout << "-";
                if (data.getRealGraph()) {
                    for (int i = 0; i < 30; i++) cout << "-";
                }
                cout << "\n";
                Print("Backtrack", 11, true);
                stringstream tb;
                tb << fixed << setprecision(6) << data.report.timeBacktrack;
                Print(tb.str(), 14, true);
                stringstream db;
                db << fixed << setprecision(3) << data.report.distBacktrack;
                Print(db.str(), 14, true);
                if (data.getRealGraph()) {
                    stringstream thb;
                    thb << fixed << setprecision(6) << data.haversineReport.timeBacktrack;
                    Print(thb.str(), 14, true);
                    stringstream dhb;
                    dhb << fixed << setprecision(3) << data.haversineReport.distBacktrack;
                    Print(dhb.str(), 14, true);
                }
                cout << "|\n";
                Print("MST", 11, true);
                stringstream tmst;
                tmst << fixed << setprecision(6) << data.report.timeMST;
                Print(tmst.str(), 14, true);
                stringstream dmst;
                dmst << fixed << setprecision(3) << data.report.distMST;
                Print(dmst.str(), 14, true);
                if (data.getRealGraph()) {
                    stringstream thmst;
                    thmst << fixed << setprecision(6) << data.haversineReport.timeMST;
                    Print(thmst.str(), 14, true);
                    stringstream dhmst;
                    dhmst << fixed << setprecision(3) << data.haversineReport.distMST;
                    Print(dhmst.str(), 14, true);
                }
                cout << "|\n";
                Print("MST2", 11, true);
                stringstream tmst2;
                tmst2 << fixed << setprecision(6) << data.report.timeMST2;
                Print(tmst2.str(), 14, true);
                stringstream dmst2;
                dmst2 << fixed << setprecision(3) << data.report.distMST2;
                Print(dmst2.str(), 14, true);
                if (data.getRealGraph()) {
                    stringstream thmst2;
                    thmst2 << fixed << setprecision(6) << data.haversineReport.timeMST2;
                    Print(thmst2.str(), 14, true);
                    stringstream dhmst2;
                    dhmst2 << fixed << setprecision(3) << data.haversineReport.distMST2;
                    Print(dhmst2.str(), 14, true);
                }
                cout << "|\n";
                Print("NN", 11, true);
                stringstream tnn;
                tnn << fixed << setprecision(6) << data.report.timeNearNeighbor;
                Print(tnn.str(), 14, true);
                stringstream dnn;
                dnn << fixed << setprecision(3) << data.report.distNearNeighbor;
                Print(dnn.str(), 14, true);
                if (data.getRealGraph()) {
                    stringstream thnn;
                    thnn << fixed << setprecision(6) << data.haversineReport.timeNearNeighbor;
                    Print(thnn.str(), 14, true);
                    stringstream dhnn;
                    dhnn << fixed << setprecision(3) << data.haversineReport.distNearNeighbor;
                    Print(dhnn.str(), 14, true);
                }
                cout << "|\n";
                for (int i = 0; i < 43; i++) cout << "-";
                if (data.getRealGraph()) {
                    for (int i = 0; i < 30; i++) cout << "-";
                }
            }
            break;
        case 4:
            MainMenu();
        case 0:
            exit(0);
        default:
            break;
    }
    cout << "\n\n";
    cout << "Press 7 to continue\n";
    getUserInput({7});
    InfoMenu();
}
