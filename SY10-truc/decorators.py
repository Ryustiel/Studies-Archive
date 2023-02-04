def complementation(f): # verifie que la fonction est une complementation
    if f(0) == 1 and f(1) == 0:
        i = 0
        prec = f(0)
        while i < 1:
            curr = f(i)
            if curr > prec or curr > 1 or curr < 0: # decroissant et appartient a [0, 1]
                raise ValueError("%s : %s" % (i, curr))
            i += 0.001
        return f
    raise ValueError(f"f(0) != 1 ({f(0)}) OU f(1) != 0 ({f(1)})")


def distance(f):
    i = 0
    j = 0
    k = 0
    while i <= 1:
        while j <= 1:
            if i == j:
                if f(i, j) != 0: # axiome de separation
                    raise ValueError(f"({i}, {j}) : {f(i, j)} = 0 : axiome de separation")
            else:
                if f(i, j) != f(j, i): # axiome de symetrie
                    raise ValueError(f"({i}, {j}) : {f(i, j)} = {f(j, i)} : axiome de symetrie")

                while k <= 1: # inegalite triangulaire
                    if f(i, k) > f(i, j) + f(j, k):
                        raise ValueError(f"({i}, {j}, {k}) : {f(i, k)} <= {f(i, j)} + {f(j, k)} : inegalite triangulaire")
                    k += 0.01
                k = 0
            j += 0.01
        j = 0
        i += 0.01
    return f



