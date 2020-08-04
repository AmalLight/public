import System.IO
import Data.Char
import System.Environment

-- Reading and Writing Files:
-- import System.IO

-----------------------------------------------------------------------------
-- openFile and withFile Functions
main = do
    handle <- openFile "girlfriend.txt" ReadMode
    contents <- hGetContents handle
    putStr contents
    hClose handle

main2 = do
     withFile "girlfriend.txt" ReadMode
     ( \ handle -> do contents <- hGetContents handle putStr contents )
--   withFile take 3 argument, withFile è abbastanza inutile
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
-- Grab the Handles!
main3 = do
      contents <- readFile "girlfriend.txt"
      putStr contents

main4 = do
      contents <- readFile "girlfriend.txt"
      writeFile "girlfriendcaps.txt" ( map toUpper contents )
-----------------------------------------------------------------------------
-----------------------------------------------------------------------------
-- Append and Deleting Items
main5 = do
      todoItem <- getLine
      appendFile "todo.txt" ( todoItem ++ "\n" )

main6 = do
      file <- getLine
      removeFile file
-----------------------------------------------------------------------------

------------------------
-- UTILI:
-- readFile
-- writeFile
-- removeFile
-------------------------

-----------------------------------------------------------------------------
-- Command-Line Arguments, import System.Environment
main7 = do
      args <- getArgs
      progName <- getProgName
      putStrLn "The arguments are:"
      mapM putStrLn args
      putStrLn "The program name is:"
      putStrLn progName
-----------------------------------------------------------------------------

-- Randomness, import System.Random
