// g++ -g completesquare.cpp -std=c++11 -o cts
// Need -std=c++11 for std::to_String()
/*
 * update: Version 3 attempts to beautify (simplify)
 * 30 June 2019
 * using struct fraction, and doing addition and simplifying
 * with Brute Force: added printFraction(ostream* os, const double)
 * to print rational coefficients, reducing with rat_0_1
 */

#include<iostream>
#include<cstdlib>
#include<cmath> // for sqrt() function
#include<string>

struct fraction {
	int n;
	int d;
	fraction(int n, int d) {
		this->n = n;
		this->d = d;
	}
	double asDecimal() {
		return double((double)n/(double)d);
	}
};

std::string simplifyRadical(int radicand);

template<class T>
int completeSquare(T a, T b, T c);

int gcd(int a, int b);
int lcm(int a, int b);
std::ostream &printFraction(std::ostream* os, const double target);


int main() {
  double a,b,c;
  std::cout << "a*x^2 + b*x + c = 0\n\n";
  std::cout << "Enter a, b, c (a>0) :\n";
  std::cin >> a >> b >> c;
  completeSquare(a,b,c);

//std::cout << "\nTesting simplifyRadical(144) : " << simplifyRadical(144) << std::endl;
//std::cout << "\nTesting simplifyRadical(160) : " << simplifyRadical(160) << std::endl;
  return 0;
}

template<class T>
int completeSquare(T a, T b, T c)
{

  double d = (b*b) - (4*a*c);
  std::cout << "\nQuadratic Equation:  (" << a << ")*x^2 + ("
                 << b << ")*x + (" << c << ") = 0\n\n";

if (a > 1)  {
    std::cout << "Divide through by " << a;
    std::cout <<  "\nx^2 + (" << b << "/" << a << ")*x + (" << c << "/" << a << ") = 0";
    std::cout <<  "\nx^2 + (" << b << "/" << a << ")*x =  (" << -c << "/" << a << ")\n";
}
  std::cout << "-----------------------------------------------------------\n";
  std::cout << "Complete the square : \n";
  /************************************************************************
  * THE INJECTION OF rat_0_1:
  ***********************************************************************/

  std::cout << "\nx^2 + (" << b << "/" << a << ")*x + (" << b << "/" << 2*a
                 << ")^2  =  (" << -c << "/" << a << ") + (" << b << "/" << 2*a
                                << ")^2\n";

 std::cout << "\nx^2 + (";
 printFraction(&std::cout, (double)b/(double)a);
 std::cout << ")*x + (";
 printFraction(&std::cout, (double)b/(double)2*a);
 std::cout << ")^2  =  (";
 printFraction(&std::cout, (double)-c/(double)a);
 std::cout << ") + (";
 printFraction(&std::cout, (double)b/(double)2*a);
 std::cout << ")^2\n";
/* replace:
std::cout << " [ x + (" << b << "/" << (2*a) << ") ]^2 =  (" << -c << "/" << a << ") + (" << b*b
                << "/" << 4*a*a << ")\n";
std::cout << " [ x + (" << b << "/" << (2*a) << ") ]^2 =  (" << d << "/" << (4*a*a) << ")\n";
with:
*/
std::cout << "-----------------------------------------------------------\n";

std::cout << " [ x + (";
printFraction(&std::cout, (double)b/(double)(2*a));
std::cout << ") ]^2 =  (";
printFraction(&std::cout, (double)(-c)/(double)a);
std::cout << ") + (";
printFraction(&std::cout, (double)(b*b) / (double)(4*a*a));
std::cout << ")\n";
std::cout << " [ x + (";
printFraction(&std::cout, (double)b/(double)(2*a));
std::cout << ") ]^2 =  (";
printFraction(&std::cout, (double)d/(double)(4*a*a));
std::cout << ")\n";
std::cout << "-----------------------------------------------------------\n";

if (d < 0)
{
  std::cout << "\nSince the square of a real number must be a nonnegative real number,\n ";
  std::cout << "the equation, (" << a << ")*x^2 + (" << b << ")*x + (" << c << ") = 0 \n";
  std::cout << "has no real-number solution.\n";
  std::cout << "\nRoots are Complex (not real-numbers) : ";
  double r = sqrt(-d);
  double r1 = -double(b)/(2*a);
  double r2 = r/(2*a);
  std::cout << "\nReal Part : " << r1;
  std::cout << "\nImaginary Part : " << r2;
  std::cout << "\n\nThus, extending the replacement set of the variable to include\n ";
  std::cout << "imaginary numbers, we can write the COMPLEX solution set as :\n\n";
  std::cout << "{ " << r1 << " + " << r2 << "i, " << r1 << " - " << r2 << "i }\n";

  // Test out simplifyRadical with Complex results (just for the hell of it)
  std::cout << "\nAn attempt to represent EXACT COMPLEX SOLUTIONS:\n";
  std::string str = simplifyRadical(-d);
  std::cout << " \nx = [" << -b << " + " << str << " i ] / " << 2*a;
  std::cout << " \nx = [" << -b << " -  " << str << " i ] / " << 2*a;

  std::cout << "\n\nReal Part : " << -b << '/' << 2*a;
  std::cout << "\nImaginary Part : " << "[+/-] " << str << '/' << 2*a;

   if (str.find("*") != std::string::npos)  {
     int w = std::stoi( str.substr(0, str.find("*")) );
     //std::cout << "\nw from string is " << w << "\n\n";
     int g = abs( gcd(2*a, gcd(b, w)) );
     std::cout << "\n\ngcd(" << 2*a << ", gcd(" << b << ", " << w << ")) = " << g << "\n\n";
     std::cout << "\n-----------------------------------------------------------\n";

     // Divide through by greatest common divisor
     std::cout << "Reducing to lowest terms : \n";
     if (2*a/g != 1)  {
          std::cout << " \nx = [" << -b/g << " + " << simplifyRadical(-d/(g*g))  << " i ] / " << (2*a)/g;
          std::cout << " \nx = [" << -b/g << " -  " << simplifyRadical(-d/(g*g)) << " i ] / " <<(2*a)/g;
     }
     else {
        std::cout << " \nx = " << -b/g << " + " << simplifyRadical(-d/(g*g))  << " i";
        std::cout << " \nx = " << -b/g << " -  " << simplifyRadical(-d/(g*g)) << " i";
     }
     std::cout << std::endl;
   }
   else {
     int g = abs( gcd(2*a, b));
     std::cout << "\n\ngcd(" << 2*a << ", " << b << ") = " << g << "\n\n";
     std::cout << "\n-----------------------------------------------------------\n";

     // Divide through by greatest common divisor
     std::cout << "Reducing to lowest terms : \n";
     if (2*a/g != 1)  {
          std::cout << " \nx = [" << -b/g << " + " << simplifyRadical(-d/(g*g))
                    << " i ] / " << (2*a)/g;
          std::cout << " \nx = [" << -b/g << " -  " << simplifyRadical(-d/(g*g))
                    << " i ] / " <<(2*a)/g;
     }
     else {
        std::cout << " \nx = " << -b/g << " + " << simplifyRadical(-d/(g*g))  << " i";
        std::cout << " \nx = " << -b/g << " -  " << simplifyRadical(-d/(g*g)) << " i";
     }
     std::cout << std::endl;
   }
   std::cout << std::endl << std::endl;
}
else if (d == 0) {
  std::cout << "\nThere is only one root, called a double root: " << -b/(2*a);
  std::cout << std::endl;
}
else if (d > 0)  {
  std::cout << " x + (";
  printFraction(&std::cout, (double)b/(double)(2*a));
  std::cout << ")  =  +- sqrt(";
  printFraction(&std::cout, (double)d/(double)(4*a*a));
  std::cout << ")\n";
  std::cout << "\n\nThere are two different real roots of the equation,  \n("
            << a << ")*x^2 + (" << b << ")*x + (" << c << ") = 0 \n\n";
  std::cout << " x = (";
  printFraction(&std::cout, (double)(-b)/(double)(2*a));
  std::cout << ") +/- sqrt(";
  printFraction(&std::cout, (double)d/(double)(4*a*a));
  std::cout << ")\n";
  std::cout << " x = (";
  printFraction(&std::cout, (double)(-b)/(double)(2*a));
  std::cout << ") +/- [(" << simplifyRadical(d) << ") / " << 2*a << "]";
  std::cout << " \nx = [" << -b << " +/- ("
            << simplifyRadical(d) << ") ]  / " << 2*a;

  std::string str = simplifyRadical(d);
  std::cout << " \n\nx = [" << -b << " + " << str << "] / " << 2*a;
  std::cout << " \nx = [" << -b << " -  " << str << "] / " << 2*a;

 if (str.find("*") != std::string::npos)  {
   int w = std::stoi( str.substr(0, str.find("*")) );
  // std::cout << "\nw from string is " << w << "\n\n";
   int g = abs( gcd(2*a, gcd(b, w)) );
  std::cout << "\n\ngcd(" << 2*a << ", gcd(" << b << ", " << w << ")) = "
            << g << "\n\n";
  std::cout << "\n-----------------------------------------------------------\n";

   // Divide through by greatest common divisor
   std::cout << "Reducing to lowest terms : \n";
   std::cout << " \nx = [" << -b/g << " + " << simplifyRadical(d/(g*g))  << "] / " << (2*a)/g;
   std::cout << " \nx = [" << -b/g << " -  " << simplifyRadical(d/(g*g)) << "] / " <<(2*a)/g;
 }
 else {
  int g = abs( gcd(2*a, b) );
  std::cout << "\n\ngcd(" << 2*a << ", " << b << ") = " << g << "\n\n";
  std::cout << "\n-----------------------------------------------------------\n";

   // Divide through by greatest common divisor
   std::cout << "Reducing to lowest terms : \n";
   if (2*a/g != 1)  {
      std::cout << " \nx = [" << -b/g << " + " << simplifyRadical(d/(g*g))
                << "] / " << (2*a)/g;
      std::cout << " \nx = [" << -b/g << " -  " << simplifyRadical(d/(g*g))
                << "] / " <<(2*a)/g;
   }
   else {
      std::cout << " \nx = " << -b/g << " + " << simplifyRadical(d/(g*g));
      std::cout << " \nx = " << -b/g << " -  " << simplifyRadical(d/(g*g));
   }
 }
  std::cout << "\n\nThe decimal representation of the two solutions are :\n";
  std::cout << "Root 1:  x = " << -b/(2*a)  + sqrt(d /(4*a*a)) << "\n";
  std::cout << "Root 2:  x = " << -b/(2*a)  - sqrt(d /(4*a*a)) << "\n";
}
  return 0;
}
int gcd(int a, int b)    {
  int t;
  while (a)
    {
      t = a;
      a = b%a;
      b = t;
    }
  return b;
}

int lcm(int a, int b)
{
    return (a / gcd(a, b)) * b;
}

// Reducing radicals to simplest terms for posterity
std::string simplifyRadical(int radicand)  {

  int factor = 316; // 31^2 = 961; 316^2 = 99856
  while ( radicand%(factor*factor) != 0 )  {
    factor -= 1;
  }
  int r = radicand/(factor*factor);
  std::string reduced = "";

  if ( (factor > 1) && (r != 1) )  {
    reduced.append(std::to_string(factor) + "*");
//    reduced.append("*");
  }
  if (r == 1)  {  reduced.append(std::to_string(factor));  }
  else {
      reduced.append("sqrt(" + std::to_string(r) + ")");
  }
  return reduced;
}

// Explanation of rat_0_1:
// N: largest acceptable denominator
/******************************************************************
 * The idea is to start with two fractions, a/b = 0/1 and c/d = 1/1.
 * We update either a/b or c/d at each step so that a/b will be the
 * best lower bound of x with denominator no bigger than b,
 * and c/d will be the best upper bound with denominator no bigger
 * than d.
 *
 * At each step we do a sort of binary search by introducing
 * the mediant of the upper and lower bounds.
 * The mediant of a/b and c/d is the fraction (a+c)/(b+d)
 * which always lies between a/b and c/d.
******************************************************************/
fraction rat_0_1(double x, int N)   {
     int a = 0;
     int b = 1;
     int c = 1;
     int d = 1;
     double mediant;

     while ( (b <= N) && (d <= N) )  {
         mediant = (double)((double)a + (double)c)/((double)b + (double)d);
         if (x == mediant)   {
             if (b + d <= N)  return fraction(a + c, b + d);
             else {
               if (d > b)  return fraction(c, d);
               else return fraction(a, b);
             }
        }
         else {
           if  (x > mediant) {
              a += c;
              b += d;
           }
           else {
              c += a;
              d += b;
           }
         }
     }
     if (b > N)  return fraction(c, d);
     else  return fraction(a, b);
}

std::ostream &printFraction(std::ostream* os, const double target)  {
  // This does a combination of what Fraction constructor (double)
  // does along with the overloaded >>operator
  // Of extreme significance *os rather than &os, const doubl, not &double;
  // then, when calling the ostream, printFraction(&std::cout, (double))
  int MAX_DENOMINATOR = 500;
  double d = target - std::floor(target);
  fraction f = rat_0_1(d, MAX_DENOMINATOR);
  fraction g = fraction(std::floor(target), 1);
  int lcd = lcm(f.d, g.d);
  int quot1 = lcd/f.d;
  int quot2 = lcd/g.d;
  //    fract.set(num * quot1 + other.num * quot2, lcd);
  int numerator = f.n * quot1 + g.n * quot2;
  int denominator = lcd;

  if (numerator == 0) *os << 0;
  else {
    if (denominator == 1) *os << numerator;
    else *os << numerator << "/" << denominator;
  }
  return *os;
}
