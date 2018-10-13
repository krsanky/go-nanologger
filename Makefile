CFLAGS +=		-W -Wall -O2 -std=c99 -g
LDFLAGS = -lnanomsg

nanologger: ${.TARGET}.c
	$(CC) $(CFLAGS) -o ${.TARGET} \
		${.TARGET}.c \
		util.c \
		-L/usr/local/lib -I/usr/local/include \
		$(LDFLAGS)

nanoclient: ${.TARGET}.c
	$(CC) $(CFLAGS) -o ${.TARGET} \
		${.TARGET}.c \
		util.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg

# TEST 
strstrp: ${.TARGET}.c util.c
	$(CC) $(CFLAGS) -o ${.TARGET} ${.TARGET}.c util.c

test_forms: ${.TARGET}.c forms.c forms.h
	$(CC) $(CFLAGS) -o ${.TARGET} ${.TARGET}.c \
		forms.c util.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg

params_test: ${.TARGET}.c params.c params.h util.h util.c 
	$(CC) $(CFLAGS) -o ${.TARGET} ${.TARGET}.c \
		params.c util.c \
		-L/usr/local/lib -I/usr/local/include \
		-lnanomsg

anchortest: test1.c myhtml.c
	$(CC) $(CFLAGS) -o $(.TARGET) \
		util.c test1.c myhtml.c \
		-L/usr/local/lib -I/usr/local/include \
		$(LDFLAGS)

test:
	@echo CURDIR:${.CURDIR}
	@echo TARGET:${.TARGET} [should be 'test']

clean:
	rm -f writef myserver nanologger nanoclient mdtest params_test
	rm -rf a.out *.BAK *.cgi *.core
cleanlogs: 
	rm -rf nlog.txt log.txt

.PHONY: test clean cleanlogs indent

