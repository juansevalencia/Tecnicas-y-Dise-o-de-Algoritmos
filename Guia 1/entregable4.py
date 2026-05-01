def main():
    palabra1 = input()
    palabra2 = input()
    if(len(palabra1)% 2 != 0 ):
        print ("NO")
    if areEqual(palabra1, palabra2):
        print("YES")
    else:
        print("NO")

def areEqual(palabra1, palabra2)-> bool:
    if palabra1 == palabra2:
        return True
    if len(palabra1) == 0 or len(palabra2):
        return False 
    if len(palabra1) == 1 and len(palabra2) == 1:
        return palabra1 == palabra2
    mitad1 = len(palabra1) // 2
    a1 = palabra1[:mitad1]
    a2 = palabra1[mitad1:]
    mitad2 = len(palabra2) // 2
    b1 = palabra2[:mitad2]
    b2 = palabra2[mitad2:]
    return (areEqual(a1, b1) and areEqual(a2, b2)) or (areEqual(a1, b2) and areEqual(a2, b1))

if __name__ == "__main__":
    main()
