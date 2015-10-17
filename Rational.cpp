/*
Created 17 October 2015
Author : Ahmed Ashraf Gamal
Notes : 
-This is a prototype for a college assignment.
-Supports negative fractions as well.
-Initially and after any operation the fraction is reduced to it's lowest terms.
-Supports (+,-,*,/,>=,<=,<,>,==) operators.
-Supports taking fraction as input using standard input (e.g. cin) in one of the following formats :
"(X)" or "X" or "(X/Y)" or "X/Y" or even "(X/Y" if you forgot the closing brace :D.
-Supports outputing the fraction using standard output (e.g. cout).
*/
#include <bits/stdc++.h>
using namespace std;
#define FOR(i,n) for (int i = 0; i < (int)(n); i++)
#define RFOR(i,x,n) for (int i = (x); i <= (int)(n); i++)
#define take(n) scanf("%d",&n)
#define take2(n,m) scanf("%d%d",&n,&m)
#define take3(n,m,k) scanf("%d%d%d",&n,&m,&k)
#define takell(n) scanf("%lld",&n)
#define takes(n) scanf("%s",n)
#define takef(n) scanf("%lf",&n)
#define ii pair <int,int>
#define is pair <int,string>
#define pdd pair <double,double>
#define ll long long
#define LSB(x) (x & (-x))
#define N 50010
#define vi vector <int>
#define iv pair <int,vi>
#define pss pair <string,string>
#define vll vector <ll>
#define all(v) v.begin(),v.end()
#define MOD 1000000007
#define read(s) freopen(s,"r",stdin)
#define left(x) (2*x)
#define right(x) (2*x+1)

class Rational{
private:
	int a,b;
public:
	Rational(int,int); //constructor working for N & D, N only, or none
	int getN(); //get numerator
	int getD(); //get denominator
	void setN(int); //set numerator
	void setD(int); //set denominator
	void displayMixed(); //display as mixed fraction
	void reduce(); //reduce fraction
	void invert(); //swap N & D
	friend Rational operator +(const Rational&,const Rational&); //r3 = r1 + r2;
	friend Rational operator -(const Rational&,const Rational&);
	friend Rational operator *(const Rational&,const Rational&);
	friend Rational operator /(const Rational&,const Rational&);
	friend bool operator <(const Rational&,const Rational&);
	friend bool operator >(const Rational&,const Rational&);
	friend bool operator >=(const Rational&,const Rational&);
	friend bool operator <=(const Rational&,const Rational&);
	friend bool operator ==(const Rational&,const Rational&);
	friend ostream& operator <<(ostream&,const Rational&); //cout << r1;
	friend istream& operator >>(istream&,Rational&);
	//cin >> r1; (accepts input in format) -> "(X)" or "X" or "(X/Y)" or "X/Y" or even "(X/Y" if you forgot the closing brace :D
	//(X & Y can be negative integers).
};
int GCD(int x,int y){
	return (y == 0? x : GCD(y,x%y));
}
int LCM(int x,int y){
	return x*(y/GCD(x,y));
}
Rational::Rational(int x = 0,int y = 1){
	if (y == 0)
		throw std::overflow_error("The Dominator can't be a zero!");
	a = x;
	b = y;
	reduce();
}
int Rational::getN(){
	return a;
}
int Rational::getD(){
	return b;
}
void Rational::setN(int x){
	a = x;
	reduce();
}
void Rational::setD(int x){
	b = x;
	reduce();
}
void Rational::displayMixed(){
	if (b == 1)
		cout << *this << "\n";
	else{
		if (a > b)
			cout << a/b << " + " << a%b << "/" << b << "\n";
		else
			cout << *this << "\n";
	}
}
void Rational::reduce(){
	int g = GCD(abs(a),abs(b));
	a /= g;
	b /= g;
	if (b < 0)
		a *= -1, b *= -1;
}
void Rational::invert(){
	a += b;
	b = a - b;
	reduce();
}
Rational SolveLinear(){ //takes input in format rX"sign"r=r where r = rational number of any of the above formats and the sign can be (+,-)
	Rational r1,r2,r3;
	char c,C;
	cin >> r1 >> c >> C >> r2 >> c >> r3;
	r2 = r2 * (-1*(C == '-'));
	return (r3-r2)/r1;
}
Rational SolveLinear(Rational r1,Rational r2,Rational r3){ //solves linear equation with given parameters.
	return (r3-r2)/r1;
}
Rational operator +(const Rational& r1,const Rational& r2){
	int x1,y1,x2,y2,NM,D;
	x1 = r1.a; y1 = r1.b; x2 = r2.a; y2 = r2.b;
	D = LCM(abs(y1),abs(y2));
	NM = x1*(D/y1) + x2*(D/y2);
	Rational tmp(NM,D);
	return tmp;
}
Rational operator -(const Rational& r1,const Rational& r2){
	int x1,y1,x2,y2,NM,D;
	x1 = r1.a; y1 = r1.b; x2 = r2.a; y2 = r2.b;
	D = LCM(abs(y1),abs(y2));
	NM = x1*(D/y1) - x2*(D/y2);
	Rational tmp(NM,D);
	return tmp;
}
Rational operator *(const Rational& r1,const Rational& r2){
	int NM,D;
	NM = r1.a * r2.a;
	D = r1.b * r2.b;
	Rational tmp(NM,D);
	return tmp;
}
Rational operator /(const Rational& r1,const Rational& r2){
	if (r2.a == 0)
		throw std::overflow_error("Can't divide by zero!");
	int NM,D;
	NM = r1.a * r2.b;
	D = r1.b * r2.a;
	Rational tmp(NM,D);
	return tmp;
}
bool operator <(const Rational& r1,const Rational& r2){
	if (r1.a*r2.b < r2.a*r1.b)
		return true;
	else
		return false;
}
bool operator <=(const Rational& r1,const Rational& r2){
	if (r1.a*r2.b <= r2.a*r1.b)
		return true;
	else
		return false;
}
bool operator >(const Rational& r1,const Rational& r2){
	if (r1.a*r2.b > r2.a*r1.b)
		return true;
	else
		return false;
}
bool operator >=(const Rational& r1,const Rational& r2){
	if (r1.a*r2.b >= r2.a*r1.b)
		return true;
	else
		return false;
}
bool operator ==(const Rational& r1,const Rational& r2){
	if (r1.a*r2.b == r2.a*r1.b)
		return true;
	else
		return false;
}
ostream& operator <<(ostream& out,const Rational& r){
	out << r.a;
	if (r.b != 1)
		out << "/" << r.b;
	return out;
}
istream& operator >>(istream& in,Rational& r){
	int x,y = 1;
	char c;
	in >> c;
	bool b = true;
	if (c != '('){
		in.putback(c);
		b = false;
	}
	in >> x;
	if (in.peek() != '\n'){
		in >> c;
		if (c == '/')
			in >> y;
		else
			in.putback(c);
		if (b){
			in >> c;
			if (c != ')')
				in.putback(c);
		}
	}
	r.a = x;
	r.b = y;
	r.reduce();
	return in;
}

int main(){
	//read("in.txt");
	Rational r1,r2;
	cin >> r1 >> r2;
	cout << r1 << "\n";
	cout << r2 << "\n";
	cout << r1 + r2 << "\n";
	cout << r1 - r2 << "\n";
	cout << r1 * r2 << "\n";
	cout << r1 / r2 << "\n";
	cout << SolveLinear() << "\n";
}
