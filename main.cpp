#include <bits/stdc++.h>
using namespace std;

vector<long long> poly_from_roots(const vector<long long>& roots) {
    vector<long long> poly = {1};
    for (long long r : roots) {
        vector<long long> term = {-r, 1};
        vector<long long> newpoly(poly.size() + 1, 0);
        for (size_t i = 0; i < poly.size(); i++) {
            for (size_t j = 0; j < term.size(); j++) {
                newpoly[i + j] += poly[i] * term[j];
            }
        }
        poly = newpoly;
    }
    reverse(poly.begin(), poly.end());
    return poly;
}

int main() {
    vector<long long> roots_tc1 = {
        stoll("4", nullptr, 10),
        stoll("111", nullptr, 2),
        stoll("12", nullptr, 10)
    };
    vector<long long> coeffs_tc1 = poly_from_roots(roots_tc1);
    cout << "Testcase 1 Coefficients (descending):\n";
    for (auto c : coeffs_tc1) cout << c << " ";
    cout << "\n\n";

    vector<pair<int,string>> tc2 = {
        {6, "13444211440455345511"},
        {15,"aed7015a346d635"},
        {15,"6aeeb69631c227c"},
        {16,"e1b5e05623d881f"},
        {8,"316034514573652620673"},
        {3,"2122212201122002221120200210011020220200"},
        {3,"20120221122211000100210021102001201112121"}
    };
    vector<long long> roots_tc2;
    for (auto &p : tc2) roots_tc2.push_back(stoll(p.second, nullptr, p.first));
    vector<long long> coeffs_tc2 = poly_from_roots(roots_tc2);
    cout << "Testcase 2 Coefficients (descending):\n";
    for (auto c : coeffs_tc2) cout << c << " ";
    cout << "\n";
}
