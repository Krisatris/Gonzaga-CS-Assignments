{- 
  Name: Linden Beemer
  File: HW8.hs
  Date: Spring 2022
  Desc: 
-}


module HW8 (
  myMin,
  myMedian,
  myMidpoint,
  myManhattanDistance,
  myEuclideanDistance,
  myRangeSum,
  myFib,
  myGCD,
  myEven,
  myOdd
) where


-- TODO: Implement the following functions

-- (1). myMin x y 
myMin x y = 
  if x < y
    then x
  else 
    y

-- (2). myMedian x y z
myMedian x y z = 
  if x > y
    then (if x < z
      then x
      else (if y > z
        then y
        else z))
    else (if x > z
      then x
      else (if y < z
        then y
        else z))

-- (3). myMidpoint (x1,y1) (x2,y2)
myMidpoint (x1,y1) (x2,y2) = (r1,r2)
  where
    r1 = (fst (x1,y1) + fst (x2,y2)) / 2
    r2 = (snd (x1,y1) + snd (x2,y2)) / 2

-- (4). myManhattanDistance (x1,y1) (x2,y2)
myManhattanDistance (x1,y1) (x2,y2) = (r1,r2)
  where
    r1 = abs (fst (x1,y1) - fst (x2,y2))
    r2 = abs (snd (x1,y1) - snd (x2,y2))
  
-- (5). myEuclideanDistance (x1,y1) (x2,y2)
myEuclideanDistance (x1,y1) (x2,y2) = sqrt ((r1 ** 2) + (r2 ** 2))
  where
    r1 = abs (fst (x1,y1) - fst (x2,y2))
    r2 = abs (snd (x1,y1) - snd (x2,y2))

-- (6). myRangeSum v1 v2
myRangeSum v1 v2 =
  if v1 > v2
    then 0
  else 
    v1 + myRangeSum (v1 + 1) v2

-- (7). fib 
myFib n =
  if n == 0
    then 0
  else (if n == 1 || n == 2
    then 1
  else myFib(n - 1) + myFib(n - 2))

-- (8). myGCD x y
myGCD x y =
  let n = mod x y
  in if y == 0
    then x
  else
    myGCD y n

-- (9). myEven
myEven x =
  if x < 0
    then False
  else (if x == 0
    then True
  else
    myOdd (pred x))

-- (10). myOdd
myOdd x =
  if x <= 0
    then False
  else (if x == 1
    then True
  else 
    myEven (subtract 3 x))
