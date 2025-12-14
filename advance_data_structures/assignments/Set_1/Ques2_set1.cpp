#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements to insert: ";
    cin >> n;

    int capacity = 1;
    int size = 0;
    int bankBalance = 0;

    int totalActualCost = 0;
    int totalAmortizedCost = 0;

    int* arr = new int[capacity];

    cout << "\nStep | Size | Capacity | Actual Cost | Bank Balance\n";
    cout << "---------------------------------------------------\n";

    for (int i = 1; i <= n; i++) {

        int actualCost = 1;   // insertion cost
        int amortizedCharge = 3;  // fixed charge per insertion
        bankBalance += (amortizedCharge - actualCost);

        // Check if resize needed
        if (size == capacity) {
            int copyCost = size;
            actualCost += copyCost;
            bankBalance -= copyCost;

            capacity *= 2;
            int* newArr = new int[capacity];

            for (int j = 0; j < size; j++)
                newArr[j] = arr[j];

            delete[] arr;
            arr = newArr;
        }

        arr[size++] = i;

        totalActualCost += actualCost;
        totalAmortizedCost += amortizedCharge;

        cout << i << "    |  " << size
             << "   |    " << capacity
             << "     |      " << actualCost
             << "       |      " << bankBalance << endl;
    }

    cout << "\nTotal Actual Cost     : " << totalActualCost;
    cout << "\nTotal Amortized Cost  : " << totalAmortizedCost;
    cout << "\nAmortized Cost per Insertion = "
         << (double)totalAmortizedCost / n << endl;

    delete[] arr;
    return 0;
}
