int f(vector<int> A, vector<int> B ,int i ){
    if(A.size() == 0){
        return B[i];
    }else if(B.size() == 0){
        return A[i];
    }
    midA = A.size() /2
    int pos = posicionDondeIriaEnB(A, B, midA)
    if( midA  + pos < i   ){
        A = subseq(A, midA +1, A.size()-1);
        B = subseq(B, pos , B.size() -1);
        return f(A, B, i - midA - pos);
    }else{
        B = subseq(B,0, pos - 1);
        A = subseq(A, 0 , midA);
        return f(A, B, i);
    }
}