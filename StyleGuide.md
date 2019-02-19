<img src ="/images/RetroConnect.png" height ="100" width = "100"/>

# RetroConnect Team Style Guide
---

## Areas of Focus:
---
* **External Documentation**
* **Class Documentation**
* **Interal Documentation & Naming**
* **Indentation**
* **Miscellaneous**
---
#### External Documentation:
* At the top of each file created, the name of the team member working on this file and a brief description of the purpose of the file should be added.

```C 
/* 
Name: <Team member Name>
File Description: <Description of files purpose>
*/
```
#### Class Documentation:
* Each support class is to be preceded with a block comment that includes:
   * Class name
   * Names of external packages the class depends on
   * Parameter names and brief description
   * Brief note on the classes purpose

```C
/* 
Class Name: ExampleFunction
Parameter Names & Purpose: <Name & Purpose>
Description: <Class/function description>
Names of External Packages: <External packages used>
*/
int ExampleFunction() {

}
```

#### Internal Documentation & Naming:
* It is encouraged to name variables and methods descriptively, but if variable names become scarce inline comments are necessary for future readability.
* *Complex* pieces of code are encouraged to be commented heavily.


#### Indentation:

* RetroConnect is a **Tab** operated team with **tab stop = 4**
* Consistency in format/style is important for clean understandable code, if any team member has any specific formatting styles they should bring it up to the team for vote.


#### Miscellaneous/Example Code:
* The following guidelanes are reccomended to follow when writing any code:
  * Write programs with modularity; that is, create classes when appropriate, write methods that accomplish limited and well-defined tasks
  * **Limited** or very monitored use of Global Variables
  * Indent bodies of methods, loops and IF statements with consistent style
  * Polish code before merging to Master branch

```C
int x, y, z; // Variable creation/declartion at the top
var condition;

if (condition) {
        // Statements
}

```

