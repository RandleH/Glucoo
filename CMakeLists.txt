cmake_minimum_required(VERSION 2.6)
PROJECT(Glucoo)

aux_source_directory( ./core/BlackHouse     dir_blk        )
aux_source_directory( ./core/Glucoo         dir_glu        )
aux_source_directory( ./core/Glucoo/draw    dir_glu_draw   )
aux_source_directory( ./core/Glucoo/image   dir_glu_image  )
aux_source_directory( ./core/Glucoo/object  dir_glu_object )
aux_source_directory( ./core/Glucoo/menu    dir_glu_menu   )
aux_source_directory( ./core/Glucoo/font    dir_glu_font   )
aux_source_directory( ./core/Glucoo/window  dir_glu_window )
aux_source_directory( ./core/Glucoo/utility dir_glu_utility)

include_directories( ./                    )
include_directories( ./core/BlackHouse     )
include_directories( ./core/STB            )
include_directories( ./core/Glucoo         )
include_directories( ./core/Glucoo/draw    )
include_directories( ./core/Glucoo/image   )
include_directories( ./core/Glucoo/object  )
include_directories( ./core/Glucoo/menu    )
include_directories( ./core/Glucoo/font    )
include_directories( ./core/Glucoo/window  )
include_directories( ./core/Glucoo/utility )

link_libraries( "-lm" )

add_executable( glucoo          ./main.c;
                                ./RH_common.c;        
                                ${dir_blk};
                                ${dir_glu};
                                ${dir_glu_draw};
                                ${dir_glu_image};
                                ${dir_glu_object};
                                ${dir_glu_menu};
                                ${dir_glu_font};
                                ${dir_glu_window};
                                ${dir_glu_utility}; )


