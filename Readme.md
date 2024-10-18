# SEA Airport Route Finder

This project implements Dijkstra's algorithm to find the shortest route between airports in Southeast Asia (SEA), including functionalities for travel distances and fees.

## Project Structure

project/ │ ├── src/ │ ├── main.cpp # Main program file │ └── utils/ │ ├── Graph.cpp # Graph class definition │ └── Graph.h # Graph class declaration │ ├── include/ │ └── utils/ │ └── Graph.h # Header file for the Graph class │ ├── graph_data.csv # CSV file containing airport routes ├── Makefile # Makefile for compiling the project └── README.md # This README file

## Compilation Instructions

To compile the code, you can use either a `Makefile` for convenience or compile manually using the `g++` compiler.

### Using Makefile

1. Navigate to the root directory of the project:

```bash
   cd path/to/project
```

   Run the make command:

```bash
    make
```
This command will compile all the source files and produce an executable named program.

### Manual Compilation
If you prefer to compile manually, use the following command:

```bash
    g++ src/main.cpp src/utils/Graph.cpp -I include -o program
```
    > src/main.cpp: The main program file.
    > src/utils/Graph.cpp: The implementation of the Graph class.
    > -I include: This option tells the compiler where to find the header files.
    > -o program: This specifies the name of the output executable.

### Running the Program
After compiling, run the executable with:

```bash
./program
```
### Input File Format
The program reads routes from a CSV file (graph_data.csv) formatted as follows:

SRC, DST, DISTANCE, FEE
HAN, DAD, 606, 100   # Hà Nội - Đà Nẵng, 606 km, $100
DAD, SGN, 961, 150   # Đà Nẵng - Ho Chi Minh, 961 km, $150
...

Each line represents a route between two airports, including the distance in kilometers and the travel fee in dollars.

### Example
After running the program, you will be able to see the output of the shortest path between specified airports and the corresponding travel fees.

Finding shortest path from HAN to MNL:
Distance: 1200 km
Path: HAN - DAD - SGN - MNL
Total travel fee: $250

### Conclusion
This project provides a basic implementation of a graph-based algorithm to model airport routes and travel fees in Southeast Asia. Feel free to modify and extend the functionalities as needed.