
list-targets:
	echo "basic-ncurses"

.PHONY: clean
clean:
	rm -f bin/ncvm

basic-ncurses: clean
	$(MAKE) -C $@
	./emulate-target.sh -t

stop-test:
	./emulate-target.sh -k

