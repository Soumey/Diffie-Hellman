// Diffie-Hellman.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cmath>

using namespace std;

bool PD_prime(long long number);
int modulo(int a, int b, int p);
bool isPrimitiveRoot(int g, int p);


int main()
{
    int identity = 0;
    long long p = 0;
    int g = 0;
    int primeCheck = 0;
    int a, b, A, B;
        
    
    cout << "Welcome to Diffie-Hellman Key Exchange Algorithm\nAre you Bob (1) or Alice(2) ?\n";
    while (identity != 1 || identity != 2)
    {
        cin >> identity;
        //todo 
        //enter P
        // is p prime?
        PD_prime(p);
        while (PD_prime(p) != 1)
        {
            cout << "Enter p (for better security pls enter p as prime number):\n";
            cin >> p;
        }
        //enter g 
        // is g primitive root of modulo p?
        cout << "Enter g (remember that g needs to be primitive root modulo p):\n";
        cin >> g;
        while (isPrimitiveRoot(g,p) != 1)
        {
            cout << "g is not primitive root modulo p, reenter the value.\n";
            cin >> g;
        }

        if (identity == 1)
        {
            cout << "Enter Bob's secret" << endl;

            //read bobs secret as b
            cin >> b;
            //calculate B = g^b mod p
            B = modulo(g, b, p);
            cout << "Bob's public :"<<B << endl;
            // get A from diff debug
            cout << "What's Alice public (A)?" << endl;
            cin >> A;
            //Bob computes S
           
            cout << "Shared secret equals : " << modulo(A, b, p) << endl;
            //s=A^b mod p = result
        }
        else if (identity == 2)
        {
            cout << "Enter Alice's secret" << endl;
            //read Alice secret as a
            cin >> a;
           //calculate A = g^a mod p
            A = modulo(g, a, p);
            cout << "Alice's public :" << A << endl;
           // get B from diff debug
            cout << "What's Bob public (B)?" << endl;
            cin >> B;
            //alice computes S
            cout << "Shared secret equals : " << modulo(B, a, p) << endl;
            //s=B^a mod p = result

        }
        return 0;

    }
}

bool PD_prime(long long number) {
    if (number <= 1) return false; // 1 is not prime
    if (number <= 3) return true; // 2 and 3 is prime
    if (number % 2 == 0 || number % 3 == 0) return false; // if can be divided by 2 or 3 it isnt prime
    long long i = 5;
    while (i * i <= number)
    {
        if (number % i == 0 || number % (i + 2) == 0)
        {
            return false;
        }
        i += 6;
        // 6 because every prime number >3 is equal to either 6k+1 or 6k-1, where k is natural number
        // it gives us numbers from 5 like 5,7,11,13 and so on...
        //
    }
    return true;
}

int modulo(int a, int b, int p) {
    int result = 1;
    a = a % p;

    while (b > 0) {
        if (b % 2 == 1) {
            result = (result * a) % p;
        }
        b = b / 2;
        a = (a * a) % p;
    }

    return result;
}

bool isPrimitiveRoot(int g, int p) {
    // Check if g^i is congruent to any power of g mod p
    for (int i = 1; i < p - 1; i++) {
        int exp = modulo(g, i, p);
        if (exp == 1) {
            return false;
        }
    }

    // Check if g^phi(p) is congruent to 1 mod p
    int phi = p - 1;
    for (int i = 2; i * i <= phi; i++) {
        if (phi % i == 0) {
            if (modulo(g, i, p) == 1 || modulo(g, phi / i, p) == 1) {
                return false;
            }
        }
    }

    return true;
}
