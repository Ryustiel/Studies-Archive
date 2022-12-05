from treelib import Node, Tree
import random

def remplir(T: Tree, n, node=None):
    if node is None:
        val1 = random.randint(0, 10)
        T.create_node(val1, 1)
        node = 1

    else:
        val1 = random.randint(0, 10)
        val2 = random.randint(0, 10)
        T.create_node(val1, node+1, parent=node)
        T.create_node(val2, node+2, parent=node)

    node = remplir(T, n-1, node+1)
    remplir(T, n-1, node+1)

    return node

def main():
    arbre = Tree()
    remplir(arbre, 2)
    arbre.show()


main()