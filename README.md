# c-checkers-api
Simple C Api for russian checkers

This Api allows to check if the move is valid and allows to build game tree up to specified depth of moves.

#input data
Board - board it is two dimensional array of char
        //0    1    2    3    4    5    6    7
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //0
        {' ', '1', ' ', '1', ' ', '1', ' ', '1'},  //1
        {'1', ' ', '1', ' ', '1', ' ', '1', ' '},  //2
        {' ', '#', ' ', '#', ' ', '#', ' ', '#'},  //3
        {'#', ' ', '#', ' ', '#', ' ', '#', ' '},  //4
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'},  //5
        {'3', ' ', '3', ' ', '3', ' ', '3', ' '},  //6
        {' ', '3', ' ', '3', ' ', '3', ' ', '3'}}; //7

    '1' is white checker
    '2' is white king
    '3' is black checker
    '4' is black king
    '#' is empty black field
    ' ' is empty white field

#build
Use cmake to configure project for your prefferd compiler
