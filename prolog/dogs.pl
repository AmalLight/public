
%interprete swi-prolog --> swipl
%dichiarazione con funzione(...).
%legame o regola con funzione2(X..Y..Z..):-funzione3(..).
%principio fondamentale di sostituzione e ricorsione.

dog(fido).
dog(rover).
dog(henry).
cat(felix).
cat(michael).
cat(jane).
animal(X):-dog(X).

%si stampa con write(..) e si va a capo con ,nl,.. .
%Two other built-in predicates: halt and statistics.

% halt => break, exit, ...
%statistics = statistiche.

%A sequence of one or more goals entered by the user at the prompt:
%is often called: a query.

%if you open only swipl without pl,
%The program can then be loaded for use by the Prolog system using the built-in:
%consult.

%Prolog programs consist only of a sequence of clauses.
%All clauses are either facts or rules.

%facts:- dog() e cat().
%fido,jane,henry are atom.
%the final line is rules or its called clauses ( from facts ).
%X is a variable.

%command listing:
%isting(dog). %List all the clauses defining predicate dog.

%dog(Y) = dog(X).
