# C Plus (CP/C+). The intermediate language between C and C++/CPP
## So what is it?
It is framework for the **C** programming language, that its main purpose is to turn **C** programming language into more friendly and easy to use programming language for beginners and pros and to make it as easy to use as **Python** scripting language. Also to encourage developers to make libraries and packages for **C** as they are doing for **Python** like [**numpy** - **tensorflow** - **etc.**] and to be widely used in **Artificial Intelligence** projects and other **Data Science** projects. The future plan for this project to turn it into a programming language.

## Who asked for this?
Well none (I guess), but **C** is one of my best programming language and i'd liked to be easily used for developers and programmers in complex projects.

## The Development
The development of this project will be done in **C99** version of C programming language. The **editor** that i'll use is either **VSCode** or **VIM**, you can use whatever you like. The compiler that i'm using is ***[tdm-gcc](https://jmeubank.github.io/tdm-gcc/download/)*** on **Windows**. On **Ubuntu** and **Windows Subsystem For Linux**  i'll be using **gcc**. I don't have a **MAC** device, but if someone wants to test on that environment it will be appreciated.

I know this project will take time to be done as well as it be will hard to achieve and the required, but if you have the passion for coding and for **C**, i think it will be done.

 ## The concept map
 The following is a concept map diagram, which holds high-level of information about what is to be done in this project. The design was made by **Microsoft Visio**. There is a **pdf** version of this design is the: **"./des/concept_map/pdf/"** directory of the project. ![Concept-Map](https://i.imgur.com/PIAoGUm.jpg)
 
## Project layout
Regarding the directories; i like them to be named with maximum 3 characters, but inner directories have no constraints regarding naming. The only constraint is to make the name of the directories have an objective and can be understood by reading them. The layout goes as follows:
- ***src***: Holds the source code of the project.
- ***hdr***: Holds the header files of the project.
- ***bin***: Holds objects files **\*.o** or **\*.obj**.
- ***lib***: Holds libraries.
- ***tst***: Holds test cases and test executable for the project.
- ***cmp***: Holds **\*.bat** file for windows and **\*.sh** for linux and unix like OS. These files are used to automate the compilation of the project and automate other tasks. You may say "You can use MakeFile", but personally i don't see the difference, but you are more than welcome to use it, if you are used to it.
- ***exe***: Holds the executable of different components of the project.
- ***des***: Holds some diagrams for the projects.
- ***doc***: Holds the documentation of the project.
- ***ext***: Holds the external sources like images, videos, etc.

You add some folder as  you like, but do not forget to update the **README.md** file, so i and others if will contribute knows what's new.

## Comments on functions
The way i make a comment on a function. I create a multi-line comment and i include the following:
1- **INPT**: *This will have all the input(s) passed to the function.*
2- **OTPT**: *This will have The return type of a function.*
3- **INFO**: *This will have information/description of a function.*
***Example:***
```C
/*
INPT: A pointer to char, which will hold our main string to make a copy of.
OTPT: On success returns a pointer to char, otherwise returns NULL on failure.
INFO: This function is used to make a copy of an existing string. If a passed string
     is an empty string aka "", not NULL, then we will create an empty string.
*/
char * getCopy (char * str) {...}
```
## What has been done?
- [x] Made a concept map about the project.
- [x] Made redef.h file.
- [x] Made redef.c file.
- [x] Made char.h file.
- [x] Made char.c file.
- [x] Made memory.h file.
- [x] Made memory.c file.
- [x] Made string.h file.
- [x] Made some functions in string.c file.
- [x] Made array.h file.
- [x] Made array.c file.