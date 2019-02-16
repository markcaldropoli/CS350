CFLAGS = -Wall -Wextra -DDEBUG -g -pedantic
T = prog2tree
O = test
SF = simplefork

default: $(T)

#main assignment

$(T): $(T).o
	gcc $(CFLAGS) $(T).o -o $(T)

$(T).o: $(T).c
	gcc $(CFLAGS) -c $(T).c -o $(T).o

#test process program

$(O): $(O).o
	gcc $(CFLAGS) $(O).o -o $(O)

$(O).o: $(O).c
	gcc $(CFLAGS) -c $(O).c -o $(O).o

#simplefork

$(SF): $(SF).o
	gcc $(CFLAGS) $(SF).o -o $(SF)

$(SF).o: $(SF).c
	gcc $(CFLAGS) -c $(SF).c -o $(SF).o

#clean

clean:
	rm -f *o $(T) $(O) $(SF)
