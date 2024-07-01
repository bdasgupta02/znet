file(GLOB SOURCES *.cpp)

add_library(znet ${SOURCES})

target_link_libraries(znet
  Boost::unordered
  Boost::hana
)

target_include_directories(znet PUBLIC ${PROJECT_SOURCE_DIR}/include)
