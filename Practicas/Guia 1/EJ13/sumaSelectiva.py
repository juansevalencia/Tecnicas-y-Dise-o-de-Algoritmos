def SumaSelectiva(i ,j, listaA , listaB):
    if(i == len(listaA)):
        return []
    if(abs(listaA[i] - listaB[j])<= 1):
        return [listaA[i], listaB[j]] + SumaSelectiva(i +1  , j+ 1 , listaA , listaB)
    if(listaA[i] < listaB[j]):
        return [SumaSelectiva(i + 1 , j ,listaA , listaB)]
    else:
        return [SumaSelectiva(i , j+1 ,listaA , listaB)]
##recorre para la mas chica , y anda matcheando. Si encontras una pareja
##que tenga diferencia menor a 1 absoluto. Una vez que los encontras, eliminalos a ambos o haces que tus iteraciones empiecen a recorrer desde el siguiente para todos porque sabes que es creciente


  