
%cat(X),dog(Y) == any possible <cat(X),dog(Y)> | x ( = or not = ) Y.
%this <X,Y> is like foreach second elements, exec first.
%cat(X),dog(X) == any possible <cat(X),dog(X)> | x must be equals Y.

%Data Objects in Prolog are called terms ( atom ).
%different types of term:
%   -Numbers
%   -Strings == Atoms == no only Numbers
%   -Variables ( init like `Upper Char` o `_ Char` ), composed only from char and _
%   -Compound Terms:
%        The functor is followed by a sequence of one or more arguments,
%        The functor represents the name of the record,
%        The number of arguments a compound term has is called its arity.
%
%   -Lists: like compound, enclosed in square brackets and separated by commas.
%   -Other Types of Term: not be described in this book.

%------------------------------
%   Clauses and Predicates
%------------------------------

go:-write('hello world'),nl.
%go is viseble from interpreter, with simple command: 'go.'

dog(fido). large(fido).
cat(mary). large(mary).
dog(rover). dog(jane).
dog(tom). large(tom). cat(harry).
dog(fred). dog(henry).
cat(bill). cat(steve).
small(henry). large(fred).
large(steve). large(jim).
large(mike).
large_animal(X):- dog(X),large(X).
large_animal(Z):- cat(Z),large(Z).

%------------------------------
%   Predicates
%------------------------------

parent(victoria,albert).
parent(X,Y):-father(X,Y).
parent(X,Y):-mother(X,Y).
father(john,henry).
mother(jane,henry).

%possible combination foreach ideas. clauses:-predicates, and viceversa.
%for more confusing :D is possible create fake facts:
%    facts = caluses = clauses(predicates).

%listing(..) load only clauses, predicates ( no atoms ).
%listing(..) view only clauses, predicates writed on text.
%listing not calculate!!

%interesting way to programming:
go2:-parent(john,B),
     write(B),write(' is a name of child').

%write contains only 1 argument!!

%------------------------------
%   Recursion
%------------------------------

animal(Y):-cat(Y).
animal(Y):-dog(Y).
animal(Y):-butterfly(Y). butterfly(blu).

%likes(eva,Y). john deve essere sicuro che Y non sia un cane.
%likes(eva,Y):-not(dog(Y)). jhon accetta solo argomenti Atomici.
likes(eva,Y):-animal(Y),not(dog(Y)).

% si può con atom(Y) chiedere se un elemento è atomico.
% ma è controproducente perchè atom trasforma in condizione.
% andrebbe invece mantenuto tutto come facts.
% animal rappresenta un or ( di facts ).

% atom serve per valutare, una valutazione negativa, blocca scelte sucessive.
% si può vedere atom come un while loops, per un for usare le liste.

likes(lucra,Y):-cat(Y).
likes(mario,Y):-dog(Y).
likes(john,X,Y):-likes(X,Y),not(dog(Y)).

%likes(john,X):-likes(X,Y),dog(Y). contains bug ( no termination, loop ).
%for not equals must be written: not(..).
