## PA5 FAQ

#### Relationship between position *(x, y)* and game board grid *width x height*. Also, isn't there an out-of-bounds bug in one of the tests?
The convention used in the game is the standard matrix convention:
1. In position (x, y), x indexes the rows, so also the height.
2. In position (x, y), y indexes the columns, so also the width.
3. Positions are always defined as (row, col), so (x, y).
4. A somewhat looser convention is to define a matrix (game board grid) as width by height (w x h).

