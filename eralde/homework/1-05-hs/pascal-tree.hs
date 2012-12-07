import Data.List.Utils (join)
import Text.Printf (printf)
import Data.Bits ((.&.))

--
--  Calculates the Pascal triangle :-)
--
--  Good ol' fashioned way - add together previous row & previous row shifted 1 item to the right
--  (both padded with zeros to be of the same length)
--
--  Usage: `pascalTriangle !! 5`    ->  5-th row
--
pascalTriangle :: [[Integer]]
pascalTriangle = iterate (\row -> zipWith (+) (0:row) (row ++ [0])) [1]

pascalTriangleMod2 :: [[Integer]]
pascalTriangleMod2 = map (map (\x -> x `mod` 2)) pascalTriangle

matrix :: (Integer -> Integer -> a) -> Integer -> [[a]]
matrix f size = [genRow f j size | j <- [0 .. size]]
    where
        genRow f rownum size = [f rownum i | i <- [0 .. size]]

--
--  Algebra of polynomials (see the end of the http://www.haskell.org/haskellwiki/Blow_your_mind) 
--
--  a + b*x + c*x^2 + ... <-> [a, b, c, ...]
--
--  >_<
--

instance  Num a =>  Num [a] where
    (f:fs) + (g:gs) = f+g : fs+gs               --  (f+x*fs) + (g+x*gs) = f+g + x*(fs+gs)
    fs + [] = fs                                --  end of the list rule for addition
    [] + gs = gs                                --  end of the list rule for addition
    (f:fs) * (g:gs) = f*g : [f]*gs + fs*(g:gs)  --  (f+x*fs) * (g+x*gs) = f*g + x*(f*gs + fs*(g+x*gs))
    _ * _ = []                                  --  end of the list rule for multiplication
                                                --  ('_' will match only 1 element list because of the previous rule)
                    
    --  This stuff is not required to calculate the Pascal Triangle...
    abs           = undefined
    signum        = map signum
    fromInteger n = [fromInteger n]
    negate        = map (\x -> -x)

pascal :: [[Integer]]
pascal = map ([1, 1]^) [0..]    --  calculates (lazily) all elements of the [(1 + 1) ^ n, n = 0, 1, 2, ...] list

main    =   do
    let size    =   20
    let range   =   [0 .. 20]

    let printSep = putStr "\n\n"
    let showFn = printf "%3d"
    --  process each element of a row with showFn
    --  then join them with spaces
    let showLineN n rowGen = (join " " (map (map showFn) rowGen !! n))
    
    --  show 20 lines of the Pascal triangle
    mapM_ (\x -> putStr ((showLineN x pascalTriangle) ++ "\n")) range
    printSep
    
    --  show 20 lines of the Pascal triangle with each element replaced by its (mod 2)
    mapM_ (\x -> putStr ((showLineN x $pascalTriangleMod2) ++ "\n")) range
    printSep
    
    --  show 20 of 2x2 matrix with (i,j)-th element is '*' if p & q /= 0 and ' ' if p & q == 0
    let asteriskMatrix = matrix (\i j -> if 0 /= i .&. j then "*" else " ") size
    
    mapM_ (\x -> putStr (((map (join " ") asteriskMatrix) !! x) ++ "\n")) range
    printSep
    
    --  show 20 lines of the Pascal triangle with each element replaced by '*' if (el mod 2 == 1) or ' ' otherwise
    let showLineN' n rowGen = (join " " (map (map (\x -> if 0 /= x `mod` 2 then "*" else " ")) rowGen !! n))
    mapM_ (\x -> putStr ((showLineN' x $pascalTriangleMod2) ++ "\n")) range
    printSep
    
    return  ()