.PHONY: physostigmine hyoscine
all:  physostigmine hyoscine

physostigmine:
	@make -C physostigmine

hyoscine:
	@make -C hyoscine

clean:
	@make clean -C physostigmine 
	@make clean -C hyoscine