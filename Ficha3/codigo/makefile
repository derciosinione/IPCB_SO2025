FLAGS = -Wall -g

all:
	make ex21
	make ex23
	make ex25a
	make ex26a
	make ex26b
	make ex31
	make ex44
	make ex45a
	make ex45b
	make ex45c
	make ex45d

% : %.c
	gcc ${FLAGS} $< -o $@

ex21:	ex21.c
ex23:	ex23.c
ex25a:	ex25a.c
ex26a:	ex26a.c
ex26b:	ex26b.c
ex31:	ex31.c
ex44a:	ex44.c
ex44a:	ex45a.c
ex44b:	ex45b.c
ex44c:	ex45c.c
ex44d:	ex45d.c

clean:
	@rm -rf ex21 ex23 ex25a ex26a ex26b ex31 ex44 ex45a ex45b ex45c ex45d
