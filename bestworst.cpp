#include<bits/stdc++.h>
using namespace std;

void firstFit (int blockSize [], int m, int processSize [], int n) {
    int allocation [n];
    memset(allocation, -1, sizeof(allocation));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize [j] >= processSize [i]) {
                allocation [i] = j;
                blockSize [j] -= processSize [i];
                break;
            }
        }
    }
    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i+1 << "\t\t" << processSize [i] << "\t\t";
        if (allocation [i] != -1)
            cout << allocation [i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

void bestFit (int blockSize [], int m, int processSize [], int n) {
    int allocation [n];
    memset(allocation, -1, sizeof(allocation));
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize [j] >= processSize [i]) {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize [bestIdx] > blockSize [j])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation [i] = bestIdx;
            blockSize [bestIdx] -= processSize [i];
        }
    }
    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i+1 << "\t\t" << processSize [i] << "\t\t";
        if (allocation [i] != -1)
            cout << allocation [i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

void worstFit (int blockSize [], int m, int processSize [], int n) {
    int allocation [n];
    memset(allocation, -1, sizeof(allocation));
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize [j] >= processSize [i]) {
                if (worstIdx == -1)
                    worstIdx = j;
                else if (blockSize [worstIdx] < blockSize [j])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation [i] = worstIdx;
            blockSize [worstIdx] -= processSize [i];
        }
    }
    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++) {
        cout << " " << i+1 << "\t\t" << processSize [i] << "\t\t";
        if (allocation [i] != -1)
            cout << allocation [i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

int main () {
    int blockSize [] = {100, 500, 200, 300, 600};
    int processSize [] = {212, 417, 112, 426};
    int m = sizeof(blockSize) / sizeof(blockSize [0]);
    int n = sizeof(processSize) / sizeof(processSize [0]);

    cout << "First Fit Algorithm:\n";
    firstFit (blockSize, m, processSize, n);

    cout << "\nBest Fit Algorithm:\n";
    bestFit (blockSize, m, processSize, n);

    cout << "\nWorst Fit Algorithm:\n";
    worstFit (blockSize, m, processSize, n);

    return 0;
}
