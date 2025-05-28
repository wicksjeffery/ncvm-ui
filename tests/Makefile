.PHONY: all clean basic-ncurses ncvm-test1

list-targets:
	echo "basic-ncurses"

basic-ncurses:
	$(MAKE) -C $@
	./emulate-target.sh -t

ncvm-test1:
	$(MAKE) -C $@
	./emulate-target.sh -t

stop-test:
	./emulate-target.sh -k

clean:
	rm -f bin/ncvm
	$(MAKE) -C ncvm-test1 clean

