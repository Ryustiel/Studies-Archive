import matplotlib.pyplot as plt
from fonctions import intersection

class PartitionFloue():
    def __init__(self, referentiel):
        self.referentiel = referentiel
        self.parties = {} # ensemble de sous ensembles

    def display(self):
        referentiel = list(self.referentiel())
        for label, ensemble in self.parties.items():
            plt.plot(referentiel, [ensemble.membership(x) for x in referentiel])

        plt.xlabel("X Referentiel")
        plt.ylabel("Appartenances")
        plt.show()
    





class EnsembleFlou():
    def __init__(self, referentiel, membership):
        self.referentiel = referentiel # fonction generatrice
        self.membership = membership # fonction sur tout referentiel

    def __call__(self, n) -> float: # renvoie le degre d'appartenance de ce point du referentiel
        if n in self.referentiel():
            return self.membership(n)

    def to_ift(self): 
        """
        realise une approximation par un trapeze si la quantite floue est convexe
        """
        # convexite
        kaufmann = [0, 0, 0, 0]
        hauteur = self.hauteur()

        croissant = True
        prev = self.membership(self.referentiel[0])
        assert prev == 0 # le nombre flou est dans le referentiel (nul tout a gauche)
        for i, x in enumerate(self.referentiel()):

            m = self.membership(x)

            if croissant and prev == 0 and m != 0 and i != 0: # le nombre n'est pas le premier nombre du referentiel
                kaufmann[0] = self.referentiel[i-1]

            elif croissant and self.membership(x) < m: # cesse d'etre croissant
                kaufmann[2] = self.referentiel[i-1]
                croissant = False

            elif not croissant:
                assert self.membership(x) <= prev # sinon non convexe sur le referentiel

            # membership vaut 1 pour la premiere fois
            if croissant and prev != hauteur and m == hauteur:
                kaufmann[1] = self.referentiel[i]

            if croissant:
                assert self.membership(x) >= m

            elif not croissant and self.membership(x) == 0:
                kaufmann[3] = self.referentiel[i-1]

        return IFT(self.referentiel, kaufmann, hauteur)


    def support(self) -> list: # parties avec valeur non nulle
        s = []
        for x in self.referentiel():
            prev = self.membership(x)
            if m != 0:
                s.append(x)
        return s

    def noyau(self) -> list:
        noyau = []
        for x in self.referentiel():
            m = self.membership(x)
            if m == 1:
                noyau.append(x)
        return noyau
    
    def hauteur(self) -> float:
        mx = 0
        for x in self.referentiel():
            m = self.membership(x)
            if m > mx:
                mx = m
        return mx

    def socle(self) -> float:
        mn = None
        for x in self.referentiel():
            m = self.membership(x)
            if m != 0:
                if mn is None: # minimum sauf zero
                    mn = m
                elif mn > m:
                    mn = m
        return mn

    def cards(self):
        n = 0
        for x in self.referentiel():
            n += self.membership(x)
        return n

    def cardsr(self):
        n = self.cards()
        return n / len(self.referentiel())

    def inclus_dans(self, E): # E: EnsembleFlou (test self inclu (non strict) dans E)
        assert self.referentiel == E.referentiel
        for x in self.referentiel():
            if self.membership(x) > E.membership(x):
                return False
        return True

    def a_coupe(self, a, stricte=False): # -> EnsembleFlou || membership function of the returned "fuzzy set"
        referential_above_a = []
        for x in self.referentiel():
            if (not stricte and self.membership(x) >= a) or (stricte and self.membership(x) > a):
                referential_above_a.append(x)
        def coupe(x):
            assert x in self.referentiel()
            if x in referential_above_a:
                return self.membership(x)
            else:
                return 0
        ensemble = EnsembleFlou(self.referentiel, coupe)
        return ensemble

    def complementaire(self, c): # -> EnsembleFlou
        def cmembership(x):
            return c(self.membership(x))
        return EnsembleFlou(self.referentiel, cmembership)

    def operateur(self, E, op):
        def new_membership(x):
            return op(self.membership(x), E.membership(x))
        return EnsembleFlou(self.referentiel, new_membership)

    def troncature(self, k, op):
        def new_membership(x):
            return op(k, self.membership(x))
        return EnsembleFlou(self.referentiel, new_membership)

    def display(self):
        plt.plot(list(self.referentiel()), [self.membership(x) for x in self.referentiel()])
        plt.xlabel("X Referentiel")
        plt.ylabel("Appartenance")
        plt.show()







class IFT(): # avec cet objet, on fait des operations sur les bornes!
    def __init__(self, referentiel, kaufmann, hauteur):
        self.referentiel = referentiel
        self.kaufmann = kaufmann # intervalles de transition du nombre de flou
        self.hauteur = hauteur


    def intersect_ift(self, N):
        # segments horizontaux : 
        if (self.kaufmann[1] <= N.kaufmann[1] and self.kaufmann[1] >= N.kaufmann[2]) or (self.kaufmann[2] <= N.kaufmann[1] and self.kaufmann[2] >= N.kaufmann[2]) or (self.kaufmann[1] >= N.kaufmann[2] and self.kaufmann[2] <= N.kaufmann[2]): # un des bords du segment self est compris du segment N, ou self est a l'interieur de N
            
            return min([self.hauteur, N.hauteur])
        
        else:
            # comparaison des hauteurs

            hauteurs = [
                intersection( (self.kaufmann[0], 0), (self.kaufmann[1], self.hauteur), (N.kaufmann[0], 0), (N.kaufmann[1], N.hauteur) ), # croissant croissant

                intersection( (self.kaufmann[0], 0), (self.kaufmann[1], self.hauteur), (N.kaufmann[1], N.hauteur), (N.kaufmann[2], N.hauteur) ), # croissant horizontal

                intersection( (self.kaufmann[0], 0), (self.kaufmann[1], N.hauteur), (N.kaufmann[2], N.hauteur), (N.kaufmann[3], 0) ), # croissant decroissant

                intersection( (self.kaufmann[1], self.hauteur), (self.kaufmann[2], self.hauteur), (N.kaufmann[0], 0), (N.kaufmann[1], N.hauteur) ), # horizontal croissant

                intersection( (self.kaufmann[1], self.hauteur), (self.kaufmann[2], self.hauteur), (N.kaufmann[2], N.hauteur), (N.kaufmann[3], 0) ), # horizontal decroissant

                intersection( (self.kaufmann[2], self.hauteur), (self.kaufmann[3], 0), (N.kaufmann[0], 0), (N.kaufmann[1], N.hauteur) ), # decroissant croissant

                intersection( (self.kaufmann[2], self.hauteur), (self.kaufmann[3], 0), (N.kaufmann[1], N.hauteur), (N.kaufmann[2], N.hauteur) ), # decroissant horizontal

                intersection( (self.kaufmann[2], self.hauteur), (self.kaufmann[3], 0), (N.kaufmann[2], N.hauteur), (N.kaufmann[3], 0) ) # decroissant decroissant
            ]

            return max(hauteurs)


    def simple_intersection(self, N):
        """
        les deux quantites floues associees sont des ensembles flous normaux, 
        et les IFT sont des nombres flous triangulaires.
        """
        if (self.kaufmann[1] <= N.kaufmann[1] and self.kaufmann[1] >= N.kaufmann[2]) or (self.kaufmann[2] <= N.kaufmann[1] and self.kaufmann[2] >= N.kaufmann[2]) or (self.kaufmann[1] >= N.kaufmann[2] and self.kaufmann[2] <= N.kaufmann[2]): # un des bords du segment self est compris du segment N, ou self est a l'interieur de N
            
            return 1

        else:
            # comparaison des hauteurs

            hauteurs = [
                intersection( (self.kaufmann[0], 0), (self.kaufmann[1], 1), (N.kaufmann[0], 0), (N.kaufmann[1], 1) ), # croissant croissant

                intersection( (self.kaufmann[0], 0), (self.kaufmann[1], 1), (N.kaufmann[2], 1), (N.kaufmann[3], 0) ), # croissant decroissant

                intersection( (self.kaufmann[2], 1), (self.kaufmann[3], 0), (N.kaufmann[0], 0), (N.kaufmann[1], 1) ), # decroissant croissant

                intersection( (self.kaufmann[2], 1), (self.kaufmann[3], 0), (N.kaufmann[2], 1), (N.kaufmann[3], 0) ) # decroissant decroissant
            ]

            return max(hauteurs)


    def ef(self): # tres peu couteux
        def membership(x):
            if x > self.kaufmann[0]:
                if x <= self.kaufmann[1]
                    return self.hauteur * (x - self.kaufmann[0]) / (self.kaufmann[1] - self.kaufmann[0])
                elif x <= self.kaufmann[2]:
                    return 1
                elif x <= self.kaufmann[3]:
                    return self.hauteur * (self.kaufmann[2] - x) / (self.kaufmann[1] - self.kaufmann[0])
            return 0

        return EnsembleFlou(self.referentiel, membership)