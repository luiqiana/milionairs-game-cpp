cmake_minimum_required(VERSION 4.0)
project(mil)

set(CMAKE_CXX_STANDARD 20)

#   MySQL 9.5.0 path in case of using MacOS on Mac with Apple Silicon
set(MYSQL_ROOT "/opt/homebrew/Cellar/mysql-connector-c++/9.5.0")

include_directories(${MYSQL_ROOT}/include)

#   GLOB because of * in path
file(GLOB FOUND_LIBRARIES "${MYSQL_ROOT}/lib/libmysqlcppconn*.dylib")

#   Check is anything in there
if(FOUND_LIBRARIES)
    message(STATUS "Found libraries: ${FOUND_LIBRARIES}")
else()
    message(FATAL_ERROR "Directory ${MYSQL_ROOT}/lib doesn't have any files with .dylib extension")
endif()

file(COPY database/.env DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/database)
file(COPY database/dbSchem.sql DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/database)
file(COPY database/dbQuest.sql DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/database)

add_executable(mil main.cpp
        database/envLoader.h
        database/Database.cpp
        database/Database.h
        database/dbInit.cpp
        database/dbInit.h
        utils/utils.h
        utils/formating.h
        interface/mainMenu.cpp
        interface/mainMenu.h
        interface/credentials.h)

target_link_libraries(mil ${FOUND_LIBRARIES})