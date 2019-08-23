// g++ -g completesquare.cpp -std=c++11 -o cts
// Need -std=c++11 for std::to_String()

#include<iostream>
#include<cstdlib>
#include<cmath> // for sqrt() function
#include<string>

std::string simplifyRadical(int radicand);

template<class T>
int completeSquare(T a, T b, T c);

int gcd(int a, int b);

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
  std::cout << "\nx^2 + (" << b << "/" << a << ")*x + (" << b << "/" << 2*a
                 << ")^2  =  (" << -c << "/" << a << ") + (" << b << "/" << 2*a
                                << ")^2\n";
  std::cout << " [ x + (" << b << "/" << (2*a) << ") ]^2 =  (" << -c << "/" << a << ") + (" << b*b
                << "/" << 4*a*a << ")\n";
std::cout << " [ x + (" << b << "/" << (2*a) << ") ]^2 =  (" << d << "/" << (4*a*a) << ")\n";
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
          std::cout << " \nx = [" << -b/g << " + " << simplifyRadical(-d/(g*g))  << " i ] / " << (2*a)/g;
          std::cout << " \nx = [" << -b/g << " -  " << simplifyRadical(-d/(g*g)) << " i ] / " <<(2*a)/g;
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
  std::cout << " x + (" << b << "/" << (2*a) << ")  =  +- sqrt(" << d << "/" << (4*a*a) << ")\n";
  std::cout << "\n\nThere are two different real roots of the equation,  \n("
                << a << ")*x^2 + (" << b << ")*x + (" << c << ") = 0 \n\n";
  std::cout << " x = (" << -b << "/" << (2*a) << ") +/- sqrt(" << d << "/" << (4*a*a) << ")\n";
  std::cout << " x = (" << -b << "/" << (2*a) << ") +/- [sqrt(" << d << ") / " << 2*a << "]";
  std::cout << " \nx = [" << -b << " +/- sqrt(" << d << ") ]  / " << 2*a;

  std::string str = simplifyRadical(d);
  std::cout << " \n\nx = [" << -b << " + " << str << "] / " << 2*a;
  std::cout << " \nx = [" << -b << " -  " << str << "] / " << 2*a;

 if (str.find("*") != std::string::npos)  {
   int w = std::stoi( str.substr(0, str.find("*")) );
  // std::cout << "\nw from string is " << w << "\n\n";
   int g = abs( gcd(2*a, gcd(b, w)) );
  std::cout << "\n\ngcd(" << 2*a << ", gcd(" << b << ", " << w << ")) = " << g << "\n\n";
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
      std::cout << " \nx = [" << -b/g << " + " << simplifyRadical(d/(g*g))  << "] / " << (2*a)/g;
      std::cout << " \nx = [" << -b/g << " -  " << simplifyRadical(d/(g*g)) << "] / " <<(2*a)/g;
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

/*  std::cout << "\n\nPess <ENTER> to exit.\n";
  std::cin.ignore().get();  // Pause Command for Linux Terminal
  */
  return 0;
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
