cmake_minimum_required(VERSION 3.12)
project(EncryptedDiary)

set(CMAKE_CXX_STANDARD 17)

add_executable(main main.c Security.c Security.h Enter.c Enter.h View.c View.h)
add_executable(View main.c View.c View.h)