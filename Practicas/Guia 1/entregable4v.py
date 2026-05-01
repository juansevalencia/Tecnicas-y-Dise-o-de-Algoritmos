def areEqual(palabra1 , palabra2)-> bool:
    if(len(palabra1)% 2 != 0 ):
        return (palabra1 == palabra2)
    else:
        if(len(palabra1) == 2 ):
            palabra_dada_vuelta1 = palabra1[::-1]
            return (palabra1 == palabra2 or palabra_dada_vuelta1 == palabra2)
        else:                
            mitad1 = len(palabra1) // 2
            a1 = palabra1[:mitad1]
            a2 = palabra1[mitad1:]
            mitad2 = len(palabra2) // 2
            b1 = palabra2[:mitad2]
            b2 = palabra2[mitad2:]
            return ((areEqual(a1, b2) and areEqual(a2, b1)) or areEqual(a1, b1) and areEqual(a2, b2))

def main():
    p1 = input()
    p2 = input()
    if(p1 == p2):
        print("YES")
    else:    
        if(areEqual(p1 , p2)):
            print("YES")
        else:
            print("NO")    
    
if __name__ == "__main__":
    main()