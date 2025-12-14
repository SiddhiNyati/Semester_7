#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Cost {
    long long comparisons = 0;
    long long assignments = 0;
};

// Insertion Sort with cost counting
void insertionSort(vector<int>& arr, Cost &cost) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        cost.comparisons++;   // for-loop check
        int key = arr[i];
        cost.assignments++;   // key assignment

        int j = i - 1;

        while (j >= 0) {
            cost.comparisons++;   // j >= 0
            cost.comparisons++;   // arr[j] > key

            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                cost.assignments++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
        cost.assignments++;
    }
}

// Case generators
vector<int> generateAscending(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = i + 1;
    return a;
}

vector<int> generateDescending(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = n - i;
    return a;
}

vector<int> generateRandom(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = rand() % 1000;
    return a;
}

vector<int> generateHalfRandomHalfDescending(int n) {
    vector<int> a;
    int half = n / 2;

    for (int i = 0; i < half; i++)
        a.push_back(rand() % 1000);

    for (int i = half; i < n; i++)
        a.push_back(n - i);

    return a;
}

void testCase(const string& title, vector<int> arr) {
    Cost cost;
    insertionSort(arr, cost);

    cout << "\n" << title << endl;
    cout << "Comparisons : " << cost.comparisons << endl;
    cout << "Assignments : " << cost.assignments << endl;
    cout << "Total Cost  : " << cost.comparisons + cost.assignments << endl;
}

int main() {
    srand(time(0));
    int n;

    cout << "Enter array size: ";
    cin >> n;

    testCase("Case A: Random Data", generateRandom(n));
    testCase("Case B: Descending Order", generateDescending(n));
    testCase("Case C: Half Random Half Descending", generateHalfRandomHalfDescending(n));
    testCase("Case D: Ascending Order", generateAscending(n));

    return 0;
}
