CFLAGS = -Wall -Wextra -DDEBUG -g -pedantic
S = prog1sorter
G = prog1generator

default: $(G) $(S)

$(S): $(S).o
	gcc $(CFLAGS) $(S).o -o $(S)

$(G): $(G).o
	gcc $(CFLAGS) $(G).o -o $(G)

$(S).o: $(S).c
	gcc $(CFLAGS) -c $(S).c -o $(S).o

$(G).o: $(G).c
	gcc $(CFLAGS) -c $(G).c -o $(G).o

clean:
	rm -f *o $(S) $(G)
