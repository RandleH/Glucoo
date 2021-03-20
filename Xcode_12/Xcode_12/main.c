//
//  main.c
//  Xcode_12
//
//  Created by Randle.Helmslay on 2021/3/5.
//

#include <stdio.h>
#include "RH_common.h"
#include "RH_data.h"
#include "RH_gui.h"
#include "RH_gui_api.h"
#include "RH_font.h"

#include "RH_time.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    Simul_API_Init();

    GUI_RefreashScreen();


    __GUI_Window_t cfg2;
    cfg2.area.xs     = 200;
    cfg2.area.ys     = 140;
    cfg2.area.height = 130;
    cfg2.area.width  = 300;
    cfg2.type        = kGUI_WindowType_macOS;
    cfg2.size        = 40;
    cfg2.appearance  = kGUI_Appearance_Light;
    cfg2.title       = "a";
    cfg2.text        = "Most people effortlessly recognize those digits as 504192. That ease is deceptive. In each hemisphere of our brain, humans have a primary visual cortex, also known as V1, containing 140 million neurons, with tens of billions of connections between them. And yet human vision involves not just V1, but an entire series of visual cortices - V2, V3, V4, and V5 - doing progressively more complex image processing. We carry in our heads a supercomputer, tuned by evolution over hundreds of millions of years, and superbly adapted to understand the visual world. Recognizing handwritten digits isn't easy. Rather, we humans are stupendously, astoundingly good at making sense of what our eyes show us. But nearly all that work is done unconsciously. And so we don't usually appreciate how tough a problem our visual systems solve.";

    ID_t ID_Window2 = GUI_create_window(&cfg2);

    GUI_insert_window( ID_Window2 );
    GUI_RefreashScreen();

    GUI_delete_window( ID_Window2 );

//    const size_t width = 300;
//    const char* text = "Glucoo people effortlessly recognize those digits as 504192. That ease is deceptive. In each hemisphere of our brain, humans have a primary visual cortex, also known as V1, containing 140 million neurons, with tens of billions of connections between them. And yet human vision involves not just V1, but an entire series of visual cortices - V2, V3, V4, and V5 - doing progressively more complex image processing. We carry in our heads a supercomputer, tuned by evolution over hundreds of millions of years, and superbly adapted to understand the visual world. Recognizing handwritten digits isn't easy. Rather, we humans are stupendously, astoundingly good at making sense of what our eyes show us. But nearly all that work is done unconsciously. And so we don't usually appreciate how tough a problem our visual systems solve.";
//
//    char* pSentence = (char*)alloca(strlen(text));
//    strcpy(pSentence, text);
//
//    
//    // When <str> is equal to NULL, it means this is a node for blank space.
//    struct WordInfo_t{
//        char*   str;
//        size_t  pixsW;
//    };
//    typedef struct WordInfo_t WordInfo_t;
//
//    WordInfo_t WordInfo = {.str = strtok(pSentence," "), .pixsW = 0};
//    for(int i=0; i<strlen(WordInfo.str); i++){
//        size_t w = 0;
//        __Font_getCharSize(&w, NULL, WordInfo.str[i]);
//        WordInfo.pixsW += w;
//    }
//
//    __LinkLoop_t* pTextHead = __LINK_Loop_createHead( &WordInfo );
//
//    char* p = NULL;
//    while( (p = strtok(NULL," ")) != NULL ){
//        WordInfo_t* pWordInfo = alloca(sizeof(WordInfo_t));
//        pWordInfo->str   = p;
//        pWordInfo->pixsW = 0;
//        for(int i=0; i<strlen(WordInfo.str); i++){
//            size_t w = 0;
//            __Font_getCharSize(&w, NULL, pWordInfo->str[i]);
//            pWordInfo->pixsW += w;
//        }
//        __LINK_Loop_add( pTextHead, pWordInfo );
//    }
//
//    
//
//    //=======Test======//
//    const __LinkLoop_t* pIter  = pTextHead;
//    const __LinkLoop_t* pIter1 = pTextHead;
//    const __LinkLoop_t* pIter2 = pTextHead;
//    do{
//        printf("%s\t\tlen=%ld\n", ((WordInfo_t*)pIter->object)->str,((WordInfo_t*)pIter->object)->pixsW);
//        pIter = pIter->pNext;
//    }while( pIter != pTextHead );
//    
//    size_t cnt = 0;
//    do{
//        cnt += ((WordInfo_t*)(pIter1->object))->pixsW;
//        cnt +=
//        pIter1 = pIter1->pNext;
//    }while( pIter1 != pTextHead );
//    
//    
//    
    return 0;
}
