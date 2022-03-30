project(breakpad)
cmake_minimum_required(VERSION 3.19)
set(BREAKPAD_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src)

if (WIN32)

elseif (APPLE)
    set(BREADPAD_SRC
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/mac/crash_generation/crash_generation_client.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/mac/handler/breakpad_nlist_64.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/mac/handler/dynamic_images.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/mac/handler/exception_handler.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/mac/handler/minidump_generator.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/mac/MachIPC.mm
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/mac/bootstrap_compat.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/mac/file_id.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/mac/macho_id.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/mac/macho_utilities.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/mac/macho_walker.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/mac/string_utilities.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/minidump_file_writer.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/convert_UTF.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/md5.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/string_conversion.cc
            )
    find_library(FOUNDATION_LIB Foundation REQUIRED)
    set(DUMPSYMS_LIBS ${FOUNDATION_LIB})
    message(${DUMPSYMS_LIBS})
elseif (UNIX)
    message(UNIX)
    set(BREADPAD_SRC
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/linux/crash_generation/crash_generation_client.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/linux/dump_writer_common/thread_info.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/linux/dump_writer_common/ucontext_reader.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/linux/handler/exception_handler.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/linux/handler/minidump_descriptor.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/linux/log/log.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/linux/microdump_writer/microdump_writer.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/linux/minidump_writer/linux_core_dumper.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/linux/minidump_writer/linux_dumper.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/linux/minidump_writer/linux_ptrace_dumper.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/client/linux/minidump_writer/minidump_writer.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/linux/breakpad_getcontext.S
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/linux/elfutils.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/linux/file_id.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/linux/guid_creator.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/linux/linux_libc_support.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/linux/memory_mapped_file.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/linux/safe_readlink.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/linux/elf_core_dump.cc
            ${CMAKE_CURRENT_SOURCE_DIR}/breakpad/src/common/linux/breakpad_getcontext.S
            )
endif ()


#cmake_minimum_required(VERSION 3.19)
#set(CMAKE_TOOLCHAIN_FILE /usr/local/Cellar/vcpkg/2022.02.01/vcpkg/scripts/buildsystems/vcpkg.cmake
#        CACHE STRING "Vcpkg toolchain file")
#project(vcp_breakpad)
set(CMAKE_CXX_STANDARD 11)
include_directories(breakpad/src)
add_executable(breakpad test/main.cpp ${BREADPAD_SRC})
target_link_libraries(breakpad pthread)
