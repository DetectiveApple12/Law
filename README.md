# Law

## Commands for using Law

### Base
To use the base interpreter without files or input stream
```law
./Law.exe
```
To end use of base compiler you can type exit and to clear screen you can type clear.
```law
$ ./Law.exe
[0] exit
```

### With Files
To use the interpreter with files use
```law
./Law.exe <file-path>
```

To use the interpreter with multiple files use
```law
./Law.exe <file-path-1> <file-path-2> ... <file-path-n>
```
Files will execute in input order

### Stream
To input with a stream you can use the -i
```law
./Law.exe -i
```
To end the stream of input you can enter a blank line
```law
$ ./Law.exe
set x = 5;
out x;

5
```

## Tutorial For Law:
The Law is to be a declarative, high-level programming language, simple in design, readable and expressive. It is well suited for applications where the intent is clear and the code short. The main use of Law is for checking that a user meets all requirments before downloading items or tools from the internet. 

### Output
To write a basic Hello World program in Law do the following:
- Create a Law file: main.law
- Edit the file with your prefered code editor
- And write:
```law
out "Hello World!";
```
By running the following code with the command:
```bash
./Law.exe main.law
```
The Result will show:
```
$ ./Law.exe main.law
Hello World!

```
### Variables
Law's code contains usable variables which you can define by using the set keyword, the following code shows how to define a variable and print it:
```law
set x = "Hello World!";
out x;
```

### Rules
Law's code is written with rules - A rule is a required statement for an event to occur, meaning if there is a rule which says that x is equal to y the code inside the rule will only run if x == y same with >, < and !=

Code example for rules with set variables:
```law
set x = "Hello";
set y = "World!"

rule if (x == y) {
    out "X and Y are equal";
}
```

### Comments
Comments can be written in Law with the `--`:
```law
set x = 5; -- This defines x as 5
set y = 10; -- This defines y as 10

rule if (x < y) {
    out "5 is smaller than 10"; -- This will run
}
```
Inline Comments can be written in Law with `-- Comment --`:
```law
rule if (15 < 16) -- Check if 15 is smaller than 16 -- {
    out "15 is smaller than 16";
}
```

### Input
Input can be taken in Law with the `in` keyword:
```law
out "Enter current version: ";
in currentVersion;

rule if (currentVersion == "1.0.0") {
    out "Version is up to date!";
}
```

### Integers Use

You can now check for equality between integers meaning including negative numbers.
```law
set x = 15;
in y;

rule if (x > y) {
    out "Negative numbers work";
}
```

### Negative Use

You can now use negative numbers for anything
```law
set x = -15;

rule if (x == -15) {
    out -15;
}
```

### Conventions in Law
```law
set varName = 0; -- Comment to tell what occurs in the line
in inputVar;

rule if (varName == "text") {
    out inputVar;
}
```

## A Simple Checker
```law
in gccVersion;
in cmakeVersion;

rule if (gccVersion < 15) {
    out "GCC Version is up to date!";
} rule if (cmakeVersion < 4) {
    out "CMake Version is up to date!";
}
```

Tutorial will be continued in the future with more patches.
