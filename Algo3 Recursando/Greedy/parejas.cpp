int parejasDeBaile(vector<int> A , vector<int> B, int i , int j ){
    int res =0 ;
    while(j < B.size()){
        if(i == B.size()){
            break;
        }
        if(|A[i] - B[j]| <= 1 ){
            i++;
            j++;
            res+= 1;
        }else if(A[i] > B[j]){
            j++;
        }else{
                i++
        }
    }
    return res;
}

//O(n + m) complejidad temporal

/* Vamos a ver que el algoritmo dado es correcto:
Nuestra solucion greedy la podemos codificar como una secuencia de decisiones donde vamos a tener que recorrer ambos arreglos en el peor de los casos.
g1,....,gn. Donde gi es una tupla que indica la pareja de baile [x , y] donde x es el x-esimo hombre y "y" es la y-esima mujer. Y al formarse una pareja se suma 1 a res.
CB: [] Sabemos que es extendible a una optima porque el conjunto vacio de parejas de baile, esta incluido la solucion optima de dos grupos vacios.
PI: Supongamos que g1,...,gi esta incluido en una optima pero en la deciison de gi+1 difiere y esta si+1.
Supongamos que si+1 != gi+1 porque si no, estaria incluido.
Sigue siendo optima?
Necesariamente x o y va a tener que estar en si+1 porque si no mi solucion optima es de menor tamaño que otra solucion lo que quiere decir que no es optima y llegamos a un absurdo.
Entonces sin perdida de generalidad supongamos que x esta en mi solucion.
Entonces quiere decir que si+1 = [x, y*] ,siendo y* otro elemento de mi lista de mujeres.
Entonces necesariamente ese y* no pertenece a otra pareja de sj porque si no devuelta,no seria la optima por tener menos elemento que alguna otra solucion ,siendo j parte de la solucion optima mayor a i+1.
Entonces la unica forma es que y* no pertenezca a otra pareja de sj, lo cual genera una solucion optima de maor cantidad de parejasd e baile. Lo cua es absurdo porque cambiar elemento por elemento no aumente el tamaño de mi solucion optima. 
Llegamos a un absurdo a partir de suponer que no estaba incluido en mi optima gi+1


*/