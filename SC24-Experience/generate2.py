import random as rd

def randomize_array(arr):
    for (i, j) in [(rd.randint(0, len(arr)-2), rd.randint(0, len(arr)-2)) for j in range(len(arr))]:
        temp = arr[i]
        arr[i] = arr[j]
        arr[j] = temp
    return arr


class Fonction():
    def __init__(self, name, mode):
        self.name = name
        self.mode = mode # above, below / above, in between if threshold_count = 2
        self.threshold = rd.randint(2, 8)
        self.value = rd.randint(1, 10)
        self.modifier = rd.randint(2, 4)
        self.operator = rd.choice(['x', '+', '/'])

    def __str__(self):
        s = f"""
        FUNCTION {self.name}
        """
        if self.mode == 'above':
            s += f"""
                if value > {self.threshold}:
                    value {self.operator} {self.modifier}
                else
                    {self.value}
            """
        else:
            s += f"""
                if value < {self.threshold}:
                    value {self.operator} {self.modifier}
                else
                    {self.value}
            """

        return s

    def __call__(self, input):
        if self.mode == "above":
            if input <= self.threshold:
                return self.value
        else:
            if input >= self.threshold:
                return self.value
        
        if self.operator == "+":
            return input + self.modifier
        elif self.operator == "x":
            return input * self.modifier
        else:
            return input / self.modifier


class Nombre():
    def __init__(self, name):
        self.name = name
        self.value = rd.randint(1, 4)
    def __str__(self):
        s = f"""
        CONST {self.name} = {self.value}
        """
        return s
    def solve(self):
        return self.value


class Problem():
    def __init__(self, name: str, vars: list, func: list):
        self.expression = []
        self.name = name

        a = randomize_array( [0]*(len(vars)-1) + [1]*len(func) ) + [0] # doit finir par une voyelle
        iboucle = 0 # indicateur "interieur d'une composition", donne une chance d'en sortir (vv)
        for i in range(len(vars) + len(func)):

            if a[i]: # 1 ajoute une fonction (profondeur de recursion max = 1)
                self.expression.append( func.pop() )
                self.expression.append('(')
                iboucle += 1

            else: # 0 ajoute un nombre
                self.expression.append( vars.pop() )

                if iboucle:
                    if rd.randint(0, 1):
                        while iboucle != 0:
                            self.expression.append(')')
                            iboucle -=1

                if rd.randint(0, 1):
                    self.expression.append('+')
                else:
                    self.expression.append('x')

        self.expression = self.expression[:-1]

        while iboucle != 0:
            self.expression.append(')')
            iboucle -=1

    def __str__(self):
        s = f"EXPRESSION {self.name} = "
        for e in self.expression:
            if type(e) == str:
                s += e
            else:
                s += e.name # problem, function, number

        for e in self.expression:
            if type(e) != str:
                s += "\n"
                s += str(e)

        return s


    def calculer(self, values):
        depth = 0 # si (, jute obtenir le resultat de la fonction et ignorer le reste
        i = 1
        
        operator = ""
        result = values[self.expression[0].name]

        
        
        while i < len(self.expression):
            if self.expression[i] in ["(", ")", "+", "x"]: # ne fait rien tant que depth est non nul (n'analyse que la partie de l'expression de profondeur minimale)
                if self.expression[i] == "(":
                    depth += 1
                elif self.expression[i] == ")":
                    depth -= 1
                else:
                    operator = self.expression[i]

            elif depth == 0:
                if operator == "+":
                    result += values[self.expression[i].name]
                elif operator == "x":
                    result *= values[self.expression[i].name]
            
            i += 1

        return result


    def solve(self):
        """
        retourne un dictionnaire de valeurs pour la fonction.
        """
        pile = [] # empiler les fonctions jusqu'à avoir l'argument fermant (nombre)
        results = {}

        for e in self.expression:

            if type(e) == Fonction:
                pile.append(e)
            elif type(e) == Nombre:
                if pile != []:
                    n = e.value
                    results[e.name] = n
                    while pile != []:
                        f = pile.pop()
                        n = f(n)
                        results[f.name] = n
                else:
                    results[e.name] = e.value
                        
            elif type(e) == Problem: # type = problem
                if pile != []:
                    results.update(e.solve()) # ajoute des resultats du truc subsecant
                    n = e.calculer(results)
                    results[e.name] = n
                    while pile != []:
                        f = pile.pop()
                        n = f(n)
                        results[f.name] = n

                else:
                    results.update(e.solve()) # ajoute des resultats du truc subsecant

                    results[e.name] = e.calculer(results)

        results[self.name] = self.calculer(results)
        return results





counter = 1
while counter < 21:
    c = Nombre('C')
    i = Fonction('I', 'below')

    s = Problem('F', [Nombre('A'), Nombre('B'), Nombre('C')], [Fonction('D', 'below'), Fonction('E', 'above')])

    f = s = Problem('J', [Nombre('G'), Nombre('H')], [i])

    k = Problem('O', [s, Nombre('K'), Nombre('L'), Nombre('M')], [Fonction('N', 'above'), i])

    t = Problem('Q', [k, f, c], [Fonction('P', 'above'), i])

    solutions = t.solve()

    not_valid = False
    for key, value in solutions.items():
        if value != int(value) or value > 20:
            not_valid = True
            break

    if not_valid:
        counter -= 1
    else:
        print(f"\n\n\n\nPROBLEME NUMERO {counter}")

        print(t)

        print("SOLUTIONS\n", t.solve())

    counter += 1
