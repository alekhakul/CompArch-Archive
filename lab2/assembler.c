/*
	Name 1: Alex Lekhakul
	Name 2: Ohkyo Kwon
	UTEID 1: akl2747
	UTEID 2: ok2769
*/

#include <stdio.h> /* standard input/output library */
#include <stdlib.h> /* Standard C Library */
#include <string.h> /* String operations library */
#include <ctype.h> /* Library for useful character operations */
#include <limits.h> /* Library for definitions of common variable type characteristics */

#define MAX_LINE_LENGTH 255
#define MAX_LABEL_LEN 20    
#define MAX_SYMBOLS 255

enum {DONE, OK, EMPTY_LINE};

int toNum( char * pStr );
int isOpcode(char * lPtr);
int readAndParse( FILE * pInfile, char * pLine, char ** pLabel, char
** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4);
void pass1(FILE * fp);
int getReg(char * regStr);
int getLabel(char * pLabel);
void pass2(FILE * pInfile, FILE *pOutfile);

FILE* infile = NULL;
FILE* outfile = NULL;

typedef struct {
	int address;
	char label[MAX_LABEL_LEN + 1];
} TableEntry;
TableEntry symbolTable[MAX_SYMBOLS];

int main(int argc, char* argv[]) {

    char *prgName   = NULL;
    char *iFileName = NULL;
    char *oFileName = NULL;

    prgName   = argv[0];
    iFileName = argv[1];
    oFileName = argv[2];

    // printf("program name = '%s'\n", prgName);
    // printf("input file name = '%s'\n", iFileName);
    // printf("output file name = '%s'\n", oFileName);

    /* open the source file */
    infile = fopen(argv[1], "r");
    outfile = fopen(argv[2], "w");
        
    if (!infile) {
    printf("Error: Cannot open file %s\n", argv[1]);
    exit(4);
        }
    if (!outfile) {
    printf("Error: Cannot open file %s\n", argv[2]);
    exit(4);
    }

    /* Do stuff with files */
    pass1(infile);
    
    // Pass 1 debug
    // printf("\n--SYMBOL TABLE TEST--\n");
    // for (int i = 0; i < MAX_SYMBOLS; i++) {
    //     // Stop printing if table ends
    //     if (symbolTable[i].label[0] == '\0') break; 
        
    //     // Print Label and addr
    //     printf("Label: %s \tAddress: x%04X\n", symbolTable[i].label, symbolTable[i].address);
    // }
    // printf("-------------------------\n");
    
    rewind(infile);

    pass2(infile, outfile);

    fclose(infile);
    fclose(outfile);
}

int isOpcode(char * lPtr) {
    if (lPtr == NULL) return -1;

    if (strcmp(lPtr, "add") == 0) return 0;
    if (strcmp(lPtr, "and") == 0) return 0;
    if (strcmp(lPtr, "halt") == 0) return 0;
    if (strcmp(lPtr, "jmp") == 0) return 0;
    if (strcmp(lPtr, "jsr") == 0) return 0;
    if (strcmp(lPtr, "jsrr") == 0) return 0;
    if (strcmp(lPtr, "ldb") == 0) return 0;
    if (strcmp(lPtr, "ldw") == 0) return 0;
    if (strcmp(lPtr, "lea") == 0) return 0;
    if (strcmp(lPtr, "nop") == 0) return 0;
    if (strcmp(lPtr, "not") == 0) return 0;
    if (strcmp(lPtr, "ret") == 0) return 0;
    if (strcmp(lPtr, "lshf") == 0) return 0;
    if (strcmp(lPtr, "rshfl") == 0) return 0;
    if (strcmp(lPtr, "rshfa") == 0) return 0;
    if (strcmp(lPtr, "rti") == 0) return 0;
    if (strcmp(lPtr, "stb") == 0) return 0;
    if (strcmp(lPtr, "stw") == 0) return 0;
    if (strcmp(lPtr, "trap") == 0) return 0;
    if (strcmp(lPtr, "xor") == 0) return 0;
    if (strcmp(lPtr, "br") == 0) return 0;
    if (strcmp(lPtr, "brn") == 0) return 0;
    if (strcmp(lPtr, "brz") == 0) return 0;
    if (strcmp(lPtr, "brp") == 0) return 0;
    if (strcmp(lPtr, "brnz") == 0) return 0;
    if (strcmp(lPtr, "brnp") == 0) return 0;
    if (strcmp(lPtr, "brzp") == 0) return 0;
    if (strcmp(lPtr, "brnzp") == 0) return 0;

    return -1;
}

int toNum( char * pStr )
{
   char * t_ptr;
   char * orig_pStr;
   int t_length,k;
   int lNum, lNeg = 0;
   long int lNumLong;

   orig_pStr = pStr;
   if( *pStr == '#' )				/* decimal */
   { 
     pStr++;
     if( *pStr == '-' )				/* dec is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isdigit(*t_ptr))
       {
	 printf("Error: invalid decimal operand, %s\n",orig_pStr);
	 exit(4);
       }
       t_ptr++;
     }
     lNum = atoi(pStr);
     if (lNeg)
       lNum = -lNum;
 
     return lNum;
   }
   else if( *pStr == 'x' )	/* hex     */
   {
     pStr++;
     if( *pStr == '-' )				/* hex is negative */
     {
       lNeg = 1;
       pStr++;
     }
     t_ptr = pStr;
     t_length = strlen(t_ptr);
     for(k=0;k < t_length;k++)
     {
       if (!isxdigit(*t_ptr))
       {
	 printf("Error: invalid hex operand, %s\n",orig_pStr);
	 exit(4);
       }
       t_ptr++;
     }
     lNumLong = strtol(pStr, NULL, 16);    /* convert hex string into integer */
     lNum = (lNumLong > INT_MAX)? INT_MAX : lNumLong;
     if( lNeg )
       lNum = -lNum;
     return lNum;
   }
   else
   {
	printf( "Error: invalid operand, %s\n", orig_pStr);
	exit(4);  /* This has been changed from error code 3 to error code 4, see clarification 12 */
   }
}

int
readAndParse( FILE * pInfile, char * pLine, char ** pLabel, char
** pOpcode, char ** pArg1, char ** pArg2, char ** pArg3, char ** pArg4
)
{
    char * lRet, * lPtr;
    int i;
    if( !fgets( pLine, MAX_LINE_LENGTH, pInfile ) )
    return( DONE );
    for( i = 0; i < strlen( pLine ); i++ )
    pLine[i] = tolower( pLine[i] );
    
        /* convert entire line to lowercase */
    *pLabel = *pOpcode = *pArg1 = *pArg2 = *pArg3 = *pArg4 = pLine + strlen(pLine);

    /* ignore the comments */
    lPtr = pLine;

    while( *lPtr != ';' && *lPtr != '\0' &&
    *lPtr != '\n' ) 
    lPtr++;

    *lPtr = '\0';
    if( !(lPtr = strtok( pLine, "\t\n ," ) ) ) 
    return( EMPTY_LINE );

    if( isOpcode( lPtr ) == -1 && lPtr[0] != '.' ) /* found a label */
    {
    *pLabel = lPtr;
    if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
    }
    
        *pOpcode = lPtr;

    if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );
    
        *pArg1 = lPtr;
    
        if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

    *pArg2 = lPtr;
    if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

    *pArg3 = lPtr;

    if( !( lPtr = strtok( NULL, "\t\n ," ) ) ) return( OK );

    *pArg4 = lPtr;

    return( OK );
}

void pass1(FILE * pInfile){
    int lCounter = -1;
    char lLine[MAX_LINE_LENGTH + 1];
    char *lLabel, *lOpcode, *lArg1, *lArg2, *lArg3, *lArg4;
    int lRet;
    int symCount = 0;

    do {
        lRet = readAndParse(pInfile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4);
        if (lRet == DONE || lRet == EMPTY_LINE) continue;
        
        // Check for .ORIG
        if (strcmp(lOpcode, ".orig") == 0) {
            lCounter = toNum(lArg1);
            // Check for alignment
            if (lCounter % 2 != 0) exit(4);
        }

        // Check for .END
        if (strcmp(lOpcode, ".end") == 0) {
            break;
        }

        // Check for labels
        if (lLabel && *lLabel) {
            if (lCounter != -1) {
                for (int i = 0; i < symCount; i++) {
                    if (strcmp(lLabel, symbolTable[i].label) == 0) exit(4);
                }
                strcpy(symbolTable[symCount].label, lLabel);
                symbolTable[symCount].address = lCounter;
                symCount++;
            } else exit(4);
        }

        // Update lCounter
        if (isOpcode(lOpcode) == 0) {
            lCounter = lCounter + 2;
        }
        if (strcmp(lOpcode, ".fill") == 0) {
            lCounter = lCounter + 2;
        }

    } while (lRet != DONE);
}

// Helper function to turn RX into number
int getReg(char * regStr) {
    if (regStr[0] != 'r') exit(4); // Exit if doesn't start w/ r
    int reg = regStr[1] - '0'; // Convert to number char to int
    if (reg < 0 || reg > 7) exit(4);
    return reg;
}

int getLabel(char *pLabel) {
    for (int i = 0; i < MAX_SYMBOLS; i++) {
        // End of table
        if (symbolTable[i].label[0] == '\0') break;
        if (strcmp(symbolTable[i].label, pLabel) == 0){
            return symbolTable[i].address;
        }
    }
    exit(1); // Undef label error
}

void pass2(FILE *pInfile, FILE *pOutfile) {
    int lCounter = -1;
    char lLine[MAX_LINE_LENGTH + 1];
    char *lLabel, *lOpcode, *lArg1, *lArg2, *lArg3, *lArg4;
    int lRet;
    int instruction = 0;

    do{
        lRet = readAndParse(pInfile, lLine, &lLabel, &lOpcode, &lArg1, &lArg2, &lArg3, &lArg4);
        if (lRet == DONE || lRet == EMPTY_LINE) continue;

        // .ORIG
        if (strcmp(lOpcode, ".orig") == 0) {
            lCounter = toNum(lArg1);
            fprintf(pOutfile, "0x%04X\n", lCounter);
            continue;
        }

        // .END
        if (strcmp(lOpcode, ".end") == 0) {
            break;
        }

        // .FILL
        if (strcmp(lOpcode, ".fill") == 0) {
            int val;
            // Check for numbers
            if (lArg1[0] == 'x' || lArg1[0] == '#' || isdigit(lArg1[0]) || lArg1[0] == '-') {
                val = toNum(lArg1);
            } else {
                val = getLabel(lArg1);
            }
            fprintf(pOutfile, "0x%04X\n", (val & 0xFFFF));
            lCounter += 2;
            continue;
        }
        
        // ADD
        if (strcmp(lOpcode, "add") == 0) {
            int dr = getReg(lArg1);
            int sr1 = getReg(lArg2);
            instruction = 1 << 12 | dr << 9 | sr1 << 6;

            // Register
            if (lArg3[0] == 'r') {
                int sr2 = getReg(lArg3);
                instruction |= sr2;
            }

            // Immediate
            else {
               int imm5 = toNum(lArg3);
               if (imm5 > 15 || imm5 < -16) exit(3);
               instruction |= (1 << 5);
               instruction |= (imm5 & 0x1F);
            }
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // AND
        if (strcmp(lOpcode, "and") == 0) {
            int dr = getReg(lArg1);
            int sr1 = getReg(lArg2);
            instruction = 5 << 12 | dr << 9 | sr1 << 6;

            // Register
            if (lArg3[0] == 'r') {
                int sr2 = getReg(lArg3);
                instruction |= sr2;
            }

            // Immediate
            else {
               int imm5 = toNum(lArg3);
               if (imm5 > 15 || imm5 < -16) exit(3);
               instruction |= (1 << 5);
               instruction |= (imm5 & 0x1F);
            }
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // BR
        if (strncmp(lOpcode, "br", 2) == 0) {
            int n = 0, z = 0, p = 0;
            // BR
            if (strcmp(lOpcode, "br") == 0) {
                n = 1;
                z = 1;
                p = 1;
            // NZP Checks
            } else {
                if (strchr(lOpcode, 'n')) n = 1;
                if (strchr(lOpcode, 'z')) z = 1;
                if (strchr(lOpcode, 'p')) p = 1;
            }
            int target = getLabel(lArg1);
            // (Target addr - (PC + 2)) / 2 to find PC offset
            int offset = (target - (lCounter + 2)) / 2;
            if (offset > 255 || offset < -256) exit(4);
            
            instruction = (0 << 12) | n << 11 | z << 10 | p << 9 | (offset & 0x1FF);
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // JMP
        if (strcmp(lOpcode, "jmp") == 0) {
            int baseR = getReg(lArg1);
            instruction = 12 << 12 | baseR << 6;
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // JSR
        if (strcmp(lOpcode, "jsr") == 0) {
            int target = getLabel(lArg1);
            // (Target addr - (PC + 2)) / 2 to find PC offset
            int offset = (target - (lCounter + 2)) / 2;
            if (offset > 1023 || offset < -1024) exit(4);
            instruction = 4 << 12 | 1 << 11 | (offset & 0x7FF);
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // JSRR
        if (strcmp(lOpcode, "jsrr") == 0) {
            int baseR = getReg(lArg1);
            instruction = 4 << 12 | baseR << 6;
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // LDB
        if (strcmp(lOpcode, "ldb") == 0) {
            int dr = getReg(lArg1);
            int baseR = getReg(lArg2);
            int offset = toNum(lArg3);

            if (offset > 31 || offset < -32) exit(4);

            instruction = 2 << 12 | dr << 9 | baseR << 6 | (offset & 0x3F);
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // LDW
        if (strcmp(lOpcode, "ldw") == 0) {
            int dr = getReg(lArg1);
            int baseR = getReg(lArg2);
            int offset = toNum(lArg3);

            if (offset > 31 || offset < -32) exit(4);

            instruction = 6 << 12 | dr << 9 | baseR << 6 | (offset & 0x3F);
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // LEA
        if (strcmp(lOpcode, "lea") == 0) {
            int dr = getReg(lArg1);
            int target = getLabel(lArg2);
            // (Target addr - (PC + 2)) / 2 to find PC offset
            int offset = (target - (lCounter + 2)) / 2;
            if (offset > 255 || offset < -256) exit(4);   
            instruction = 14 << 12 | dr << 9 | (offset & 0x1FF);
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // NOT
        if (strcmp(lOpcode, "not") == 0) {
            int dr = getReg(lArg1);
            int sr = getReg(lArg2);

            instruction = 9 << 12 | dr << 9 | sr << 6 | 1 << 5 | 0x1F;
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // RET
        if (strcmp(lOpcode, "ret") == 0) {
            instruction = 12 << 12 | 7 << 6;
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // RTI
        if (strcmp(lOpcode, "rti") == 0) {
            fprintf(pOutfile, "0x8000\n");
            lCounter += 2;
            continue;
        }

        // LSHF
        if (strcmp(lOpcode, "lshf") == 0) {
            int dr = getReg(lArg1);
            int sr = getReg(lArg2);
            int amount = toNum(lArg3);
            if (amount < 0 || amount > 15) exit(4);
            instruction = 13 << 12 | dr << 9 | sr << 6 | (amount & 0xF);
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // RSHFL
        if (strcmp(lOpcode, "rshfl") == 0) {
            int dr = getReg(lArg1);
            int sr = getReg(lArg2);
            int amount = toNum(lArg3);
            if (amount < 0 || amount > 15) exit(4);
            instruction = 13 << 12 | dr << 9 | sr << 6 | 1 << 4 | (amount & 0xF);
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // RSHFA
        if (strcmp(lOpcode, "rshfa") == 0) {
            int dr = getReg(lArg1);
            int sr = getReg(lArg2);
            int amount = toNum(lArg3);
            if (amount < 0 || amount > 15) exit(4);
            instruction = 13 << 12 | dr << 9 | sr << 6 | 1 << 5 | 1 << 4 | (amount & 0xF);
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // STB
        if (strcmp(lOpcode, "stb") == 0) {
            int sr = getReg(lArg1);
            int baseR = getReg(lArg2);
            int offset = toNum(lArg3);
            if (offset > 31 || offset < -32) exit(4);
            instruction = 3 << 12 | sr << 9 | baseR << 6 | (offset & 0x3F);
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // STW
        if (strcmp(lOpcode, "stw") == 0) {
            int sr = getReg(lArg1);
            int baseR = getReg(lArg2);
            int offset = toNum(lArg3);
            if (offset > 31 || offset < -32) exit(4);
            instruction = 7 << 12 | sr << 9 | baseR << 6 | (offset & 0x3F);
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // TRAP
        if (strcmp(lOpcode, "trap") == 0) {
            int vect = toNum(lArg1);
            if (vect < 0 || vect > 255) exit(4);
            instruction = 15 << 12 | vect & 0xFF;
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

         // XOR
        if (strcmp(lOpcode, "xor") == 0) {
            int dr = getReg(lArg1);
            int sr1 = getReg(lArg2);
            instruction = 9 << 12 | dr << 9 | sr1 << 6;

            // Register
            if (lArg3[0] == 'r') {
                int sr2 = getReg(lArg3);
                instruction |= sr2;
            }

            // Immediate
            else {
               int imm5 = toNum(lArg3);
               if (imm5 > 15 || imm5 < -16) exit(3);
               instruction |= (1 << 5);
               instruction |= (imm5 & 0x1F);
            }
            fprintf(pOutfile, "0x%04X\n", instruction);
            lCounter += 2;
            continue;
        }

        // HALT
        if (strcmp(lOpcode, "halt") == 0) {
            fprintf(pOutfile, "0xF025\n");
            lCounter += 2;
            continue;
        }

        // NOP
        if (strcmp(lOpcode, "nop") == 0) {
            fprintf(pOutfile, "0x0000\n");
            lCounter += 2;
            continue;
        }

    } while(lRet != DONE);
}