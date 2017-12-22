g++ -std=c++11 -pg -o hw1 hw1.cpp
./hw1 ../Updated_Dataset/updated_train.txt ../Updated_Dataset/updated_test.txt 
gprof hw1 gmon.out > hw1_gprof_output.txt