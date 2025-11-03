objects = src/main.o src/system.o src/auth.o src/register.o src/file.o

atm : $(objects)
	cc -o atm $(objects)

main.o : src/header.h
system.o : src/header.h
auth.o : src/header.h
register.o : src/header.h
file.o : src/header.h

clean :
	rm -f $(objects)
