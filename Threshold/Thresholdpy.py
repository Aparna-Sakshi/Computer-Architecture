#This code finds the range of values that T (i.e) threshold can take
#Lets formulate the problem statement: Here the input is weights of the threshold element (i,e) a,b,c... so on in [a,b,c,...,T] and the boolean expression for eg: xy + z. The output of the code is minimum and maximum values that T can take.

#Example 3: weights:5,7,10, boolean expression:xy+z
weights = [5,7,10] #weights (i.e) a,b,c,d, etc


#Given a boolean list, (i.e)boolean values of x,y,z..., this function evaluates the boolean expression
def bf(bl): #bl=boolean list, bf=Bool function or boolean expression
    x,y,z = bl
    return (x and y) or z # This is the expression xy+z




#Given an array of weights and the boolean list, this function calculates ax+by+cz...
def evaluate(w,bl):#t=threshold element
    val=sum([a*int(x) for (a,x) in zip(w,bl)])
    return val




#This function is a python generator: Given a number of weights, in this example number of weights is 3 (i.e)5,7,10, this function generates all possible combinations of a list of size n that consists of only boolean entries. 
def boolList(n):
    for i in range(2**n):
        srti=bin(i)
        yield [bool(int(j)) for j in srti[2:].zfill(n)]



#This function prints min and max values of T. 
def ranges(w):
    n=len(w)
    d={}
    d[True]=[]
    d[False]=[]
    for bl in boolList(n):
        d[bf(bl)].append(evaluate(w,bl))
    #printing min and max values of T
    if len(d[True])!=0:
        print("max:",min(d[True]))
    if len(d[False])!=0:
        print("min:",max(d[False]))
   

ranges(weights)  

#Output of the code is to be interpreted as follows:
#T belongs to the interval (min,max]
#if min>=max, then no value is possible 