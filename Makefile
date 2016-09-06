VPATH = src : tests
OBJS = main.o roman_numeral.o
COBJ = roman_numeral.o check_roman_numeral.o

roman_numeral_cal : $(OBJS)
	cc -o roman_numeral_cal $(OBJS)

$(OBJS) : roman_numeral.h

check : $(COBJ) roman_numeral_cal
	cc -o check_roman_numeral $(COBJ) `pkg-config --cflags --libs check`

.PHONY : clean
clean :
	rm roman_numeral_cal $(OBJS)

.PHONY : clean-check
clean-check:
	rm roman_numeral_cal check_roman_numeral $(OBJS) check_roman_numeral.o
