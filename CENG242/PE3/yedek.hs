module PE3 where

data Cell = SpaceCraft Int | Sand | Rock Int | Pit deriving (Eq, Read, Show)

type Grid = [[Cell]]
type Coordinate = (Int, Int)

data Move = North | East | South | West | PickUp | PutDown deriving (Eq, Read, Show)

data Robot = Robot { name :: String,
                     location :: Coordinate,
                     capacity :: Int,
                     energy :: Int,
                     storage :: Int } deriving (Read, Show)

-------------------------------------------------------------------------------------------
--------------------------------- DO NOT CHANGE ABOVE -------------------------------------
------------- DUMMY IMPLEMENTATIONS ARE GIVEN TO PROVIDE A COMPILABLE TEMPLATE ------------
------------------- REPLACE THEM WITH YOUR COMPILABLE IMPLEMENTATIONS ---------------------
-------------------------------------------------------------------------------------------
-------------------------------------- PART I ---------------------------------------------

--
isInGrid :: Grid -> Coordinate -> Bool
isInGrid grid coor = (fst coor) >= 0 && (snd coor) >= 0 && (fst coor) < col && (snd coor) < row where
                     row = length grid
                     col = length (grid !! 0)

-------------------------------------------------------------------------------------------

totalCountOneList :: [Cell] -> Int
totalCountOneList [] = 0
totalCountOneList (Rock a:xs) = a + totalCountOneList xs
totalCountOneList (_:xs) = totalCountOneList xs

totalCount :: Grid -> Int
totalCount grid = totalSum where
                  sumList = [totalCountOneList list | list <- grid]
                  totalSum = sum sumList 

-------------------------------------------------------------------------------------------

coordinatesOfPitsOneListOnce :: Int -> [(Int, Cell)] -> ([Coordinate], [(Int, Cell)])
coordinatesOfPitsOneListOnce rowNum [] = ([], [])
coordinatesOfPitsOneListOnce rowNum ((a, Pit):xs) = ([(a, rowNum)], xs) 
coordinatesOfPitsOneListOnce rowNum (_:xs) = ([], xs)

coordinatesOfPitsOnce :: [(Int, [(Int, Cell)])] -> ([Coordinate], [(Int, [(Int, Cell)])])
coordinatesOfPitsOnce [] = ([],[])
coordinatesOfPitsOnce [(a, [])] = ([], [])
coordinatesOfPitsOnce (x:xs) = (coordinateOnceResult ++ coordinateList, [(fst x, remainingListOnce)] ++ remainingList) where
                               returnResult = coordinatesOfPitsOnce xs
                               coordinateList = fst returnResult
                               remainingList = snd returnResult
                               onceResult = coordinatesOfPitsOneListOnce (fst x) (snd x)
                               coordinateOnceResult = fst onceResult
                               remainingListOnce = snd onceResult

coordinatesOfPitsUntilFinish :: [(Int, [(Int, Cell)])] -> ([Coordinate], [(Int, [(Int, Cell)])])
coordinatesOfPitsUntilFinish [] = ([],[])
coordinatesOfPitsUntilFinish zippedGrid = (resultCoord ++ fst recursiveResult, snd recursiveResult) where
                                        result = coordinatesOfPitsOnce zippedGrid
                                        resultCoord = fst result
                                        resultGrid = snd result
                                        recursiveResult = coordinatesOfPitsUntilFinish resultGrid

zipGrid :: Grid -> [(Int, [(Int, Cell)])]
zipGrid grid = zippedGrid where
                         zippedGrid = zip [0..] [zip [0..] a | a <- grid]

coordinatesOfPits :: Grid -> [Coordinate]
coordinatesOfPits grid = fst (coordinatesOfPitsUntilFinish zippedGrid) where
                         zippedGrid = zipGrid grid

-------------------------------------------------------------------------------------------

tracePathHelper :: Int -> Int -> Coordinate -> Bool -> Int -> Grid -> [Move] -> [Coordinate]
tracePathHelper _ _ _ _ _ _ [] = []
tracePathHelper m n coord False energy grid (x:xs) = [coord] ++ tracePathHelper m n coord False energy grid xs 
tracePathHelper m n coord True 0 grid (x:xs) = [coord] ++ tracePathHelper m n coord False 0 grid xs
tracePathHelper m n coord True energy grid (x:xs) = [newCoord] ++ tracePathHelper m n newCoord ableToMove newEnergy grid xs where
                                                    newCoord = if energy >= energyReq && not (elem coord pits)
                                                        then case x of West -> if (fst coord - 1) >= 0 then (fst coord - 1, snd coord) else coord
                                                                       East -> if (fst coord + 1) < n then (fst coord + 1, snd coord) else coord
                                                                       South -> if (snd coord + 1) < m then (fst coord, snd coord + 1) else coord
                                                                       North -> if (snd coord - 1) >= 0 then (fst coord, snd coord - 1) else coord
                                                                       PickUp -> coord
                                                                       PutDown -> coord
                                                    else coord
                                                    ableToMove = if energy >= energyReq then
                                                         if elem newCoord pits || elem coord pits then False
                                                            else True 
                                                         else False
                                                    newEnergy = if energy >= energyReq then energy - energyReq else 0
                                                    energyReq = case x of West -> 1
                                                                          East -> 1
                                                                          North -> 1
                                                                          South -> 1
                                                                          PickUp -> 5
                                                                          PutDown -> 3
                                                    pits = coordinatesOfPits grid

tracePath :: Grid -> Robot -> [Move] -> [Coordinate]
tracePath grid robot moves = tracePathHelper m n coord True energyOfRobot grid moves where
                            m = length grid
                            n = length (grid !! 0)
                            coord = location robot
                            energyOfRobot = energy robot

------------------------------------- PART II ----------------------------------------------

checkIfSpaceCraft :: Cell -> Bool
checkIfSpaceCraft (SpaceCraft _) = True
checkIfSpaceCraft _ = False

findSpaceCraft :: Grid -> Coordinate
findSpaceCraft grid = [(fst cell, fst row) | row <- zippedGrid, cell <- (snd row), checkIfSpaceCraft (snd cell)] !! 0 where
    zippedGrid = zipGrid grid

setStorageOfRobot :: Int -> Robot -> Robot
setStorageOfRobot value robot = robot{storage = value}
setEnergyOfRobot :: Int -> Robot -> Robot
setEnergyOfRobot value robot = robot{energy = value}
setLocationOfRobot :: Coordinate -> Robot -> Robot
setLocationOfRobot coord robot = robot{location = coord}

energiseRobots :: Grid -> [Robot] -> [Robot]
energiseRobots grid [] = []
energiseRobots grid (robot:xs) = [newRobot] ++ energiseRobots grid xs where
    spaceCraftLocation = findSpaceCraft grid
    gain = if 100 - (xDiff + yDiff) * 20 >= 0 then 100 - (xDiff + yDiff) * 20 else 0
    xDiff = abs (fst spaceCraftLocation - (fst $ location robot))
    yDiff = abs (snd spaceCraftLocation - (snd $ location robot))
    newEnergy = if gain + energy robot > 100 then 100 else gain + energy robot
    newRobot = setEnergyOfRobot newEnergy robot

-------------------------------------------------------------------------------------------

numOfRocks :: Cell -> Int
numOfRocks (Rock a) = a
numOfRocks (SpaceCraft a) = a

getCell :: Grid -> Coordinate -> Cell
getCell grid coord = grid !! (snd coord) !! (fst coord)

setList :: [Cell] -> Int -> Int -> Cell -> [Cell]
setList [] _ _ _ = []
setList (x:xs) indexToSet curIndex object = if indexToSet == curIndex then [object] ++ setList xs indexToSet (curIndex+1) object else [x] ++ setList xs indexToSet (curIndex+1) object

setGrid :: Grid -> Coordinate -> Cell -> Grid
setGrid grid coord object = setGridRecursive grid coord object 0 where
    setGridRecursive [] _ _ _ = []
    setGridRecursive (row:xs) coord object curRowNumber = if curRowNumber /= (snd coord) 
        then [row] ++ setGridRecursive xs coord object (curRowNumber + 1) 
        else [setList row (fst coord) 0 object] ++ setGridRecursive xs coord object (curRowNumber + 1)

applyMoves :: Grid -> Robot -> [Move] -> (Grid, Robot)
applyMoves grid robot [] = (grid, robot)
applyMoves grid robot (PickUp:xs) = applyMoves newGrid newRobot xs where
    energyReq = 5
    isEnergyEnough = (energy robot - energyReq) >= 0
    newEnergy = if isEnergyEnough then energy robot - energyReq else 0
    isStorageEnough = (storage robot < capacity robot)
    numberOfRocks = numOfRocks (getCell grid (location robot))
    doesRockExist = numberOfRocks > 0
    success = isEnergyEnough && isStorageEnough && doesRockExist
    newStorage = if success then (storage robot) + 1 else storage robot
    newGrid = if success then setGrid grid (location robot) (Rock (numberOfRocks - 1)) else grid
    newRobot = setEnergyOfRobot newEnergy (setStorageOfRobot newStorage robot)
applyMoves grid robot (PutDown:xs) = applyMoves newGrid newRobot xs where
    energyReq = 3
    isEnergyEnough = (energy robot - energyReq) >= 0
    newEnergy = if isEnergyEnough then energy robot - energyReq else 0
    success = isEnergyEnough
    numberOfRocks = numOfRocks (getCell grid (location robot))
    newGrid = if success then setGrid grid (location robot) (SpaceCraft (numberOfRocks + 1)) else grid
    newStorage = if success then (storage robot) - 1 else storage robot
    newRobot = setEnergyOfRobot newEnergy (setStorageOfRobot newStorage robot)
applyMoves grid robot (move:xs) = applyMoves grid newRobot xs where
    energyReq = 1
    isEnergyEnough = (energy robot - energyReq) >= 0
    newEnergy = if isEnergyEnough then energy robot - energyReq else 0
    position = location robot
    destination = case move of
        West -> (fst position -1, snd position)
        East -> (fst position + 1, snd position)
        North -> (fst position, snd position - 1)
        South -> (fst position, snd position + 1)
    inBounds = isInGrid grid destination
    pitList = coordinatesOfPits grid
    inPit = elem position pitList
    success = isEnergyEnough && inBounds && not inPit
    newLocation = if success then destination else position
    newRobot = setEnergyOfRobot newEnergy (setLocationOfRobot newLocation robot)
