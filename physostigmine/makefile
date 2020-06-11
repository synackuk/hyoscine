.PHONY: n1ghtshade_app jb_init

all: n1ghtshade_app jb_init

n1ghtshade_app:
	@echo Building $(@)
	@make copy -C $(@)

jb_init:
	@echo Building $(@)
	@make copy -C $(@)

clean:
	@make clean -C n1ghtshade_app
	@make clean -C jb_init
