{-
   Name: Linden Beemer
   File: HW10.hs
   Date: Spring 2022
   Desc: Set ADT implementation
-}


module HW10 (
  Set (Elem, EmptySet),
  member,
  add,
  remove,
  size,
  subset,
  union,
  intersect,
  difference,
  filterSet,
  toList
) where

data Set a = Elem a (Set a)
           | EmptySet
           deriving (Show, Eq)

-- TODO: Implement each of the functions below. For each function
-- include the function's type. The type of the member function (as well
-- as a "stubbed out" implementation) is given below as an
-- example. You are NOT allowed to use any if-then-else expressions in
-- your implementation. See the homework assignment for additional
-- information and restrictions.

-- (1). member
member :: Eq a => a -> Set a -> Bool
member _ EmptySet = False
member n (Elem x s)
  | n == x = True
  | otherwise = member n s

-- (2). add
add :: Eq a => a -> Set a -> Set a
add n EmptySet = Elem n EmptySet
add n s | member n s == True = s
add n (Elem x s) = Elem x (add n s)

-- (3). remove
remove :: Eq a => a -> Set a -> Set a
remove n EmptySet = EmptySet
remove n s | member n s == False = s
remove n (Elem x s) 
  | n == x = remove n s
  | otherwise = Elem x (remove n s)

-- (4). size
size :: Set a -> Int
size EmptySet = 0
size (Elem x s) = 1 + size s

-- (5). subset
subset :: Eq a => Set a -> Set a -> Bool
subset EmptySet _ = True
subset (Elem x n) s 
  | member x s == False = False
  | otherwise = subset n s

-- (6). union
union :: Eq a => Set a -> Set a -> Set a
union EmptySet s = s
union (Elem x n) s
  | member x s == True = union n s
  | otherwise = union n (add x s)

-- (7). intersect
intersect :: Eq a => Set a -> Set a -> Set a
intersect EmptySet _ = EmptySet
intersect _ EmptySet = EmptySet
intersect (Elem x n) (Elem y s)
  | x == y = Elem x (intersect n s)
  | (member x s) == True = Elem x (intersect n s)
  | (member y n) == True = Elem y (intersect n s)
  | otherwise = intersect n s

-- (8). difference
difference :: Eq a => Set a -> Set a -> Set a
difference s EmptySet = s
difference s (Elem x n)
  | member x s == True = difference (remove x s) n
  | otherwise = difference s n

-- (9). filterSet
--   Note: functions can be passed in as named arguments and called
--   within the body of the function. For example, here is a simple
--   implementation of the standard map function over lists:
--       map _ [] = []
--       map f (x:xs) = f x : map f xs
filterSet :: Eq a => (a -> Bool) -> Set a -> Set a
filterSet _ EmptySet = EmptySet
filterSet f (Elem x s)
  | (f x) == True = Elem x (filterSet f s)
  | otherwise = filterSet f s

-- (10). toList
toList :: Eq a => Set a -> [a]
toList EmptySet = []
toList (Elem x s) = x : toList s
