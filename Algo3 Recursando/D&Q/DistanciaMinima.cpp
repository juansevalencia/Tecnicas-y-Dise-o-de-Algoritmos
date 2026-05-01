//ejercicio 10 ,si es log n -> f(n) = O(1) ,a  = 1 ,c >= 2
int distanciaMinima(vector<int> A, vector<int> B ,int i , int j,int n){
    if(i == j){
        return A[i] - B[i];
    }
    mid = i + ((j - i )/2);
    if(|A[mid] - B[mid]| > |A[mid + 1] - B[ mid + 1]|){
        distanciaMinima(A, B , i, mid )
    }else{
        distanciaMinima(A, B, mid + 1, j);
    }
}

