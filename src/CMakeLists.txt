find_package(Eigen3 3.4 REQUIRED NO_MODULE)
add_executable(wireframe main.cpp)
target_link_libraries (wireframe PUBLIC Eigen3::Eigen ncursesw)
target_include_directories(wireframe PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_sources(wireframe PUBLIC
    ${PROJECT_SOURCE_DIR}/src/application.cpp
    ${PROJECT_SOURCE_DIR}/src/buffer.cpp
    ${PROJECT_SOURCE_DIR}/src/camera.cpp
    ${PROJECT_SOURCE_DIR}/src/color.cpp
    ${PROJECT_SOURCE_DIR}/src/display.cpp
    ${PROJECT_SOURCE_DIR}/src/geometry.cpp
    ${PROJECT_SOURCE_DIR}/src/poly.cpp
    ${PROJECT_SOURCE_DIR}/src/scene.cpp
    ${PROJECT_SOURCE_DIR}/src/sphere.cpp
    ${PROJECT_SOURCE_DIR}/src/timer.cpp
)
