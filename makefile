WORKDIR := $(PWD)

usage:
	${info usage:	`make basic-example` to test whether it builds and runs okay}

basic:
	cd basic/ && qmake && $(MAKE)

## It turns out that passing TARGET=$(WORKDIR)/$@
## give a strange result, so let's just move it!
basic-example: basic
	cd ../projects/basic/blank/ && \
	qmake TARGET=$@ && $(MAKE) && \
	mv $@ $(WORKDIR) && cd - && \
	env LD_LIBRARY_PATH=./basic/ ./$@

.PHONY: basic
