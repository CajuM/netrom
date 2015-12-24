add_custom_target(copy_res_files ALL)

list(APPEND res_files
	fonts/
	fonts/unifont_csur-8.0.01.ttf
	levels/
	levels/intro
	levels/intro/intro.py
	levels/openworld
	levels/openworld/openworld.py
)

foreach(file_name IN LISTS res_files)
	set(src ${CMAKE_CURRENT_SOURCE_DIR}/${file_name})
	set(dst ${CMAKE_BINARY_DIR}/dist/share/netrom/${file_name})
	if(IS_DIRECTORY ${src})	
		add_custom_command(TARGET copy_res_files
			COMMAND ${CMAKE_COMMAND} -E make_directory ${dst}
		)
	else()
		add_custom_command(TARGET copy_res_files
			COMMAND ${CMAKE_COMMAND} -E copy ${src} ${dst}
		)
	endif()
endforeach(file_name)