file(GLOB TEST_SOURCES *.cpp)

add_executable(znet_tests ${TEST_SOURCES})

target_link_libraries(znet_tests
  znet
  Boost::unit_test_framework
  Boost::unordered
  Boost::hana
)

target_include_directories(znet_tests PRIVATE ${PROJECT_SOURCE_DIR}/include)
