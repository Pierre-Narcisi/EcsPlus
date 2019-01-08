cmake_minimum_required(VERSION 3.10)
project(EcsPlus)

set(CMAKE_CXX_STANDARD 17)

find_package (Threads)
find_package(SFML 2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})
include_directories(src)

add_executable(EcsPlus
        src/ecs/DataBank.hpp
        src/ecs/Ecs.hpp
        src/ecs/Entity.cpp
        src/ecs/Entity.hpp
        src/ecs/ComponentList.hpp
        src/ecs/Time.cpp
        src/ecs/Time.hpp
        src/ecs/TimedEvent.cpp
        src/ecs/TimedEvent.hpp
        src/ecs/TimedEventAdmin.cpp
        src/ecs/TimedEventAdmin.hpp
		src/physic2D/system/physic2D.cpp
		src/physic2D/system/physic2D.hpp
		src/physic2D/Vec2/vec2.cpp
		src/physic2D/Vec2/vec2.hpp

        src/ecs/ThreadPool.cpp
        src/ecs/ThreadPool.hpp

        Main.cpp)

target_link_libraries(EcsPlus ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(EcsPlus ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})