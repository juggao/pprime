#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

/* Check if string is a palindrome */
bool isPalindrome(const string& s) {
    return equal(s.begin(), s.begin() + s.size()/2, s.rbegin());
}

/* Modular exponentiation */
cpp_int modpow(cpp_int base, cpp_int exp, const cpp_int& mod) {
    cpp_int result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

/* Miller–Rabin primality test */
bool isPrime(const cpp_int& n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0) return false;

    // write n-1 = d * 2^s
    cpp_int d = n - 1;
    unsigned int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }

    // Deterministic bases sufficient for large integers
    static const int bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

    for (int a : bases) {
        if (a >= n) continue;
        cpp_int x = modpow(a, d, n);
        if (x == 1 || x == n - 1) continue;

        bool composite = true;
        for (unsigned int r = 1; r < s; ++r) {
            x = (x * x) % n;
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

int main() {
    vector<string> seq = {
        "2",
        "30203",
        "133020331",
        "1713302033171",
        "12171330203317121",
        "151217133020331712151",
        "1815121713302033171215181",
        "16181512171330203317121518161",
        "331618151217133020331712151816133",
        "9333161815121713302033171215181613339",
        "11933316181512171330203317121518161333911"
    };

    for (const auto& s : seq) {
        cpp_int n(s);
        bool pal = isPalindrome(s);
        bool prime = isPrime(n);

        cout << s << "\n";
        cout << "  Palindrome: " << (pal ? "YES" : "NO") << "\n";
        cout << "  Prime:      " << (prime ? "YES" : "NO") << "\n\n";
    }

    return 0;
}

