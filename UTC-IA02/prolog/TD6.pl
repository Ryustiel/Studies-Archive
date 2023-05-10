% oedipe predicats et tout

% fixes genres

femme(s�m�l�).
femme(harmonie).
femme(antigone).
femme(ism�ne).
femme(jocaste).
femme(eurydice).
femme(agav�).

homme(cr�on).
homme(cadmos).
homme(�chion).
homme(laios).
homme(oedipe).
homme(h�mon).
homme(�t�ocle).
homme(polynice).
homme(m�n�c�e).
homme(labdacos).
homme(zeus).
homme(polydore).
homme(labdacos).

% fixes parents

parent(cadmos, polydore).
parent(cadmos, agav�).
parent(harmonie, polydore).
parent(harmonie, agav�).
parent(cadmos, �chion).
parent(harmonie, �chion).
parent(harmonie, zeus).
parent(harmonie, s�m�l�).
parent(cadmos, s�m�l�).
parent(cadmos, zeus).
parent(penth�e, m�n�c�e).
parent(cr�on, h�mon).
parent(eurydice, h�mon).
parent(m�n�c�e, jocaste).
parent(m�n�c�e, cr�on).
parent(laios, oedipe).
parent(jocaste, oedipe).
parent(oedipe, �t�ocle).
parent(oedipe, polynice).
parent(oedipe, antigone).
parent(oedipe, ism�ne).
parent(jocaste, �t�ocle).
parent(jocaste, polynice).
parent(jocaste, antigone).
parent(jocaste ,ism�ne).

% koupoulah

couple(agav�, �chion).
couple(s�m�l�, zeus).
couple(oedipe, jocaste).
couple(cadmos, harmonie).
couple(laios, jocaste).
couple(cr�on, eurydice).
couple(X, Y) :- couple(Y, X), X \= Y. % ah h�viter
couple(X, Y) :- couple(Y, X), dif(X, y).

% pr�dictate pahrrrrr mahrrrrr

pere(X, Y) :- homme(X), parent(X, Y).

mere(X, Y) :- femme(X), parent(X, Y).

% predicats suppl�mentaires

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



















