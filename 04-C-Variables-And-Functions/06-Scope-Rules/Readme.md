# Refer: https://www.geeksforgeeks.org/understanding-extern-keyword-in-c/

# The difference between the “declaration” and the “definition” of a variable or function

* **Declaration**: simply declares that the variable or function exists somewhere in the program, but the memory is not allocated for them.
* **Definition**: in addition to everything that a declaration does, it also allocates memory for that variable or function. Therefore, declaration as a subset of the definition.
* **extern** is a short name of external. The extern variable is used when a particular files need to access a variable from another file.