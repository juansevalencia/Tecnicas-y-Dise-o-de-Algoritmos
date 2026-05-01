#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <utility>

void caminoMinimo(){
    std::string input;
    while (true) {
        std::getline(std::cin, input); // Leer una línea de entrada
        
        if (input.empty()) {
            break; // Salir del bucle si la entrada está vacía
        }//verifico que la primera linea no sea vacia
        
        int n, k;
        std::cin>> n >> k;
        std::string linea_input;

        std::getline(std::cin, linea_input); // Leer toda la línea de entrada

        std::istringstream iss(linea_input); // Convertir la línea en un stream de entrada
        int num;
        std::vector<int> arreglo_tiempos; // Vector para almacenar los enteros

        // Leer enteros uno por uno desde el stringstream
        while (iss >> num) { //EMPIEZA DESDE CEROOO y yo indexo en 1
            arreglo_tiempos.push_back(num); // Agregar el entero al vector
        }
        //guardo los nodos por <piso, ascensor>
        std::vector<int> vertices;
        std::unordered_map<std::pair<<int, int>,<int, int>>, int> PesoAristas = {};
        int i = 1;
        while(i <= n){
            std::getline(std::cin, linea_input);
            std::istringstream iss(linea_input); 
            int num;
            int k = 1;
            int ant = 0;
            while (iss >> num) { //EMPIEZA DESDE CEROOO y yo indexo en 1
                vertices.push_back(num); // Agregar el entero al vector
                if(k == 1){
                    ant = num;
                    k = k - 1;
                }else{
                    aristas[{{ant, i },{num, i}}] = (num - ant)*arreglo_timepos[i -1] ;
                    ant = num;                
                }
            }
            i++;
        } 
        //tengo que probar si esta guardando bein los valores
        //falta guardar las aristas entre ascensores cuando comaprten y aplicar djikstra.
    }    
        
}
int main(){
    caminoMinimo();
    return 0;
}
