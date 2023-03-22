#makefile autotest (create new test executable and execute it)
test: autotests.c maintest.c ../code/visualisationC.c ../code/visualisationT.c ../code/regulation.c ../code/consigne.c
	gcc autotests.c maintest.c ../code/visualisationC.c ../code/visualisationT.c ../code/regulation.c ../code/consigne.c -o test
	
	./test

#execute test request even if test executable is up to date
.PHONY: test
