
% les schtroumpf sont bleus
bleu(X) :- schtroumpf(X).

% les schtroumpf sont des lutins
lutin(X) :- schtroumpf(X).

% les lutins sont petits
petit(X) :- lutin(X).

% les schtroumpf sont tous amis entre eux
ami(X, Y) :- schtroumpf(X), schtroumpf(Y), X \= Y.

% quelques Schtroupmfs
schtroumpf(grand_schtroumpf).
schtroumpf(coquet).
schtroumpf(costaud).
schtroumpf(a_lunette).
schtroumpf(schtroumpfette).
