#include <iostream>
#include <exception>
 
class fraction{
public:
    fraction(unsigned mm = 0, unsigned nn = 1): m{mm}, n{nn}{}    // 构造函数
    fraction(const fraction& f): m{f.m}, n{f.n}{}    // 拷贝构造函数
    ~fraction(){}    // 析构函数
   
    fraction operator+(const fraction& a){    // 重载 + 运算符
        unsigned den = lcm(n, a.n);    // 分母
        unsigned num = m*den/n + a.m*den/a.n;    // 分子
        unsigned cd = gcd(den, num);
        return fraction{num/cd, den/cd};
    }
   
    fraction operator+=(const fraction& a){    // 重载 += 运算符
        unsigned den = lcm(n, a.n);    // 分母
        unsigned num = m*den/n + a.m*den/a.n;    // 分子
        unsigned cd = gcd(den, num);
        m = num/cd;
        n = den/cd;
        return *this;
    }
   
    fraction operator-(const fraction& a){    // 重载 - 运算符
        if(*this < a){
            throw std::exception{};
        }
        unsigned den = lcm(n, a.n);    // 分母
        unsigned num = m*den/n - a.m*den/a.n;    // 分子
        unsigned cd = gcd(den, num);
        return fraction{num/cd, den/cd};
    }
   
    fraction operator-=(const fraction& a){    // 重载 -= 运算符
        if(*this < a){
            throw std::exception{};
        }
        unsigned den = lcm(n, a.n);    // 分母
        unsigned num = m*den/n - a.m*den/a.n;    // 分子
        unsigned cd = gcd(den, num);
        m = num/cd;
        n = den/cd;
        return *this;
    }
   
    fraction operator*(const fraction& a){    // 重载 * 运算符
        unsigned den = n*a.n;    // 分母
        unsigned num = m*a.m;    // 分子
        unsigned cd = gcd(den, num);
        return fraction{num/cd, den/cd};
    }
   
    fraction operator*=(const fraction& a){    // 重载 *= 运算符
        unsigned den = n*a.n;    // 分母
        unsigned num = m*a.m;    // 分子
        unsigned cd = gcd(den, num);
        m = num/cd;
        n = den/cd;
        return *this;
    }
   
    fraction operator/(const fraction& a){    // 重载 / 运算符
        unsigned den = n*a.m;    // 分母
        unsigned num = m*a.n;    // 分子
        unsigned cd = gcd(den, num);
        return fraction{num/cd, den/cd};
    }
   
    fraction operator/=(const fraction& a){    // 重载 /= 运算符
        unsigned den = n*a.m;    // 分母
        unsigned num = m*a.n;    // 分子
        unsigned cd = gcd(den, num);
        m = num/cd;
        n = den/cd;
        return *this;
    }
   
    bool operator<(const fraction& a){    // 重载 < 运算符
        long long den = lcm(n, a.n);
        long long diff = den/n*m - den/a.n*a.m;
        return diff < 0;
    }
   
    friend std::ostream& operator<<(std::ostream& out, const fraction& a){    // 重载 << 运算符
        out << a.m << '/' << a.n;
        return out;
    }
   
private:
    unsigned gcd(unsigned a, unsigned b){
        unsigned r;
        while(b){
            r = a % b;
            a = b;
            b = r;
        }
        return a;
    }
    unsigned lcm(unsigned a, unsigned b){
        return a / gcd(a, b) * b;
    }
private:
    unsigned m;
    unsigned n;
};
 
int main()
try{
    fraction a{40, 20}, b{3, 4}, c;
   
    c = a + b;
    std::cout << c << '\n';
   
    c = a - b;
    std::cout << c << '\n';
   
    c = a * b;
    std::cout << c << '\n';
   
    c = a / b;
    std::cout << c << '\n';
   
    std::cout << std::endl;
 
    return 0;
}catch(std::exception& e){
    std::cout << e.what() << std::endl;
}catch(...){
    std::cout << "unkonwn exception" << std::endl;
}
