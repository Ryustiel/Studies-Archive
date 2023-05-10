% oedipe predicats et tout

% fixes genres

femme(sémélé).
femme(harmonie).
femme(antigone).
femme(ismène).
femme(jocaste).
femme(eurydice).
femme(agavé).

homme(créon).
homme(cadmos).
homme(échion).
homme(laios).
homme(oedipe).
homme(hémon).
homme(étéocle).
homme(polynice).
homme(ménécée).
homme(labdacos).
homme(zeus).
homme(polydore).
homme(labdacos).

% fixes parents

parent(cadmos, polydore).
parent(cadmos, agavé).
parent(harmonie, polydore).
parent(harmonie, agavé).
parent(cadmos, échion).
parent(harmonie, échion).
parent(harmonie, zeus).
parent(harmonie, sémélé).
parent(cadmos, sémélé).
parent(cadmos, zeus).
parent(penthée, ménécée).
parent(créon, hémon).
parent(eurydice, hémon).
parent(ménécée, jocaste).
parent(ménécée, créon).
parent(laios, oedipe).
parent(jocaste, oedipe).
parent(oedipe, étéocle).
parent(oedipe, polynice).
parent(oedipe, antigone).
parent(oedipe, ismène).
parent(jocaste, étéocle).
parent(jocaste, polynice).
parent(jocaste, antigone).
parent(jocaste ,ismène).

% koupoulah

couple(agavé, échion).
couple(sémélé, zeus).
couple(oedipe, jocaste).
couple(cadmos, harmonie).
couple(laios, jocaste).
couple(créon, eurydice).
couple(X, Y) :- couple(Y, X), X \= Y. % ah héviter
couple(X, Y) :- couple(Y, X), dif(X, y).

% prédictate pahrrrrr mahrrrrr

pere(X, Y) :- homme(X), parent(X, Y).

mere(X, Y) :- femme(X), parent(X, Y).

% predicats supplémentaires

epoux(X, Y) :- couple(X, Y), homme(X). % """surchaaarge"""
epoux(X, Y) :- couple(Y, X), homme(X).

fils(X, Y) :- parent(Y, X), homme(X).
fille(X, Y) :- parent(Y, X), femme(X).
enfant(X, Y) :- parent(Y, X).

grandpere(X, Y) :- parent(Z, Y), pere(X, Z).
grandmere(X, Y) :- parent(Z, Y), mere(X, Z).
grandparent(X, Y) :- grandpere(X, Y).
grandparent(X, Y) :- grandmere(X, Y).

oncle(X, Y) :-
    dif(X, Y),
    homme(X),
    parent(Z, Y),
    meme_parent(X, Z).



















