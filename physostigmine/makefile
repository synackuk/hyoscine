.PHONY: n1ghtshade_app jb_init non_default_apps

all: n1ghtshade_app jb_init non_default_apps

n1ghtshade_app:
	@echo Building $(@)
	@make copy -C $(@)

jb_init:
	@echo Building $(@)
	@make copy -C $(@)

non_default_apps:
	@echo Building $(@)
	@make copy -C $(@)

clean:
	@make clean -C n1ghtshade_app
	@make clean -C jb_init
	@make clean -C non_default_apps
