#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
#include <string>
#include <cstring>

using namespace std;

string to_str(int num) {
    string ret;
    if (num == 0)
        return "0";
    while (num > 0) {
        ret = (char)('0' + (num % 10)) + ret;
        num /= 10;
    }
    return ret;
}

int strtoi(const string &st) {
    int num = 0;
    for (int i = 0; i < st.size(); i++)
        num = num * 10 + (st[i] - '0');
    return num;
}

map<string, vector<long long> > memo;

vector<long long> operator +(const vector<long long> &lhs, const vector<long long> &rhs) {
    vector<long long> ret(10);
    for (int i = 0; i < 10; i++)
        ret[i] = lhs[i] + rhs[i];
    return ret;
}

vector<long long> operator -(const vector<long long> &lhs, const vector<long long> &rhs) {
    vector<long long> ret(10);
    for (int i = 0; i < 10; i++)
        ret[i] = lhs[i] - rhs[i];
    return ret;
}

vector<long long> solve(string num) {
    if (num[0] == '-')
        return vector<long long>(10);

    if (num.size() == 1) {
        vector<long long> ret(10, 0);
        for (int i = 0; i <= num[0] - '0'; i++)
            ret[i] = 1;
        return ret;
    }

    if (memo.count(num))
        return memo[num];
    
    vector<long long> & value = memo[num];
    value.assign(10, 0);

    vector<long long> sub = solve(to_str((int)pow(10, num.size() - 1) - 1));
    value = sub; 
    vector<long long> reg = sub;

    for (int i = 1; i < num.size() - 1; i++) {
        int temp;
        if (i == 1)
            temp = 10;
        else
            temp = pow(10, i) - pow(10, i - 1);
        reg[0] += (num.size() - 1 - i) * temp;
    }

    for (int i = 1; i < (num[0] - '0'); i++) {
        value = value + reg;
        value[i] += pow(10, num.size() - 1);
    }

    int subnum = strtoi(num.substr(1));
    string substr = to_str(subnum);

    
    value[num[0] - '0'] += subnum + 1;
    value = value + solve(substr);

    while (subnum >= 0) {
        int temp;
        if (subnum < 10)
            temp = subnum + 1;
        else
            temp = (subnum - pow(10, substr.size() - 1)) + 1;

        value[0] += temp * (num.size() - substr.size() - 1);
        if (subnum < 10)
            break;
        else
            subnum = pow(10, substr.size() - 1) - 1;
        substr = to_str(subnum);
    }

    return value;
}
    
int main() {
    int a, b;
    while (cin >> a >> b && a) {
        if (a > b)
            swap(a, b);
        vector<long long> ans = solve(to_str(b)) - solve(to_str(a - 1)); 
        cout << ans[0];
        for (int i = 1; i < 10; i++)
            cout << " " << ans[i];
        cout << "\n";
    }

    return 0;
}
