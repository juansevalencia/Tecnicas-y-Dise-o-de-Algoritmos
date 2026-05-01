//Ruta Eficiente. N - tanque >= 0 
int cantidadDeParadas(vector<int> x , int C){
    vector<int> parada = [];
    int res = 0;
    int tanque = C;
    for (int i = 0; i < n-1 , i++){
        if(tanque - x[i+1] <0 ){
            parada.append(i);
            tanque = C;
            res++;
        }else{
            tanque -= x[i+1];
        }
    }
    return res;
}

/* Demo: 
Sea g1, ..., gn la decodificacion de mi solucion greedy.
El paso gi representa la decision de haber parado o haber seguido.

Primero veamos que nuestra solucion es valida:
Si fuese invalida para algun gi parariamos en una estacion no existente y esto por como recorre nuestro algoritmos las paradas no es posible.

Optimalidad:
Veamos que esta incluida en mi solución optima.
Asumamos que hasta el paso i, esta inlcuida en la optima. Veamos que en i+1 < n es optima.
CB: El conjunto vacio esta incluido en toda solucion optima.
PI:
Asumamos que gi+1 != si+1. Tenemos dos casos.
Gi+1 = 0 y si+1 = 1. Lo cual implica que mi solucion optima implica que se cargue nafta en la parada i
Si nuestra solucion greedy no es igual a 1 es porque podría haber seguido porque llegaba con la nafta para seguir una parada más.
Independientemente de lo que pase después podemos asegurar que al momento i+1 nuestra solucion optima esta sumando cuando nuestra solucion no.
Lo cual implica que hay una solucion menor a la optima en busca de miniminizacion al paso si+1. 
Y esto es absurdo.

Si Gi+1 = 0 y si+1 = 1. Implica que tanque - x[i+1] < 0. Entonces estamos recorriendo sin tanque y esto es absurdo.
Todo a partir de suponer que no esta incluida en solucion optima.

DEMOB:

Si al momento i+1, si+1 = 1 y Gi+1 = 0.
Veamos que nuestra greedy contiene el mismo resultado que

Podría pasar 

Se puede dar el caso que cargue en una estacion pero no cargue en la siguiente.
c= 8
 5      8     10   
xi+1, xi+2 , xi+3
4      1       7
4      9       7

Si+2 = 0 y Gi+1 = 1 porque 



f(i , t) = {  +inf        si t< 0
           {   0          si i == n
           { min(f(i+1,t - (x[i+1] - x[i])) , f(i +1, C - (x[i+1] - x[i] ))) +1) cc 


DEMO C:

Queremos ver que es optimo. Entonces la cantidad de paradas ne la So es igual en la Sg.

Entonces codifiquemos a g1,... ,

*/


