
-- Tuples

-- list of various element
-- tuple can't located in a list, can't be a element of list
-- list can be element of list

-- can't create a fake like tuple with [[],[]]

-- Action fort tuple:
          --fst == head for list
          --snd == second
          --zip list1 list2, create duble tuple foreach el: ( list1, list2 )

-- caso interessante di pattern matching,
-- qui questo linguaggio inizia a essere simile a prolog
rightTriangles = [ (a,b,c) | c <- [1..10], a <- [1..c], b <- [1..a], 
                             a^2 + b^2 == c^2, a+b+c == 24 ]
-- questo può essere visto come backtrack e pattern matching


--serarch type in ghci with :t or :type like :l is :load

-- define type of functions:
remove_upper :: [Char] -> [Char] --( only for good practice => optional )
remove_upper a = [ x | x <- a, x `elem` [ 'A'..'Z' ] ]

-- so:
sumThree :: Int -> Int -> Int -> Int
sumThree a b c = a+b+c

-- if you have to write a correct type for function,
-- you can consult other built-in function like head,
-- with `:t head`.

------------------------
-- Type Classes
------------------------

-- le classi non sono creabili e sono solo built-in
-- si possono converite le classi con `::`,
-- possibile conversione solo per i tipi di dati, pseudo-simili
