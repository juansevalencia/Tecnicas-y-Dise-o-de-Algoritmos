//Suma Selectiva
#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int SumaSelectiva(vector<int> s, int k){
    priority_queue<int , vector<int>, greater<int>> min_heap;
    int n = s.size();
    int count =0 ;
    int sum;
    for (int i = 0 ; i < n ; i++){
        if(count == k){
            if(min_heap.top() < s[i]){
                sum -= min_heap.top();
                min_heap.pop();
                min_heap.push(s[i]);
                sum+= s[i];
            }
        }else{
            count++;
            min_heap.push(s[i]);
            sum += s[i];
        }
    }
    return sum;
}
/* 
complejidad : O(n log k)
Demostracion:
Codifiquemos la solucion como la suma de elementos g1, .. ,gk, ..
Donde para todo j < k sabemos que el elemento j es mas grande ya que por nuestro algoritmo goloso fuimos seleccionando los j mas grandes.
Asumamos que g1, .. ,gi ,siendo i+1 < k, esta incluido en una solucion optima.
Probemos que gi+1 también.
CB:

Si mi solucion es el conjunto vacio entonces la suma de nigun elemento va a coincidir con que el maximo sea 0 porque no tengo nugnu elemento por agregar

PI:

Supongamos que gi+1 no esta incluida en una solucion optima.

Entonces si+1 siendo s una solucion optima , difiere de gi+1.
Si difiere es porque no se sumo el gi+1.
Mas especificamente podemos decir que no se suma el elemento gi+1, n nigun momento.
Pero podemos deducir que gi+1 > si+1 ,entonces Optima + (gi+1 - si+1) > Optima
Pero esto es absurdo ya que estoy dando un escenario donde mi Optima no es optima.
Y esto partio de suponer que la solucionegoloso no esta incluida en una solucion optima.


*/