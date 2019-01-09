cmake_minimum_required(VERSION 3.10)
project(EcsPlus)

set(CMAKE_CXX_STANDARD 17)

find_package (Threads)
find_package(SFML 2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})
include_directories(src)
include_directories(component)
include_directories(system)

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
		src/ecs/Vector2.hpp

        src/ecs/ThreadPool.cpp
        src/ecs/ThreadPool.hpp

		src/ecs/Graphic.cpp
		src/ecs/Graphic.hpp

		src/physic2D/system/physic2D.cpp
		src/physic2D/system/physic2D.hpp
		src/physic2D/Vec2/vec2.cpp
		src/physic2D/Vec2/vec2.hpp

		src/component/graphical/Drawable.hpp
		src/component/graphical/Sprite.hpp

		src/component/control/Controller.hpp
		src/component/control/Keyboard.hpp
		src/component/control/Mouse.hpp

		src/system/control/ControlsSFML.cpp
		src/system/control/ControlsSFML.hpp
		src/system/control/Controls.cpp
		src/system/control/Controls.cpp

		Main.cpp src/system/Update.cpp src/system/Update.hpp)

target_link_libraries(EcsPlus ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(EcsPlus ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})