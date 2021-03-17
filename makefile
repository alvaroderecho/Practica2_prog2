CFLAGS = -g -Wall -pedantic
CC = gcc
LDFLAGS = -L.
IDFLAGS = -I.
LDLIBS = -lstack_fDoble

p2_e1a: p2_e1a.o libstack_fDoble.a
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(IDFLAGS) $(LDLIBS)

p2_e1a.o: p2_e1a.c file_utils.h stack_fDoble.h types.h
	$(CC) $(CFLAGS) -c $<

p2_e1b: p2_e1b.o libstack_fDoble.a vertex.o
	$(CC) $(CFLAGS) -o $@ $< vertex.o $(LDFLAGS) $(IDFLAGS) $(LDLIBS)

p2_e1b.o: p2_e1b.c file_utils.h stack_fDoble.h types.h vertex.h
	$(CC) $(CFLAGS) -c $<

vertex.o: vertex.c vertex.h types.h
	$(CC) $(CFLAGS) -c $<


clean:
	@echo "Cleaning: "
	rm -rf *.o p2_e1a p2_e1b