#include <stdio.h>
#include <stdlib.h>
#include "stack_fDoble.h"
#include "file_utils.h"


Status mergeStacks(Stack * sin1, Stack * sin2, Stack * sout);

int main() {


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
            if (float_cmp(stack_top(sin1),stack_top(sin2)) > 0)
                e = stack_pop(sin1);
            else
                e = stack_pop(sin2);
            stack_push(sout, e);
        }
        //Detect non-empty stack
        if (stack_isEmpty(sin1) == TRUE) 
            ps = sin2;
        else
            ps = sin1;

        //pop
        while (stack_isEmpty(ps) == FALSE ) {
            e = stack_pop(ps);
            stack_push(sout,e);
        }
    st = OK;
    return st;

    }