
% più comandi in fila:
% dog(X),large(X),write(X),write(' is a large dog'),nl.
% possono essere visti come un &&, che si interrompe appena non esiste un match.

% more consult to consecutive ( --> && ) --> places the clauses in the database.
% " this delete past shared ( --> == ) facts and add new facts,
%   the past facts that aren't shared are keep ".

%-----------------------------------------
%   Variables [[ scritte in maiuscolo ]]
%-----------------------------------------

% le variabili non sono esplicitamente associabili,
% son il binding inmplicito del programma, che valuta le rules, cluses, etc..
% pertanto per l'utente non è possibile assegnare o valutare una variabile:
%      poichè le variabili sono nulle finchè non c'è un binding.

% The underscore character _ denotes a special variable, called the anonymous
% variable. This is used when the user does not care about the value of the variable.
% If only the surname of any people named paul is of interest, this can be found by
% making the other three variables anonymous in a goal

% ?- person(paul,Surname,_,_,_).
% Surname = smith
% Similarly, if only the ages of all the people named martin in the database are of
% interest, it would be simplest to enter the goal.

% ?- person(martin,_,_,Age,_).
% This will give two answers by backtracking.
% Age = 23;
% Age = 47.

% ?- person(martin,X,X,Age,X).
% with variable X instead of underscore each time, would produce the answer
% false.
% as there are no clauses with first argument martin where the second, third and fifth
% arguments are identical.

animal(mammal,tiger,carnivore,stripes).
animal(mammal,hyena,carnivore,ugly).
animal(mammal,lion,carnivore,mane).
animal(mammal,zebra,herbivore,stripes).
animal(bird,eagle,carnivore,large).
animal(bird,sparrow,scavenger,small).
animal(reptile,snake,carnivore,long).
animal(reptile,lizard,scavenger,small).

reload(X):-consult(X).

% q1:-animal(mammal,Name,_,_),write(Name),nl.
% q1(X):-animal(mammal,Name,_,_).
q1( Name ) :- animal( mammal, Name, _, _ ).

% mammal is a variable that have match, so binding
% Name doesn't have binding, so is a free and so will be shown.

q2( Name ) :- animal( mammal, Name, carnivore, _ ).
% print false because animal ... is like and, and.

person(bill,male).
person(george,male).
person(alfred,male).
person(carol,female).
person(margaret,female).
person(jane,female).

couple( Man, Girl ) :- person( Man, male ), person( Girl, female ).

%------------------------------------
%    Backtracking
%------------------------------------

% Backtracking is the process of going back to a previous goal and trying to resatisfy
% it, i.e. to find another way of satisfying it.
% This section gives two very detailed accounts of the way that Prolog tries to
% satisfy a sequence of goals using unification and backtracking. With practice it
% is quite easy to work out the sequence of operations by visual inspection of the
% database. However, it may be helpful to have a detailed account available for
% reference.

% prima: binding of variable for rules; after true o false for facts ( atom ).

% Satisfying Goals: A Summary
% The method described in the previous sections is shown in diagrammatic form in
% Figures 3.5 and 3.6. Note how the two flowcharts refer to each other.
% Evaluating a Sequence of Goals: Summary
% Evaluate the goals in turn, working from left to right. If they all succeed, the whole
% sequence of goals succeeds. If one fails, go back through the previous goals in the
% sequence one by one from right to left trying to resatisfy them. If they all fail, the
% whole sequence fails. As soon as one succeeds, start working through the goals from
% left to right again.
% Evaluating/Re-evaluating a Goal: Summary
% Search through the clauses in the database, working from top to bottom 1 until one is
% found, the head of which matches with the goal. If the matching clause is a fact,
% the goal succeeds. If it is a rule, evaluate the sequence of goals in its body. If
% the sequence succeeds, the goal succeeds. If not, continue searching through the
% database for further matches. If the end of the database is reached, the goal fails.
