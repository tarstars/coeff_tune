import Data.Char (isSpace)

main :: IO ()
main = do
    putStrLn "Enter the number of the elements of the Fibbonaci sequence you want to calculate:"
    do
        n <- getInt
        print (fib n)

-- from http://www.haskell.org/pipermail/beginners/2010-February/003408.html    
getInt :: IO Integer
getInt = do
    inp <- getLine
    case reads inp of
      ((a,tl):_) | all isSpace tl -> return a
      _ -> error "Invalid input! Enter a number next time!"
      
fib :: Integer -> [Integer]
fib n
    | n < 1     = error "Invalid number. Enter a number, greater then 1"
    | otherwise = 1:1:[fib' x 2 1 1 | x <- [3.. n]]

fib' :: Integer -> Integer -> Integer -> Integer -> Integer
fib' n k fk fk1
    | k == n = fk
    | k < n  = fib' n (k+1) (fk + fk1) fk