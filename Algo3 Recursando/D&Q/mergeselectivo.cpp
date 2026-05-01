puntoA(vector<int> A, vector<int> B){
    vector<int> Orig;
    izq = 0;
    der = 0;
    original = 0;
    while(izq < A.size() && der < B.size()){
        if(A[izq] > B[der]){
            Orig[original] = A[izq]
            original++;
            izq++;
        }else{
            Orig[original] = B[der]
            der++
            original;
        }
        if(original - 1 == i){
            return Orig[original-1];
        }
    }
    while(izq < A.size()){
        Orig[original] = A[izq]
        original++;
        izq++;
        if(original - 1 == i){
            return Orig[original-1];
        }
    }
     while(der < B.size()){
        Orig[original] = B[der]
        original++;
        der++;
        if(original - 1 == i){
            return Orig[original- 1]; 
        }
    }
}