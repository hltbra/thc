all:
	gcc -o thc.o -c thc.c

test:
	python -m unittest discover -v -p '*tests.py'

clean:
	rm thc.o
