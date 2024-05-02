# ==========================  声明Cmake最小版本  =============================== #
cmake_minimum_required(VERSION 3.16.0)
# 声明项目名称、版本和语言
project(bayesian VERSION 0.2 LANGUAGES CXX)

# ==========================  设定编译选项  ==================================== #
# 强制开启 C++ 14以上标准以兼容ROS2
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # 采用通用编译参数适应跨平台编译
# Enable compile optimizations
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
# Enable debug flags (use if you want to debug in gdb)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -Wall")
# 项目文件路径
set(LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/lib")
# ===========================  设置依赖库  ==================================== #
# r如果存在多版本3rd库，则手动设置路径到包含对应的.cmake文件
# set(OpenCV_DIR "")
# set(Ceres_DIR "")

find_package(Ceres 2.2.0 REQUIRED)  # 非线性优化库
find_package(Eigen3 REQUIRED)       # 矩阵运算库
find_package(fmt REQUIRED)          # 格式化IO库
message(STATUS "Found 3rd party packages:\n"
  "-- => Ceres: " ${Ceres_VERSION} 
  "\n-- => fmt: " ${fmt_VERSION}
)

set(3RD_PARTY_LIBS
  Ceres::ceres
  Eigen3::Eigen
  fmt::fmt
)

# ============================  添加项目库  =================================== #
# ============================  添加可执行文件  ================================ #