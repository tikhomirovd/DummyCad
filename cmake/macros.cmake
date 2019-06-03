# Created on: April 15, 2019
# Created by: Artem ZHIDKOV
# Summary: Helpful macro-commands

foreach(_mode ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER "${_mode}" _mode_uc)

  set(TEST_ENV_PATH_${_mode_uc} $ENV{PATH} CACHE INTERNAL "")
  set(TEST_ENV_LD_LIBRARY_PATH_${_mode_uc} $ENV{LD_LIBRARY_PATH} CACHE INTERNAL "")
endforeach()


# Initialize variables related to PATH and LD_LIBRARY_PATH
# Following variables will be initialized:
#   TEST_ENV_PATH_DEBUG
#   TEST_ENV_PATH_RELEASE
#   TEST_ENV_PATH_RELWITHDEBUG
#   TEST_ENV_LD_LIBRARY_PATH_DEBUG
#   TEST_ENV_LD_LIBRARY_PATH_RELEASE
#   TEST_ENV_LD_LIBRARY_PATH_RELWITHDEBUG
function(add_test_environment CONFIG_MODE TEST_PATH)
  if(WIN32)
    set(_separator "\\;")
  else()
    set(_separator ":")
  endif()

  string(TOUPPER "${CONFIG_MODE}" _mode_uc)

  set(TEST_ENV_PATH_${_mode_uc} "${TEST_PATH}${_separator}${TEST_ENV_PATH_${_mode_uc}}" CACHE INTERNAL "")
  set(TEST_ENV_LD_LIBRARY_PATH_${_mode_uc} "${TEST_PATH}${_separator}${TEST_ENV_LD_LIBRARY_PATH_${_mode_uc}}" CACHE INTERNAL "")
endfunction(add_test_environment)



# Set environment variable for the test
function(set_test_environment TEST_NAME)

  set(_env_path "")
  set(_env_ld_library_path "")
  foreach(_mode ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER "${_mode}" _mode_uc)
    set(_env_path "${_env_path}$<$<CONFIG:${_mode}>:${TEST_ENV_PATH_${_mode_uc}}>")
    set(_env_ld_library_path "${_env_ld_library_path}$<$<CONFIG:${_mode}>:${TEST_ENV_PATH_${_mode_uc}}>")
  endforeach()

  set(gtest_case_name_regex ".*\\( *([A-Za-z_0-9]+) *, *([A-Za-z_0-9]+) *\\).*")
  set(gtest_test_type_regex "(TYPED_TEST|TEST_?[FP]?)")

  get_property(source_files TARGET ${TEST_NAME} PROPERTY SOURCES)
  foreach(source ${source_files})
    file(READ "${source}" contents)
    string(REGEX MATCHALL "${gtest_test_type_regex} *\\(([A-Za-z_0-9 ,]+)\\)" found_tests ${contents})
    foreach(hit ${found_tests})
      string(REGEX MATCH "${gtest_test_type_regex}" test_type ${hit})

      # Parameterized tests have a different signature for the filter
      if("x${test_type}" STREQUAL "xTEST_P")
        string(REGEX REPLACE ${gtest_case_name_regex}  "*/\\1.\\2/*" test_name ${hit})
      elseif("x${test_type}" STREQUAL "xTEST_F" OR "x${test_type}" STREQUAL "xTEST")
        string(REGEX REPLACE ${gtest_case_name_regex} "\\1.\\2" test_name ${hit})
      elseif("x${test_type}" STREQUAL "xTYPED_TEST")
        string(REGEX REPLACE ${gtest_case_name_regex} "\\1/*.\\2" test_name ${hit})
      else()
        message(WARNING "Could not parse GTest ${hit} for adding it to set environment.")
        continue()
      endif()

      set_property(TEST ${test_name} PROPERTY ENVIRONMENT "PATH=${_env_path}")
      set_property(TEST ${test_name} APPEND PROPERTY ENVIRONMENT "LD_LIBRARY_PATH=${_env_ld_library_path}")
    endforeach()
  endforeach()

  # Replace *.user file for debugging unit tests in Visual Studio
  if(".${CMAKE_CXX_COMPILER_ID}." STREQUAL ".MSVC.")
    set(_user_file_template "unittest.vcxproj.user.in")
    foreach(_path ${CMAKE_MODULE_PATH})
      if(EXISTS "${_path}/${_user_file_template}")
        set(_user_file_template "${_path}/${_user_file_template}")
        break()
      endif()
    endforeach()

    configure_file("${_user_file_template}"
                   "${CMAKE_CURRENT_BINARY_DIR}/${TEST_NAME}.vcxproj.user")
  endif()

endfunction(set_test_environment)

# Replace absolute paths to OCCT dependencies (FreeType, FreeImage, Tcl/Tk
function(fix_occt_3rdparties OCCT_3RDPARTIES)

  foreach(_target ${OpenCASCADE_LIBRARIES})
    get_target_property(_linked ${_target} INTERFACE_LINK_LIBRARIES)
    set(_new_dep "")
    foreach(_dep ${_linked})
      foreach(_thirdparty ${OCCT_3RDPARTIES})
        replace_occt_3rdparty_path(_dep "${_dep}" "${_thirdparty}")
      endforeach()
      set(_new_dep ${_new_dep} ${_dep})
    endforeach()
    set_target_properties(${_target} PROPERTIES INTERFACE_LINK_LIBRARIES "${_new_dep}")
  endforeach()

endfunction(fix_occt_3rdparties)

function(replace_occt_3rdparty_path DEST_PATH SOURCE_PATH 3RDPARTY_NAME)

  set(_dest "${SOURCE_PATH}")

  if(IS_ABSOLUTE "${SOURCE_PATH}")
    string(TOLOWER "${SOURCE_PATH}" lc_SOURCE_PATH)
    string(TOLOWER "${3RDPARTY_NAME}" lc_3RDPARTY_NAME)
    string(TOUPPER "${3RDPARTY_NAME}" uc_3RDPARTY_NAME)

    string(FIND "${lc_SOURCE_PATH}" "${lc_3RDPARTY_NAME}" _pos)
    if(${_pos} GREATER -1)
      get_filename_component(_path "${SOURCE_PATH}" DIRECTORY)
      get_filename_component(_path "${_path}" DIRECTORY)

      string(REPLACE "${_path}" "${3RDPARTY_${uc_3RDPARTY_NAME}_DIR}" _dest "${SOURCE_PATH}")
    endif()
  endif()

  set(${DEST_PATH} "${_dest}" PARENT_SCOPE)
  
endfunction(replace_occt_3rdparty_path)
