#include "Graph.h"

// Constructor for the Graph class
Graph::Graph() {
    for (int i = 0; i < NUM_AIRPORTS; i++) {
        for (int j = 0; j < NUM_AIRPORTS; j++) {
            adjMatrix[i][j] = 0;
            travelFeeMatrix[i][j] = 0;
        }
    }
}

// Add an edge between two airports with the given distance (cost) and travel fee
void Graph::addEdge(Airport u, Airport v, int distance, int travelFee) {
    adjMatrix[u][v] = distance;
    adjMatrix[v][u] = distance;  // If it's an undirected graph
    travelFeeMatrix[u][v] = travelFee;
    travelFeeMatrix[v][u] = travelFee;
}

// Convert a string to an enum value
Airport Graph::getAirportEnum(const string& code) {
    if (code == "HAN") return HAN;
    if (code == "DAD") return DAD;
    if (code == "SGN") return SGN;
    if (code == "BKK") return BKK;
    if (code == "SIN") return SIN;
    if (code == "KUL") return KUL;
    if (code == "MNL") return MNL;
    if (code == "CGK") return CGK;
    if (code == "PNH") return PNH;
    if (code == "RGN") return RGN;
    throw invalid_argument("Unknown airport code: " + code);
}

// Utility function to trim whitespace from strings
string Graph::trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return (first == string::npos || last == string::npos) ? "" : str.substr(first, last - first + 1);
}

// Read edges from a CSV file with format: SRC, DST, DISTANCE, FEE
void Graph::readFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;

    // Skip the header (first row if necessary)
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;  // Skip empty lines

        stringstream ss(line);
        string srcCode, dstCode, distanceStr, feeStr;

        // Read the values separated by commas
        getline(ss, srcCode, ',');
        getline(ss, dstCode, ',');
        getline(ss, distanceStr, ',');
        getline(ss, feeStr, ',');

        // Trim any leading/trailing spaces from the extracted parts
        srcCode = trim(srcCode);
        dstCode = trim(dstCode);
        distanceStr = trim(distanceStr);
        feeStr = trim(feeStr);

        try {
            // Convert the extracted strings to appropriate types
            Airport src = getAirportEnum(srcCode);
            Airport dst = getAirportEnum(dstCode);
            int distance = stoi(distanceStr);
            int fee = stoi(feeStr);

            // Add the edge to the graph
            addEdge(src, dst, distance, fee);
        } catch (const exception& e) {
            cerr << "Error parsing line: " << line << ". " << e.what() << endl;
        }
    }

    file.close();
}

// Find the unvisited node with the minimum distance
int Graph::find_min_distance() {
    int min = INT_MAX, min_index = -1;
    for (int node = 0; node < NUM_AIRPORTS; node++) {
        if (distances[node] < min && freeNode[node] == 1) {
            min = distances[node];
            min_index = node;
        }
    }
    return min_index;
}

// Dijkstra's algorithm to find the shortest path
void Graph::dijkstra(Airport start, Airport end) {
    for (int i = 0; i < NUM_AIRPORTS; i++) {
        distances[i] = INT_MAX;
        freeNode[i] = 1;
        prevNode[i] = -1;
    }

    distances[start] = 0;
    prevNode[start] = start;

    for (int i = 0; i < NUM_AIRPORTS - 1; i++) {
        int min_node = find_min_distance();
        if (min_node == -1) return;
        freeNode[min_node] = 0;

        if (end == min_node) return;

        for (int y = 0; y < NUM_AIRPORTS; y++) {
            if (adjMatrix[min_node][y] > 0 && freeNode[y] == 1 &&
                distances[y] > distances[min_node] + adjMatrix[min_node][y]) {
                distances[y] = distances[min_node] + adjMatrix[min_node][y];
                prevNode[y] = min_node;
            }
        }
    }
}

// Dijkstra's algorithm excluding a specific node
void Graph::dijkstra_exclude_node(Airport start, Airport end, Airport exclude) {
    for (int i = 0; i < NUM_AIRPORTS; i++) {
        distances[i] = INT_MAX;
        freeNode[i] = 1;
        prevNode[i] = -1;
    }

    distances[start] = 0;
    prevNode[start] = start;

    for (int i = 0; i < NUM_AIRPORTS - 1; i++) {
        int min_node = find_min_distance();
        if (min_node == -1) return;
        freeNode[min_node] = 0;

        if (end == min_node) return;

        for (int y = 0; y < NUM_AIRPORTS; y++) {
            int weight = (y == exclude) ? INT_MAX / 2 : adjMatrix[min_node][y];
            if (weight > 0 && freeNode[y] == 1 &&
                distances[y] > distances[min_node] + weight) {
                distances[y] = distances[min_node] + weight;
                prevNode[y] = min_node;
            }
        }
    }
}

// Find and print the shortest path from start to end
void Graph::find_path(Airport start, Airport end) {
    int path[NUM_AIRPORTS], idx = 0;
    for (int k = end; k != start; k = prevNode[k]) {
        if (k == -1) {
            cout << "No path found!" << endl;
            return;
        }
        path[idx++] = k;
    }
    path[idx++] = start;

    for (int i = idx - 1; i >= 0; i--) {
        cout << path[i];
        if (i != 0) cout << " - ";
    }
    cout << endl;
}

// Get the distance to a specific airport
int Graph::getDistance(Airport node) {
    return distances[node];
}

// Get the total travel fee for a specific path
int Graph::calculateTravelFee(Airport start, Airport end) {
    int totalFee = 0;
    for (int k = end; k != start; k = prevNode[k]) {
        if (k == -1) {
            return -1; // No path found
        }
        totalFee += travelFeeMatrix[prevNode[k]][k];
    }
    return totalFee;
}

// Function to print airport names based on the enum
void printAirport(Airport airport) {
    switch (airport) {
    case HAN: cout << "HAN"; break;
    case DAD: cout << "DAD"; break;
    case SGN: cout << "SGN"; break;
    case BKK: cout << "BKK"; break;
    case SIN: cout << "SIN"; break;
    case KUL: cout << "KUL"; break;
    case MNL: cout << "MNL"; break;
    case CGK: cout << "CGK"; break;
    case PNH: cout << "PNH"; break;
    case RGN: cout << "RGN"; break;
    }
}
