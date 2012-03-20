module Main( main ) where
import Control.Monad         ( filterM )
import System                ( getArgs )
import System.Console.GetOpt (
        getOpt, 
        usageInfo,
        ArgOrder (RequireOrder), 
        OptDescr (Option),
        ArgDescr (NoArg, ReqArg)
    )


main = do
    args  <- getArgs
    options <- case getOpt RequireOrder options args of
        ([],    [],      [])     -> error $ usageInfo header options
        (flags, [],      [])     -> return flags
        (_,     nonOpts, [])     -> error $ "unrecognized arguments: " ++ unwords nonOpts
        (_,     _,       msgs)   -> error $ concat msgs ++ usageInfo header options
    mapM_ execOption options


data Flag = Version | Help | Input String deriving Show


options = [
        Option ['V'] ["version"] (NoArg Version)        "show version number",
        Option ['i'] ["input"]   (ReqArg Input "FILE")  "the OBJ file to parse",
        Option []    ["help"]    (NoArg Help)           "display this help information"
    ]


header  = "Usage: main [OPTION...]"


version = "ObjLoader v0.1"


execOption :: Flag -> IO ()
execOption Version = putStrLn $ version
execOption Help    = putStrLn $ usageInfo header options
execOption (Input objFile) = do
    putStrLn $ "The file name is " ++ objFile
    contents <- readFile objFile
    let ls = lines contents
    print ls
    
