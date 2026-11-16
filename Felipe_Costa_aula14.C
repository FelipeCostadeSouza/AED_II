#include <bits/stdc++.h>
#include <chrono>
#include <random>
using namespace std;

class Hash {
    int bucketCount;
    vector<vector<int>> table;

public:
    Hash(int buckets) {
        bucketCount = buckets;
        table.resize(bucketCount);
    }

    void insert(int key) {
        int index = getHashIndex(key);
        table[index].push_back(key);
    }
    
    bool search(int key) {
        int index = getHashIndex(key);
        for (int k : table[index]) {
            if (k == key) {
                return true; 
            }
        }
        return false; 
    }

    void display() {
        for (int i = 0; i < bucketCount; i++) {
            cout << i;
            for (int key : table[i]) {
                cout << " --> " << key;
            }
            cout << endl;
        }
    }

private:
    int getHashIndex(int key) {
        return key % bucketCount;
    }
};

vector<int> linearProbing(const vector<int>& arr, int m) {
    vector<int> hashTable(m, -1);

    for (int value : arr) {
        int index = value % m;

        for (int count = 0; count < m; count++) {
            int pos = (index + count) % m;

            if (hashTable[pos] == value)
                break;

            if (hashTable[pos] == -1) {
                hashTable[pos] = value;
                break;
            }
        }
    }

    return hashTable;
}
bool searchLinear(const vector<int>& hashTable, int key) {
    int m = hashTable.size();
    int index = key % m;

    for (int count = 0; count < m; count++) {
        int pos = (index + count) % m;

        if (hashTable[pos] == key) {
            return true;
        }

        if (hashTable[pos] == -1) {
            return false;
        }
    }

    return false; 
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numKeys = 10000;
    int m = 10000; 
    vector<int> keys;
    unordered_set<int> uniqueKeys;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(1, 5000000);

    while (uniqueKeys.size() < numKeys) {
        uniqueKeys.insert(dist(gen));
    }
    keys.assign(uniqueKeys.begin(), uniqueKeys.end());

    Hash hashTable(m);
    
    auto start1 = chrono::high_resolution_clock::now();
    for (int key : keys) {
        hashTable.insert(key);
    }
    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration1 = end1 - start1;

    auto start2 = chrono::high_resolution_clock::now();
    vector<int> resultLinear = linearProbing(keys, m);
    auto end2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> duration2 = end2 - start2;
    
    auto startSearch1 = chrono::high_resolution_clock::now();
    
    hashTable.search(999);
    
    auto endSearch1 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationSearch1 = endSearch1 - startSearch1;

    auto startSearch2 = chrono::high_resolution_clock::now();
    searchLinear(resultLinear, 999);
    
    auto endSearch2 = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> durationSearch2 = endSearch2 - startSearch2;

    cout << "Inserção\n";
    cout << "Encadeamento Separado: " << duration1.count() << " ms\n";
    cout << "Sondagem Linear      : " << duration2.count() << " ms\n";
    cout << "Busca\n";
    cout << "Encadeamento Separado: " << durationSearch1.count() << " ms\n";
    cout << "Sondagem Linear      : " << durationSearch2.count() << " ms\n";

    return 0;
}
