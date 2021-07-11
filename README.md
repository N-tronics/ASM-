# ASM# Documentation
## Write beefed up assembly  with a .asms extention!

### Docs:
1. ```#``` - Defines an integer
2. ```*``` - Defines a float
3. ```lda``` - Loads a value to the A register
4. ```ldb``` - Loads a value to the B register
5. ```ldc``` - Loads a value to the C register
6. ```lds``` - Loads a value to the support register
7. ```out``` - Outputs the value of the output register
8. ```push``` - Pushes a value to the stack
	1. ```push #42``` - Pushes a number to the stack
	2. ```push``` - Pushes the value of the support register to the stack
9. ```pull``` - Pulls the last value from the stack and loads it to the support register
10. ```sum``` - Loads the support register with the sum of the values in A and B registers