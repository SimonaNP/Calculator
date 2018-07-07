# Calculator

getValue - returns the current result from the arithmetic operations

<arithmetic operation> <number> - applies the corresponding arithmetic operation (+, -, *, /) to the 
current result and the number and changes the value of the current result
  
listOperations - prints a list with all of the arithmetic  operations we have done so far in the right order

undo - cancels the previous arithmetic operation, changing the current result

reset - resets the calculator state. After it, the UNDO operation has no effect

save <file name> - saves in an appropriate format the series of currently performed arithmetic operations in a file with the specified name
  
restore <file name> - restores the status of the calculator from a specified file generated by the SAVE command. The current result after restore must matches the executed arithmetic actions from the file
