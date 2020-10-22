objects = parsemodule.o p_sent.o 

parse : $(objects)
	gcc -o parse $(objects) -lm

$(objects) : parse.h

clean:
	rm parse $(objects)
