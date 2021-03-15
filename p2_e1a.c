#include <stdio.h>
#include <stdlib.h>
#include "stack_fDoble.h"
#include "file_utils.h"


Status mergeStacks(Stack * sin1, Stack * sin2, Stack * sout);

int main(int argc,char * argv[]) {
Stack *p1,*p2,*pout;
FILE *f1,*f2;
int num1,num2,i,x;
float nota1[100],nota2[100];
p1 = stack_init();
p2 = stack_init();
pout = stack_init();
f1 = fopen (argv[1],"r");
fscanf(f1,"%d",&num1);
for(i=0;fscanf(f1,"%f",&nota1[i])==1;i++){

}
for (i=0;i<num1;i++){
    
    if (stack_push(p1,&nota1[i])==ERROR) return -1;
}
fclose(f1);

f2 = fopen (argv[2],"r");
fscanf(f2,"%d",&num2);
for(i=0;fscanf(f2,"%f",&nota2[i])==1;i++){

}
for (i=0;i<num2;i++){
    
    if (stack_push(p2,&nota2[i])==ERROR) return -1;
}
fclose(f2);

printf("Ranking 0:\n");

x=stack_print(stdout,p1,float_print);
if (x<0) return -1;
printf("Ranking 1:\n");
x=stack_print(stdout,p2,float_print);
if (x<0) return -1;
printf("Ranking 2:\n");
if (mergeStacks(p1,p2,pout)==ERROR) return -1;
x=stack_print(stdout,pout,float_print);
if (x<0) return -1;
return 0;
}

Status mergeStacks(Stack * sin1, Stack * sin2, Stack * sout) {

        void *e;
        Stack * ps;
        Status st = ERROR;
        if ((ps = stack_init()) == NULL) return st;


        while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE)
        {
            //una de las dos vacía se sale del bucle
            //int i;
            //i = float_cmp(stack_top(sin1),stack_top(sin2));
            if (*(float*)stack_top(sin1)>*(float*)stack_top(sin2)){
                e = stack_pop(sin1);
                if (e == NULL) return ERROR;
                if (stack_push(sout, e)==ERROR) return ERROR;
            }
            else{
                e = stack_pop(sin2);
                if (e == NULL) return ERROR;
                if (stack_push(sout, e)==ERROR) return ERROR;
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
            if (e == NULL) return ERROR;
            if (stack_push(sout,e) == ERROR) return ERROR;
        }
    st = OK;
    return st;

    }