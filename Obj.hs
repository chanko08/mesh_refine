module Obj where

type Vertex = (Float, Float, Float, Float)

data ObjDataType = GeometricVertex | Polygon deriving Eq

data ObjData = 
    GVertex {
        vertex::Vertex,
        dType ::ObjDataType
    }
    | Face {
        vertexIndices::[Int],
        dType ::ObjDataType
    }
    deriving Eq

instance Show ObjData where
    showsPrec _ r = showObjData r where


        showObjData (GVertex verts _) s = shows ("v " ++ vertexToStr verts) s where
            vertexToStr (x,y,z,w) = init . concat . map (\x -> show x ++ " ") $ [x,y,z,w]


        showObjData (Face indices _) s = shows face s where
            face = "f " ++ (init . concat . map (\x -> show x ++ " ") $ indices)

instance Read ObjData where
    readsPrec _ r = parseObjData r where

        parseObjData "" = []
        parseObjData (s:str)
            | s == 'v' = parseVertexType str 
            | s == 'f' = parseFaceType str
            | otherwise = [] where


        parseVertex str
            | length pts >= 4 = (take 4 pts, rest 3)
            | length pts == 3 = (pts ++ [1.0], rest 2) 
            | otherwise       = ([],  rest 0) where
            floats = floatSeq str
            pts = map fst $ floats
            rest i = (map snd $ floats) !! i
            floatSeq s 
                | res == [] = []
                | otherwise = head res : floatSeq s2 where
                    res = reads s::[(Float, String)]
                    (i,s2) = head res


        parseVertexType (' ':str)
            | numFloats == 4 = [(GVertex (x,y,z,w) GeometricVertex, rest)]
            | otherwise = [] where
            (floats,rest) = parseVertex str
            [x,y,z,w] = floats
            numFloats = length floats


        parseFaceType str 
            | numIndices > 0 = [(Face indices Polygon, rest)]
            | otherwise = [] where
            ints = intSeq str
            indices = map fst $ ints
            rest = snd . last $ ints
            numIndices = length indices
            intSeq s
                | res == [] = []
                | otherwise = head res : intSeq s2 where
                    res = reads s::[(Int, String)]
                    (i, s2) = head res
         

data ObjFile = ObjFile {
    vertices :: [ObjData],
    faces ::[ObjData]
} deriving Show

loadObjFile f = ObjFile vs fs where
    objects = map (fst . head) . filter (\x -> x /= []) . map (\x -> reads x::[(ObjData,String)]) . lines $ f
    vs = filter (\x -> dType x == GeometricVertex) objects
    fs = filter (\x -> dType x == Polygon) objects






   
    

