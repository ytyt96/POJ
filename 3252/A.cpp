#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <cmath>

using namespace std;

vector<vector<long long> > table(40, vector<long long>(40, -1));
map<unsigned, long long> memo;

int num_of_bits(int num) {
    if (num == 0)
        return 1;
    int bits = 0;

    while (num) {
        bits++;
        num /= 2;
    }
    return bits;
}

long long binom(int n, int k) {
    if (n < k)
        return 0;

    long long value = 1;

    int temp = k;
    for (int i = n; i > n - k; i--) {
        value *= i;

        if (temp && value % temp == 0) {
            value /= temp;
            temp--;
        }
    }

    while (temp) {
        value /= temp;
        temp--;
    }

    return value;
}

long long find(int bits, int zero) {
    if (bits < zero)
        return 0;

    if (table[bits][zero] != -1)
        return table[bits][zero];

    long long &value = table[bits][zero];

    value = 0;
    for (int i = zero; i <= bits; i++)
        value += binom(bits, i);
    return value;
}

unsigned last_n_bits(unsigned num, int bits) {
    for (int i = bits; i < 32; i++)
        num &= ~(1 << i);
    return num; 
}

long long solve(unsigned num) {
    if (memo.count(num))
        return memo[num];
    
    if (num <= 1)
        return 1;

    long long &answer = memo[num];

    int bits = num_of_bits(num);
    answer = solve((1 << (bits - 1)) - 1);

    int zero = ceil(bits / 2.0), one = 1;
    for (int i = bits - 1; i >= 1; i--) {
        if (num & (1 << (i - 1)))  {
            answer += find(i - 1, max(0, zero - 1));
            one++;
        }
        else
            zero = max(0, zero - 1);
    }

    if (one <= (bits - one))
        answer++;

    return answer;
}

int main() {
    int start, finish;
    cin >> start >> finish;
    cout << solve(finish) - solve(start - 1) << "\n";
    return 0;
}
