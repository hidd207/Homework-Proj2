#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // �D�ص��w�Ѽ�
    const double t_s = 0.08;   // seek time (sec)
    const double t_l = 0.02;   // latency (sec)
    const double t_t = 0.001;  // �C����ƶǰe�ɶ� (sec)
    const int n = 200000;      // ��Ƶ���
    const int S = 2000;        // buffer �j�p

    cout << "k\tTotal Input Time (sec)\n";
    cout << "---------------------------------\n";
    for (int k = 1; k <= 64; ++k) {
        double t_input = (double(n) * k / S) * (t_s + t_l) + n * t_t;
        cout << setw(2) << k << "\t" << fixed << setprecision(2) << t_input << endl;
    }
    return 0;
}