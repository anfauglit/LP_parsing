objects = parsemodule.o p_sent.o 

parse : $(objects)
	gcc -o parse $(objects)

$(objects) : parse.h

clean:
	rm parse $(objects)
