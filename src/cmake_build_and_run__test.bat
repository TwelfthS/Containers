del build\Debug\s21_containers.exe

cmake -D CMAKE_CXX_COMPILER=g++ -S . -B build 
cmake --build build
build\Debug\s21_containers.exe