# CMake generated Testfile for 
# Source directory: /mnt/c/users/tvkain/desktop/Project-1.2/libs
# Build directory: /mnt/c/users/tvkain/desktop/Project-1.2/build/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ArrayListTest "/mnt/c/users/tvkain/desktop/Project-1.2/build/test/test/array_list_test")
set_tests_properties(ArrayListTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/users/tvkain/desktop/Project-1.2/libs/CMakeLists.txt;11;add_test;/mnt/c/users/tvkain/desktop/Project-1.2/libs/CMakeLists.txt;0;")
add_test(InsertionSortTest "/mnt/c/users/tvkain/desktop/Project-1.2/build/test/test/insertion_sort_test")
set_tests_properties(InsertionSortTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/users/tvkain/desktop/Project-1.2/libs/CMakeLists.txt;12;add_test;/mnt/c/users/tvkain/desktop/Project-1.2/libs/CMakeLists.txt;0;")
add_test(MergeSortTest "/mnt/c/users/tvkain/desktop/Project-1.2/build/test/test/merge_sort_test")
set_tests_properties(MergeSortTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/users/tvkain/desktop/Project-1.2/libs/CMakeLists.txt;13;add_test;/mnt/c/users/tvkain/desktop/Project-1.2/libs/CMakeLists.txt;0;")
subdirs("algorithms")
subdirs("data_structures")
subdirs("test")
