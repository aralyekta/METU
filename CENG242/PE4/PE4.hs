module PE4 where

import Data.Maybe -- up to you if you want to use it or not

-- Generic DictTree definition with two type arguments
data DictTree k v = Node [(k, DictTree k v)] | Leaf v deriving Show

-- Lightweight Char wrapper as a 'safe' Digit type
newtype Digit = Digit Char deriving (Show, Eq, Ord) -- derive equality and comparison too!

-- Type aliases
type DigitTree = DictTree Digit String
type PhoneNumber = [Digit]


---------------------------------------------------------------------------------------------
------------------------- DO NOT CHANGE ABOVE OR FUNCTION SIGNATURES-------------------------
--------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
--------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
---------------------------------------------------------------------------------------------


----------
-- Part I:
-- Some Maybe fun! Basic practice with an existing custom datatype.

-- toDigit: Safely convert a character to a digit
toDigit :: Char -> Maybe Digit
toDigit a | a == '0' = Just $ Digit a
    | a == '1' = Just $ Digit a
    | a == '2' = Just $ Digit a
    | a == '3' = Just $ Digit a
    | a == '4' = Just $ Digit a
    | a == '5' = Just $ Digit a
    | a == '6' = Just $ Digit a
    | a == '7' = Just $ Digit a
    | a == '8' = Just $ Digit a
    | a == '9' = Just $ Digit a
    | otherwise = Nothing

-- toDigits: Safely convert a bunch of characters to a list of digits.
--           Particularly, an empty string should fail.

{-
concatMaybeDigits :: Maybe PhoneNumber -> Maybe PhoneNumber -> Maybe PhoneNumber
concatMaybeDigits Nothing Nothing = Nothing
concatMaybeDigits (Just phone) Nothing = Just phone
concatMaybeDigits Nothing (Just phone) = Just phone
concatMaybeDigits (Just []) (Just []) = Just []
concatMaybeDigits (Just []) (Just phone) = Just phone
concatMaybeDigits (Just phone) (Just []) = Just phone
concatMaybeDigits (Just phone1) (Just phone2) = Just (phone1++phone2)
-}

turnDigitPhNumber :: Maybe Digit -> Maybe PhoneNumber
turnDigitPhNumber Nothing = Nothing
turnDigitPhNumber (Just a) = Just [a]

getDigitList :: Maybe PhoneNumber -> PhoneNumber
getDigitList phoneNumber = fromMaybe [] phoneNumber 

toDigits :: String -> Maybe PhoneNumber
toDigits [] = Nothing
toDigits [x] = if digitised == Nothing then Nothing else turnDigitPhNumber digitised where
    digitised = toDigit x
toDigits (x:xs) = if digitised == Nothing || recResult == Nothing then Nothing else (Just concatedList) where
    concatedList = list1 ++ list2
    list1 = getDigitList listedx
    digitised = toDigit x
    listedx = turnDigitPhNumber digitised
    list2 = getDigitList recResult
    recResult = toDigits xs

-----------
-- Part II:
-- Some phonebook business.

-- numContacts: Count the number of contacts in the phonebook...
numContacts :: DigitTree -> Int
numContacts (Leaf a) = 1
numContacts (Node list) = sum sumList where
    sumList = map numContacts sndList
    sndList = map snd list

evalLevel :: PhoneNumber -> PhoneNumber -> [DigitTree] -> [(PhoneNumber, String)]
evalLevel _ [] _ = []
evalLevel _ _ [] = []
evalLevel phone (dig:digs) (nod:nods) = (getContactsHelper (phone ++ [dig]) nod) ++ 
    evalLevel phone digs nods

getContactsHelper :: PhoneNumber -> DigitTree -> [(PhoneNumber, String)]
getContactsHelper phone (Leaf a) = [(phone, a)]
-- We can assume that treeList is not empty
getContactsHelper phone (Node treeList) = evalLevel phone list1 list2 where
    list1 = map fst treeList
    list2 = map snd treeList

-- getContacts: Generate the contacts and their phone numbers in order given a tree. 
getContacts :: DigitTree -> [(PhoneNumber, String)]
getContacts tree = getContactsHelper [] tree

removeUnnecessary :: Digit -> [(Digit, DigitTree)] -> (Maybe DigitTree)
removeUnnecessary _ [] = Nothing
removeUnnecessary digit (x:xs) = if (fst x) == digit then Just (snd x) else removeUnnecessary digit xs

autoCompleteHelper :: PhoneNumber -> (Maybe DigitTree) -> (Maybe DigitTree)
autoCompleteHelper _ Nothing = Nothing
autoCompleteHelper [] tree = tree
autoCompleteHelper _ (Just (Leaf a)) = Nothing
autoCompleteHelper (x:xs) (Just (Node treeList)) = autoCompleteHelper xs singleElement where
        singleElement = removeUnnecessary x treeList


-- autocomplete: Create an autocomplete list of contacts given a prefix
-- e.g. autocomplete "32" areaCodes -> 
--      [([Digit '2'], "Adana"), ([Digit '6'], "Hatay"), ([Digit '8'], "Osmaniye")]

autocomplete :: String -> DigitTree -> [(PhoneNumber, String)]
autocomplete str tree = if phone == Nothing || isNothing subTree then [] else getContacts subTreeItself where
    phone = toDigits str
    subTree = autoCompleteHelper (getDigitList phone) (Just tree)
    subTreeItself = fromMaybe (Leaf "empty") subTree


-----------
-- Example Trees
-- Two example trees to play around with, including THE exampleTree from the text. 
-- Feel free to delete these or change their names or whatever!

exampleTree :: DigitTree
exampleTree = Node [
    (Digit '1', Node [
        (Digit '3', Node [
            (Digit '7', Node [
                (Digit '8', Leaf "Jones")])]),
        (Digit '5', Leaf "Steele"),
        (Digit '9', Node [
            (Digit '1', Leaf "Marlow"),
            (Digit '2', Node [
                (Digit '3', Leaf "Stewart")])])]),
    (Digit '3', Leaf "Church"),
    (Digit '7', Node [
        (Digit '2', Leaf "Curry"),
        (Digit '7', Leaf "Hughes")])]

areaCodes :: DigitTree
areaCodes = Node [
    (Digit '3', Node [
        (Digit '1', Node [
            (Digit '2', Leaf "Ankara")]),
        (Digit '2', Node [
            (Digit '2', Leaf "Adana"),
            (Digit '6', Leaf "Hatay"),
            (Digit '8', Leaf "Osmaniye")])]),
    (Digit '4', Node [
        (Digit '6', Node [
            (Digit '6', Leaf "Artvin")])])]
