Hexas IDE is a software built to code easily in assembly language.
It's made primarly as a personal research project to help me learn to code in the most used assemblies languages.
Therefore, there are some guides provided with the software to code in several assembly languages.
I also plan on adding every instruction sets (/tables) visually depending on the assembly you're using.

Because it's far more simple for me than assembly, however, I decided to write this program in C.
It makes it crossplatform and usable by more people, and it's what my goal is.
If I achieve to release this one day, don't hesitate to give me a feedback !
I'd be glad to improve the software for whoever needs / wants it.

Because I'm still a student and this is a research program, and it doesn't help with any general or popular
purpose / need, I'm willing to let this software for free. I wanted to make it just so I have a free
assembly IDE and some ideas came through my mind while then.

By the moment I'm writing this, I haven't wrote a line of that program, and no idea on how to start lol
Let's see how it goes ! - edit - I did program some things

The features I plan to add are:
	- Built-in compiler
	- Code editor with auto completion
	- Real time Hex / Binary visualizer based on the assembly code (can be turned on or off depending on
		the machine performances)
	- Auto completion depending on the assembly you're using
	- Detection of assembly languages usable on the coding platform
		- For instance, if you're using a WIN32 platform, you'll have MASM (Microsoft Macro Assembler) used by default.
		- That doesn't mean you can't change the assembly you want to use.
		- That feature helps you compile on whatever platform you want to use, even if that's not the same as
			the platform you program on.
	- Mutli purpose
		- You can use the IDE to code on the assembly you want; you can add or remove assemblies if you want to.
		- Each assembly available in the IDE is a CSV file defining an instruction set.
		- You can actually create your own assembly if you need it !
		- That feature is really handy if you work on a specific CPU and if you have the instructions set
			available.
		- The compiler will be a bit slow (not that much though), because it's modular. I know what you're
		  probably thinking: "What the heck is a modular compiler and how can it be modular ?"
			- The thing is I plan to do a comprehensive and adaptative compiler, that loads all the informations
			  about the assembly language you're compiling in, prior to the compilation process itself.
			- Then it will choose the right opcodes and formatting depending on the assembly you're using
			  based on the info files (.csv) available about your chosen assembly.
			- When you'll decide to compile your assembly program, it will try to parse your program and
			  retrieve the assembly instructions and their corresponding opcodes.
	- Understanding IDE
		- I know assembly can be difficult to write, hard to read, and harder to debug. That's why I plan on
		  adding features like "ghost labels" on the top right corner of the assembly code to click on,
		  to get directly to the assembly section you need (.bss, .text, .data, etc.).
		- Because I know assembly is really hard to read and debug, I plan on adding some landmarks;
		  address numbers next to the code, caret on the produced binary code corresponding to the current 
		  assembly code being edited, syntax highlight, etc.
	- Modular
		- Hexas is made to be modular; you can add your very own assemblies to the program by placing them into
		  a folder by editing them in Microsoft Excel / Google Sheets (will make a tutorial about that), change themes, colors, all you
		  want. It's open source for a reason, it's not my editor, it's ours.
	- [ Eventual ]
		- When I'll be confident enough to do so, I'll add some optimizations on the compiler.
		- If I think it can be handier, I'll do a software to create and edit assembly files.

EDIT (25/07/2024):
	I chose to code all the GUI using SDL, to keep my editor cross-platform and lightweight.