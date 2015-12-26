## PA5 FAQ

#### Relationship between position *(x, y)* and game board grid *width x height*. Also, isn't there an out-of-bounds bug in one of the tests?
The convention used in the game is the standard matrix convention: 

1. In position (x, y), x indexes the rows, so also the height.
2. In position (x, y), y indexes the columns, so also the width.
3. Positions are always defined as (row, col), so (x, y).
4. A somewhat looser convention is to define a matrix (game board grid) as width by height (w x h).

#### How will the smoketest generate InsufficientDimensionsEx with width=2?
Notice the constants 
```C++
Game::MIN_WIDTH=3 
```
and
```C++
Game::MIN_HEIGHT=3
```
The exception was defined to be called in the *Game* constructor.

#### I keep receiving the error 
```
"terminate called after throwing an instance of 'std::regex_error'" "throw_regex_error(regex_constants::error_brack);"
```
You are using GCC with version less than 4.9.0, in which full support for C++11 <regex> was [added](https://isocpp.org/blog/2014/04/gcc-4.9.0). C++11 compiler support is required for this course. Consider upgrading. If you are on Ubuntu/Mint, here is a helpful [link](http://superuser.com/questions/772954/install-gcc-g-version-4-9-in-linux-mint).

#### 
