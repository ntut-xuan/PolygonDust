if(EXISTS "/Users/xuan/Documents/PolygonDust/PolygonDust-gtest[1]_tests.cmake")
  include("/Users/xuan/Documents/PolygonDust/PolygonDust-gtest[1]_tests.cmake")
else()
  add_test(PolygonDust-gtest_NOT_BUILT PolygonDust-gtest_NOT_BUILT)
endif()
