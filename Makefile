#makefile autotest (create new test executable and execute it)
test: autotests.c maintest.c visualisationC.c visualisationT.c regulation.c consigne.c
	gcc autotests.c maintest.c visualisationC.c visualisationT.c regulation.c consigne.c -o test
	
	./test

#execute test request even if test executable is up to date
.PHONY: test

#makefile simulation (create new simulation executable and execute it)
simulation: simulateur.c test_simulateur.c visualisationC.c visualisationT.c regulation.c consigne.c
	gcc simulateur.c test_simulateur.c visualisationC.c visualisationT.c regulation.c consigne.c -o simulation
	
	./simulation


#execute simulation request even if simulation executable is up to date
.PHONY: simulation


testusb: test_usb.c visualisationC.c visualisationT.c regulation.c consigne.c releve.c commande.c
	gcc test_usb.c visualisationC.c visualisationT.c regulation.c consigne.c releve.c commande.c lib/ftd2xx.lib -o testusb
	
	./testusb

#execute testusb request even if testusb executable is up to date
.PHONY: testusb


#makefile clean (delete all executable)
clean:
	rm -f test simulation testusb