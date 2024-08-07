# Law

## Tutorial For Law:
The Law is to be a declarative, high-level programming language, simple in design, readable and expressive. It is well suited for applications where the intent is clear and the code short. The main use of Law is for checking that a user meets all requirments before downloading items or tools from the internet. 

### Output:
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
### Variables:
Law's code contains usable variables which you can define by using the set keyword, the following code shows how to define a variable and print it:
```law
set x = "Hello World!";
out x;
```

### Rules:
Law's code is written with rules - A rule is a required statement for an event to occur, meaning if there is a rule which says that x is equal to y the code inside the rule will only run if x == y same with >, < and !=

Code example for rules with set variables:
```law
set x = "Hello";
set y = "World!"

rule if (x == y) {
    out "X and Y are equal";
}
```

### Comments:
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

### Input:
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

Tutorial will be continued in the future with more patches.
