#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack_fDoble.h"
#include "file_utils.h"

#define MAX_LENGTH 100
#define FAIL -1

Status mergeStacks(Stack * sin1, Stack * sin2, Stack * sout);

int main(int argc,char * argv[]) {

Stack *p1,*p2,*pout;
FILE *f1,*f2;
int num1,num2,i,x;
float nota1[MAX_LENGTH],nota2[MAX_LENGTH];
if (argc != 3 ){
    printf("Wrong number of input parameters.");
    return FAIL;
}
if (strcmp(argv[1],"grades1.txt")!=0){
    printf ("Error opening file 1: %s.", argv[1]);
    return FAIL;
}
if (strcmp(argv[2],"grades2.txt")!=0){
    printf ("Error opening file 1: %s.", argv[2]);
    return FAIL;
}
if ((p1 = stack_init()) == NULL){ 
    printf("Error creating the stacks.");
    return FAIL;
}
if ((p2 = stack_init()) == NULL){ 
    printf("Error creating the stacks.");
    return FAIL;
}
if ((pout = stack_init()) == NULL){ 
    printf("Error creating the stacks.");
    return FAIL;
}
if ((f1 = fopen (argv[1],"r")) == NULL) return FAIL;
fscanf(f1,"%d",&num1);
for(i=0;fscanf(f1,"%f",&nota1[i])==1;i++){

}
for (i=0;i<num1;i++){
    
    if (stack_push(p1,&nota1[i])==ERROR){ 
    printf("Error pushing elements into stack 1.");
    stack_free(p1);
    stack_free(p2);
    stack_free(pout);
    fclose(f1);
    return FAIL;
    }
}
fclose(f1);

if ((f2 = fopen (argv[2],"r")) == NULL) return FAIL;
fscanf(f2,"%d",&num2);
for(i=0;fscanf(f2,"%f",&nota2[i])==1;i++){

}
for (i=0;i<num2;i++){
    
    if (stack_push(p2,&nota2[i])==ERROR){
    printf ("Error pushing elements into stack 2.");
    stack_free(p1);
    stack_free(p2);
    stack_free(pout);
    fclose(f2);
    return FAIL;
}
}
fclose(f2);

printf("Ranking 0:\n");

x=stack_print(stdout,p1,float_print);
if (x<0){
    stack_free(p1);
    stack_free(p2);
    stack_free(pout);
    return FAIL;
}
printf("Ranking 1:\n");
x=stack_print(stdout,p2,float_print);
if (x<0){
    stack_free(p1);
    stack_free(p2);
    stack_free(pout);
    return FAIL;
}
printf("Joint Ranking:\n");
if (mergeStacks(p1,p2,pout)==ERROR){
    printf("Error in mergeStacks.");
    stack_free(p1);
    stack_free(p2);
    stack_free(pout);
return FAIL;
}
x=stack_print(stdout,pout,float_print);
stack_free(p1);
stack_free(p2);
stack_free(pout);
return 0;
}

Status mergeStacks(Stack * sin1, Stack * sin2, Stack * sout) {

        void *e;
        Stack * ps;
        Status st = ERROR;
        
        if (sin1 == NULL)return ERROR;
        if (sin2 == NULL) return ERROR;


        while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE)
        {
            //una de las dos vac??a se sale del bucle
            
            if (float_cmp(stack_top(sin1),stack_top(sin2)) > 0){
                e = stack_pop(sin1);
                if (e == NULL) return st;
                if (stack_push(sout, e)==st) return st;
            }
            else{
                e = stack_pop(sin2);
                if (e == NULL) return st;
                if (stack_push(sout, e)==st) return st;
        }
        }
        //Detect non-empty stack
        if (stack_isEmpty(sin1) == TRUE) 
            ps = sin2;
        else
            ps = sin1;

        //pop
        while (stack_isEmpty(ps) == FALSE ) {
            e = stack_pop(ps);
            if (e == NULL){
            //stack_free(ps);
             return st;
        }
            if (stack_push(sout,e) == st) {
            //stack_free(ps);
            return st;
            }
        }
        //stack_free(ps);
        st = OK;
    return st;

    }