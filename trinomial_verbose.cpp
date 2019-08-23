// Factoring a quadratic trinomial of the form a*x^2 + b*x + c is just a matter of  brute force:
// plugging in the factors of the second degree coefficient a and the factors of the constant c
// and seeing which combinations add up to first degree coefficient b.

#include <iostream>
#include <cmath>
#include <vector>
// #include <cstdlib>

using namespace std;

vector<int> factors(int number, int negative = 0);
int factorTrinomial(int a,int b,int c);

int main()  {
  int a, b, c;
   cout << "To factor quadratic trinomial of the form a*x^2 + b*x + c," << endl;
   do {
     cout << "Input a (>0), b, and c (!=0):" << endl;
     cin >> a >> b >> c;
     } while ( (a <= 0) || (c == 0) );
    factorTrinomial(a, b, c);
    return 0;
}


int factorTrinomial(int a,int b,int c)  {
// factors a polynomial of the form a*x^2 + b*x + c'''
	vector<int> afactors = factors(a,0);
	vector<int> cfactors = factors(c,1);
  char sign = '+';

  int irreducible = 0;

// variables used for "Trial Factorizations and Linear Term"
double a2, c2;

  cout << endl << "We want to find the binomial factors of " << a << "*x^2 + " << b << "*x + " << c;
  cout << endl << "of the form (m*x + p)(n*x + q), where " << endl;
  cout << "m*n = " << a << endl;
  cout << "p*q = " << c << endl;
  cout << "m*q + p*n = " << b;
  cout << endl << endl;

  cout << "The integral factors of " << a << " are {";
  for (int i = 0; i < afactors.size(); i++)   {
       cout << afactors[i];
       if (i < afactors.size() - 1)  {  cout << ", "; }
       else {  cout << "}" << endl << endl; }
   }
   cout << "The integral factors of " << c << " are {";
   for (int i = 0; i < cfactors.size(); i++)   {
        cout << cfactors[i];
        if (i < cfactors.size() - 1)  {  cout << ", "; }
        else {  cout << "}" << endl << endl; }
   }

   cout << "TRIAL FACTORIZATION                   LINEAR TERM" << endl;
   cout << "--------------------------------------------------------------------" << endl;
   for (int i = 1; i <= abs(a); i++)     {
         a2 = double(a)/double(i);
         if ( abs(a2) != int(abs(a2)) )  { continue;}
         if ( a2 < i ) { break; }
         cout << endl << "(m)   (p) (n)    (q)             m*q + n*p = b"  << endl;
        cout << "--------------------------------------------------------------------" << endl;

         for (int j = 1; j <= abs(c); j++)   {
               c2 = double(c)/double(j);
               if ( abs(c2) != int(abs(c2)) )  { continue; }

               cout << "(" << i << "*x + " <<  j  << ") ("
                                 << 	a2 << "*x + " <<   c2 << ")"
                                 << "             ";
                cout <<   i  << "*" << c2  << " + " <<  a2
                                  << "*" << j << " = "
                                  << i * c2 + a2 * j;
                cout << endl;
                // include negative factors of c (-c2 = -c/j, and -j)
                cout << "(" << i << "*x + " <<  -j  << ") ("
                                  << 	a2 << "*x + " <<   -c2 << ")"
                                  << "             ";
                 cout <<   i  << "*" << -c2  << " + " <<  a2
                                   << "*" << -j << " = "
                                   << i * -c2 + a2 * -j;
                 cout << endl;
          } // end inner for loop
     }// end outer for loop

    cout << endl <<  "--------------------------------------------------------------------" << endl;
    cout << "The unique complete factorization is:  ";

     for (int i = 0; i < afactors.size(); i++)     {   // try all the factors of a
           for (int j = 0; j < cfactors.size(); j++)   {  // and all the factors of c
                                                                    // see which combinations add up to b
                    if ( afactors[i] * ( c / cfactors[j] ) + ( a / afactors[i] ) * cfactors[j]  == b )  {

                         if (std::fabs(afactors[i] - 1.0) < 0.00001) {
                              if (afactors[i] > 0)  cout << "(x";
                              else cout << "(-x";
                         }
                         else cout << "(" << afactors[i] << 'x';
                         if (fabs(cfactors[i] - 0.0) < 0.00001) cout << ')';
                         else {
                           if (cfactors[i] < 0) sign = '-';
                           else sign = '+';
                           cout << ' ' << sign << ' ' << std::abs(cfactors[j]) << ')';
                         }
                         if (std::abs(int(a / afactors[i])) == 1) {
                             if (int(a / afactors[i]) > 0)  cout << "(x";
                             else cout << "(-x";
                         }
                         else cout << "(" << int(a / afactors[i]) << 'x';
                         if (int( c / cfactors[j]) == 0) cout << ')';
                         else {
                            if (int( c / cfactors[j]) < 0) sign = '-';
                            else sign = '+';
                            cout << ' ' << sign << ' ' << std::abs(int( c / cfactors[j])) << ')';
                         }
                    cout << endl << endl;
                    return 0;
                  }
           } // end inner for loop
      }// end outer for loop

    /* DEBUG:
      cout << "What happened?" << endl << endl;
      cout << "The integral factors of " << a << " are {";
      for (int i = 0; i < afactors.size(); i++)   {
           cout << afactors[i];
           if (i < afactors.size() - 1)  {  cout << ", "; }
           else {  cout << "}" << endl << endl; }
       }
       cout << "The integral factors of " << c << " are {";
       for (int i = 0; i < cfactors.size(); i++)   {
            cout << cfactors[i];
            if (i < cfactors.size() - 1)  {  cout << ", "; }
            else {  cout << "}" << endl << endl; }
       }
    // end DEBUG  */


    if (irreducible == 0) {  cout << endl << "IRREDUCIBLE" << endl << endl; }
    return 0;
}

vector<int> factors(int n, int neg) {
  // returns a list of the positive and negative factors of a number n'''
	vector<int> factorList;
	n = abs(n);
	for (int i = 1; i <= n; i++)   {
  		if (n % i  == 0)       {   // if n is divisible by i (i divides n)
  			  factorList.push_back(i);   //  i is a factor
          if (neg == 1)  {  factorList.push_back(-i);   }   // so is -i
       }
    }
    return factorList;
}

// a*x^2 + b*x + c = (m*x + p)(n*x + q)
// Given a*x^2 + b*x + c, we want to output the factorization
// in the form (m*x + p)(n*x + q), where
//  m*n = a
// p*q = c
// m*q + n*p = b
