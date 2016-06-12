add_custom_target(copy_res_files ALL)

list(APPEND res_files
	fonts/
	fonts/Monospace.ttf
	levels/
	levels/intro
	levels/intro/intro.lua
	levels/openworld
	levels/openworld/
	levels/gamelib/
	levels/gamelib/bindings.lua
	levels/gamelib/GameObject.lua
	levels/gamelib/GlyphMat.lua
	levels/gamelib/Level.lua
	levels/gamelib/MsgBox.lua
	levels/gamelib/netrom.lua
	levels/gamelib/Netrom.lua
	levels/gamelib/Scene.lua
	levels/gamelib/UIElement.lua
	levels/gamelib/util.lua
)

foreach(file_name IN LISTS res_files)
	set(src ${CMAKE_CURRENT_SOURCE_DIR}/${file_name})
	set(dst ${CMAKE_BINARY_DIR}/share/netrom/${file_name})
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