# Law
Law is an interpreted rule-based language
***
## Current Types:
String \
Integer

## Tutorial For Law:
The Law is to be a declarative, high-level programming language, simple in design, readable and expressive. It is well suited for applications where the intent is clear and the code short.

To write a basic Hello World program in Law do the following:
- Create a Law file: main.law
- Edit the file with your prefered code editor
- And write:
```law
out "Hello World!";
```
By running the following code with the command:
```bash
./law main.law
```
The Result will show:
```
$ ./law main.law
Hello World!

```
Law's code contains usable variables which you can define by using the set keyword, the following code shows how to define a variable and print it:
```law
set x = "Hello World!";
out x;
```

Law's code is written with rules - A rule is a required statement for an event to occur, meaning if there is a rule which says that x is equal to y the code inside the rule will only run if x == y same with >, < and !=

Code example for rules with set variables:
```law
set x = "Hello";
set y = "World!"

rule if (x == y) {
    out "X and Y are equal";
}
```

Comments can be written in Law with the `--`:
```law
set x = 5; -- This defines x as 5
set y = 10; -- This defines y as 10

rule if (x < y) {
    out "5 is smaller than 10"; -- This will run
}
```

Tutorial will be continued in the future with more patches.