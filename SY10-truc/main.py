from ensembles import *
from fonctions import *

def x():
    i = 0
    while i < 10:
        yield i
        i = round(i + 0.01, 2)
    return

def mA(x):
    if x > 3:
        if x <= 3.5:
            n = 2*(x-3)
            return round(n, 2)
        elif x <= 4:
            n = 1 - 2*(x-3.5)
            return round(n, 2)
    return 0

def mB(x):
    if x > 2:
        if x <= 4:
            n = (x-2)/2
            return round(n, 2)
        elif x <= 7:
            n = 1 - (x-4)/3
            return round(n, 2)
    return 0



A = EnsembleFlou(x, mA)
B = EnsembleFlou(x, mB)

N = NFT([2.4, 3.5, 4.6, 8])

partition = {
    #"A": A,
    #"B": B,
    # "B Coupe 0.2": B.a_coupe(0.2),
    # "ckB": B.complementaire(ck),
    # "intersection": A.operateur(B, T_norme_probabiliste),
    #"intersection 2": A.operateur(B, T_conorme_probabiliste),
    "max intersection": A.operateur(B, max),
    "min intersection": A.operateur(B, min)
}

# print(A.hauteur(), A.socle(), A.noyau(), min(B.support()), max(B.support()))
print(partition["min intersection"].support())
print(partition.fuzzifier(3.2))
# print(partition.nombre_flou())

p = PartitionFloue(x)
p.parties = partition
p.display()