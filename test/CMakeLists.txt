foreach(_name
        differential
        representation)
    set(_target test_${_name})

    add_executable(${_target} "")
    target_sources(${_target} PRIVATE ${_name}.cpp test.cpp)
    target_link_libraries(${_target}
            PRIVATE
            astronomy_compile_options
            astronomy_include_directories
            astronomy_dependencies)
    add_test(test.astro.${_name} ${_target})

    unset(_name)
    unset(_target)
endforeach()

