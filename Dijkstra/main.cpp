#include "Graph.h"

int main() {
    Graph g;

    // Read the edges from a CSV file
    g.readFromCSV("graph_data.csv");

    Airport start = HAN;
    Airport end = MNL;
    Airport exclude = BKK;

    // Finding the shortest path between airports
    cout << "Finding shortest path from ";
    printAirport(start);
    cout << " to ";
    printAirport(end);
    cout << ":\n";
    g.dijkstra(start, end);
    cout << "Distance: " << g.getDistance(end) << " km\nPath: ";
    g.find_path(start, end);

    // Calculating travel fee for the path
    int totalFee = g.calculateTravelFee(start, end);
    if (totalFee != -1) {
        cout << "Total travel fee: $" << totalFee << endl;
    } else {
        cout << "No valid path found to calculate travel fee." << endl;
    }

    // Finding the shortest path excluding a specific airport
    cout << "\nFinding shortest path from ";
    printAirport(start);
    cout << " to ";
    printAirport(end);
    cout << " excluding ";
    printAirport(exclude);
    cout << ":\n";
    g.dijkstra_exclude_node(start, end, exclude);
    cout << "Distance: " << g.getDistance(end) << " km\nPath: ";
    g.find_path(start, end);

    // Calculating travel fee for the path excluding a specific airport
    totalFee = g.calculateTravelFee(start, end);
    if (totalFee != -1) {
        cout << "Total travel fee: $" << totalFee << endl;
    } else {
        cout << "No valid path found to calculate travel fee." << endl;
    }

    return 0;
}
