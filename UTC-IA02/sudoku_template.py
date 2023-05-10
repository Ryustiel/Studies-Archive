"""
[IA02] TP SAT/Sudoku template python
author:  Sylvain Lagrue
version: 1.1.0
"""

from typing import List, Tuple
import subprocess

# alias de types
Grid = List[List[int]] 
PropositionnalVariable = int
Literal = int
Clause = List[Literal]
ClauseBase = List[Clause]
Model = List[Literal]

example: Grid = [
    [5, 3, 0, 0, 7, 0, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9],
]


example2: Grid = [
    [0, 0, 0, 0, 2, 7, 5, 8, 0],
    [1, 0, 0, 0, 0, 0, 0, 4, 6],
    [0, 0, 0, 0, 0, 9, 0, 0, 0],
    [0, 0, 3, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 5, 0, 2, 0],
    [0, 0, 0, 8, 1, 0, 0, 0, 0],
    [4, 0, 6, 3, 0, 1, 0, 0, 9],
    [8, 0, 0, 0, 0, 0, 0, 0, 0],
    [7, 2, 0, 0, 0, 0, 3, 1, 0],
]


empty_grid: Grid = [
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
]

#### fonctions fournies


def write_dimacs_file(dimacs: str, filename: str):
    with open(filename, "w", newline="") as cnf:
        cnf.write(dimacs)


def exec_gophersat(
    filename: str, cmd: str = "gophersat", encoding: str = "utf8"
) -> Tuple[bool, List[int]]:
    result = subprocess.run(
        [cmd, filename], capture_output=True, check=True, encoding=encoding
    )
    string = str(result.stdout)
    lines = string.splitlines()

    if lines[1] != "s SATISFIABLE":
        return False, []

    model = lines[2][2:-2].split(" ")

    return True, [int(x) for x in model]


#### extension : modelisation du soudoukou


def cell_to_variable(i: int, j: int, val: int) -> PropositionnalVariable:
    return PropositionnalVariable( val + 9*i + 9*9*j )


def at_laest_one(variables: List[PropositionnalVariable]) -> Clause:
    # chaine de "or"
    assert False not in (v > 0 for v in variables)
    return Clause(variables)


def unique(variables: List[PropositionnalVariable]) -> ClauseBase:
    # xi => non xj pour chaque j != i pour chaque i
    assert False not in (v > 0 for v in variables)
    base = at_least_one(variables)
    n_vars = len(variables)
    for i in range(n_vars):
    	for j in range(n_vars):
            base.append([-variables[i], -variables[j]])
    return base
    
    
def create_box_constraints(grid_length) -> ClauseBase:
    clauses = ClauseBase([])
    for x_start in [k*3 for k in range(3)]:
    	for y_start in [k*3 for k in range(3)]:
    	    # valeurs au sein d'une sous grille
    	    litteraux = []
    	    for i in range(3):
    	    	for j in range(3):
    	    	    for val in range(
    	    	        litteraux.append(cell_to_variable(x_start + i, y_start + j, val))
    	    clauses.append(at_least_one(litteraux)) # ClauseBase.append(Clause)
    return clauses
    
def create_lin_constraints(grid_length) -> ClauseBase:
    for i in range(3):
    	litteraux = []
    	for j in range(3):
    	    for val in range(
    	    	litteraux.append(cell_to_variable(i, j, val))
    	    clauses.append(at_least_one(litteraux)) # ClauseBase.append(Clause)
    return clauses
    
def create_column_constraints(grid_length) -> ClauseBase:
    for i in range(3):
    	litteraux = []
    	for j in range(3):
    	    for val in range(
    	    	litteraux.append(cell_to_variable(j, i, val))
    	    clauses.append(at_least_one(litteraux)) # ClauseBase.append(Clause)
    return clauses
    
def create_value_constraints(grid: Grid) -> ClauseBase:
    # iterer sur colonne + lignes + 3x3 (par repere) <= grille carree
    # renseigner "chaque valeur au moins une fois" parce que le nombre est limite.
    # faire une regle sur au moins une des cases de la liste (case 1,1 ou case 1,2, ou ...), pour chaque chiffre
    grid_length = len(grid[0])
    base = ClauseBase([])
    
    # individual cell constraints
    for i in range(grid_length):
    	for j in range(grid_length): # cell y
    	    cell_variables = [cell_to_variable(i, j, val) for val in range(9)]
    	    base.extend(unique(cell_variables))
    	    
    base.extend(create_box_constraints(grid_len))
    base.extend(create_lin_constraints(grid_len))
    base.extend(create_column_constraints(grid_len))
    	    
    return base
    
    
def generate_problem(grid: Grid) -> ClauseBase:
    # ajouter les cases fixees
    base = create_value_constraints(grid)
    for i, line in enumerate(grid):
    	for j, value in enumerate(line):
    	    if value: # value is not 0 (unset)
    	    	base.append(cell_to_variable(i, j, value)) # ClauseBase.append(PropositionnalVariable)
    return base
    

#### extension : appel au solveur


clauses_to_dimacs(clauses: ClauseBase, nb_vars: int) -> str:
    # self explanatory.
    assert len(clauses) == 3270
    fstring = f"p cnf {nb_vars} {len(clauses)}"
    for clause in clauses:
        fstring += "\n"
        for litteral in clause:
            fstring += f" {litteral}" # litteral => string
    print(fstring)
    return fstring


#### fonction principale


def main():
    pass


if __name__ == "__main__":
    main()
