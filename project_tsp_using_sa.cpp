#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;
struct City {
    int x, y;
};

double distance(const City &a, const City &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double calculateTotalDistance(const vector<int> &tour, const vector<City> &cities) {
    double totalDistance = 0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        totalDistance += distance(cities[tour[i]], cities[tour[i + 1]]);
    }
    totalDistance += distance(cities[tour.back()], cities[tour[0]]);
    return totalDistance;
}

vector<int> getNeighbor(const vector<int> &currentTour) {
    vector<int> neighbor = currentTour;
    int i = rand() % neighbor.size();
    int j = rand() % neighbor.size();
    swap(neighbor[i], neighbor[j]);
    return neighbor;
}

vector<int> simulatedAnnealing(const vector<City> &cities, int maxIterations, double initialTemp, double coolingRate) {
    int numCities = cities.size();
    vector<int> currentTour(numCities);
    for (int i = 0; i < numCities; ++i) currentTour[i] = i; 
    
    random_shuffle(currentTour.begin(), currentTour.end()); 
    double currentCost = calculateTotalDistance(currentTour, cities);
    
    vector<int> bestTour = currentTour;
    double bestCost = currentCost;
    
    double temperature = initialTemp;

    for (int iteration = 0; iteration < maxIterations; ++iteration) {
        vector<int> newTour = getNeighbor(currentTour);
        double newCost = calculateTotalDistance(newTour, cities);

        if (newCost < currentCost || (exp((currentCost - newCost) / temperature) > (rand() / (double) RAND_MAX))) {
            currentTour = newTour;
            currentCost = newCost;

            if (currentCost < bestCost) {
                bestTour = currentTour;
                bestCost = currentCost;
            }
        }

        temperature *= coolingRate;
    }
    return bestTour;
}

int main() {
    srand(time(0)); 
    vector<City> cities = {{0, 0}, {1, 3}, {4, 3}, {6, 1}, {3, 7}};
    
    int maxIterations = 10000;
    double initialTemp = 10000.0;
    double coolingRate = 0.995;

    vector<int> bestTour = simulatedAnnealing(cities, maxIterations, initialTemp, coolingRate);

    cout << "Best Tour: ";
    for (int city : bestTour) cout << city << " ";
    cout << endl;
    cout << "Cost: " << calculateTotalDistance(bestTour, cities) << endl;

    return 0;
}