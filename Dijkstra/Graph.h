#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <climits>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
using namespace std;

// Enum for representing airport codes as nodes in SEA (Southeast Asia)
enum Airport {
    HAN,  // Nội Bài, Hà Nội, Vietnam
    DAD,  // Đà Nẵng, Vietnam
    SGN,  // Tân Sơn Nhất, Ho Chi Minh City, Vietnam
    BKK,  // Suvarnabhumi, Bangkok, Thailand
    SIN,  // Changi, Singapore
    KUL,  // Kuala Lumpur, Malaysia
    MNL,  // Ninoy Aquino, Manila, Philippines
    CGK,  // Soekarno-Hatta, Jakarta, Indonesia
    PNH,  // Phnom Penh, Cambodia
    RGN   // Yangon, Myanmar
};

// Constants
const int NUM_AIRPORTS = 10;

// Class definition for the Graph
class Graph {
private:
    int adjMatrix[NUM_AIRPORTS][NUM_AIRPORTS];    // Adjacency matrix to store distances
    int travelFeeMatrix[NUM_AIRPORTS][NUM_AIRPORTS]; // Travel fee matrix
    int distances[NUM_AIRPORTS];                  // Shortest distances from source
    int prevNode[NUM_AIRPORTS];                   // Previous node in the shortest path
    int freeNode[NUM_AIRPORTS];                   // Unvisited nodes

    // Utility function to trim whitespace from strings
    string trim(const string& str);

    // Find the unvisited node with the minimum distance
    int find_min_distance();

public:
    Graph();

    // Add an edge between two airports with the given distance (cost) and travel fee
    void addEdge(Airport u, Airport v, int distance, int travelFee);

    // Convert a string to an enum value
    Airport getAirportEnum(const string& code);

    // Read edges from a CSV file with format: SRC, DST, DISTANCE, FEE
    void readFromCSV(const string& filename);

    // Dijkstra's algorithm to find the shortest path
    void dijkstra(Airport start, Airport end);

    // Dijkstra's algorithm excluding a specific node
    void dijkstra_exclude_node(Airport start, Airport end, Airport exclude);

    // Find and print the shortest path from start to end
    void find_path(Airport start, Airport end);

    // Get the distance to a specific airport
    int getDistance(Airport node);

    // Get the total travel fee for a specific path
    int calculateTravelFee(Airport start, Airport end);
};

// Function to print airport names based on the enum
void printAirport(Airport airport);

#endif
