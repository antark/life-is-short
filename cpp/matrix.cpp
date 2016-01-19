#include <iostream>
using namespace std;
 
class Matrix{
public:
    Matrix(int n);
    Matrix(const Matrix& m);
#if __cplusplus >= 201103L
    Matrix(Matrix && m);
#endif
    ~Matrix();
    void build(int data[]);
    void print();
    
    void operator= (const Matrix& m);
    friend Matrix operator+(const Matrix&m, const Matrix& n);
    
private:
    int n;
    int *data;
};
 
Matrix::Matrix(int n): n(n)
{
    if(n <= 0)
        throw invalid_argument("matrix dim <= 0");
    data = new int[n*n];
}
 
Matrix::Matrix(const Matrix& m)
{
    this->n = m.n;
    this->data = new int[n*n];
    this->build(m.data);
}
 
#if __cplusplus >= 201103L
Matrix::Matrix(Matrix&& m)
{
    this->n = m.n;
    this->data = m.data;
    m.data = 0;
}
#endif
 
Matrix::~Matrix()
{
    delete[] data;
    data = 0;
}
 
void Matrix::build(int data[])
{
    for(int i = 0; i < n*n; ++i)
        this->data[i] = data[i];
}
 
void Matrix::operator=(const Matrix& m)
{
    if(this->n != m.n){
        throw runtime_error("operator = , dim not equal ");
    }
    this->build(m.data);
}
 
Matrix operator+(const Matrix&m, const Matrix& n)
{
    if(m.n != n.n){
        throw runtime_error("operator + , dim not equal ");
    }
    Matrix result(m.n);
    for(int i = 0; i < m.n*m.n; ++i)
        result.data[i] = m.data[i] + n.data[i];
    return result;
}
 
void Matrix::print()
{
    for(int i = 0; i < n*n; ++i){
        cout << data[i] << ' ';
        if( (i+1) % n == 0)
            cout << '\n';
    }
    cout << endl;
}
 
int main()
try{
    int n;
    cin >> n;
    
    Matrix a(n), b(n);
    
    int data[1000];
    for(int i = 0; i < n*n; ++i){
        cin >>data[i];
    }
    a.build(data);
    a.print();
    
    for(int i = 0; i < n*n; ++i){
        cin >>data[i];
    }
    b.build(data);
    b.print();
    
    Matrix c(a+b);
    c.print();
    
    return 0;
}catch(invalid_argument e){
    cout << "argument error: "  << e.what() << endl;
}catch(runtime_error e){
    cout << "runtime error: " << e.what() << endl;
}
