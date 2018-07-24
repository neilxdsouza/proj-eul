LIB_SRC=big_int.h big_int.cpp 

TEST_SRC=test_big_int.cpp

test_multiply.exe: $(LIB_SRC) test_big_int.cpp
	g++ -g  -DTEST_MULTIPLY test_big_int.cpp big_int.cpp -o $@

test_oper_less.exe: $(LIB_SRC) test_big_int.cpp 
	g++ -g -DTEST_OPER_LESS test_big_int.cpp big_int.cpp -o $@ 

test_oper_subtract.exe: $(LIB_SRC) test_big_int.cpp 
	g++ -g -DTEST_SUBTRACT test_big_int.cpp big_int.cpp -o $@ 

test_oper_is_eq.exe: $(LIB_SRC) test_big_int.cpp 
	g++ -g -DTEST_OPER_IS_EQ test_big_int.cpp big_int.cpp -o $@ 

2_euler.exe: 2_euler.cpp $(LIB_SRC)
	g++ -std=c++11 -g -o $@ 2_euler.cpp big_int.cpp
