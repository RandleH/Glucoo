cmake_minimum_required (VERSION 2.8)

project(Glucoo)

#add_executable(main main.c)


include_directories (../Glucoo)
include_directories (../Glucoo/Font)
include_directories (../Glucoo/STB)
include_directories (../BlackHouse)


aux_source_directory(.              SRC_MAIN)
aux_source_directory(../BlackHouse  SRC_BLACKHOUSE)
aux_source_directory(../Glucoo      SRC_GLUCOO)
aux_source_directory(../Glucoo/Font SRC_FONT)

add_compile_options(-std=c99)
add_executable(main main.c ${SRC_BLACKHOUSE})


