set(OMEGA_ENABLE_PYTHON true CACHE BOOL "Enables python support if available.")
if(OMEGA_ENABLE_PYTHON)
	if(WIN32)
        set(OMEGA_EXTERNAL_PYTHON_DIR "" CACHE String "Builds omegalib using an external python distribution")
        if(OMEGA_EXTERNAL_PYTHON_DIR)
            set(OMEGA_USE_PYTHON true)
            set(PYTHON_INCLUDE_DIRS ${OMEGA_EXTERNAL_PYTHON_DIR}/include)
            set(PYTHON_LIBRARIES ${OMEGA_EXTERNAL_PYTHON_DIR}/libs/python27.lib)
            include_directories(${PYTHON_INCLUDE_DIRS})
            configure_file(${OMEGA_EXTERNAL_PYTHON_DIR}/python27.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG} COPYONLY)
            configure_file(${OMEGA_EXTERNAL_PYTHON_DIR}/python27.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE} COPYONLY)
        else()
            # On windows use the included python distribution
            set(OMEGA_USE_PYTHON true)
            set(EXTLIB_NAME python)
            set(EXTLIB_TGZ ${CMAKE_BINARY_DIR}/${EXTLIB_NAME}.tar.gz)
            set(EXTLIB_DIR ${CMAKE_SOURCE_DIR}/modules/${EXTLIB_NAME})

            if(OMEGA_ARCH_32)
                set(EXTLIB_URL http://omegalib.s3.amazonaws.com/python/python-windows-x86.tar.gz)
            else()
                set(EXTLIB_URL http://omegalib.s3.amazonaws.com/python/python-windows-x64.tar.gz)
            endif()


            if(NOT EXISTS ${EXTLIB_DIR})
                message(STATUS "Downloading Python...")
                file(DOWNLOAD ${EXTLIB_URL} ${EXTLIB_TGZ} SHOW_PROGRESS)
                execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf
                    ${EXTLIB_TGZ} WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/modules)
            endif()
            
            set(PYTHON_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/modules/python/include)
            set(PYTHON_LIBRARIES ${CMAKE_SOURCE_DIR}/modules/python/libs/python27.lib)
            include_directories(${PYTHON_INCLUDE_DIRS})
            # copy the python dll to the output folders
            if(OMEGA_ARCH_32)
                configure_file(${CMAKE_SOURCE_DIR}/external/libs32/python27.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG} COPYONLY)
                configure_file(${CMAKE_SOURCE_DIR}/external/libs32/python27.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE} COPYONLY)
            else()
                configure_file(${CMAKE_SOURCE_DIR}/external/libs64/python27.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG} COPYONLY)
                configure_file(${CMAKE_SOURCE_DIR}/external/libs64/python27.dll ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE} COPYONLY)
            endif()
        endif()
    else()
		find_package(PythonLibs 2.7)
		if(PYTHONLIBS_FOUND)
			set(OMEGA_USE_PYTHON true)
			include_directories(${PYTHON_INCLUDE_DIRS})
		else()
			message("Python libraries not found on this system. Omegalib Python support will be disabled")
		endif()
	endif()
else()
	set(OMEGA_USE_PYTHON false)
endif()

