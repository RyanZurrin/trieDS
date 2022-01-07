cmake_minimum_required(VERSION 3.16)
project(trieDS)

set(CMAKE_CXX_STANDARD 14)

add_executable(trieDS main.cpp PrefixTrie.h SuffixTrie.h)
