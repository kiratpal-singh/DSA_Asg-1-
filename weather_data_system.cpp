#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <iomanip>
using namespace std;

// WeatherRecord ADT
struct WeatherRecord {
    string date;      // format: dd/mm/yyyy
    string city;
    double temperature;

    WeatherRecord(string d = "", string c = "", double t = -9999.0) {
        date = d;
        city = c;
        temperature = t; // sentinel value for missing data
    }
};

// WeatherDataStorage using 2D array
class WeatherDataStorage {
private:
    int yearsCount;
    vector<string> cities;
    int startYear;
    vector<vector<double>> data; // 2D array: years x cities
    const double SENTINEL = -9999.0;

    unordered_map<string, int> cityIndex; // map city -> column index

public:
    WeatherDataStorage(int numYears, vector<string> cityList, int start)
        : yearsCount(numYears), cities(cityList), startYear(start) {
        data.assign(yearsCount, vector<double>(cities.size(), SENTINEL));
        for (int i = 0; i < cities.size(); i++)
            cityIndex[cities[i]] = i;
    }

    // Insert weather record
    void insert(string city, int year, double temp) {
        if (cityIndex.find(city) == cityIndex.end()) {
            cout << "City not found!\n";
            return;
        }
        int row = year - startYear;
        if (row < 0 || row >= yearsCount) {
            cout << "Year out of range!\n";
            return;
        }
        int col = cityIndex[city];
        data[row][col] = temp;
        cout << "Inserted " << temp << "C for " << city << " in " << year << endl;
    }

    // Delete record
    void deleteRecord(string city, int year) {
        if (cityIndex.find(city) == cityIndex.end()) return;
        int row = year - startYear;
        if (row < 0 || row >= yearsCount) return;
        data[row][cityIndex[city]] = SENTINEL;
        cout << "Deleted record for " << city << " in " << year << endl;
    }

    // Retrieve city data by year
    void retrieve(string city) {
        if (cityIndex.find(city) == cityIndex.end()) return;
        int col = cityIndex[city];
        cout << "Data for " << city << ":\n";
        for (int row = 0; row < yearsCount; row++) {
            int year = startYear + row;
            if (data[row][col] != SENTINEL)
                cout << year << ": " << data[row][col] << "C\n";
            else
                cout << year << ": No data\n";
        }
    }

    // Row-major access
    void rowMajorAccess() {
        cout << "\nRow-major access:\n";
        for (int row = 0; row < yearsCount; row++) {
            for (int col = 0; col < cities.size(); col++) {
                cout << setw(8);
                if (data[row][col] != SENTINEL)
                    cout << data[row][col];
                else
                    cout << "NA";
            }
            cout << endl;
        }
    }

    // Column-major access
    void columnMajorAccess() {
        cout << "\nColumn-major access:\n";
        for (int col = 0; col < cities.size(); col++) {
            for (int row = 0; row < yearsCount; row++) {
                cout << setw(8);
                if (data[row][col] != SENTINEL)
                    cout << data[row][col];
                else
                    cout << "NA";
            }
            cout << endl;
        }
    }

    // Handle sparse data
    void handleSparseData() {
        cout << "\nHandling sparse data (non-empty entries only):\n";
        for (int row = 0; row < yearsCount; row++) {
            for (int col = 0; col < cities.size(); col++) {
                if (data[row][col] != SENTINEL) {
                    cout << "Year " << startYear + row
                         << ", City " << cities[col]
                         << ": " << data[row][col] << "C\n";
                }
            }
        }
    }

    // Analyze complexity
    void analyzeComplexity() {
        cout << "\nComplexity Analysis:\n";
        cout << "Insert: O(1)\n";
        cout << "Delete: O(1)\n";
        cout << "Retrieve: O(n) for years\n";
        cout << "Row-major access: O(n*m)\n";
        cout << "Column-major access: O(n*m)\n";
        cout << "Space Complexity: O(n*m)\n";
    }
};

// Main function
int main() {
    vector<string> cities = {"Delhi", "Mumbai", "Chennai"};
    WeatherDataStorage storage(5, cities, 2021);

    storage.insert("Delhi", 2021, 32.5);
    storage.insert("Delhi", 2022, 30.2);
    storage.insert("Mumbai", 2021, 28.1);
    storage.insert("Chennai", 2023, 35.0);

    storage.retrieve("Delhi");

    storage.rowMajorAccess();
    storage.columnMajorAccess();

    storage.handleSparseData();

    storage.deleteRecord("Delhi", 2022);
    storage.retrieve("Delhi");

    storage.analyzeComplexity();

    return 0;
}
