all:
	gcc -o test.out thc.c test_thc.c && ./test.out

test:
	python -m unittest discover -v -p '*tests.py'
