Hexas IDE is a software built to code easily in assembly language.
It's made primarly as a personal research project to help me learn to code in the most used assemblies languages.
Therefore, there are some guides provided with the software to code in several assembly languages.
I also plan on adding every instruction sets (/tables) visually depending on the assembly you're using.

Because it's far more simple for me, however, I decided to write this program in C.
It makes it crossplatform and usable by more people, and it's what my goal is.
If I achieve to release this one day, don't hesitate to give me a feedback !
I'd be glad to improve the software for whoever needs / wants it.

Because I'm still a student and this is a research program, and it doesn't help with any general or popular
purpose / need, I'm willing to let this software for free. I wanted to make it just so I have a free
assembly IDE and some ideas came through my mind while then.

By the moment I'm writing this, I haven't wrote a line of that program, and no idea on how to start lol
Let's see how it goes !

The features I plan to add are:
	- Built-in compiler
	- Code editor with auto completion
	- Real time Hex / Binary visualizer based on the assembly code
	- Auto completion depending on the assembly you're using
	- Detection of assembly languages usable on the coding platform
		- For instance, if you're using a WIN32 platform, you'll have MASM used by default.
		- That doesn't mean you can't change the assembly you want to use.
		- That feature helps you compile on whatever platform you want to use, even if that's not the same as
			the platform you code on.
	- Mutli purpose
		- You can use the IDE to code on the assembly you want; you can add or remove assemblies if you want to.
		- Each assembly available in the IDE is a CSV file defining an instruction set.
		- You can actually create your own assembly if you need it !
		- That feature is really handy if you work on a specific CPU and if you have the instructions set
			available.


EDIT (25/07/2024):
	I chose to code all the GUI using SDL, to keep my editor cross-platform and lightweight.