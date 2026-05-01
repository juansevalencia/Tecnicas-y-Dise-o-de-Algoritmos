#include <vector>
#include <iostream>

using namespace std;

// Asumiendo que la función posicionDondeIriaEnB y subseq están definidas

int posicionDondeIriaEnB(const vector<int>& A, const vector<int>& B, int midA) {
    int midB = B.size() /2
    if(B[midB ] < A[midA]){
        B = subseq(B, midB + 1 , B.size() - 1);
        return posicionDondeIriaEnB( A, B , midA, res + midB);
    }else{
        B = subseq(B, 0 , midB, res );
        return posicionDondeIriaEnB(A, B, midA, res);
    }
}

vector<int> subseq(const vector<int>& vec, int start, int end) {
    vector<int> subvec;
    for (int i = start; i <= end; ++i) {
        subvec.push_back(vec[i]);
    }
    return subvec;
}

int f(vector<int> A, vector<int> B, int i){
    if (A.empty()){
        return B[i];
    } else if (B.empty()) {
        return A[i];
    }

    int midA = A.size() / 2;
    int pos = posicionDondeIriaEnB(A, B, midA);

    if (midA + pos < i) { // mira para la posicion en adelante de los dos.
        A = subseq(A, midA + 1, A.size() - 1);
        B = subseq(B, pos, B.size() - 1);
        return f(A, B, i - midA - pos);
    } else { //mira para la posicion para atras de los dos.
        B = subseq(B, 0, pos - 1);
        A = subseq(A, 0, midA);
        return f(A, B, i);
    }
}


int main() {
    vector<int> A = {1, 3, 5};
    vector<int> B = {2, 4, 6};
    int index = 2; // Cambia esto según lo que necesites

    int result = f(A, B, index);
    cout << "Resultado: " << result << endl;

    return 0;
}
