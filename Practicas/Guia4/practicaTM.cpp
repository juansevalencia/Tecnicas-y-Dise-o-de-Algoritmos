vector<vector<int>> aristas;
vector<bool> visitados;

void dfs(int v){
    visitados[v] = true;
    for(int u : aristas[v]){
        if(!visitados[u]){
            dfs(u);
        }
    }
}

bool esConexo(){
    visitados.assign(aristas.size(), false); // Inicializa visitados
    dfs(nodos[0]) //o 0 
    for(bool visitado : visitados){
        if(visitado == false){
            return false;
        }
    }
    return true
}

//ejercicio 2 
//Dar un algoritmo que dado un grafo devuelva la cantidad de componentes conexas que tiene.
//aplica dfs en un nodo, suma uno, si alguno quedo sin visitar hace en ese recursivamente dfs

int cantCompConexas(){
    visitados.assign(aristas.size(), false); // Inicializa visitados
    int res = 0;
    int i = 0;
    while(i < len(visitados)){
        if(!visitados[i]){
            dfs(i);
            res += 1;
        i++;    
        }
    }
    return res;
}        

