#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double a, b, c;
    cin >> a >> b >> c;

    double D = b * b - 4 * a * c; // 判別式

    if (D < 0) {
        cout << "実数解は存在しません。" << endl;
    } else {
        double x1 = (-b - sqrt(D)) / (2 * a);
        double x2 = (-b + sqrt(D)) / (2 * a);

        if (x1 < x2) {
            cout << "x = " << x1 << ", " << x2 << endl;
        } else {
            cout << "x = " << x2 << ", " << x1 << endl;
        }
    }

    return 0;
}
