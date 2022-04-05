# Developer Log

## Preface

Rosky is a pet project of mine that I've been working on since mid 2021. In the early stages of making this interpreter, I wanted a long term project and thought making a language on my own could be a good way to get immersed in C++, and the concepts of design from an architectural perspective.

I started this in my spare time during my first developer job out of college, a Software Engineer I position at a big company. I hopped on to an existing project with a large prexisting codebase. Of course as a Software Engineer I, my job wasn't big picture design. I was told what needed to happen, and I implemented it. There's a pleasure to getting those euphoric "eureka" moments when you solve one of your implementation tickets, and there's a nice feeling of being an actual contributor to a project as robust as the one I was working on.

But there's a certain aspect that's missing in plugging tickets as a lower software engineer. In the army, I compared it to moving sandbags. The spot you're moving them from and to has been plotted already by someone that wears a higher rank than you. Just grab the sandbag and move it to point B. Nothing wrong with that. And it doesn't come without it's challenges.

Design was the itch that I wanted to scratch. To be the general and the foot soldier at the same time. And this project was my outlet of doing that. Being able to put the pieces together of a large project from nothing; linking together and sketching the relationships between interworking components and then carrying my own sandbags was a truly rewarding task. And for the first 6 months-ish... i failed... big time.

This repo is actually my second repo after starting over from my first project. The true software "sandbag carrier" in me was too eager to get hands on keyboard and jump in. And it went exactly as well as you'd expect a private being promoted straight to general would go. I didn't respect the design as well as I should've. And frankly, being up against the wall, lacking motivation to continue a project because of how it irredeemably horrible my design was humbled me. It takes a lot to look at something you've sunk so much time into and scrap it.

But i scrapped it with a newfound respect for the process, and the background knowledge that goes into it. In between my first and second (current) attempts, I did my research. I sat down with books on compiler theory from a variety of professors, looked at design patterns that I thought could be effective in streamlining my design, and only even picked up a pen to start plotting design once I really felt ready. There's a difference between being scared to dive in and giving the preparation the respect it deserves, and I hoped I was achieving the latter.

I took the first week before putting my hands on keyboard prototyping different components, drawing dependency diagrams, and revisiting chapters in the compiler theory books I read. Finally after that I felt ready to put hands on keyboard again, and I created this respository. I hope this learning experience will give me a leg up as I work the ranks of the software engineering ladder and maybe even work my way to being the architect on a large scale project at a big company.

## March 24, 2022

* Created the repo!
* Started off writing a bare-bones lexer that I knew could be expanded upon as I added more complexity.
* Added parsing of command line arguments borrowed from my last repo.
* Created a source handler to read in the provided source file.

At the end of today, we could turn a source that looks like this:
| ![alt text](https://i.imgur.com/7uFTwvI.png "Source1") |
|:--:|

Into a table of tokens like this:
| ![alt text](https://i.imgur.com/bESIgbj.png "Token Table 1") |
|:--:|

Here's the current dependency diagram:
| ![alt text](https://i.imgur.com/bjg6MZV.png "Dependency Diagram 1") |
|:--:|

## March 25, 2022

Big day today.
* Created the main parser, which takes in the token table and makes parsing decisions based on the tokens it encounters.
* Created the expression parser, which turns a token table for an expression into a parse tree.
* Created the evaluator which evaluates and acts on the parse tree.
* Created the variable handler to manage the variable table, which for now is a basic map.
* Created the object interface which defines the behavior of all built-in objects
  * Created the first object, the integer, which inherits from the interface.

I can already tell the expression parser and evaluator are going to be the most complex components of this project. I love how elegant the expression parser is compared to my last attempt and how it uses the binary tree data structure.

For an expression like this:
```python
x = 2 + 3 * 4;
```

We get a token table that looks like this:
| ![alt text](https://i.imgur.com/UEP9xXg.png "Token Table 2") |
|:--:|

And the expression parser turns that table into a tree like this:
| ![alt text](https://i.imgur.com/qyWSgKd.png "Parse Tree 1") |
|:--:|

From there the evaluator can perform the operations, including calling the variable table backend for storing variables on assignment. These variables can later be retreived (during evaluation) in an expression like this:
```python
y = x + 4;
```

* I've also created the error_handler which streamlines throwing different kinds of errors throughout execution. It nicely reports the column and line number that the error occured at from the stored metadata of the token. Like so:
```python
x = 2 +;
```

| ![alt text](https://i.imgur.com/AXLH8RU.png "Error Report 1") |
|:--:|

And here's what the dependency diagram is looking like now! Much more complex!
| ![alt text](https://i.imgur.com/Z0c6m3J.png "Dependency Diagram 2") |
|:--:|

## March 26, 2022

Lots of structural changes today. I switched over the expression parse tree to be a tree of objects from the backend rather than a tree of tokens. It now falls on the parser to form the objects rather than the evaluator as it views the tokens.

This allows the parser to make recursive calls to itself whenever it needs to do intermediate evaluations, such as parentheses, function calls, etc.

To test it out, I added parentheses as a viable token. So now we can run source like this:
```python
x = (1+2) * 3;
```

The expression parser will call itself recursively to evaluate the parentheses first.

No new files added with this change, but since the parser is now responsible for object creation we see it referencing the variable handler and the object backend. Here's the dependency diagram. I've cleaned up the diagram a little bit to only show the major components rather than every file.
| ![alt text](https://i.imgur.com/6gIiLms.png "Dependency Diagram 3") |
|:--:|

## March 27, 2022

A few more structural changes today based off of a learning experience i had about the ```static``` keyword in C++. I thought it worked similar to python global variables in that i define a static instance of something once and all external files will share the instance, but that wasn't the case.

My workaround solution to this was to instantiate the things I had previously made static, which eliminated that nasty global variable "code smell" and replaces it with a nice RAII compliant design.

I then got annoyed with having to pass around the instances of my classes such as the variable handler to every parse function, so i made the Parser into an object as well, which the lexer instantiates before passing in the token table. The parser keeps these class instances as class members so all of it's sub components can use them rather than having to pass them into each function.

With that out of the way, I implemented variable scoping and the ```{``` and ```}``` tokens. Each variable is now stored with an associated scope attribute and when the current scope drops below the variable's scope, the variable is removed from the table. So a piece of code like this:
```python
{
    x = 4;
}
y = x;
```
will throw this error:
```
Error [Line 4 Column 5]: Unrecognized symbol: 'x'
Exiting...
```

which is the behavior I want. I like the scoping rules that C and C++ offer, so I integrated that style into my language.

The dependency diagram hasn't changed, so no updates there.

---

Another entry in the same day. I added a second object type to the object backend, this time pointers. I think an inclusion of a raw pointer into an interpreted language is an appealing concept to tackle. Python purposefully stayed away from this feature. This is a quote from the website ```realpython.com```:

```
"Could pointers in Python exist natively?
Probably, but pointers seem to go against the Zen of Python.
Pointers encourage implicit changes rather than explicit.
Often, they are complex instead of simple, especially for beginners.
Even worse, they beg for ways to shoot yourself in the foot,
or do something really dangerous like read from a section of
memory you were not supposed to."
```

In my mind, I see Rosky as a quick and dirty scripting language. My language isn't meant to have any sort of safety handrails. I love the freedom that C++ and C gives with respect to memory management, and the ease of use of python. Rosky is the features I like from both languages put together into a feature-rich language that won't stop you from doing what you want to do (including blow your foot off).

So pointers seem to naturally follow this mantra. It came with a host of different side-effects, such as having to restructure the parse tree again to contain underlying _pointers_ to objects, rather than just the objects. When we pass objects around in a parse tree, or during evaluation, copies of the objects are made (it's actually in a shared_ptr but the concept is the same). This means that when we edit a raw object, it's editing the copy, and the actual data in the variable table, for instance, isn't affected. So we have to carry a pointer to the actual data if it's applicable. Makes the parse nodes in the tree a pointer heavier, but that's ok.

Now we can do things like this. Don't see this in Python!
```python
x = 4;

ptr = @x; # I use the '@' operator for 'address of'

*ptr = 6; # x is now 6 via dereference

z = x; # z is 6
```

I like this change a lot. It also introduced the first unary operators in Rosky: the ```@``` operator and the ```*``` operator ('address of' and 'dereference' respectively. Which was a quick behavior edit in the expression parser.

The dependency diagram has not changed, but the object backend now contains the pointer class which inherits from the object interface.

## March 28, 2022

I added the null object type as well as the first few keywords into the language. The null type will act similarly to Python's ```None``` object. I mainly added this in because tomorrow I hope to add the foundations of the function handler. When the return type of a "void" function is requested, the null object should be returned. Like this:
```python
# 'out' will be my 'print' function to stdout
x = out("Hello, World!");

out(x); # "Null"
```

```out``` will be a void function that prints to stdout, so when we try to get a value from it, it will return with the null object.

I also added the ```null``` and ```nullptr``` keywords, which are the first reserved keywords in the language. The parse_expr function will form a ```null``` object and a pointer with the value nullptr when assigned respectively.

So now we can do things like this:
```cpp
x = nullptr;

y = null;
```

I also added an error message for trying to dereference a nullptr:
```cpp
x = nullptr;
y = *x;
```
```
Error [Line 2 Column 5]: Attempt to dereference null pointer
Exiting...
```

## March 29, 2022

As mentioned in my last entry, I implemented the foundation for the function backend today. The function backend consists of a function table object which is a mapping between the name of a function and a function pointer.

As of right now, I've only implemented built-in functions. User defined functions will come a bit later, although I have a good idea as to how I want to tackle them.

When a function is encountered by the expression parser, it is handed off to the function parser, which formats the provided arguments (throwing errors if necessary) and then calling the ```call_function``` function of the backend to execute the built-in function given the arguments.

The two built-in functions I've implemented so far is ```out``` and ```outln``` which are really the same thing except ```outln``` inserts a new line after. Both of these functions print a given argument to standard output. Like so:

```python
x = 4;
y = null;

outln(y);
out(x);
```
```
null
4
```

Where I diverge from python is that python allows the user to overwrite reserved functions. So this is valid syntax is python
```python
print = 5 # overwriting of a reserved function name
```

I've decided that is not allowed in Rosky, so doing something similar will produce an error:
```python
out = 2;
```
```
Error [Line 1 Column 1]: Syntax error: 'Illegal use of reserved function name 'out''
Exiting...
```

Here's what the dependency diagram is looking like now. Note the addition of the function handler in the backend:
| ![alt text](https://i.imgur.com/ARaTcxP.png "Dependency Diagram 4") |
|:--:|

## March 30, 2022

Today I added the built in string type for the language. Strings are surrounded in double quotes. I've also added a couple escape sequences such as ```\n``` and ```\t```. All of that processing is handled in the lexer, so if a string is improperly formatted (i.e. unclosed quote or bad escape sequence) it will not be sent to the parser.

So now without further ado...
```python
out("Hello, World!");
```
```
Hello, World!
```

That feels really good to see working. I've also added the string concatenation operator ```&```, similar to Ada's string concat operator. This will convert the left and right side's of the operator to strings and put them together, like so:
```python
name = "Mike";

out("Hello, " & name & "!");
```
```
Hello, Mike!
```

Concatenation also works with non-string types:
```python
x = 92;
ptr = @x;

out("x is " & *ptr & " and is located at address " & ptr);
```
```
x is 92 and is located at address 0x9e8fc0
```

Very happy with the progress so far and how easy it was to make these changes. It shows how a good foundational design goes a long way when expanding new features down the road. All of today's changes took less than an hour before I went in to work. I'm very happy with the design so far.

The dependency diagram has not changed, but the object backend now has the string class defintion.

## March 31, 2022

Today I added the ```bool``` type to the project as well as the ```==``` operator. Creating a relationship table between each object type in comparison operations was something I had planned out before I started, so it was just a matter of putting in my design notes. I also added the ```true``` and ```false``` keywords.

The most interesting one was the ```null``` type. The ```null``` type will only ever return ```true``` in a comparison when compared to another ```null``` type. So for example:
```python
null == 0;
null == true;
null == false;
null == "";
null == nullptr;
```
all return ```false```! However,
```python
null == null;
```
returns ```true```.

The goal with null is to test if an object is "legitimate" or not. So ```false``` and ```nullptr```, while typically being thought of as the negative state, is still a valid object, so it will return ```false``` when compared to ```null```.

This addition sets the stage for my plans for either later today or tomorrow: the first bits of control flow! I'm going to look to add ```if``` statements and ```while``` loops in the next entry, and of course we need boolean logic for that.

---

I've gone ahead an added the ```if``` statement and the ```while``` loop to the parser. It leverages a recrusive call to the expression parser to evaluate the condition, and then recursively calls the main parser within the body if the condition is ```true```.

Here's an example of this in action:
```python
if true {
    outln("Condition is true");
}
```
```
Condition is true
```

Note that the syntax follows C/C++'s approach in that the body must be wrapped in ```{``` ```}```, but differs in that the condition does NOT need to be wrapped in ```(``` ```)```. 

So this syntax still works fine:
```python
if (true) {
    outln("Condition is true");
}
```
but the parentheses around ```true``` are unnecessary.

In the next entry I'll add the ```elsif``` and ```else``` clauses. I also would like to add ```continue``` and ```break``` statements to while loops, but that isn't as straight forward. The while loop parser calls the main parse function recursively, so I'll have to add some sort of flag there to let the main parse function know that it is in a loop or not. I'm not sure if it would be smarter to add the flag as a member of the ```Parser_T``` class, or as an argument in the main parse function.

The ```break``` keyword also comes with a bit more complexity, because it has to let the while loop parser know that we're breaking so it doesn't check the condition again. I'm sure another flag can take care of this, but I'm not sure where to put it yet.

## April 1, 2022

I've decided to stop working on this project. I've just gotten a little tired or how this project is turning out. April fools of course! Another day another feature! I've gone ahead and implemented the ```elsif``` and ```else``` keywords, which came with a rework to the ```parse_if``` function. Now we can run code like this:
```python
y = 2;
ptr = @y;

out("ptr -> ");
if ptr == nullptr {
    out("nullptr");
} else {
    out(*ptr);
}
```
```
ptr -> 2
```
It's really starting to feel and look like a legitimate language.

---

Another feature I tackled today, a bit off topic, was member functions. Member functions was a thing I've had in the "design works" for quite a few days now and I finally found a design that I felt the most confident with.

Member functions are a little trickier than the normal functions we already have. The trick being that not only do we have to do all the normal function parsing along with the actual function invoking, but we have to pass the object being acted upon as well. For instance:
```python
name = "Lukey";

name_len = name.size();
```
My expression parser will go left to right forming the tree function, so when we arrive at the ```.```, the tree looks like this:
| ![alt text](https://i.imgur.com/dulT8SG.png "Member function tree 1") |
|:--:|

We can see the ```name``` object is already in the parse tree, but now we encounter the ```.``` operator. We can't simply insert the ```.``` as a normal operator on the tree and the ```size()``` as it's right child. The parse tree is a tree of objects and operators and ```size()``` is an invocable function. So how do we go about performing the member function on the ```name``` object?

My solution was when we encounter a ```.``` operator, we ensure that the token to it's right (in this case ```size```) actually names a function. We then retreive the object that was last inserted into the tree, which is always the right-most node. And because the ```.``` operator will throw if we're not expecting an operator, the tree is guaranteed to not be null, so object retreival will always succeed.

We retreive the right-most object, send the function off along with the object to be handled by the function backend, but now what?

Our tree still looks the same. We essentially have to replace the node that we just retreived with the new object formed by the member function. This can be done by either popping the node upon retreival and inserting the new object as normal, or by replacing the contents of the right-most node with the new object contents, and I opted for the latter, but either would work fine.

So after the function backend is called and the object is replaced, the tree would look like this:
| ![alt text](https://i.imgur.com/TqBZU3t.png "Member function tree 1") |
|:--:|

And from then on we let the tree be evaluated. So this code outputs:
```python
name = "Lukey";

name_len = name.size();

out(name & " is " & name_len & " letters long");
```
```
Lukey is 5 letters long
```

## April 4, 2022

Now that most of the core features of the language are in place, I'm able to start fleshing out of the features of the language. The biggest thing I added today was the ```group``` data type. This is similar to a python ```list``` in that it is a collection of objects:
```python
x = [1,2,3];

out(x);
```
```
[1, 2, 3]
```

This comes with the concept called "iterators". ```strings``` and ```groups``` are considered iterators in Rosky, meaning they can be indexed as such:
```python
s = "Hello";
g = [1,2,3];

outln(s[0]);
out(g[0]);
```
```
H
1
```

The key difference in these two objects is that a group is considered an "addressable" iterator. This means that the objects that a ```group``` is holding are considered "l-values" just as variables are, while non-addressable iterators like ```string``` have their indexable objects considered "r-values".

So for example:
```python
g = [1,2,3];

g[0] = 4;
```
runs fine, and ```g``` is now ```[4,2,3]```. Whereas:
```python
s = "hello";

s[0] = "a";
```
will throw:
```
Error [Line 3 Column 6]: Attempt to assign to r-value
Exiting...
```

This also has applications in pointers:
```python
g = [1,2,3];

ptr = @g[0]; # ptr holds the address of the 0th object of g

*ptr = 4;

out(g);
```
```
[4, 2, 3]
```

Conversely, we aren't able to take the address of an indexed string because it is considered an r-value:
```python
s = "hello";

ptr = @s[0];
```
```
Error [Line 3 Column 7]: Attempt to get address of temporary
Exiting...
```

I've also added the ```append``` member function to the ```group``` data type"
```python
x = [1,2,3];
x.append(4);
out(x);
```
```
[1, 2, 3, 4]
```

---

The next feature added today was the ```break``` and ```continue``` keywords. To make these work I added a few flags to the parser object, namely a "break" flag, "continue" flag, and "loop" flag.

The "break" flag is asserted when we encounter a break statement, and tells the ```while``` parser to terminate. The ```while``` parser then deasserts the flag.

The "continue" flag works the exact same way, except the ```while``` parser loops again instead of breaking.

Finally the "loop" flag is asserted when we are in a loop, which allows us to throw errors if we encounter ```break``` and ```continue``` outside of a loop. Like so:
```python
break;
```
```
Error [Line 1 Column 1]: Bad use of reserved keyword: 'break' not in loop
Exiting...
```

So now we can make a counter like this: (Using the operators that we currently have implemented)
```python
idx = 0;
while true {
    idx = idx + 1; 
    out(idx & " ");
    if idx == 10 {
        break;
    }
}
```
```
1 2 3 4 5 6 7 8 9 10
```

---

I've also added in the ```assert``` function which throws an error if the condition it is given is false, and will print an optional string if supplied:
```python
x = 5;
y = @x;

assert(y == nullptr, "y is non nullptr");
```
```
Error [Line 4 Column 1]: Assertion error: y is non nullptr
Exiting...
```

The next feature I'm looking to add is custom user functions.
