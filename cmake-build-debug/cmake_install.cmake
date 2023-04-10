<<<<<<< HEAD
# Install script for directory: C:/DA/project/ProjectDA1
=======
# Install script for directory: C:/Users/Bernardo/OneDrive/Ensino superior/2ano_2semestre/DA/ProjectDA1
>>>>>>> e7b528b703242b23fd4fa9d129d3cf8996ccf539

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Projeto1")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
<<<<<<< HEAD
  set(CMAKE_OBJDUMP "C:/Program Files/JetBrains/CLion 2022.2.3/bin/mingw/bin/objdump.exe")
=======
  set(CMAKE_OBJDUMP "C:/Users/Bernardo/AppData/Local/JetBrains/Toolbox/apps/CLion/ch-0/231.8109.222/bin/mingw/bin/objdump.exe")
>>>>>>> e7b528b703242b23fd4fa9d129d3cf8996ccf539
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
<<<<<<< HEAD
file(WRITE "C:/DA/project/ProjectDA1/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
=======
file(WRITE "C:/Users/Bernardo/OneDrive/Ensino superior/2ano_2semestre/DA/ProjectDA1/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
>>>>>>> e7b528b703242b23fd4fa9d129d3cf8996ccf539
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
