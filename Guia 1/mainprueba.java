import java.util.Scanner;
import java.util.HashMap;
import java.util.*;
import java.util.List;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        scanner.nextLine();
        
        System.out.println("Número total de casos a procesar: " + T); // Imprime el número total de casos a procesar

        for(int caseNumber = 1 ; caseNumber <= T ;caseNumber++){
            HashMap<String , int[]> cualidades = new HashMap<>();
            List<String> jugadores = new ArrayList<>();
            System.out.println("Caso actual: " + caseNumber); // Imprime el número del caso actual
            for( int j = 0;j<10;j++){
                String linea = scanner.nextLine();
                System.out.println("Línea de entrada: " + linea); // Imprime cada línea de entrada
                String[] e = linea.split(" ");
                String nombre = e[0];
                int ataque = Integer.parseInt(e[1]);
                int defensa = Integer.parseInt(e[2]);
                cualidades.put(nombre, new int[]{ataque, defensa});
                jugadores.add(nombre);
            }
            Collections.sort(jugadores);
            System.out.println("Jugadores ordenados: " + jugadores); // Imprime la lista de jugadores ordenada
            List<String> primera = new ArrayList<>();
            primera.add(jugadores.get(0));
            System.out.println("Parámetros de equipo: índice inicial: 0, atacantes: " + primera + ", cualidades: " + cualidades + ", jugadores: " + jugadores + ", posrestantes: 5"); // Imprime los parámetros del método equipo
            List<String> ms = equipo(0 ,new ArrayList<>(), primera , cualidades , jugadores, 5 );
            List<String> def = new ArrayList<>(); 
            for(String d : jugadores){
                if(noEsta(d , ms)){
                    def.add(d);
                }
            }
            Collections.sort(def);
            System.out.println("Case " + caseNumber + ":");
            System.out.println("Atacantes: " + ms.get(0) + ", " + ms.get(1) + ", " + ms.get(2) + ", " + ms.get(3) + ", " + ms.get(4));
            System.out.println("Defensores: " + def.get(0) + ", " + def.get(1) + ", " + def.get(2) + ", " + def.get(3) + ", " + def.get(4));

        }
        scanner.close();
    }    

    public static List<String> equipo(int i , List<String> ms , List<String> sp , HashMap<String, int[]> cualidades , List<String> jugadores , int posrestantes){ 
            if( sp.size() == 5 ){
                if(contieneNull(sp)){
                    return ms;
                }
                if(ms.size()< 5 || contieneNull(ms)){
                    ms = sp; //salva el caso en q no tengan el mismo tamaño pero por ejemplo sumen la misma ataque.
                }
                if( sumaAtaque(sp, cualidades) > sumaAtaque(ms , cualidades) ){    
                    ms = sp;
                }else{
                    if(sumaAtaque(sp ,cualidades ) == sumaAtaque(ms, cualidades)){
                        if(sumaDefensa(sp, cualidades) < sumaDefensa(ms, cualidades)){
                            ms = sp;
                        }else{
                            if(sumaDefensa(sp , cualidades) == sumaDefensa(ms , cualidades)){
                                if(lexicograficaAntes(sp , ms) > 0){
                                    ms = sp;     
                                }
                            }
                        }
                    }
                }    
            }else{ 
                if(i != 9 && (10 - i >= posrestantes) ){
                    List<String> sp2 = new ArrayList<>(sp);
                    sp2.add(jugadores.get(i+1));
                    sp.remove(jugadores.get(i));
                    jugadores.set(i , null); //tengo que tener cuidado que para llenar def ese todo compleoy jugadores original
                    ms = maxS(equipo( i + 1 ,ms , sp2 , cualidades , jugadores ,posrestantes - 1), equipo(i + 1 ,ms ,sp , cualidades , jugadores , posrestantes ) , cualidades);              
                }else{        
                    return new ArrayList<>(5); //seria un problema que lo quiera pensar como un ListString?
                }   
            }    
            System.out.println("Equipo actual: " + ms); // Imprime el equipo actual
            return ms;            
    }

        public static int sumaAtaque(List<String> s , HashMap<String , int[] > c ){
            int res = 0;
            if(s.size() == 0 || s.get(0) == null || s.get(4) == null){
                return -1;
            }else{
                for(int i = 0 ; i < s.size() ; i++){
                    if(s.get(i) != null){
                        res += c.get(s.get(i))[0];
                    }    
                }
            }
            return res;
        }

        public static int sumaDefensa(List<String> s , HashMap<String , int[] > c ){
            int res = 0;
            if(s.size() == 0 || s.get(0) == null || s.get(4) == null){
                return -1;
            }else{
                for(int i = 0 ; i < s.size() ; i++){
                    if(s.get(i) != null){
                        res += c.get(s.get(i))[1];
                    }
                }
            }
          return res;
        }

        
        //comparo el primero y si es necesario comparo los segundos y asi sucesivamente hasta el ultimo en donde necesariamente van a ser distintos
        public static int lexicograficaAntes(List<String> s0 , List<String> s1){
            for(int i = 0 ; i < s0.size()  ; i++){
                String elemS0 = s0.get(i);
                String elemS1 = s1.get(i);
                
                if (elemS0 == null && elemS1 != null) {
                    return -1; // s0 es menor
                } else if (elemS0 != null && elemS1 == null) {
                    return 1; // s1 es menor
                } else if (elemS0 != null && elemS1 != null) {
                    int comp = elemS0.compareTo(elemS1);
                    if(comp != 0){
                        return comp;
                    }
                }
            }
            return 0; // s0 y s1 son iguales
        } 

        public static boolean noEsta(String i , List<String> s){
            if(s.size()==0 || s.get(0)== null){
                return true;
            }else{
                for( String k : s){
                    if(k.equals(i)){
                        return false;
                    }
                }
                return true;
            }    
        }

        public static List<String> maxS(List<String> s1 , List<String> s2 , HashMap<String , int[] > cualidades){
            if(s1.size() == 0 || s1.get(0) == null  ){
                return s2;    
            }
            if(s2.size() == 0 || s2.get(0) == null){
                return s1;           
            }
            if( sumaAtaque(s1, cualidades) > sumaAtaque(s2 , cualidades) ){	
                return s1;
            }else{
                if(sumaAtaque(s1 ,cualidades ) == sumaAtaque(s2, cualidades)){
                    if(sumaDefensa(s1, cualidades) < sumaDefensa(s2, cualidades)){
                        return s1;
                    }else{
                        if(sumaDefensa(s1 , cualidades) == sumaDefensa(s2 , cualidades)){
                            if(lexicograficaAntes(s1 , s2) > 0){
                                return s1; 	
                            }
                        }
                    }                        
                }
            }
            return s2;
        }        

        public static boolean contieneNull(List<String> l){
            for(int i = 0; i< l.size(); i++){
                if(l.get(i)== null){
                    return true;
                }
            }
            return false;
        }

}


