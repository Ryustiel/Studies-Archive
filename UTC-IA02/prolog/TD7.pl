tete([H|_], H). % -H

reste([_|H], H).

vide([]).

element(X, [X|_]).
element(X, [Y|L]) :-
    dif(X, Y),
    element(X, L).

dernier(X, [X]). % ordre des claus impaure tante
dernier(X, [_|Q]) :- % des que... sinon
    dernier(X, Q).

longueur([_], 1).
longueur([_|Q], Lg) :-
    longueur(Q, Lg2),
    Lg is Lg2 + 1.

nombre([], _, 0).
nombre([X|Q], X, N1) :- nombre(Q, X, N2), N1 is N2 + 1.
nombre([Y|Q], X, N1) :-  % to (dan)
    dif(X, Y),
    nombre(Q, X, N1).

concat([], L2, L2).
concat([X|Q], L2, [X|R]) :-
    concat(Q, L2, R).

inverse([], []).
inverse([X|Q], I) :-
    inverse(Q, IQ),
    concat(IQ, [X], I). % !! types des elements liste

valide(_, []).
valide([X|L1], [X|L2]) :- valide(L1, L2).

sous_liste(_, []).
sous_liste([X|Q1], [X|Q2]) :- valide(Q1, Q2).
sous_liste([_|Q1], L2) :- sous_liste(Q1, L2).

retire_element([], _, []).
retire_element([H|T], H, T).
retire_element([X|T], H, [X|RES]) :- retire_element(T, H, RES).


