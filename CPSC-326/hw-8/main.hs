{-
  Name:
  File: main.hs
  Date: Spring 2022
  Desc: Basic tests for HW8. To execute from the command line using
        ghci, run: ghci main.hs -e main
-}

import HW8


-- TODO: Add additional tests to main below

main = do
  putStrLn (assertEqual 1 (myMin 1 2) "myMinTest 1")
  putStrLn (assertEqual 1 (myMin 2 1) "myMinTest 2")
  putStrLn (assertEqual 1 (myMin 1 1) "myMinTest 3")  
  putStrLn (assertEqual (3,5) (myMidpoint (1,4) (5,6)) "myMidpointTest 1")
  putStrLn (assertEqual (3,4) (myMidpoint (6,8) (0,0)) "myMidpointTest 2")
  putStrLn (assertEqual (5,5) (myMidpoint (10,0) (0,10)) "myMidpointTest 3")
  putStrLn (assertEqual (4,2) (myManhattanDistance (1,4) (5,6)) "myManhattanDistanceTest 1")
  putStrLn (assertEqual (6,8) (myManhattanDistance (6,8) (0,0)) "myManhattanDistanceTest 2")
  putStrLn (assertEqual (10,10) (myManhattanDistance (10,0) (0,10)) "myManhattanDistanceTest 3")
  putStrLn (assertEqual 4.47213595499958 (myEuclideanDistance (1,4) (5,6)) "myEuclideanDistance 1")
  putStrLn (assertEqual 10 (myEuclideanDistance (6,8) (0,0)) "myEuclideanDistance 2")
  putStrLn (assertEqual 14.142135623730951 (myEuclideanDistance (10,0) (0,10)) "myEuclideanDistance 3")
  putStrLn (assertEqual 3 (myRangeSum 1 2) "myRangeSum 1")
  putStrLn (assertEqual 0 (myRangeSum 2 1) "myRangeSum 2")
  putStrLn (assertEqual 1 (myRangeSum 1 1) "myRangeSum 3")  
  putStrLn (assertEqual 1 (myFib 1) "myFib 1")
  putStrLn (assertEqual 5 (myFib 5) "myFib 2")
  putStrLn (assertEqual 55 (myFib 10) "myFib 3")
  putStrLn (assertEqual 1 (myGCD 1 10) "myGCD 1")
  putStrLn (assertEqual 5 (myGCD 5 25) "myGCD 2")
  putStrLn (assertEqual 4 (myGCD 8 12) "myGCD 3")
  putStrLn (assertEqual False (myEven 1) "myEven 1")
  putStrLn (assertEqual True (myEven 124518) "myEven 2")
  putStrLn (assertEqual False (myEven 99) "myEven 3")
  putStrLn (assertEqual True (myOdd 1) "myOdd 1")
  putStrLn (assertEqual False (myOdd 124518) "myOdd 2")
  putStrLn (assertEqual True (myOdd 99) "myOdd 3")
  



assertEqual :: (Show a, Eq a) => a -> a -> String -> String
assertEqual x y s =
  if x == y then
    s ++ " [Pass]"
  else
    s ++ " [Fail] ... expecting " ++ (show x) ++ " found " ++ (show y)


