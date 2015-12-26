## PA5 FAQ

#### Relationship between position *(x, y)* and game board grid *width x height*. Also, isn't there an out-of-bounds bug in one of the tests?
The convention used in the game is the standard matrix convention: 

1. In position (x, y), x indexes the rows, so also the height.
2. In position (x, y), y indexes the columns, so also the width.
3. Positions are always defined as (row, col), so (x, y).
4. A somewhat looser convention is to define a matrix (game board grid) as width by height (w x h).

#### How will the smoketest generate InsufficientDimensionsEx with width=2?
Notice the *static* constants 
```C++
const unsigned Game::MIN_WIDTH = 3;
```
and
```C++
const unsigned Game::MIN_HEIGHT = 3;
```
The exception was defined to be called in the *Game* constructor.

#### In the printout tests, I keep receiving the error 
```
"terminate called after throwing an instance of 'std::regex_error'" "throw_regex_error(regex_constants::error_brack);"
```
You are using GCC with version less than 4.9.0, in which full support for C++11 &lt;regex&gt; was [added](https://isocpp.org/blog/2014/04/gcc-4.9.0). C++11 compiler support is required for this course. Consider upgrading. If you are on Ubuntu/Mint, here is a helpful [link](http://superuser.com/questions/772954/install-gcc-g-version-4-9-in-linux-mint).

#### What do I do with the method
```C++
Advantage::getCapacity()
```
As stated elsewhere in the requirements, you are supposed to return the present capacity multiplied by the *static* constant
```C++
const double Advantage::ADVANTAGE_MULT_FACTOR = 2.0;
```

#### How do I implement _Piece::operator*()_? What do I do in _Piece::interact()_? How do I use _Piece::finish()_?
Study, run, and understand the code in this [section](http://www.linuxtopia.org/online_books/programming_books/thinking_in_c++/Chapter15_027.html) of Bruce Eckel's *Thinking in C++*. The code was analyzed in class twice and is referenced from the PA5 requirements. In short, the virtual function mechanism implements *single* (late) dispatch, which means that when a virtual method is called, the mechanism dereferences a function pointer from the calling object's virtual table, thus executing the correct version of the function. Since _Piece::operator*()_ (aka "interaction operator") implements an interaction of two objects, one calling and one a right-hand side argument) (e.g. in _a * b_, a is the calling object and b is the argument), there are two objects with unknown runtime (dynamic) type. Therefore, single dispatch is not enough as it will only help determine the runtime type of one of the objects. Double dispatch is needed, instead. This is implemented by adding an overloaded pure virtual _interact()_ function. The overridden _operator*()_ only calls the _interact()_ function on the right-hand side object with its own *this* pointer as an argument. This is the second virtual function dispatch. The _interact()_ functions, implemented by each of the derived types that need to participate in an interaction, actually implement the functionality of the interaction, including terminating objects that have been consumed (as with _Resource_) or defeated (as with _Agent_). The _finish()_ function is provided to achieve the termination of _Agent_ objects, and should be called from the _interact()_ functions.
