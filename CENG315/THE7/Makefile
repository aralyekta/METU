CXXFLAGS=-Wall -std=c++11 -g
SRCS=main.cpp the7.cpp
EXENAME=the7


the7:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(EXENAME)

clean:
	$(RM) $(EXENAME)
	-rm -rf my_outputs differance


test%: the7
	-@mkdir -p differance/
	-@mkdir -p my_outputs/
	-@./$(EXENAME) small_inputs/$@ > my_outputs/$@.out
	-@diff -s small_outputs/$@.out my_outputs/$@.out > differance/$@
	
test_all: the7
	@for foo in small_inputs/*;do bar="$${foo#small_inputs/}"; make $$bar ; done
