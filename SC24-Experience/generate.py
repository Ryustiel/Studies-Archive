import random as rd

def randomize_array(arr):
    for (i, j) in [(rd.randint(0, len(arr)-2), rd.randint(0, len(arr)-2)) for j in range(len(arr))]:
        temp = arr[i]
        arr[i] = arr[j]
        arr[j] = temp
    return arr

def get_line(nval: int, nfonc: int) -> tuple:
    valeurs = []
    fonctions = []

    a = randomize_array( [1]*nfonc + [0]*nval + [0] )
    op = []
    iboucle = 0 # indicateur "interieur d'une composition", donne une chance d'en sortir (vv)
    for i in range(nval + nfonc + 1):
        new = chr(ord('A')+i)

        if a[i]: # 1 ajoute une fonction (profondeur de recursion max = 1)
            fonctions.append( new )
            op.append( new )
            op.append('(')
            iboucle += 1

        else: # 0 ajoute un nombre
            valeurs.append( new )
            op.append( new )

            if iboucle:
                if rd.randint(0, 1):
                    while iboucle != 0:
                        op.append(')')
                        iboucle -=1

            if rd.randint(0, 1):
                op.append('+')
            else:
                op.append('x')

    op = op[:-1]

    while iboucle != 0:
        op.append(')')
        iboucle -=1

    # parsing time!

    return (op, valeurs, fonctions)


def get_function():
    # threshold, fixed value, number of thresholds [1, 2]
    threshold = rd.randint(6, 14)
    fixed_value = rd.randint(1, 7)




class Superliste():
    def __init__(self):
        self.cats = [] # list of ratio keys
        self.latest = []
        self.cycle = 0
        self.last_chr = 'J'
        self.ratios = {
            'A': 5,
            'B': 4,
            'C': 4,
            'D': 3,
            'E': 3,
            'F': 3,
            'G': 2,
            'H': 1,
            'I': 1,
            'J': 1
        }
        self.update_cats()

    def update_cats(self):
        self.cats = []
        for key, value in self.ratios.items():
            if value != 0:
                self.cats.append(key)

    def pickone(self, latest_len): # picking a random letter from cats that has ratio != 0 and is not the latest picked
        assert len(self.cats) != 0
        utterances = 0
        self.cycle += 1

        if self.cycle > latest_len: # resets the latest tab, we're creating a new tab cuz of the cycle
            self.cycle = 0
            self.latest = []

        one = rd.choice(self.cats)
        while self.ratios[one] == 0 or one in self.latest:
            utterances += 1

            one = rd.choice(self.cats)
            if len(self.cats) > 0.5*utterances:
                self.last_chr = chr(ord(self.last_chr) + 1)
                return self.last_chr # emergency key
        
        self.ratios[one] -= 1
        if len(self.latest) > latest_len:
            self.latest.pop(0) # retire le latest le plus ancien
        self.latest.append(one)
        self.update_cats()
        return one


def display_expression(s):

    ss = ""
    for c in s:
        ss += c

    o = """
    print("\n\nles variables sont : ")
    for c in s[1]:
        print(c, end=" ")

    print("\n\net les fonctions a definir sont : ")
    for c in s[2]:
        print(c, end=" ")
    """

    return ss + "\n"


class BinaryThing():
    def __init__(self, count: int, latest_var: int):
        self.true = count
        self.latest_var = latest_var # ord int
    def nextvar(self):
        self.latest_var += 1
        return chr(self.latest_var)
    def getbool(self):
        if self.true == 0:
            return 0
        else:
            ch = rd.randint(0, 1)
            if ch:
                self.true -= 1
            return ch    


class ProblemFunction():
    def __init__(self, name, mode, threshold_count):
        self.name = name
        self.mode = mode # above, below / above, in between if threshold_count = 2
        self.threshold_count = threshold_count
        self.threshold1 = rd.randint(2, 8)
        self.value1 = rd.randint(1, 10)
        self.modifier = rd.randint(2, 10)
        if threshold_count == 2:
            self.threshold2 = rd.randint(2, 8)
            self.value2 = rd.randint(1, 10)

    def __str__(self):
        s = f"""
        FUNCTION {self.name}
        
        """
        if self.mode == 'above':
            s += f"""
                if value over {self.threshold1}:
                    value + {self.modifier}
                else
                    {self.value1}
            """
        return s

    def solve(self, value):
        ...


class Problem():
    def __init__(self, name):
        self.name = name
        self.vars = {} # name : problem_reference
        self.functions = {}
        self.expression = ''

    def render_expression(self):
        nvars = len(self.vars) - 1
        nfunc = len(self.functions)
        self.expression = get_line(nvars, nfunc)

    def __str__(self):
        s = f"{self.expression} \noù"
        for name, var in self.vars.items():
            print(name, var)
            s += f"\n\n{name} : \n{str(var)}"
        for name, var in self.functions.items():
            s += f"\n\n{name} : \n{str(var)}"
        return s

    def solve(self, value):
        ...


class Nombre():
    def __init__(self, name):
        self.name = name
        self.value = rd.randint(1, 4)
    def __str__(self):
        s = f"""
        var {self.name} = {self.value}
        """
        return s


def create_problem(name: str, vars: list, tracking_func: BinaryThing):
    pb = Problem(name)

    for i in range(len(vars)):
        if type(vars[i]) != list:

            if tracking_func.getbool():
                x = ProblemFunction(name=vars[i], mode='above', threshold_count=1)
                x.__name__ = vars[i]
                pb.functions[vars[i]] = x
            else:
                pb.vars[vars[i]] = Nombre(name=vars[i]) # RANDOM VALUE FOR STATIC VARIABLE

        else: # list of vars
            new_var = tracking_func.nextvar()
            pb.vars[new_var] = create_problem(name=new_var, vars=vars[i], tracking_func=tracking_func)

    pb.render_expression()

    print("\n\ncreating problem using %s", vars)
    print("problem has %s, %s" % (pb.functions.keys(), pb.vars.keys()))

    return pb



def get_problem() -> list:

    # getting variable tree

    letters = Superliste()
    tree = [[[letters.pickone(3) for _ in range(3)] for _ in range(2)] for _ in range(3)]

    print("\nPB TREE : ", tree)

    #initialiser latest_var
    bool_func = BinaryThing(3, ord(letters.last_chr))

    #pb = create_problem('RESULTAT', ['C', 'D', 'E'], bool_func)
    #pb = ProblemFunction('A', 'above', 1)

    #print('\n', pb)

    deca = 0 # decalage de la derniere lettre

    for _ in range(4):

        (op, vars, functions) = get_line(3, 1)
        for tab in (op, vars, functions):
            for i in range(len(tab)):
                tab[i] = chr( ord(tab[i]) + deca)

        print("\n\n")
        e = display_expression(op)
        print(e)

        for function in functions: # function : str
            f = ProblemFunction(function, 'above', 1)
            print(f)

        for letter in vars:
            value = rd.randint(1, 10)
            l = f"""
        {letter} = {value}
            """
            print(l)




    # creating a problem for each subsubtab, using BinaryThing limiter for the number of functions.
    # generate a random function expression for each function in the problem
    # print the problem's data
    # append the problem to a bigger problem (2nd loop using the previous problems as variables, these problems must be registered in a list beforehand)

    #expression = get_line(0, 1)
    #print('')
    #display_expression(expression)



get_problem()


