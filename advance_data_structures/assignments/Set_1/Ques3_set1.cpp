#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter number of bits: ";
    cin >> n;

    vector<int> counter(n, 0);
    int piggyBank = 0;
    int totalActualCost = 0;
    int totalAmortizedCost = 0;

    int operations = 1 << n;   // 2^n operations

    cout << "\nStep | Binary Counter | Actual Cost | Amortized Cost | Piggy Bank\n";
    cout << "------------------------------------------------------------------\n";

    for (int step = 1; step <= operations; step++) {

        int actualCost = 0;
        int amortizedCost = 0;

        // Increment binary counter
        for (int i = n - 1; i >= 0; i--) {
            if (counter[i] == 0) {
                counter[i] = 1;
                actualCost += 1;
                amortizedCost += 2;
                piggyBank += 1;
                break;
            } else {
                counter[i] = 0;
                actualCost += 1;
                piggyBank -= 1;
            }
        }

        totalActualCost += actualCost;
        totalAmortizedCost += amortizedCost;

        cout << step << "    | ";
        for (int bit : counter) cout << bit;
        cout << "           |      " << actualCost
             << "      |        " << amortizedCost
             << "        |      " << piggyBank << endl;
    }

    cout << "\nTotal Actual Cost    : " << totalActualCost << endl;
    cout << "Total Amortized Cost : " << totalAmortizedCost << endl;
    cout << "Amortized Cost per Operation = "
         << (double)totalAmortizedCost / operations << endl;

    return 0;
}
