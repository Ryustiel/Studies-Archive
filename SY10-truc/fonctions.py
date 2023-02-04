from decorators import *

def intersection(A1, A2, B1, B2):
    # unpacking phase !
    x1, y1 = A1
    x2, y2 = A2
    x3, y3 = B1
    x4, y4 = B2

    # Calculate the slope and intercept of the first line segment
    m1 = (y2 - y1) / (x2 - x1)
    b1 = y1 - m1 * x1

    # Calculate the slope and intercept of the second line segment
    m2 = (y4 - y3) / (x4 - x3)
    b2 = y3 - m2 * x3

    # Check if the line segments are parallel (i.e. have the same slope)
    if m1 == m2:
        # The line segments are parallel, so they do not intersect
        return 0 # pas d'intersection

    # Calculate the x-coordinate of the intersection of the two line segments
    x = (b2 - b1) / (m1 - m2)

    if x < x1 or x > x2 or x < x3 or x > x4: # x est hors d'un des segments (x1 < x2 and x3 < x4, par kaufmann)
        return 0 # pas d'intersection

    # Calculate the y-coordinate of the intersection of the two line segments
    y = m1 * x + b1

    return y


def hamming(A, B):
    assert A.referentiel == B.referentiel
    s = 0
    for x in A.referentiel:
        d = A.membership(x) - B.membership(x)
        s += abs(d)
    return s

@complementation
def ck(x):
    return 1 - x

# une fois que les T normes et Conormes sont implementees, il reste a faire l'algo de prise de decision, d'intersection, et d'operations sur nombres flous

def T_norme_probabiliste(a, b):
    return a * b

def T_conorme_probabiliste(a, b):
    return a + b - a*b

def T_norme_lukasiewicz(a, b):
    return max(0, a + b - 1)

def T_conorme_lukasiewicz(a, b):
    return min(1, a + b)



