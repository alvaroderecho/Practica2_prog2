#include <stdio.h>
#include <stdlib.h>
#include "stack_fDoble.h"
#include "file_utils.h"
#include "vertex.h"

Status mergeStacks(Stack * sin1, Stack * sin2, Stack * sout, int (*funcion)());

int main(int argc,char * argv[]) {
    


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
            //i = float_cmp(stack_top(sin1),stack_top(sin2));
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