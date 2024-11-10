cmake_minimum_required(VERSION 3.10)
project(RestfulApi)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED COMPONENTS system filesystem thread system)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(RestfulApi main.cpp generated/index_html.h generated/script_js.h generated/style_css.h generated/jquery.h generated/favicon.h)
target_link_libraries(RestfulApi ${Boost_LIBRARIES})

add_executable(embedfile tools/embedfile.c)

add_custom_command(
  OUTPUT ${PROJECT_SOURCE_DIR}/generated/index_html.h
  COMMAND embedfile ${PROJECT_SOURCE_DIR}/generated/index_html ${PROJECT_SOURCE_DIR}/static/index.html indexHtml
  DEPENDS ${PROJECT_SOURCE_DIR}/static/index.html)

add_custom_command(
  OUTPUT ${PROJECT_SOURCE_DIR}/generated/script_js.h
  COMMAND embedfile ${PROJECT_SOURCE_DIR}/generated/script_js ${PROJECT_SOURCE_DIR}/static/script.js scriptJs
  DEPENDS ${PROJECT_SOURCE_DIR}/static/script.js)

add_custom_command(
  OUTPUT ${PROJECT_SOURCE_DIR}/generated/style_css.h
  COMMAND embedfile ${PROJECT_SOURCE_DIR}/generated/style_css ${PROJECT_SOURCE_DIR}/static/style.css styleCss
  DEPENDS ${PROJECT_SOURCE_DIR}/static/style.css)

add_custom_command(
  OUTPUT ${PROJECT_SOURCE_DIR}/generated/jquery.h
  COMMAND embedfile ${PROJECT_SOURCE_DIR}/generated/jquery ${PROJECT_SOURCE_DIR}/static/jquery-3.7.1.slim.min.js jqueryJs
  DEPENDS ${PROJECT_SOURCE_DIR}/static/jquery-3.7.1.slim.min.js)

add_custom_command(
  OUTPUT ${PROJECT_SOURCE_DIR}/generated/favicon.h
  COMMAND embedfile ${PROJECT_SOURCE_DIR}/generated/favicon ${PROJECT_SOURCE_DIR}/static/favicon.ico favicon
  DEPENDS ${PROJECT_SOURCE_DIR}/static/favicon.ico)