#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3};

    do {
        for (int i=0; i<v.size();i++) {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;
    } while (std::next_permutation(v.begin(), v.end()));

    return 0;
}
