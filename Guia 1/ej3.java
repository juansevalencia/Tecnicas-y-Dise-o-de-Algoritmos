import java.util.HashSet;
import java.util.Set;

public class MainClass {

    public static Set<Integer> generar(int[][] Matriz, Set<Integer> I ,int r, int i){
        Set<Integer> result = new HashSet<>(Set);
        if (r == 0 && i == n){
            return result;
        }else{
            if(r > I.size()){
                return result.add(-1);
            }else{
                return cMax(Matriz, generar(Matriz , I.remove(i), r - 1 , i + 1).add(i) , generar(Matriz , I.remove(i , r - 1 , i + 1)));
            }     
        }
    } 

    public static Set<Integer> cMax(int[][] Matriz, Set<Integer> res0 , Set<Integer> res1){
        if(sumaMatriz(Matriz, res0) > sumaMatriz(Matriz , res1)){
            return res0;
        }else{
            return res1;
        }
         
    }

    public static int sumaMatriz (int[][] Matriz, Set<Integer> res){
        int result = 0;
        for( int i : res0){
            for(int k :res0){
                if(i <= k){
                    if(i== k){
                        result += 2*Matriz[i][k];
                    }else{
                        result += Matriz[i][k];
                    }    
                }    
            }
        }
    }    
}
