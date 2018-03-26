cmake_minimum_required(VERSION 3.5)
project(naivebayes)

set(CMAKE_CXX_STANDARD 14)

add_executable(naivebayes src/Image.cpp src/Image.h src/NaiveBayesClassifier.cpp src/NaiveBayesClassifier.h src/main.cpp)
add_executable(unit-tests test/test.cpp src/Image.cpp src/Image.h src/NaiveBayesClassifier.cpp src/NaiveBayesClassifier.h)
