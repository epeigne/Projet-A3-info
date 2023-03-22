#makefile autotest (remove old test executable and create new one and execute it)
test: IHM_execs/autotests.c IHM_execs/maintest.c code/visualisationC.c code/visualisationT.c code/regulation.c code/consigne.c
	gcc IHM_execs/autotests.c IHM_execs/maintest.c code/visualisationC.c code/visualisationT.c code/regulation.c code/consigne.c -o IHM_execs/test
	
	./IHM_execs/test