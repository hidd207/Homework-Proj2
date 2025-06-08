#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // 題目給定參數
    const double t_s = 0.08;   // seek time (sec)
    const double t_l = 0.02;   // latency (sec)
    const double t_t = 0.001;  // 每筆資料傳送時間 (sec)
    const int n = 200000;      // 資料筆數
    const int S = 2000;        // buffer 大小

    cout << "k\tTotal Input Time (sec)\n";
    cout << "---------------------------------\n";
    for (int k = 1; k <= 64; ++k) {
        double t_input = (double(n) * k / S) * (t_s + t_l) + n * t_t;
        cout << setw(2) << k << "\t" << fixed << setprecision(2) << t_input << endl;
    }
    return 0;
}