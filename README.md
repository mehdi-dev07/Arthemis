# Arthemis

making a compiler for a programming language named Arthemis from scratch in C, this is practice for compiler design class. NOT VIBECODED BTW lol.

the goal is to have a "functional programming language".
My idea to this language is to have somethings really basic, for example being able to have some if statements, some kind of jumps to make loops and some kinds of functions... I also want a way to get input, and of course do the arithmetic operations.

### the language should look like this: 
(maybe i'll change somethings in the future)

#### var declaration:
```
<varType> <name> = <name> | <num> | <num> <op> <num> ;
```

#### if statement:
```
if (<cond>){
<code>
}
```

#### goto instruction:
```
:lable
<code>
goto <label>
```

#### input/output:
```
a = input;
output a;
```


here is an example on how it should look like:

```
int n = input;
int i = 0;

:lable
output i;
i = i + 1;

if (i < n){
	goto :label
}
```


