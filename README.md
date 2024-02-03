# Astral Scripting Language
Astral is a dynamically type scripting language designed to be easy to use and integrate into other software.
The language features a syntax which has mainly been inspired by JavaScript and C. There are no classes but structs can be used and passed by reference.

# Important Notice
Astral and its runtime are still currently in development. Many of the features shown here may not be implemented yet.

## Data Types
| Type   | Description                                                     |
|--------|-----------------------------------------------------------------|
| Number | 32-bit floating point number                                    |
| String | Sequence of characters                                          |
| Void   | Void is the lack of any data. Astral equivalent of null or None |
| Object | Collection of types bonded together in a struct                 |

### Planned Future Types
| Type  | Description                                                                             |
|-------|-----------------------------------------------------------------------------------------|
| Array | Dynamically sized list of data                                                          |
| Char  | Single character. Will be used when reading or writing to a string at a specified index |

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
	Println("Hello, World!");
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
### Compiler
The final stage of compilation is the compiler or assembler. It will navigate through the AST and generate bytecode. Bytecode is the instructions that the virtual machine or interpreter will execute. These instructions are very simple and will usually consist of, push value onto stack, or add together two values.

## Building
Astral was developed using Visual Studio 2022 and provides a `.sln` file for your use. Astral compiles to a `.dll` and Astral Testing (which is the playground I use to test various features) will use that `.dll` to run.
In the future, I plan to convert over to using CMAKE instead of using a Visual Studio solution.

## Linking
To use Astral, make sure that your linker is set to load `Astral.lib` and ensure that `Astral.dll` is placed in your executable folder.

## Contributing
Currently I am not accepting any support with Astral. Both Astral and Aurora are personal projects which I am working on for myself to further improve my skills. If you would like to make any changes, feel free to make and maintain your own fork.