#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "stack.h"
#include "booleanEvaluation.h"
#include "booleanWithError.h"


/* TODO
 * printNames
 * input: none
 * output: none
 *
 * Prints names of the students who worked on this solution
 */
void printNames( )
{
    /* TODO : Fill in you and your partner's names (or N/A if you worked individually) */
    printf("This solution was completed by:\n");
    printf("XXXXXXXXX\n");
    printf("YYYYYYYYY\n");
}

/* TODO
 * evaluatePostfix
 * input: a postfix expression (calls tokenizeString to get the tokens from the string)
 * output: T, F, or E
 *
 * Uses a stack to evaluates the postfix expression and returns the result as a string where "T" denotes true and "F" denotes false.
 * If the postfix expression is invalid it returns "E" to denote an error has occurred.  Be sure to use the helpful functions in booleanEvaluation.
 *
 * Hints:
 * - DO NOT free the parameter str.  It is freed by the calling function.
 * - Be sure to use the helpful functions in booleanEvaluation.
 * - Test your code often!  Get it working correctly for the first couple test cases instead of trying to solve all of them at once.
 */
char *evaluatePostfix( char *str )
{
    /* changed  (op1 operaton op2) ? "T" : "F"  to  booleanToString(op1 operation op2) */
    /* Your variable Declarations: */
    int tokenCount;
    char** arrTokens = tokenizeString( str, &tokenCount );
    /* Currently commented out to prevent a memory leak.  Uncomment to get the tokens from str. */
    int i;
    Stack* postFixEvaluation = createStack(); /* Our s */
    for (i=0; i<tokenCount;i++)
    {
       if(strcmp(arrTokens[i], "T")==0 || strcmp(arrTokens[i], "F")==0){
         push(postFixEvaluation, arrTokens[i]);
       }
       else if( (!isEmpty(postFixEvaluation))  &&  (strcmp(arrTokens[i], "NOT")==0) ){ /* NOT */
        /*char* tmp = (char*)malloc(sizeof(char)*(strlen(top(postFixEvaluation))+1));
        strcpy(tmp, pop(postFixEvaluation));*/
        char* tmp = pop(postFixEvaluation);
        boolean op1 =  stringToBoolean(tmp);
        free(arrTokens[i]);
        push(postFixEvaluation, booleanToString(!op1));
        free(tmp);
       }
       else if(postFixEvaluation->top < 1){ /*ERROR*/
         int j;
         for (j=i; j<tokenCount; ++j)
         {
           free(arrTokens[j]);
         }
         // freeStackElements(postFixEvaluation);
         free(arrTokens);
         freeStackElements(postFixEvaluation);
         freeStack(postFixEvaluation);
         return booleanToString( ERROR );
       }
       else {
         char* tmp1 = pop(postFixEvaluation);
         char* tmp2 = pop(postFixEvaluation);
         boolean op2 =  stringToBoolean(tmp1); /* Switches order for proper stack order/bicond*/
         boolean op1 =  stringToBoolean(tmp2);
         if(strcmp(arrTokens[i], "AND")==0){ /* AND */
           push(postFixEvaluation, booleanToString(op1 && op2));
         }
         else if(strcmp(arrTokens[i], "NAND")==0){ /* NAND */
           push(postFixEvaluation, booleanToString(!(op1 && op2)));
         }
         else if(strcmp(arrTokens[i], "OR")==0){ /* OR */
           push(postFixEvaluation, booleanToString(op1 || op2));
         }
         else if(strcmp(arrTokens[i], "XOR")==0){ /* XOR */
           push(postFixEvaluation,  booleanToString(op1 != op2));
         }
         else if(strcmp(arrTokens[i], "NOR")==0){ /* NOR */
           push(postFixEvaluation, booleanToString (!(op1 || op2)));
         }
         else if(strcmp(arrTokens[i], "COND")==0){ /* COND */
           push(postFixEvaluation, booleanToString(!op1 || op2) );
         }
         else if(strcmp(arrTokens[i], "BICOND")==0){ /* BICOND */
           push(postFixEvaluation, booleanToString (op1 == op2));
         }
         else{ /* ERROR "E" */
           free(tmp1);
           free(tmp2);
           int j;
           for (j=i; j<tokenCount; ++j)
           {
             free(arrTokens[j]);
           }
           freeStackElements(postFixEvaluation);
           // freeStackElements(postFixEvaluation);
           free(arrTokens);
           freeStack(postFixEvaluation);
           return booleanToString( ERROR );
         }
         free(arrTokens[i]);
         free(tmp1);
         free(tmp2);
       }

    }
    // char* x = pop(postFixEvaluation);
    boolean x = stringToBoolean(top(postFixEvaluation));
    free(pop(postFixEvaluation));
    // char* x = (char*)malloc(sizeof(char)*(strlen(top(postFixEvaluation))+1));
    // strcpy(x, pop(postFixEvaluation));
    if (isEmpty(postFixEvaluation))
    {
      freeStackElements(postFixEvaluation);
      free(arrTokens);
      freeStack(postFixEvaluation);
      return booleanToString(x);
    }
    else {
      freeStackElements(postFixEvaluation);
      free(arrTokens);
      freeStack(postFixEvaluation);
      return booleanToString( ERROR );
    }
    /* Replace this with your actual solution to return */
}

/* TODO
 * postfixToInfix
 * input: a postfix expression (calls tokenizeString to get the tokens from the string)
 * output: the equivalent infix expression
 *
 * Uses a stack to convert str to its equivalent expression in infix.
 * You can assume that the postfix expression is valid
 *
 * Hints:
 * - DO NOT free the parameter str.  It is freed by the calling function.
 * - Be sure to use the helpful functions in booleanEvaluation.
 * - Test your code often!  Get it working correctly for the first couple test cases instead of trying to solve all of them at once.
 */
char *postfixToInfix( char *str )
{
    /* Your variable Declarations: */
    int tokenCount;
    char** arrTokens = tokenizeString( str, &tokenCount );  /* Currently commented out to prevent a memory leak.  Uncomment to get the tokens from str. */
    int i;
    Stack* postFixToInfix = createStack(); /* Our s */
    for (i=0; i<tokenCount;i++)
    {
       if(strcmp(arrTokens[i], "T")==0 || strcmp(arrTokens[i], "F")==0){
         push(postFixToInfix, arrTokens[i]);
       }
       else if( (!isEmpty(postFixToInfix))  &&  (strcmp(arrTokens[i], "NOT")==0) ){ /* NOT */
         char* op1 = pop(postFixToInfix);
         int size = strlen(op1)+strlen(arrTokens[i])+6;
         char* ret = (char*)malloc(sizeof(char)*size);
         strcpy(ret, "( \0");
         push( postFixToInfix, strcat( strcat( strcat( strcat(ret, arrTokens[i]), " "), op1 ), " )" )  );
         free(arrTokens[i]);

         free(op1);
       }
       else if(postFixToInfix->top < 1){ /*ERROR*/
         int j;
         for (j=i; j<tokenCount; ++j)
         {
           free(arrTokens[j]);
         }
         free(arrTokens);
         //freeStackElements(postFixToInfix);
         freeStack(postFixToInfix);
         return booleanToString( ERROR );
       }
       else {
         char* op2 = pop(postFixToInfix);
         char* op1 = pop(postFixToInfix);
         int size = strlen(op1)+strlen(op2)+strlen(arrTokens[i])+9;
         char* ret = (char*)malloc(sizeof(char)*size);
         strcpy(ret, "( \0");
         if(strcmp(arrTokens[i], "AND")==0){ /* AND*/
           push( postFixToInfix, strcat( strcat( strcat( strcat( strcat( strcat(ret, op1), " "), arrTokens[i] ), " " ), op2 ), " )" )  );
           free(op2);
           free(op1);
         }
         else if(strcmp(arrTokens[i], "NAND")==0){ /* NAND*/
           push( postFixToInfix, strcat( strcat( strcat( strcat( strcat( strcat(ret, op1), " "), arrTokens[i] ), " " ), op2 ), " )" )  );
           free(op2);
           free(op1);
         }
         else if(strcmp(arrTokens[i], "OR")==0){ /* OR*/
           push( postFixToInfix, strcat( strcat( strcat( strcat( strcat( strcat(ret, op1), " "), arrTokens[i] ), " " ), op2 ), " )" )  );
           free(op2);
           free(op1);
         }
         else if(strcmp(arrTokens[i], "XOR")==0){ /* XOR*/
           push( postFixToInfix, strcat( strcat( strcat( strcat( strcat( strcat(ret, op1), " "), arrTokens[i] ), " " ), op2 ), " )" )  );
           free(op2);
           free(op1);
         }
         else if(strcmp(arrTokens[i], "NOR")==0){ /* NOR*/
           push( postFixToInfix, strcat( strcat( strcat( strcat( strcat( strcat(ret, op1), " "), arrTokens[i] ), " " ), op2 ), " )" )  );
           free(op2);
           free(op1);
         }
         else if(strcmp(arrTokens[i], "COND")==0){ /* COND*/
           push( postFixToInfix, strcat( strcat( strcat( strcat( strcat( strcat(ret, op1), " "), arrTokens[i] ), " " ), op2 ), " )" )  );
           free(op2);
           free(op1);
         }
         else if(strcmp(arrTokens[i], "BICOND")==0){ /* BICOND*/
           push( postFixToInfix, strcat( strcat( strcat( strcat( strcat( strcat(ret, op1), " "), arrTokens[i] ), " " ), op2 ), " )" )  );
           free(op2);
           free(op1);
         }
         else { /* ERROR "E" */
           int j;
           for (j=i; j<tokenCount; ++j)
           {
             free(arrTokens[j]);
           }
           free(arrTokens);
           free(ret);
           // freeStackElements(postFixToInfix);
           freeStack(postFixToInfix);
           return booleanToString( ERROR );
         }
         free(arrTokens[i]);
         // free(ret);
       }

    }
    char* ans = pop(postFixToInfix);
    free(arrTokens);
    // freeStackElements(postFixToInfix);
    freeStack(postFixToInfix);
    return ans; /* Replace this with your actual solution to return */
}


/* You may want to create some helper functions down here! */
