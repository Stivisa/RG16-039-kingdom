PROGRAM = Kingdom

game: sub-make
	mv src/$(PROGRAM) .

sub-make: 
	$(MAKE) -C src/


.PHONY: clean beauty

clean:
	-rm src/*.o $(PROGRAM) 

beauty:
	indent -kr src/*.c
