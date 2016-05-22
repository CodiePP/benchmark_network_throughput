cmake_minimum_required (VERSION 2.8)

find_package(Java REQUIRED)
include(UseJava)

enable_testing()

project (EchoServer)

set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.8" "-target" "1.8")

add_jar(EchoServer EchoServer.java
    MANIFEST manifest)

get_target_property(_jarFile EchoServer JAR_FILE)
get_target_property(_classDir EchoServer CLASSDIR)

message(STATUS "Jar file ${_jarFile}")
message(STATUS "Class compiled to ${_classDir}")

#add_test(NAME TestHelloWorld COMMAND ${Java_JAVA_EXECUTABLE} -cp ${_jarFile}
#    HelloWorld)
