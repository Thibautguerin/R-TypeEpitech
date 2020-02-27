cmake_minimum_required(VERSION 3.5)

project(r-type)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
    include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
else()
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake) # Not CLion
endif()
conan_basic_setup()

set(SOURCE_SERVER	./src/server/main.cpp
					./src/server/Server.cpp
					./src/server/Game.cpp
					./src/Lobby.cpp
					./src/Player.cpp
					./src/DataToVector.cpp
					./src/VectorToData.cpp)
add_executable(r-type_server WIN32 ${SOURCE_SERVER})
target_link_libraries(r-type_server ${CONAN_LIBS})

set(SOURCE_CLIENT	./src/client/main.cpp
					./src/client/Client.cpp
					./src/client/Connection.cpp
					./src/client/Lobbies.cpp
					./src/client/DisplayLobby.cpp
					./src/Lobby.cpp
					./src/Player.cpp
					./src/DataToVector.cpp
					./src/VectorToData.cpp
					./src/client/SFML/Window/SFMLWindow.cpp
					./src/client/SFML/Rectangle/SFMLRectangle.cpp
					./src/client/SFML/Text/SFMLText.cpp)
add_executable(r-type_client WIN32 ${SOURCE_CLIENT})
target_link_libraries(r-type_client ${CONAN_LIBS})