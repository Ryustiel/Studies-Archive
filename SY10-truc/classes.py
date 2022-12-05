

class NombreFlouTrapezoidal():
    def __init__(self, start, hstart, hstop, stop, height):
        self.start = start
        self.hstart = hstart
        self.hstop = hstop
        self.stop = stop
        self.height = height


class PartitionFloue():
    def __init__(self, mfuncs: list): # mfuncs[list: function]
        self.mfuncs = mfuncs

    def fuzzify(self, value):
        result = {}
        for mfunc in self.mfuncs:
            result[mfunc.__name__] = mfunc(value)
        return result


class SystemeFlou():
    def __init__(self, et: function, ou: function, tnorme: function):

        # operateurs par defaut pour algorithme
        self.et = et
        self.ou = ou
        self.tnorme = tnorme

        self.input_variables = []

    def add_regle(self, regles: list): # regles : [ {'input':[input1, input2, input3, ...], 'operateur':[operateur1, operateur2, ...], 'resultat':resultat}, ]
        for regle in regles:
            for input in regle['input']:
                if type(input) == PartitionFloue:
                    if not input.__name__ in self.input_variables:
                        self.input_variables.append(input.__name__)
                elif type(input) == SystemeFlou:
                    pass
                else:
                    raise ValueError("Unknown type for input : %s" % type(input))

    def inference(self, values: dict):
        if values.keys() != self.input_variables:
            raise ValueError("Invalid input values : %s, should be %s" % (values.keys(), self.input_variables))

        # calculer toutes les valeurs necessaires a l'inference : regarder quels sont les systemes flous dans les regles et executer leur inference (recursion)

    # determine le comportement a adopter lors de l'inference


# on genere un vecteur de "valeurs pour chaque point de la classe floue"
# passage des regles floues : on calcule la liste des "conséquences" pour chaque règle et on se retrouve avec une liste à overlaps
# assembler les conséquences en utilisant l'opérateur "ET"

#3-10 tconormes
