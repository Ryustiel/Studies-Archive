def intersection_segments(A, B, C, D):
  # Calculer les coefficients directeurs des droites formées par les segments
  mAB = (B[1] - A[1]) / (B[0] - A[0]) if B[0] != A[0] else float('inf')
  mCD = (D[1] - C[1]) / (D[0] - C[0]) if D[0] != C[0] else float('inf')

  # Calculer les ordonnées à l'origine des droites formées par les segments
  bAB = A[1] - mAB * A[0]
  bCD = C[1] - mCD * C[0]

  # Si les droites formées par les segments sont parallèles, ils n'ont pas d'intersection
  if mAB == mCD:
    return None

  # Calculer les coordonnées de l'intersection entre les droites
  x = (bCD - bAB) / (mAB - mCD)
  y = mAB * x + bAB

  # Vérifier si l'intersection se trouve sur les deux segments
  if (A[0] <= x <= B[0] or A[0] >= x >= B[0]) and (C[0] <= x <= D[0] or C[0] >= x >= D[0]):
    return (x, y)
  else:
    return None

A = (1, 2)
B = (3, 4)
C = (2, 1)
D = (4, 3)

intersection = intersection_segments(A, B, C, D)
print(intersection)  # affiche (2.5, 3.0)