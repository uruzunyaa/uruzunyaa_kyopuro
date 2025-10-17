#include <vector>
#include <iostream>

using namespace std;

long long countInversions(vector<long long>& vec) {
    int n = vec.size();
    if (n <= 1) return 0;

    long long inv_count = 0;
    vector<long long> aux(n, 0);

    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += 2 * width) {
            int left = i, mid = min(i + width, n), right = min(i + 2 * width, n);
            int leftIndex = left, rightIndex = mid;
            for (int j = left; j < right; j++) {
                if (leftIndex < mid && (rightIndex >= right || vec[leftIndex] <= vec[rightIndex])) {
                    aux[j] = vec[leftIndex];
                    leftIndex++;
                } else {
                    aux[j] = vec[rightIndex];
                    rightIndex++;
                    inv_count += mid - leftIndex;
                }
            }
        }
        vec.swap(aux);
    }

    return inv_count;
}

int main() {
    vector<long long> vec = {46,11,37,25,11,37};
    long long inv_count = countInversions(vec);
    cout << "Inversion count is " << inv_count << endl;
    return 0;
}
