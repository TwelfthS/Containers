all: clean stylecheck test

test:
	mkdir build && \
		cd build && \
		cmake -Wno-dev .. && \
		make && \
		./s21_containers

debug:
	mkdir build && \
		cd build && \
		cmake -Wno-dev -DCMAKE_BUILD_TYPE=Debug .. && \
		make && \
		./s21_containers

stylecheck:
	cp ../materials/linters/.clang-format .
	clang-format -n *.h
	clang-format -n binary_tree/*.h
	clang-format -n set/*.h 
	clang-format -n map/*.h 
	clang-format -n multiset/*.h 
	clang-format -n queue/*.h 
	clang-format -n array/*.h 
	clang-format -n vector/*.h 
	clang-format -n list/*.h 
	clang-format -n stack/*.h 
	clang-format -n tests/*.cc
	rm .clang-format
	
stylefix:
	cp ../materials/linters/.clang-format .
	clang-format -i *.h
	clang-format -i binary_tree/*.h
	clang-format -i set/*.h 
	clang-format -i map/*.h 
	clang-format -i multiset/*.h 
	clang-format -i queue/*.h 
	clang-format -i array/*.h 
	clang-format -i vector/*.h 
	clang-format -i list/*.h 
	clang-format -i stack/*.h 
	clang-format -i tests/*.cc
	rm .clang-format

valgrind:
	valgrind --leak-check=full --show-reachable=yes --track-origins=yes -s build/s21_containers

linter_check:
	cp ../materials/linters/CPPLINT.cfg .
	-python3 ../materials/linters/cpplint.py *.h 
	-python3 ../materials/linters/cpplint.py binary_tree/*.h 
	-python3 ../materials/linters/cpplint.py set/* 
	-python3 ../materials/linters/cpplint.py map/* 
	-python3 ../materials/linters/cpplint.py multiset/* 
	-python3 ../materials/linters/cpplint.py queue/* 
	-python3 ../materials/linters/cpplint.py array/* 
	-python3 ../materials/linters/cpplint.py vector/* 
	-python3 ../materials/linters/cpplint.py stack/* 
	-python3 ../materials/linters/cpplint.py list/* 
	-python3 ../materials/linters/cpplint.py tests/* 
	rm CPPLINT.cfg

gcov_report:
	cd build/CMakeFiles/s21_containers.dir/tests && \
	gcov test_runner.cc.gcno && \
	lcov -c -d . -o cov.info && \
	genhtml cov.info -o report && \
	firefox ./report/index.html

clean:
	rm -rf build
