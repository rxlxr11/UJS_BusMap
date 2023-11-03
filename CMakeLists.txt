cmake_minimum_required(VERSION 3.26)
project(datastruct C)

set(CMAKE_C_STANDARD 11)

include_directories(lib/constant)
include_directories(lib/dataio)
include_directories(lib/format)
include_directories(lib/func)
include_directories(lib/struct)
include_directories(lib/user)
include_directories(lib/cilent)
include_directories(lib/admin)

add_executable(datastruct
        lib/constant/constant.h
        lib/dataio/dataio.c
        lib/dataio/dataio.h
        lib/format/format.c
        lib/format/format.h
        lib/func/func.c
        lib/func/func.h
        lib/struct/struct.c
        lib/struct/struct.h
        lib/user/user.c
        lib/user/user.h
        lib/admin/admin.c
        lib/admin/admin.h
        lib/cilent/cilent.h
        lib/cilent/cilent.c
        main.c
        test.c
        lib/constant/constant.c
)
