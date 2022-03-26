# Developer Log

## Preface

Rosky is a pet project of mine that I've been working on since mid 2021. In the early stages of making this interpreter, I wanted a long term project and thought making a language on my own could be a good way to get immersed in C++, and the concepts of design from an architectural perspective.

I started this in my spare time during my first developer job out of college, a Software Engineer I position at a big company. I hopped on to an existing project with a large prexisting codebase. Of course as a Software Engineer I, my job wasn't big picture design. I was told what needed to happen, and I implemented it. There's a pleasure to getting those euphoric "eureka" moments when you solve one of your implementation tickets, and there's a nice feeling of being an actual contributor to a project as robust as the one I was working on.

But there's a certain aspect that's missing in plugging tickets as a lower software engineer. In the army, I compared it to moving sandbags. The spot you're moving them from and to has been plotted already by someone that wears a higher rank than you. Just grab the sandbag and move it to point B. Nothing wrong with that. And it doesn't come without it's challenges.

Design was the itch that I wanted to scratch. To be the general and the foot soldier at the same time. And this project was my outlet of doing that. Being able to put the pieces together of a large project from nothing; linking together and sketching the relationships between interworking components and then carrying my own sandbags was a truly rewarding task. And for the first 6 months-ish... i failed... big time.

This repo is actually my second repo after starting over from my first project. The true software "sandbag carrier" in me was too eager to get hands on keyboard and jump in. And it went exactly as well as you'd expect a private being promoted straight to general would go. I didn't respect the design as well as I should've. And frankly, being up against the wall, lacking motivation to continue a project because of how it irredeemably askew it went humbled me. It takes a lot to look at something you've sunk so much time into and scrap it.

But i scrapped it with a newfound respect for the process, and the background knowledge that goes into it. In between my first and second (current) attempts, I did my research. I sat down with books on compiler theory from a variety of professors, looked at design patterns that I thought could be effective in streamlining my design, and only even picked up a pen to start plotting design once I really felt ready. There's a difference between being scared to dive in and giving the preparation the respect it deserves, and I hoped I was achieving the latter.

I took the first week before putting my hands on keyboard prototyping different components, drawing dependency diagrams, and revisiting chapters in the compiler theory books I read. Finally after that I felt ready to put hands on keyboard again, and I created this respository. I hope this learning experience will give me a leg up as I work the ranks of the software engineering ladder and maybe even work my way to being the architect on a large scale project at a big company.

## March 22, 2022

* Created the repo!
* Started off writing a bare-bones lexer that I knew could be expanded upon as I added more complexity.
* Added parsing of command line arguments borrowed from my last repo.
* Created a source handler to read in the provided source file.

At the end of today, we could turn a source that looks like this:
| ![alt text](https://i.imgur.com/7uFTwvI.png "Source1") |
|:--:|

Into a table of tokens like this:
| ![alt text](https://i.imgur.com/bESIgbj.png "Token Table") |
|:--:|

Here's the current dependency diagram:
| ![alt text](https://i.imgur.com/bjg6MZV.png "Token Table") |
|:--:|

## March 23, 2022

Big day today.
* Created the main parser, which takens in the token table and makes parsing decisions based on the tokens it encounters.
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

And the expression parser turns that table into a tree like this:
