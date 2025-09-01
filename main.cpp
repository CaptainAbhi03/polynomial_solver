#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include "json/json.h"

using namespace std;

long long convertToDecimal(int base, const string& value) {
    long long result = 0;
    long long power = 1;
    
    for (int i = value.length() - 1; i >= 0; i--) {
        int digit;
        if (value[i] >= '0' && value[i] <= '9') {
            digit = value[i] - '0';
        } else if (value[i] >= 'A' && value[i] <= 'Z') {
            digit = value[i] - 'A' + 10;
        } else if (value[i] >= 'a' && value[i] <= 'z') {
            digit = value[i] - 'a' + 10;
        } else {
            throw invalid_argument("Invalid character in number");
        }
        
        if (digit >= base) {
            throw invalid_argument("Digit exceeds base");
        }
        
        result += digit * power;
        power *= base;
    }
    
    return result;
}

double lagrangeInterpolation(const vector<pair<int, long long>>& points, int x) {
    double result = 0.0;
    int n = points.size();
    
    for (int i = 0; i < n; i++) {
        double term = points[i].second;
        
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term = term * (double)(x - points[j].first) / (double)(points[i].first - points[j].first);
            }
        }
        
        result += term;
    }
    
    return result;
}

int main() {
    try {
        ifstream file("input.json");
        if (!file.is_open()) {
            cout << "Warning: Could not open input.json file. Using hardcoded test data.\n" << endl;
        }
        
        Json::Value root;
        
        if (file.is_open()) {
            file >> root;
            file.close();
        } else {
            string testJson = R"({
                "keys": {
                    "n": 4,
                    "k": 3
                },
                "1": {
                    "base": "10",
                    "value": "4"
                },
                "2": {
                    "base": "2",
                    "value": "111"
                },
                "3": {
                    "base": "10",
                    "value": "12"
                },
                "6": {
                    "base": "4",
                    "value": "213"
                }
            })";
            
            Json::Reader reader;
            reader.parse(testJson, root);
        }
        
        int n = root["keys"]["n"].asInt();
        int k = root["keys"]["k"].asInt();
        
        cout << "=== Shamir's Secret Sharing Implementation ===" << endl << endl;
        cout << "n (total roots): " << n << endl;
        cout << "k (minimum required): " << k << endl;
        cout << "Polynomial degree: " << k-1 << endl << endl;
        
        vector<pair<int, long long>> points;
        
        for (int i = 1; i <= n; i++) {
            string key = to_string(i);
            if (root.isMember(key)) {
                int base = stoi(root[key]["base"].asString());
                string value = root[key]["value"].asString();
                long long y = convertToDecimal(base, value);
                points.push_back({i, y});
                
                cout << "Root " << i << ": (" << i << ", " << y << ") ";
                cout << "[base " << base << ": \"" << value << "\" → " << y << "]" << endl;
            }
        }
        
        if (points.size() < k) {
            cout << "Error: Not enough points to reconstruct polynomial!" << endl;
            return 1;
        }
        
        vector<pair<int, long long>> selectedPoints(points.begin(), points.begin() + k);
        
        cout << "\nUsing first " << k << " points for reconstruction:" << endl;
        for (const auto& point : selectedPoints) {
            cout << "(" << point.first << ", " << point.second << ") ";
        }
        cout << endl;
        
        double secretDouble = lagrangeInterpolation(selectedPoints, 0);
        long long secret = round(secretDouble);
        
        cout << "\nLagrange interpolation calculation:" << endl;
        cout << "f(0) = " << fixed << setprecision(6) << secretDouble << endl;
        cout << "Secret (constant term): " << secret << endl;
        
        if (points.size() > k) {
            cout << "\nVerification with remaining points:" << endl;
            for (size_t i = k; i < points.size(); i++) {
                int x = points[i].first;
                long long actualY = points[i].second;
                double calculatedY = lagrangeInterpolation(selectedPoints, x);
                long long roundedCalculatedY = round(calculatedY);
                
                cout << "Point (" << x << ", " << actualY << "): ";
                cout << "Calculated = " << roundedCalculatedY;
                cout << ", Match = " << (actualY == roundedCalculatedY ? "TRUE" : "FALSE") << endl;
            }
        }
        
        cout << "\n=== FINAL OUTPUT: " << secret << " ===" << endl;
        
        return 0;
        
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
        return 1;
    }
}

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    cout << "=== Shamir's Secret Sharing Implementation ===" << endl << endl;
    
    int n = 4, k = 3;
    vector<pair<int, pair<int, string>>> rawData = {
        {1, {10, "4"}},
        {2, {2, "111"}},
        {3, {10, "12"}},
        {6, {4, "213"}}
    };
    
    cout << "n (total roots): " << n << endl;
    cout << "k (minimum required): " << k << endl;
    cout << "Polynomial degree: " << k-1 << endl << endl;
    
    vector<pair<int, long long>> points;
    
    for (auto& data : rawData) {
        int x = data.first;
        int base = data.second.first;
        string value = data.second.second;
        
        long long y = 0;
        long long power = 1;
        for (int i = value.length() - 1; i >= 0; i--) {
            int digit = (value[i] >= '0' && value[i] <= '9') ? value[i] - '0' : value[i] - 'A' + 10;
            y += digit * power;
            power *= base;
        }
        
        points.push_back({x, y});
        cout << "Root " << x << ": (" << x << ", " << y << ") [base " << base << ": \"" << value << "\" → " << y << "]" << endl;
    }
    
    vector<pair<int, long long>> selectedPoints(points.begin(), points.begin() + k);
    
    double secret = 0.0;
    for (int i = 0; i < k; i++) {
        double term = selectedPoints[i].second;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0.0 - selectedPoints[j].first) / (double)(selectedPoints[i].first - selectedPoints[j].first);
            }
        }
        secret += term;
    }
    
    cout << "\nSecret (constant term): " << round(secret) << endl;
    cout << "\n=== FINAL OUTPUT: " << round(secret) << " ===" << endl;
    
    return 0;
}
