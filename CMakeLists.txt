project (facil.io-examples C)

set(BUILD_SHARED_LIBS true)
add_subdirectory(facil.io)

add_executable(helloworld helloworld.c)
target_link_libraries(helloworld PUBLIC facil.io)

add_executable(websocket websocket.c)
target_link_libraries(websocket PUBLIC facil.io)

add_executable(echo echo.c)
target_link_libraries(echo PUBLIC facil.io)
