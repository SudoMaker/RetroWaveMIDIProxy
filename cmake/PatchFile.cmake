# Credits: https://github.com/scivision/cmake-patch-file

# use GNU Patch from any platform

if(WIN32)
    # prioritize Git Patch on Windows as other Patches may be very old and incompatible.
    find_package(Git)
    if(Git_FOUND)
        get_filename_component(GIT_DIR ${GIT_EXECUTABLE} DIRECTORY)
        get_filename_component(GIT_DIR ${GIT_DIR} DIRECTORY)
    endif()
endif()

find_program(PATCH
        NAMES patch
        HINTS ${GIT_DIR}
        PATH_SUFFIXES usr/bin
        )

if(NOT PATCH)
    message(FATAL_ERROR "Unable to find GNU Patch")
endif()

function(patch_file in_file patch_file)
    message("-- Patching file ${in_file}")

    execute_process(COMMAND ${PATCH} ${in_file} --input=${patch_file} --ignore-whitespace --forward --reject-file=-
            TIMEOUT 15
            OUTPUT_VARIABLE PATCH_OUTPUT
            RESULT_VARIABLE PATCH_RC
            )

    if (PATCH_OUTPUT MATCHES "Skipping patch")
        message("-- This file is already patched")
        set(PATCH_RC 0)
    endif()

    if(NOT PATCH_RC EQUAL 0)
        message(FATAL_ERROR "Failed to apply patch ${patch_file} to ${in_file} with ${PATCH}")
    endif()
endfunction()