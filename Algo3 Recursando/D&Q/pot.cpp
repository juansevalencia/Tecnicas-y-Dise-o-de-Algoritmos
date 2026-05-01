#include <iostream>
using namespace std;

int p(int a,int b){
    if(b == 0){
        return 1;
    }
    if(b == 1){
        return a;
    }
    int res = p(a,b/2);
    if(b % 2 == 1){
        return (res*res*a);
    }else{
        return res*res;
    }
}

//T(n/2) + f(n) , f(n) = o(1) , O(log n )

int main(){
    int res = 5 / 2;
    cout << res;
    return 0;
}