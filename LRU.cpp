#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int size = 3;
    vector<int> reference_string = {1, 2, 1, 0, 3, 0, 4, 2, 4};
    vector<int> pages;
    int faults = 0, hits = 0;

    for (int ref_page : reference_string) {
        auto it = find(pages.begin(), pages.end(), ref_page);
        if (it != pages.end()) {
            pages.erase(it);
            pages.push_back(ref_page);
            hits++;
        } else {
            faults++;
            if (pages.size() < size)
                pages.push_back(ref_page);
            else {
                pages.erase(pages.begin());
                pages.push_back(ref_page);
            }
        }
    }

    cout << "Total number of Page Hits: " << hits << endl;
    cout << "Total number of Page Faults: " << faults << endl;

    return 0;
}
