#include <iostream>
#include <vector>

using namespace std;

int main() {
    float arr[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    vector<vector<float>> mat;

    for(char i = 0; i < 3; i++) {
        vector<float> row(3);
        copy(begin(arr[i]), end(arr[i]), row.begin());
        mat.push_back(row);
    }

    for(vector<float> row: mat) {
        for(float ele: row)
            cout << ele << ' ';
        cout << endl;
    }

    return 0;
}