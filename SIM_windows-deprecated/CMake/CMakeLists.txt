cmake_minimum_required(VERSION 2.6)
PROJECT(Glucoo)

aux_source_directory( ../../core                 dir_RH            )
aux_source_directory( ../../core/Glucoo/         dir_Glucoo        )
aux_source_directory( ../../core/Glucoo/image    dir_Glucoo_image  )
aux_source_directory( ../../core/Glucoo/draw     dir_Glucoo_draw   )
aux_source_directory( ../../core/Glucoo/font     dir_Glucoo_font   )
aux_source_directory( ../../core/Glucoo/object   dir_Glucoo_object )
aux_source_directory( ../../core/Glucoo/window   dir_Glucoo_window )
aux_source_directory( ../../core/Glucoo/menu     dir_Glucoo_menu   )
aux_source_directory( ../../core/BlackHouse      dir_BlackHouse    )
aux_source_directory( ../../core/STB             dir_STB           )
aux_source_directory( ../self                    dir_self          )

include_directories( ../../core               )
include_directories( ../self                  )
include_directories( ../../core/Glucoo        )
include_directories( ../../core/Glucoo/draw   )
include_directories( ../../core/Glucoo/image  ) 
include_directories( ../../core/Glucoo/object )
include_directories( ../../core/Glucoo/window )
include_directories( ../../core/Glucoo/menu   )
include_directories( ../../core/Glucoo/font   )
include_directories( ../../core/BlackHouse    )
include_directories( ../../core/STB           )

add_executable( Glucoo ${dir_RH};
                       ${dir_Glucoo};
                       ${dir_Glucoo_image};
                       ${dir_Glucoo_draw};
                       ${dir_Glucoo_font};
                       ${dir_Glucoo_object};
                       ${dir_Glucoo_window};
                       ${dir_Glucoo_menu};
                       ${dir_BlackHouse};
                       ${dir_STB};
                       ${dir_self};  )





