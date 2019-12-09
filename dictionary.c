/*
Instructions on how to draw alphanumeric characters
Possible implementations:
1) If statements to check character and perform necessary makeLine instructions
2) 2D array that stores instructions of a character at [character's ASCII value]
3) An array of structs containing information about a character
*/

#include <string.h>

//Use ASCII table to get our indices for characters
#define DICTIONARYSIZE 128
#define MAXMOVES 16		//Stores the number of moves needed for the most complicated drawing
#define EXTENDALIAS 200.0	//Store extend marker command in instructions array as 200.0
#define RETRACTALIAS 100.0	//Store retract marker command in instructions array as 100.0
double currentX = 41.91;
double currentY = 27.305;

enum side{LEFT, RIGHT};

/*
Stores the relative distances in the following format:
1	2	-3	4 is equivalent to moving (1,2) and then (-3,4)
1	2	100.0	-3	4	200.0	5	-6 is equivalent to moving (1,2), retracting marker, moving (-3,4), extending marker, and then moving (5,-6)
*/
//double instructions[DICTIONARYSIZE][MAXMOVES];
/*
//Initialize everything to 0
int i = 0;
int j = 0;
for(i = 0; i < DICTIONARYSIZE; ++i) {
	for(j = 0; j < MAXMOVES; ++j) {
		instructions[i][j] = 0.0;
	}
}

//Goes to 2D array and carries out instructions detailed in instructions[row]
void drawRow(uint8_t row) {
	int i = 0;
	for(i = 0; i < MAXMOVES; ++i) {
		//Avoid floating point comparisons, see if the difference is negligible to compare
		if(instructions[row][i] - RETRACTALIAS < 0.1) {
			sendMessage(&servoRetract, 1, 0x373A);
		}
		else if(instructions[row][i] - EXTENDALIAS < 0.1) {
			sendMessage(&servoExtend, 1, 0x373A);
		}
		else {
			makeLine(calculateMotorDir(currentX, currentY, instructions[row][i], instructions[row][i+1], LEFT),
			calculateMotorDir(currentX, currentY, instructions[row][i], instructions[row][i+1], RIGHT),
			instructions[row][i], instructions[row][i+1]);
			//For loop needs to increment by two if moving to coordinate
			i++;
		}
	}
}

//Fill up 2D array with instructions
char c = '0';
double sequence[MAXMOVES];
sequence = {RETRACTALIAS, 43.91, 27.305, EXTENDALIAS, 42.91, 26.305, 42.91, 25.305, 43.91, 24.305, 44.91, 25.305, 44.91, 26.305, 43.91, 27.305};
memcpy(instructions[(int)c], sequence, sizeof(sequence));
c = '1';
sequence[MAXMOVES] = {};
memcpy(instructions[(int)c], sequence, sizeof(sequence));

c = '';
sequence[MAXMOVES] = {};
memcpy(instructions[(int)c], sequence, sizeof(sequence));
*/

//Assumes that the marker is retracted and at the bottom left corner of a 3cm wide, 4cm high area that character is allowed to occupy
if(character == '0') {
	makeLine(2.0, -1);	//Start at bottom of 0
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(-1.0, -2.5);
	makeLine(0.0, -1.5);
	makeLine(1.0, -2.5);
	makeLine(1.0, 0.0);
	makeLine(1.0, 2.5);
	makeLine(0.0, 1.5);
	makeLine(-1.0, 1.5);
	makeLine(-1.0, 0.0);
	//Get ready for next character
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(3.0, 1.0);
}
else if(character == '1') {
	makeLine(1.0, -1.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(3.5, 0.0);
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(-1.75, 0.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(0.0, -4.5);
	makeLine(-1.5, 1.5);
	//Get ready for next character
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(3.75, 4.0);
}
else if(character == '2') {
	makeLine(4.0, -1.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(-3.0, 0.0);
	makeLine(0.0, -2.0);
	makeLine(3.0, 0.0);
	makeLine(0.0, -1.5);
	makeLine(-3.0, 0.0);
	//Get ready for next character
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(4.0, 4.5);
}
else if(character == '3') {
	makeLine(1.0, -2.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(1.5, 1.0);
	makeLine(1.5, -1.0);
	makeLine(-1.5, -1.5);
	makeLine(1.5, -1.5);
	makeLine(-1.5, -1.0);
	makeLine(-1.5, 1.0);
	//Get ready for next character
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(4.0, 5.0);
}
else if(character == '4') {
	makeLine(3.0, -1.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(0.0, -4.5);
	makeLine(-2.0, 2.0);
	makeLine(3.5, 0.0);
	//Get ready for next character
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(0.5, 4.5);
}
else if(character == '5') {
	makeLine(1.0, -1.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(3.0, 0.0);
	makeLine(0.0, -2.0);
	makeLine(-3.0, 0.0);
	makeLine(0.0, -1.5);
	makeLine(3.0, 0.0);
	//Get ready for next character
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(1.0, 4.5);
}
else if(character == '6') {
	makeLine(1.0, -3.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(0.0, -2.0);
	makeLine(3.0, 0.0);
	makeLine(0.0, -2.0);
	makeLine(-3.0, 0.0);
	makeLine(0.0, -1.5);
	makeLine(3.0, 0.0);
	//Get ready for next character
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(1.0, 4.5);
}
else if(character == '7') {
	makeLine(1.0, -5.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(3.0, 0.0);
	makeLine(-2.0, 4.0);
	//Get ready for next character
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(1.0, 1.0);
}
else if(character == '8') {
	makeLine(1.0, -1.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(0.0, -5.0);
	makeLine(3.0, 0.0);
	makeLine(0.0, 5.0);
	makeLine(-3.0, 0.0);
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(0.0, -2.5);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(3.0, 0.0);
	//Get ready for next character
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(1.0, 3.5);
}
else if(character == '9') {
	makeLine(1.0, -1.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(3.0, 0.0);
	makeLine(0.0, -5.0);
	makeLine(-3.0, 0.0);
	makeLine(0.0, 2.5);
	makeLine(3.0, 0.0);
	//Get ready for next character
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(1.0, 3.5);
}
else if(character == 'A') {
	makeLine(47.91, 18.305);
	makeLine(53.91, 27.305);
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(50.91, 22.805);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(44.91, 22.805);
}
else if(character == 'B') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'C') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'D') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'E') {
	makeLine();
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine();
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine();
	makeLine();
	sendMessage(&servoRetract, 1, 0x373A);
	sendMessage(&servoExtend, 1, 0x373A);
}
else if(character == 'F') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'G') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'H') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'I') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'J') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'K') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'L') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'M') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'N') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'O') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'P') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'Q') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'R') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'S') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'T') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'U') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'V') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'W') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'X') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'Y') {
	makeLine();
	makeLine();

	makeLine();
	makeLine();
}
else if(character == 'Z') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'a') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'b') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'c') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'd') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'e') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'f') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'g') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'h') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'i') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'j') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'k') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'l') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'm') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'n') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
}
else if(character == 'o') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
	sendMessage(&servoRetract, 1, 0x373A);
}
else if(character == 'p') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
	sendMessage(&servoRetract, 1, 0x373A);
}
else if(character == 'q') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
	sendMessage(&servoRetract, 1, 0x373A);
}
else if(character == 'r') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
	sendMessage(&servoRetract, 1, 0x373A);
}
else if(character == 's') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
	sendMessage(&servoRetract, 1, 0x373A);
}
else if(character == 't') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
	sendMessage(&servoRetract, 1, 0x373A);
}
else if(character == 'u') {
	makeLine();
	makeLine();
	makeLine();
	makeLine();
	sendMessage(&servoRetract, 1, 0x373A);
}
else if(character == 'v') {
	makeLine(1.0, -4.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(1.5, 3.0);
	makeLine(1.5, -3.0);
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(1.0, 4.0);
}
else if(character == 'w') {
	makeLine(0.5, -4.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(1.0, 3.0);
	makeLine(1.0, -3.0);
	makeLine(1.0, 3.0);
	makeLine(1.0, -3.0);
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(0.5, 4.0);
}
else if(character == 'x') {
	makeLine(1.0, -4.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(3.0, 3.0);
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(0.0, 3.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(-3.0, 3.0);
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(4.0, 1.0);
}
else if(character == 'y') {
	makeLine(1.0, -4.0);
	makeLine(1.5, 1.5);
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(1.5, -1.5);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(-3.0, 3.0);
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(4.0, 1.0);
}
else if(character == 'z') {
	makeLine(1.0, -4.0);
	sendMessage(&servoExtend, 1, 0x373A);
	makeLine(3.0, 0.0);
	makeLine(-3.0, 3.0);
	makeLine(3.0, 0.0);
	sendMessage(&servoRetract, 1, 0x373A);
	makeLine(1.0, 1.0);
}
