Conventions:

During the project development, we have used some conventions in file names and code in order to make everything clear and easy to work with. 

These nomenclatures are:

- The images, audios and maps that we use must follow the snake_case convention (for example: character_walking.png).

- .h and .cpp files, classes, enum or enum classes, and functions will be written using PascalCase (for example: FadeToBlack.cpp, class FadeToBlack, enum class MainState, or bool PreUpdate()).

- Element definitions and enum or enum class types will use ALL_CAPS_SNAKE_CASE (for example: #define MAX_LISTENERS 10 or AWAKE).

- Variables and pointers will be in camelCase (for example: bool isAlive = “true” or Animation* currentAnimation).

- Lastly, the structs will have Pascal_Snake_Case (for example: SDL_Texture).

Other guides we use to follow an order and having everything organized are:

- Use English throughout the project, both for names and comments.

- Use full names in case of confusion (int position instead of int pos).

- Briefly comment on what each function does and, if not clear, what a variable means (on the line above).

- In case of using temporary variables, i will be used and, if more are needed, j, k, l, m…

- Use getters and setters to modify values of items in the game.

- Leave separation with the operators. For example use a + b = 3 and not a+b=3.

- In case you have to create a template class, use <class T>.

- Booleans should, if possible, start with is or has.

- Use enum class instead of enum and separate each element inside by lines and separated by commas.

- Use static_cast(variable) to change the type of a variable and dynamic_cast(general class) to pass from a general class to a particular one (for example, a general class would be figure and a particular class would be triangle).

- Input variables must clearly indicate the element they represent.

- Try to add all possible #includes in .h files and not in .cpp files.

- The functions and variables of a class must be separated into two clear blocks. The first will be for functions and the second for variables. Inside these, other smaller blocks can be identified to group elements of the same theme.

- Functions must be declared in an intuitive order in the .h file and must follow the same order in the .cpp file. The constructor and destructor will always come first and the bool CleanUp() will always come last.

- Variables should generally be grouped into blocks of the same type (_ints_ first, then _floats_, then _bools_), but there can be variables of different types in a group of the same theme.
Also, if several variables are variants of the same concept, they must be grouped on the same line. 
In addition, the priority order regarding the 8 directions that the elements of the game can have (including diagonals if necessary) will be: left -> right -> up -> down -> left-up -> right-up -> left-down -> right-down.

- Initialize the values of the variables in the .cpp file, not in the .h, following the same structure and order.

- Use if (bool) and if (!bool) instead of if (bool == true) and if (bool == false).

- Write function code using Allman style. 

- Use the curly braces even if there is only one line inside the if().

- Whenever convenient, switch() should be used instead of several if() or else if(), especially when working with numbers or elements of a list.

- Whenever several conditions are grouped together, this should be made clear using parentheses. Also, if the global parenthesis is very long, you have to separate the groups by lines so that they are aligned, using tabs if necessary. 

- In case of using an if() and else(), if there is a case in which some conditions cause the break of a loop, try to put it first.

- Use ++i in iterations to be more optimal, but variable++ in other code increments.

- Separate functions with an empty line, as well as leaving a line before and after public: or private: and their respective methods. Take into account the commented lines as well.

- Lastly, it's important not to delete code without thinking. You can always leave the code commented in case it is useful in the future. To comment out the code, two sidebars // will be used on each line, even if it is an entire block.
We won't use /* and */ as this can be tricky to manage when we want to comment a block with another smaller block commented inside.
