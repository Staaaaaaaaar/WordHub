cmake_minimum_required(VERSION 3.12)
project(vocabulary_learning)

# 强制指定架构为 x64
set(CMAKE_GENERATOR_PLATFORM "x64")

# 指定 Conda Python 路径
set(Python_ROOT_DIR "E:/Users/liu/miniconda3")
set(Python_EXECUTABLE "${Python_ROOT_DIR}/python.exe")

# 指定 pybind11 路径
set(pybind11_DIR "${Python_ROOT_DIR}/Lib/site-packages/pybind11/share/cmake/pybind11")

# 查找 Python 组件
find_package(Python REQUIRED COMPONENTS Interpreter Development)
find_package(pybind11 REQUIRED)

# 设置 Python 库文件
set(Python_LIBRARIES "${Python_ROOT_DIR}/libs/python312.lib")

# 添加所有源文件
file(GLOB SOURCES "src/*.cpp" "head/*.hpp")  # 或手动列出文件

# 生成模块
pybind11_add_module(vocabulary_learning ${SOURCES})

set_target_properties(vocabulary_learning PROPERTIES SUFFIX ".pyd")

# 设置输出目录（所有构建模式）
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/python)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/python)

# 设置输出目录
set_target_properties(vocabulary_learning PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/python
)