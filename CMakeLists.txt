####################################################################
#
# CMake Build Script for QtDeviser
#
# Frank T. Bergmann
#

cmake_minimum_required(VERSION 2.6)
project(QtDeviser)

cmake_policy(SET CMP0020 NEW)



set(SPATIAL_VERSION_MAJOR)
set(SPATIAL_VERSION_MINOR)
set(SPATIAL_VERSION_PATCH)
set(SPATIAL_VERSION_RELEASE)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt")

    file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt" VersionString NEWLINE_CONSUME)
    string(STRIP "${VersionString}" VersionString)
    string(REPLACE "." ";" VersionString "${VersionString}" )
    string(REPLACE "-" ";" VersionString "${VersionString}" )
    list(LENGTH VersionString versionLength)
    list(GET VersionString 0 SPATIAL_VERSION_MAJOR )
    list(GET VersionString 1 SPATIAL_VERSION_MINOR )
    list(GET VersionString 2 SPATIAL_VERSION_PATCH )

    if(${versionLength} GREATER 3)
        list(GET VersionString 3 SPATIAL_VERSION_RELEASE )
    endif()

endif()

set(CPACK_PACKAGE_VERSION_MAJOR "${SPATIAL_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${SPATIAL_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${SPATIAL_VERSION_PATCH}")
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/license.txt")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/readme.md")
set(CPACK_SOURCE_PACKAGE_FILE_NAME
  "${CMAKE_PROJECT_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")
set(CPACK_SOURCE_IGNORE_FILES
  "aa;aa.zip;screenshots;.DS_STORE;testmodels/.DS_Store;/build/;/.bzr/;~$;${CPACK_SOURCE_IGNORE_FILES}")
set(CPACK_NSIS_CREATE_ICONS "CreateShortCut '\$SMPROGRAMS\\\\$STARTMENU_FOLDER\\\\SBML Spatial.lnk' '\$INSTDIR\\\\bin\\\\SpatialUI.exe'")
include(CPack)

###############################################################################
#
# Need some variables set up, such as the name for the libSBML
# library and the Path and file separator characters. The
# MISC_PREFIX variable will cause libsbml bindings, examples and
# documentation to be installed in PREFIX/${MISC_PREFIX}.
#

if(UNIX OR CYGWIN)
    set(PATH_SEP "/")
    set(FILE_SEP ":")
else()
    set(PATH_SEP "\\")
    set(FILE_SEP ";")
endif()

set(EXTRA_LIBS "" CACHE STRING "List of additional libraries to link against." )
set(EXTRA_FLAGS "" CACHE STRING "List of extra flags." )
set(EXTRA_INCLUDE "" CACHE STRING "List of include diretories." )

if (EXTRA_FLAGS)
foreach(${flag} ${EXTRA_FLAGS})
	add_definitions(-D${flag})
endforeach()
endif()


if (APPLE)
add_definitions(-DDARWIN)
endif()

if (UNIX)
add_definitions(-DLINUX)
endif()



if(WIN32 AND NOT CYGWIN)

 if(MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
        set(BUILD_DEFINITIONS "${BUILD_DEFINITIONS} -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS")
        option(WITH_STATIC_RUNTIME "Compile using the static MSVC Runtime." OFF)
        if(WITH_STATIC_RUNTIME)
            foreach(flag_var
                CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
                CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
                CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)

                if(${flag_var} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
                endif(${flag_var} MATCHES "/MD")
            endforeach(flag_var)
        add_definitions( -D_MT)
        endif(WITH_STATIC_RUNTIME)
  endif()
endif()



if (PREFIX_PATH)
set (CMAKE_PREFIX_PATH "${PREFIX_PATH}") 
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/ChooseQtVersion.cmake)
QT_FIND_MODULES(Core Gui OpenGL Xml) 

file(GLOB CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/model/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp )
file(GLOB   H_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.h ${CMAKE_CURRENT_SOURCE_DIR}/model/*.h)
file(GLOB  UI_FILES ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui )
file(GLOB RCC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc )

if (Qt5_FOUND)
qt5_add_resources(RESOURCES_RCC ${RCC_FILES})
qt5_wrap_cpp(HEADERS_MOC ${H_FILES})
qt5_wrap_ui(FORMS_HEADERS ${UI_FILES})
elseif(Qt4_FOUND OR QT4_FOUND)
qt4_add_resources(RESOURCES_RCC ${RCC_FILES})
qt4_wrap_cpp(HEADERS_MOC ${H_FILES})
qt4_wrap_ui(FORMS_HEADERS ${UI_FILES})
endif()

include_directories(${CMAKE_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
set(EXECUTABLE_FLAGS)

if(WIN32 AND NOT CYGWIN)
  option(ENABLE_UI_CONSOLE "Show the console window (to see debug messages) when running QtDeviser" OFF)
  if (NOT ENABLE_UI_CONSOLE)
    set(EXECUTABLE_FLAGS WIN32)
    if(MSVC)
      set(CPP_FILES ${CPP_FILES} ${CMAKE_SOURCE_DIR}/deviser.rc)
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup ")
    endif(MSVC)
  endif(NOT ENABLE_UI_CONSOLE)
endif(WIN32 AND NOT CYGWIN)

add_executable(QtDeviser ${EXECUTABLE_FLAGS} ${CPP_FILES}
  ${H_FILES}
  ${HEADERS_MOC}
  ${FORMS_HEADERS}
  ${RESOURCES_RCC}
  ${SPATIAL_CPP_FILES}
)

QT_BIND_TO_TARGET(QtDeviser)

SET(DIRS)

if (EXTRA_LIBS)
foreach(${lib} ${EXTRA_LIBS})
  if (EXISTS ${lib})
	get_filename_component(dir ${lib} PATH)	
	SET(DIRS  ${DIRS} ${dir})
  endif()
endforeach()
endif()
if (NOT DIRS)
   if (EXISTS "${EXTRA_LIBS}")
	get_filename_component(DIRS ${EXTRA_LIBS} PATH)
   endif()
endif()

if (QT_BINARY_DIR)
  SET(DIRS ${QT_BINARY_DIR} ${DIRS})
endif()

if(NOT APPLE)

  SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/QtDeviser${CMAKE_EXECUTABLE_SUFFIX}" CACHE INTERNAL "")
  if (EXTRA_LIBS)
  install(TARGETS EXTRA_LIBS DESTINATION bin)
  endif()
  # ensure that next to the binaries also dependencies are copied
  install(CODE "
      include(BundleUtilities)
      fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")
      " COMPONENT Runtime)

endif()



message(STATUS         
"
 Project QtDeviser ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}
 ==========================
 
 Install Prefix : ${CMAKE_INSTALL_PREFIX}
                
 C   FLAGS      : ${CMAKE_C_FLAGS}
 CXX FLAGS      : ${CMAKE_CXX_FLAGS}
 Extra Libs     : ${EXTRA_LIBS} 
 
"
)


