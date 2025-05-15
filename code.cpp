#include <bits/stdc++.h>
using namespace std;

template <typename T>
bool isZero(const T& val) {
    // For floating point types
    if (std::is_floating_point<T>::value) {
        const long double EPS = 1e-9;
        return std::abs(val) < EPS;
    } 
    return val == static_cast<T>(0);
}

class Complex{
    private:
        long long int real;
        long long int img;
    public:
        Complex() { real = 0; img = 0; }
        Complex (int i){
            real=i;img=0;
        }
        Complex(long long r,long long i){
            real=r;img=i;
        }
        //will have all + - * operators that are necessary
        Complex operator-(Complex c2){
            Complex cmp(real-(c2.real),img-(c2.img));
            return cmp;
        }
        Complex operator-(){
            Complex c(-real,-img);
            return c;
        }
        Complex operator+(Complex c2){
            Complex c(real+c2.real,img+c2.img);
            return c;
        }
        Complex operator*(Complex c2) {
            // Correct formula: (a+bi)*(c+di) = (ac - bd) + (ad + bc)i
            Complex c((real * c2.real) - (img * c2.img),
                      (real * c2.img) + (img * c2.real));
            return c;
        }        
        friend ostream& operator<<(ostream& stream,Complex &c);
        friend istream& operator>>(istream& stream,Complex &c);
        friend bool isZero<Complex>(const Complex& val);
        //we will also implement cin and cout
};

ostream& operator<<(ostream& stream,Complex &c) {
    stream <<c.real<<" "<<c.img;
    return stream;
}
istream& operator>>(istream& stream,Complex &c) {
    stream >> c.real>>c.img;
    return stream;
}

template <>
bool isZero<Complex>(const Complex& val) {
    return (val.real == 0 && val.img == 0);
}

template <typename TYPE>
class Differentiate;

template <typename TYPE>
class Evaluation;

template <typename TYPE>
class Multiplication;

template <typename TYPE>
class Polynomial{
    private:
        vector<TYPE> arr;
        int deg;
    public:
        //constructor
        Polynomial(){
            // do nothing
        }
        Polynomial(int sz,string s){
            arr.resize(sz);
            deg=sz;
        }
        Polynomial(int sz){
            deg=sz;
            arr.resize(sz,0);
        }
        Polynomial(int sz,int init){
            deg=sz;
            arr.resize(sz);
            for(int i=0;i<sz;i++){arr[i]=init;}
        }
        void takeinput(){
            for(int i=0;i<deg;i++){
                cin>>arr[i];
            }
        }
        void add_term(int index,TYPE val){
            arr[index]=val;
        }
        void printpoly() {
            int j = arr.size();
            // Find the last non-zero coefficient
            for(int i=arr.size()-1;i>=0;i--){
                if(isZero(arr[i])){
                    j=i;
                }
                else{
                    break;
                }
            }
            // Print coefficients up to the last non-zero term
            for (int i = 0; i < j; i++) {
                if (typeid(arr[i]) == typeid(long double)) {
                    cout << setiosflags(ios::fixed) << setprecision(6) << arr[i] << " ";
                } else {
                    cout << arr[i] << " ";
                }
            }
            cout << endl;
        }
        Polynomial operator+(const Polynomial &p2) const {
            size_t n = max(arr.size(), p2.arr.size());
            Polynomial result(n);
            for (size_t i = 0; i < n; ++i) {
                TYPE a = i < arr.size() ? arr[i] : 0;
                TYPE b = i < p2.arr.size() ? p2.arr[i] : 0;
                result.arr[i] = a + b;
            }
            return result;
        }
        Polynomial operator-(const Polynomial &p2) const {
            size_t n = max(arr.size(), p2.arr.size());
            Polynomial result(n);
            for (size_t i = 0; i < n; ++i) {
                TYPE a = i < arr.size() ? arr[i] : 0;
                TYPE b = i < p2.arr.size() ? p2.arr[i] : 0;
                result.arr[i] = a - b;
            }
            return result;
        }
        Polynomial<TYPE> shiftbyN(int n){
            Polynomial<TYPE> ans(n+arr.size(),0);
            for(int i=0;i<arr.size();i++){
                ans.arr[i+n]=arr[i];
            }
            return ans;
        }
    friend class Multiplication<TYPE>;
    friend class Evaluation<TYPE>;
    friend class Differentiate<TYPE>;
};

template <typename TYPE>
class Multiplication{
    private:
        Polynomial<TYPE> p;
    public:
        Multiplication(){
            //do nothing
        }
        Multiplication(Polynomial<TYPE> a1){
            p=a1;
        }
        void operator*(Polynomial<TYPE> p1){
            //will perform Karastuba Algorithm and PRINT THE ANSWER
            //array of type
            //we will make the arr.size()ree to 16
            int m=p.arr.size();
            int n=p1.arr.size();
            p.arr.resize(16,0);
            for(int i=p.arr.size();i<16;i++){
                p.arr[i]=0;
            }
            p1.arr.resize(16,0);
            for(int i=p.arr.size();i<16;i++){
                p1.arr[i]=0;
            }
            Polynomial<TYPE> ans=recur(p,p1);
            vector<TYPE> arr=ans.arr;
            for (int i=0;i<m+n-1;i++) {
                if (typeid(arr[i]) == typeid(long double)) {
                    cout << setiosflags(ios::fixed) << setprecision(6) << arr[i] << " ";
                } else {
                    cout << arr[i] << " ";
                }
            }
            cout << endl;
            return;
        }
        Polynomial<TYPE> recur(Polynomial<TYPE> p1,Polynomial<TYPE> p2){
            if(p1.arr.size()==1){
                Polynomial<TYPE> base(1);
                base.arr[0]=p1.arr[0]*p2.arr[0];
                return base;
            }
            //recursive case
            int n=p1.arr.size()/2;
            Polynomial<TYPE> A0(n);
            for(int i=0;i<n;i++){A0.arr[i]=p1.arr[i];}
            Polynomial<TYPE> A1(p1.arr.size()-n);
            for(int i=0;i<A1.arr.size();i++){A1.arr[i]=p1.arr[i+n];}
            n=p2.arr.size()/2;
            Polynomial<TYPE> B0(n);
            for(int i=0;i<n;i++){B0.arr[i]=p2.arr[i];}
            Polynomial<TYPE> B1(p2.arr.size()-n);
            for(int i=0;i<B1.arr.size();i++){B1.arr[i]=p2.arr[i+n];}
            Polynomial<TYPE> T1=recur(A0,B0);
            Polynomial<TYPE> T2=recur(A1,B1);
            Polynomial<TYPE> T3=recur(A0+A1,B0+B1);
            Polynomial<TYPE> T4=T3-(T1+T2);
            // our ans will be t1+ t4* x power n/2 + t2 *x power n;
            Polynomial<TYPE> ans(2*n);      //size will be 2*n
            return T1 + T4.shiftbyN(n) + T2.shiftbyN(2 * n);
        }
};


template <typename TYPE>
class Evaluation{
    private:
    Polynomial<TYPE> p;
        long long x;
    public:
        Evaluation(){
            //do nothing
        }
        Evaluation(Polynomial<TYPE> pol,long long num){
            p=pol;
            x=num;
        }
        void evaluate(){
            //we have to print the valueof evaluation
            TYPE ans=0;
            for(int i=0;i<p.arr.size();i++){
                ans=ans+(p.arr[i]*pow(x,i));
            }
            if(typeid(ans) == typeid(long double)) { 
                cout << setiosflags(ios::fixed) << setprecision(6) << ans <<endl;
            } 
            else { 
                cout << ans <<endl;
            }
        }
};

void caseString(vector<string> arr,long long x){
    string s="";
    for(int i=arr.size()-1;i>=0;i--){
        long long times=pow(x,i);
        for(int j=0;j<times;j++){s.append(arr[i]);}
    }
    cout<<s<<endl;
}

//int or float
template <typename TYPE>
class Differentiate{
    private:
        Polynomial<TYPE> p;
    public:
        //DEFAULT CONSTRUCTOR
        Differentiate(){
            //do nothing 
        }
        Differentiate(Polynomial<TYPE> p1){
            p=p1;
        }
        void differentiate(){
            Polynomial<TYPE> ans(p.arr.size()-1,0);
            for(int i=1;i<p.arr.size();i++){
                ans.arr[i-1]=p.arr[i]*i;
            }
            ans.printpoly();
        }
};

int main(){
    int q;
    cin>>q;
    int op;
    while(q--){
        cin>>op;
        if(op==1){
            //do multiplication
            string s;cin>>s;
            int deg1;cin>>deg1;
            if(s=="integer"){
                //do for integers
                Polynomial<long long int> p1(deg1);
                p1.takeinput();
                int deg2;cin>>deg2;
                Polynomial<long long int> p2(deg2);
                p2.takeinput();
                Multiplication<long long int> mult(p1);
                mult*p2;
            }
            else if(s=="float"){
                //do for float
                Polynomial<long double> p1(deg1);
                p1.takeinput();
                int deg2;cin>>deg2;
                Polynomial<long double> p2(deg2);
                p2.takeinput();
                Multiplication<long double> mult(p1);
                mult*p2;
            }
            else if(s=="complex"){
                //do for complex
                Polynomial<Complex> p1(deg1);
                p1.takeinput();
                int deg2;cin>>deg2;
                Polynomial<Complex> p2(deg2);
                p2.takeinput();
                Multiplication<Complex> mult(p1);
                mult*p2;
            }
        }
        else if(op==2){
            string s;cin>>s;
            int deg1;cin>>deg1;
            //do evaluation
            if(s=="integer"){
                //do for integers
                Polynomial<long long int> p1(deg1);
                p1.takeinput();
                long long x;cin>>x;
                Evaluation<long long int> eval(p1,x);
                eval.evaluate();
            }
            else if(s=="float"){
                //do for float
                Polynomial<long double> p1(deg1);
                p1.takeinput();
                long long x;cin>>x;
                Evaluation<long double> eval(p1,x);
                eval.evaluate();
            }
            else if(s=="string"){
                //do for STRING
                vector<string> arr(deg1);
                for(int i=0;i<deg1;i++){
                    cin>>arr[i];
                }
                long long x;cin>>x;
                caseString(arr,x);    
            }
        }
        else{
            //do differentiastion
            string s;cin>>s;
            int deg1;cin>>deg1;
            if(s=="integer"){
                //do for integers
                Polynomial<long long int> p1(deg1);
                p1.takeinput();
                Differentiate<long long int> eval(p1);
                eval.differentiate();
            }
            else if(s=="float"){
                //do for float
                Polynomial<long double> p1(deg1);
                p1.takeinput();
                Differentiate<long double> eval(p1);
                eval.differentiate();
            }
        }
    }
}
