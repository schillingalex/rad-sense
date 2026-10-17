.PHONY: tests

tests: build/test_radiation_dose
	build/test_radiation_dose

build/test_radiation_dose: fsw/shared/radiation_dose.c tests/test_radiation_dose.c fsw/shared/radiation_dose.h
	mkdir -p build
	cc -std=c99 -Wall -Wextra -Werror -pedantic -Wstrict-prototypes -Iinclude fsw/shared/radiation_dose.c tests/test_radiation_dose.c -lm -o build/test_radiation_dose
