
-- = != ==

-- il ++ / -- si può utilizzare per diverse operazioni sui dati
-- ( liste, stringhe, numeri ed ecc ),
-- però in generale non si possono mescolare i tipi di dati

-- X liste: x ++ y unisce xy, x \\ y rimove y da x

-- aggiunta di un elemento dello stesso tipo con `:`
-- aggiunta in testa

-- prendi la testa di una lista con `!! 0`
-- ( molte cose possono essere trasformate in liste, i numeri no )

--- Comparing List
a = [3,2,1]
b = [2,1,6]

lambda1 a b = a > b --True, ma non ho capito cosa fa
lambda2 a = head a -- out: 3
lambda3 a = tail a -- out: [ 2,1 ]
lambda4 a = init a -- out: [ 3,2 ]
lambda5 a = length a -- out: 3
lambda6 a = reverse a -- out: reverse

-- take and drop like substring( drop ), teke is a length of substring of drop,
-- if take is equal of 1, take head. in this case take == head.
lambda7 a b = take b a -- out: [..]
lambda8 a b = drop b a -- out: [..]
getIndex a b = take 1 x where x = drop (b-1) a

--other makable function for list:
        --maximum
        --minimum
        --sum
        --product

-- `elem` like contains
lambda9 a b = b `elem` a

-- speed create list, with ..
-- [ x..y ]
-- [ 'x'..'z' ]
-- [ xyz...s ] 
-- ragiona automaticamente se mantenere una certa logica nel range

-- repeat == cycle, but cycle it is for element, and repeat it is for list.
-- replicate a b : return a*b ( like python ).

-- in haskell tutto è una lambda, ma è anche una funzione nativamente postvisita.
-- per creare una pre visita o un invisita avrei bisogno di creare prima:
--     una funzione interprete.

-- curiosità:
matematicamente = [ x*2 | x <- [ 1..10 ] ]
matematicamente2 b = [ x*2 | x <- [ 1..10 ], x>=b ]
matematicamente3 c = [ x | x <- [10..20], x /= 13, x /= 15, x /= 19]

-- `mod` è il mod della matematica => il resto
-- <- it is like foreach

-- quindi <- si usa solo dentro [ ], con | opzionale.
same x = [ y | y <- x ]

-- foreach el in list: makable like `_`
