#include <stdio.h>
#include <stdlib.h>
#include "stack_fDoble.h"
#include "file_utils.h"
#include "vertex.h"

#define MAX_LENGTH 64
#define FAIL -1

Status mergeStacks(Stack * sin1, Stack * sin2, Stack * sout, int (*funcion)());

int main(int argc,char * argv[]) {
Stack *p1, *p2, *pout;
FILE *f1,*f2;
Vertex *v1,*v2;
char desc1[MAX_LENGTH], desc2[MAX_LENGTH];
int num1,num2,i,sx;

if (argc != 3) {
    printf("Debe incluir tres argumentos: ./exe arg1.txt arg2.txt \n");
    return FAIL;
}

if ((p1 = stack_init()) == NULL) return FAIL;
if ((p2 = stack_init()) == NULL) {
stack_free(p1);
return FAIL;
}
if ((pout = stack_init()) == NULL) {
    stack_free(p1);
    stack_free(p2);
return FAIL;
}
if ((f1 = fopen (argv[1],"r")) == NULL) {
    stack_free(p1);
    stack_free(p2);
    stack_free(pout);
return FAIL;
}
fscanf(f1,"%d\n",&num1);

for (i=0;i<num1;i++) { //first file
    fgets(desc1,MAX_LENGTH,f1);
    v1 = vertex_initFromString(desc1);
    if (stack_push(p1,v1) == ERROR) {
        vertex_free(v1);
        stack_free(p1);
        stack_free(p2);
        stack_free(pout);
        fclose(f1);
        return FAIL;
    }
}

fclose(f1);

if ((f2 = fopen (argv[2],"r")) == NULL) {
    stack_free(p1);
    stack_free(p2);
    stack_free(pout);
return FAIL;
}
fscanf(f2,"%d\n",&num2);

for (i=0;i<num2;i++) { //second file
    fgets(desc2,MAX_LENGTH,f2);
    v2 = vertex_initFromString(desc2);
    if (stack_push(p2,v2) == ERROR) {
        vertex_free(v1);
        vertex_free(v2);
        stack_free(p1);
        stack_free(p2);
        stack_free(pout);
        fclose(f2);
        return FAIL;
    }
}
fclose(f2);

printf("Ranking 0:\n");

sx = stack_print(stdout,p1,vertex_print);
if (sx<0) {
    vertex_free(v1);
    vertex_free(v2);
    stack_free(p1);
    stack_free(p2);
    stack_free(pout);
    return FAIL;
    }

printf("Ranking 1:\n");
sx = stack_print(stdout,p2,vertex_print);

if (sx<0) {
    vertex_free(v1);
    vertex_free(v2);
    stack_free(p1);
    stack_free(p2);
    stack_free(pout);
    return FAIL;
    }

printf("Ranking 2:\n");

if (mergeStacks(p1,p2,pout,vertex_cmp)==ERROR){
    vertex_free(v1);
    vertex_free(v2);
    stack_free(p1);
    stack_free(p2);
    stack_free(pout);
return FAIL;
}
sx=stack_print(stdout,pout,vertex_print);
vertex_free(v1);
vertex_free(v2);
stack_free(p1);
stack_free(p2);
stack_free(pout);


return 0;
}

Status mergeStacks(Stack * sin1, Stack * sin2, Stack * sout,  int (*funcion)()) {

        void *e;
        Stack * ps;
        Status st = ERROR;
        


        while (stack_isEmpty(sin1) == FALSE && stack_isEmpty(sin2) == FALSE)
        {
            //una de las dos vacía se sale del bucle
            //int i;
            //i = vertex_cmp(stack_top(sin1),stack_top(sin2));
            if (funcion(stack_top(sin1),stack_top(sin2)) > 0){
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