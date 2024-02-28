# Astral Scripting Language
Astral is a dynamic typed scripting language designed to be easy to use and integrate into other software.
The language features a syntax which has mainly been inspired by JavaScript and C. There are no classes but structs can be used and passed by reference.

# Important Notice
Astral and its runtime are still currently in development. Many of the features shown here may not be implemented yet.

## Data Types
| Type     | Description                                                     |
|----------|-----------------------------------------------------------------|
| Number   | 32-bit floating point number                                    |
| String   | Sequence of characters                                          |
| Void     | Void is the lack of any data. Astral equivalent of null or None |
| Object   | Collection of types bonded together in a struct                 |
| Function | Object which can be called as a function                        |

### Planned Future Types
| Type  | Description                                                                             |
|-------|-----------------------------------------------------------------------------------------|
| Array | Dynamically sized list of data                                                          |
| Char  | Single character. Will be used when reading or writing to a string at a specified index |

## Implicit Boolean Conversion
Astral will implicitly convert some types to booleans when used in an if statement. In Astral, booleans are simply represented as a number, where true is non-zero, like C.
Void if passed into an if statement will *always* return false, and a struct will always return true. This is implemented to allow C-like null checking for pointers.
In C, you can do this to check if an object has been defined.
```c
void* myobj = NULL;
if (myobj)
	printf("My Object Exists\n");
else
	printf("My Object Doesn't Exist\n");
```
and Astral will allow this as if the object has been defined as a struct, it will return true, otherwise Void which will return false.

## Garbage Collection
Astral features a garbage collector which means that the programmer does not have to care about allocating or deallocating memory. The runtime will handle all of it. When a variable has gone out of scope and there are no more handles (variables which are a reference to another variable) the garbage collector will flag that memory block for deallocation. Due to how the garbage collector functions, you may notice spikes in the memory usage. The garbage collector will only free memory when a certain threshold has been met and these spikes and drops can be seen. The rate and threshold that the GC uses is customisable for each script so more memory heavy scripts can have a more aggressive GC.

## Syntax
Astral follows a simple syntax. A program will be made up of global variable definitions, structure definitions and functions.
Global variables are variables which can be access anywhere within the program, regardless of scope.

Global variables will be defined by using the `global` keyword. By default, they will store void. They should be initalised in the main method or before use.
Functions can be defined using the `func` keyword. Following the dynamic typing of Astral functions do not have any explicit return type.
Additionally, the language has not function overloading, although this is planned in the future.

## Examples
### Hello World
```
func Main()
{
	println("Hello, World!");
}
```
### FizzBuzz
```
func Main()
{
	let f = 3;
	let b = 5;

	for (let i = 1; i <= 100; i += 1)
	{
		let output = "";

		if (i % f == 0)
			output += "Fizz";
		
		if (i % b == 0)
			output += "Buzz";

		//If we didn't match either case, just print the number
		if (output == "")
			output = i;

		Println(output);
	}
}
```

### Value v References
By default, Astral will pass all parameter by value unless otherwise specified. Passing by value will mean that the local variables in a function will be copies of the original data.
If the function should change the original data then a reference should be used. A reference is a link to another variable so that if one instance is changed, then all instances are changed.
References are mark with the `&` operator.
```
let x = 0;
let y = &x; //Y is now linked to x. Changing x OR y will change the data.
println(x);
y = 10;
println(x); //X now stores 10 even though we changed y
```

Some built-in functions may give you an error if you pass by value. An example of this is `string_write`. This function will write a character to a string at a given index. Since this function is expected to change the underlying data, a reference should be used.
```
func main(a)
{
	let name = "Astral";

	string_write(name, 0, "O"); //Will throw a warning since it is modifying a copy
	println(name); //Prints 'Astral'

	string_write(&name, 0, "O");
	println(name); //Prints 'Ostral'
}
```

### Aurora Interoperability
Aurora is the game engine I am currently working on. Thanks to the binding system implemented in the Astral runtime, Astral can easily have support added to different programs.
This is a sample script for Aurora which will make a light flash on and off each second
```
global timer;
global active;
global rate;
global owner;

func Start()
{
	timer = 0;
	active = true;
	rate = 1.0;
	owner = PB_Get_Owner_AsLight();
}

func Update(dt)
{
	timer += dt;
	
	if (timer >= rate)
	{
		timer = 0;
		active = !active;
		owner.lightState = active;
	}
}
```

## Compilation Stages
### Lexer
The lexer, lexical analyser or tokeniser is the first stage in compilation. It will generate tokens which are sequences of related characters. For example, if the lexer reads the characters `f` `u` `n` `c` then it knows that those characters are part of the same keyword and so it can make a `func` token.
### Parser
The next stage is parsing which will take in the generated tokens and will use those to create an abstract syntax tree, or AST. This is a tree which will store a representation of the source code. These trees will take into account for operator precedence to easily allow mathematical equations to be executed.
The expression `1 + 2 * 3` will be turned into this tree.
```
 +
/ \
1  *
  / \
  2  3
```
whereas `(1 + 2) * 3` will be turned into this tree.
```
  *
 / \
 +  3
/ \
1 2
```
### Linker
The linker in Astral does not quite function the same as the C/C++ linker. In Astral, the linkers job is to resolve `include` statements. These statements will tell the compiler that it wants to use another file and load its code.
The linker will take the given filename, try to load it, and run the first two compilation stages on the code. Once a tree has been generated, it will be appended onto the end of the current tree.
Also important to the linker is to track which files have already been loaded as to ensure that the same file is not loaded multiple times (similar to `pragma once` in C++).

### Compiler
The final stage of compilation is the compiler or assembler. It will navigate through the AST and generate bytecode. Bytecode is the instructions that the virtual machine or interpreter will execute. These instructions are very simple and will usually consist of, push value onto stack, or add together two values.

## Building
Astral was developed using Visual Studio 2022 and provides a `.sln` file for your use. Astral compiles to a `.dll` and Astral Testing (which is the playground I use to test various features) will use that `.dll` to run.
In the future, I plan to convert over to using CMAKE instead of using a Visual Studio solution.

## Linking
To use Astral, make sure that your linker is set to load `Astral.lib` and ensure that `Astral.dll` is placed in your executable folder.