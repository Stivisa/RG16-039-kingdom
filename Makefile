game: sub-make
	mv src/Kingdom .

sub-make: 
	$(MAKE) -C src/


.PHONY: clean beauty

clean:
	-rm src/*.o src/$(PROGRAM) 

beauty:
	indent -kr src/*.c
