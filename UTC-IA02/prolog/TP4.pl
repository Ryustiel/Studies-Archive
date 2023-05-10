nBienPlaces([], [], 0).

% underscores jamais �niphj�
nBienPlaces([H1|T1], [H2|T2], BP) :-
    dif(H1, H2),
    nBienPlaces(T1, T2, BP).

nBienPlaces([H|T1], [H|T2], BP) :-
    nBienPlaces(T1, T2, BP2),
    BP is BP2 + 1.

longueur([], N) :- N is 0.

% attention aux overlaps de variables
longueur([_|L], N) :-
    longueur(L, N2),
    N is N2 + 1.

gagne(T1, T2) :-
    nBienPlaces(T1, T2, BP),
    longueur(T1, BP).
% BP = N //> si on en vient � noter �a, �a veut dire que dans toute la
% on peut consid�rer ces valeurs comme la m�me. (directement, par le
% nommage)

% implicite ?
% element(E, []) :- false.

% tjrs valide
element(E, [E|_]).

element(E, [E2|L]) :-
    dif(E, E2),
    element(E, L).

enleve(_, [], []).
enleve(E, [E|L1], L2) :- L2 is L1.

enleve(E, [E2|L1], L2) :-
    dif(E, E2),
    enleve(E, L1, L3),
    L2 = [E|L3].



