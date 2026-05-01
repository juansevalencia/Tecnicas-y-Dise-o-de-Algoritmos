##Quiero la cantidad minima de paradas que tiene que hacer tomas y en cuales para
## cunado este en la i-esima parada tengo que decidir si paro a cargar o sigo.
##voy a poder seguir sii llego a la proxima estación.Siendo xi la parada por donde estamos pasando y xj la siguiente.  xj-xi<= Kr
##Y Kr kilometros restantes de nafta.

##f(xi, xj , Kr)
## si xj== null -> < [], 0>
## si xj - xi <= Kr -> f(xj, x(j+1), Kr - (xj - xi))
## cc -> < , 1> + f(xj, x(j+1), Kr-)


##o podemos hacer algo del estilo res = f(xi,xj, Kr) , donde X es nuestro conjunto de paradas xi = x0 ,xj = x1, Kr = 0 
##return <res,len(res)>
## si xj == null -> []
##si xj - xi <= Kr -> f(xj, x(j+ 1) , Kr - (xj - xi))
##cc xi + f(xj , x(j+1) , C- (xj - xi))

def main(lista , C):
    x = lista
    tanque = C
    rutaEficiente(0, 1 , 0)
 
def rutaEficiente(i ,j , Kr ):
    if(x[j] == null):
        return []
    if(x[j] - x[i] <= Kr):
        return rutaEficiente(j , j+1, Kr -(x[j] - x[i]))
    else:
        return x[i] + f(x[j], x[j+1] , tanque - (x[j] -x[i]))

