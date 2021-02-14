#include "RH_Utility.h"
/*=================================================================================================
 > This part of code will never be compiled.
===================================================================================================*/
#if (1==0)
// Dummy Segment for Gussian Kernel

    int      kernel[1+2+3+4+5] = {0};
    uint16_t gus_kernel[9][9];

    int sigma = 0;

    double temp = 12.8;

    kernel[0]  = (uint16_t)(100 / (M_PI * temp));                       //[0][0]

    kernel[1]  = (uint16_t)(100 / (M_PI * temp) * exp(-1  / (temp)));   //[1][0]
    kernel[2]  = (uint16_t)(100 / (M_PI * temp) * exp(-2  / (temp)));   //[1][1]

    kernel[3]  = (uint16_t)(100 / (M_PI * temp) * exp(-4  / (temp)));   //[2][0]
    kernel[4]  = (uint16_t)(100 / (M_PI * temp) * exp(-5  / (temp)));   //[2][1]
    kernel[5]  = (uint16_t)(100 / (M_PI * temp) * exp(-8  / (temp)));   //[2][2]

    kernel[6]  = (uint16_t)(100 / (M_PI * temp) * exp(-9  / (temp)));   //[3][0]
    kernel[7]  = (uint16_t)(100 / (M_PI * temp) * exp(-10 / (temp)));   //[3][1]
    kernel[8]  = (uint16_t)(100 / (M_PI * temp) * exp(-13 / (temp)));   //[3][2]
    kernel[9]  = (uint16_t)(100 / (M_PI * temp) * exp(-18 / (temp)));   //[3][3]

    kernel[10] = (uint16_t)(100 / (M_PI * temp) * exp(-16 / (temp)));   //[4][0]
    kernel[11] = (uint16_t)(100 / (M_PI * temp) * exp(-17 / (temp)));   //[4][1]
    kernel[12] = (uint16_t)(100 / (M_PI * temp) * exp(-20 / (temp)));   //[4][2]
    kernel[13] = (uint16_t)(100 / (M_PI * temp) * exp(-25 / (temp)));   //[4][3]
    kernel[14] = (uint16_t)(100 / (M_PI * temp) * exp(-32 / (temp)));   //[4][4]

    sigma += kernel[0];        // 1
    sigma += (kernel[1]) << 2; // 4
    sigma += (kernel[2]) << 2; // 4

    sigma += (kernel[3]) << 2; // 4
    sigma += (kernel[4]) << 3; // 8
    sigma += (kernel[5]) << 2; // 4

    sigma += (kernel[6]) << 2; // 4
    sigma += (kernel[7]) << 3; // 8
    sigma += (kernel[8]) << 3; // 8
    sigma += (kernel[9]) << 2; // 4

    sigma += (kernel[10]) << 2; // 4
    sigma += (kernel[11]) << 3; // 8
    sigma += (kernel[12]) << 3; // 8
    sigma += (kernel[13]) << 3; // 8
    sigma += (kernel[14]) << 2; // 4

    int center   = ((9-1)>>1);

    for(int i = 0;i <= center;i++){
        for(int j = 0;j <= i;j++){
            gus_kernel[center + i][center + j] = kernel[i+j];
            gus_kernel[center + i][center - j] = kernel[i+j];
            gus_kernel[center - i][center + j] = kernel[i+j];
            gus_kernel[center - i][center - j] = kernel[i+j];
            gus_kernel[center + j][center + i] = kernel[i+j];
            gus_kernel[center + j][center - i] = kernel[i+j];
            gus_kernel[center - j][center + i] = kernel[i+j];
            gus_kernel[center - j][center - i] = kernel[i+j];
        }
    }
    sigma = 0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            printf("[%3d]",gus_kernel[i][j]);
            sigma += gus_kernel[i][j];
        }
        printf("\n");
    }

    printf("sigma = %d\n",sigma);


// Dummy Segment for Digital Fourier Transform
void __DFT_Float(const float_t* src,float_t* dst,size_t dftLen){
    __ComplexFLOAT_t* pTmp = (__ComplexFLOAT_t*)__malloc(dftLen*sizeof(__ComplexFLOAT_t));
    memset(pTmp,0,dftLen*sizeof(__ComplexFLOAT_t));
    for(size_t k=0;k<dftLen;k++){
        for(size_t n=0;n<dftLen;n++){
            pTmp[k].real += src[n]*cos(2*M_PI*k*n/dftLen);
            pTmp[k].imag += src[n]*sin(2*M_PI*k*n/dftLen);
        }
        dst[k] = sqrt(pTmp[k].real*pTmp[k].real+pTmp[k].imag*pTmp[k].imag);
        printf("%f + \tj*%f\n",pTmp[k].real,pTmp[k].imag);
    }
    __free(pTmp);
}


for(size_t k=0;k<((dftLen+2)>>1);k++){
    for(size_t n=0;n<dftLen;n++){
        pClx[k].real += src[n]*cos(2*M_PI*k*n/dftLen);
        pClx[k].imag += src[n]*sin(2*M_PI*k*n/dftLen);
    }
    if(dst_m != NULL)
        dst_m[k] = sqrt(pClx[k].real*pClx[k].real+pClx[k].imag*pClx[k].imag);
    
    // Since the result of DFT is symmetrical, just copy the previous value.
    if(k!=0){
        pClx[dftLen-k].real =   pClx[k].real;
        pClx[dftLen-k].imag = - pClx[k].imag;
        if(dst_m != NULL)
            dst_m [dftLen-k]    =   dst_m[k];
    }
    
}


void __cDFT_Float(const __ComplexFLOAT_t* src,float_t* dst_m,__ComplexFLOAT_t* dst_c,size_t dftLen){
    __ComplexFLOAT_t* pClx = dst_c;
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    if( pClx == NULL ){
        pClx = (__ComplexFLOAT_t*)__malloc(dftLen*sizeof(__ComplexFLOAT_t));
        if( pClx == NULL ){
            return;
        }
    }
    
    memset(pClx,0,dftLen*sizeof(__ComplexFLOAT_t));
    for(size_t k=0;k<dftLen;k++){
        for(size_t n=0;n<dftLen;n++){
            double temp = 2*M_PI*k*n/((double)(dftLen));
            pClx[k].real += src[n].real*cos(temp) + src[n].imag*sin(temp);
            pClx[k].imag += src[n].imag*cos(temp) - src[n].real*sin(temp);
        }
        if(dst_m != NULL)
            dst_m[k] = sqrt(pClx[k].real*pClx[k].real+pClx[k].imag*pClx[k].imag);
    }
    
//    for(size_t k=0;k<dftLen;k++)
//        printf("| %.4f + j* %.4f | = \t%f\n",pClx[k].real,pClx[k].imag,dst_m[k]);
    if(dst_c == NULL)
        __free(pClx);
}


void __cIDFT_Float(const __ComplexFLOAT_t* src,float_t* dst_m,__ComplexFLOAT_t* dst_c,size_t dftLen){
    __ComplexFLOAT_t* pClx = dst_c;
    if( (dst_m == NULL&& dst_c == NULL) || src == NULL )
        return;
    if( pClx == NULL ){
        pClx = (__ComplexFLOAT_t*)__malloc(dftLen*sizeof(__ComplexFLOAT_t));
    }
    memset(pClx,0,dftLen*sizeof(__ComplexFLOAT_t));
    
    for(size_t k=0;k<dftLen;k++){
        for(size_t n=0;n<dftLen;n++){
            double temp = 2*M_PI*k*n/((double)(dftLen));
            pClx[k].real += src[n].real*cos(temp) - src[n].imag*sin(temp);
            pClx[k].imag += src[n].imag*cos(temp) + src[n].real*sin(temp);
        }
        pClx[k].real = pClx[k].real/(double)(dftLen);
        pClx[k].imag = pClx[k].imag/(double)(dftLen);
        if(dst_m != NULL)
            dst_m[k] = sqrt(pClx[k].real*pClx[k].real+pClx[k].imag*pClx[k].imag);
        
    }
    
//    for(size_t k=0;k<dftLen;k++)
//        printf("| %f + \tj*%f | = \t%f\n",pClx[k].real,pClx[k].imag,dst_m[k]);
    if(dst_c == NULL)
        __free(pClx);
}

void __cDFT_Float(const __ComplexFLOAT_t* src,float_t* dst_m,__ComplexFLOAT_t* dst_c,size_t dftLen){
    __ComplexFLOAT_t* pClx = dst_c;
    if( (dst_m == NULL && dst_c == NULL) || src == NULL)
        return;
    if( pClx == NULL ){
        pClx = (__ComplexFLOAT_t*)__malloc(dftLen*sizeof(__ComplexFLOAT_t));
        if( pClx == NULL ){
            return;
        }
    }
    
    memset(pClx,0,dftLen*sizeof(__ComplexFLOAT_t));
    for(size_t k=0;k<dftLen;k++){
        for(size_t n=0;n<dftLen;n++){
            double temp = 2*M_PI*k*n/((double)(dftLen));
            pClx[k].real += src[n].real*cos(temp) + src[n].imag*sin(temp);
            pClx[k].imag += src[n].imag*cos(temp) - src[n].real*sin(temp);
        }
        if(dst_m != NULL)
            dst_m[k] = sqrt(pClx[k].real*pClx[k].real+pClx[k].imag*pClx[k].imag);
    }
    
//    for(size_t k=0;k<dftLen;k++)
//        printf("| %.4f + j* %.4f | = \t%f\n",pClx[k].real,pClx[k].imag,dst_m[k]);
    if(dst_c == NULL)
        __free(pClx);
}




//Test for BIT_REVERSE!!!
const int BIT_SIZE = 32;  // 8 , 16 , 32
for(uint32_t x=0;x<(1<<BIT_SIZE);x++){
    uint32_t y = __swap_8BIT(x);
    for(int i=0;i<BIT_SIZE;i++){
        if( (((x>>i)&0x01) ^ ((y>>(BIT_SIZE-1-i))&0x01)) == 1 )
            printf("error\n");
    }
}


static void __insertSausageLine(int x1 ,int y1 ,int x2 ,int y2 ,size_t penSize ,Pixel_t penColor ,BufferInfo_t* pBufferInfo,func_ApplyPixelMethod  Call_insertPointFunc){

    int x_offset = 0;
    int y_offset = 0;
    int x11=0,y11=0,x22=0,y22=0,x33=0,y33=0,x44=0,y44=0;

    __insertLine(x1,y1,x2,y2,penColor,pBufferInfo,Call_insertPointFunc);
    if(penSize > 1){

        //                -----------------------------------
        //              /       penSize * penSize * K^2
        // x_offset =  /    -------------------------------
        //           \/               K^2 + 1
        
        //                -----------------------------------
        //              /         penSize * penSize
        // y_offset =  /    -------------------------------
        //           \/               K^2 + 1

        
        switch(__Dir_Line(x1,y1,x2,y2)){
            case  0:
                x11 = x1; y11 = (int)(y1-(penSize>>1)+(penSize%2==0));
                x22 = x1; y22 = (int)(y1+(penSize>>1));
                x33 = x2; y33 = (int)(y2-(penSize>>1)+(penSize%2==0));
                x44 = x2; y44 = (int)(y2+(penSize>>1));
                break;
            case  1:
                x_offset = (int)lround(sqrt( ((y1-y2)*(y1-y2)*penSize*penSize/((x1-x2)*(x1-x2))) / (1.0*(y1-y2)*(y1-y2)/((x1-x2)*(x1-x2))+1) ));
                y_offset = (int)lround(sqrt( penSize*penSize/((y1-y2)*(y1-y2)/(1.0*(x1-x2)*(x1-x2))+1) ));
        
                x11 = x1+(x_offset>>1)-(x_offset%2==0); y11 = y1-(y_offset>>1);
                x22 = x1-(x_offset>>1)                ; y22 = y1+(y_offset>>1)-(y_offset%2==0);
                x33 = x2-(x_offset>>1)                ; y33 = y2+(y_offset>>1)-(y_offset%2==0);
                x44 = x2+(x_offset>>1)-(x_offset%2==0); y44 = y2-(y_offset>>1);
                break;
            case -1:
                x_offset = (int)lround(sqrt( ((y1-y2)*(y1-y2)*penSize*penSize/((x1-x2)*(x1-x2))) / (1.0*(y1-y2)*(y1-y2)/((x1-x2)*(x1-x2))+1) ));
                y_offset = (int)lround(sqrt( penSize*penSize/((y1-y2)*(y1-y2)/(1.0*(x1-x2)*(x1-x2))+1) ));
        
                x11 = x1+(x_offset>>1)                ; y11 = y1+(y_offset>>1)-(y_offset%2==0);
                x22 = x1-(x_offset>>1)+(x_offset%2==0); y22 = y1-(y_offset>>1)                ;
                x33 = x2-(x_offset>>1)+(x_offset%2==0); y33 = y2-(y_offset>>1)                ;
                x44 = x2+(x_offset>>1)                ; y44 = y2+(y_offset>>1)-(y_offset%2==0);
                break;
            case 65535:
                x11 = (int)(x1-(penSize>>1)                ); y11 = y1;
                x22 = (int)(x1+(penSize>>1)-(penSize%2==0)); y22 = y1;
                x33 = (int)(x2-(penSize>>1)                ); y33 = y2;
                x44 = (int)(x2+(penSize>>1)-(penSize%2==0)); y44 = y2;
                break;
        }
        (*Call_insertPointFunc)(x11,y11,penColor,pBufferInfo );
        (*Call_insertPointFunc)(x22,y22,penColor,pBufferInfo );
        (*Call_insertPointFunc)(x33,y33,penColor,pBufferInfo );
        (*Call_insertPointFunc)(x44,y44,penColor,pBufferInfo );

        __insertFilledQuadrilateral(  x11,y11, \
                                      x22,y22, \
                                      x33,y33, \
                                      x44,y44, \
                                      penColor  , \
                                      pBufferInfo,Call_insertPointFunc  );
        // GUI_RefreashArea(0,0,GUI_X_WIDTH-1,GUI_Y_WIDTH-1);
    }

    size_t tmp = (penSize>>1)-(penSize%2==0);
    penSize = 1;
    __insertFilledCircle(x1,y1,(int)tmp, penColor, pBufferInfo,Call_insertPointFunc);
    
    __insertFilledCircle(x2,y2,(int)tmp, penColor, pBufferInfo,Call_insertPointFunc);
    
}

// Run Test 1:

int main(int argc, const char * argv[]) {
    // insert code here...

    Simul_API_Init();
    GUI_Init();

    GUI_ManualDisplayMode();

    GUI_SetPenColor(GUI_RED);
    GUI_FillCircle(GUI_X_WIDTH>>1, GUI_Y_WIDTH>>1, 50);
    GUI_RefreashScreen();

    GUI_SetPenColor(GUI_GREEN);
    GUI_FillRect(GUI_X_WIDTH/3, GUI_Y_WIDTH/6, GUI_X_WIDTH/2, GUI_Y_WIDTH/4);
    GUI_RefreashScreen();

    GUI_SetPenColor(GUI_YELLOW);
    GUI_SetPenSize(10);
    
    GUI_FillAll(GUI_DARKGRAY);

    int ox = 30,oy = 30;
    GUI_DrawLine(10+ox, 10+oy, 50+ox, 50+oy);
    GUI_DrawLine(50+ox, 10+oy, 10+ox, 50+oy);
    GUI_DrawLine(30+ox, 10+oy, 30+ox, 50+oy);
    GUI_DrawLine(10+ox, 30+oy, 50+ox, 30+oy);

    GUI_SetPenSize(3);GUI_SetPenColor(GUI_PINK);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(4);GUI_SetPenColor(GUI_SILVER);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(5);GUI_SetPenColor(GUI_LAVENDERBLUSH);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(6);GUI_SetPenColor(GUI_PALEVIOLATRED);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(7);GUI_SetPenColor(GUI_HOTPINK);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(8);GUI_SetPenColor(GUI_MEDIUMVIOLATRED);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(9);GUI_SetPenColor(GUI_ORCHID);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(10);GUI_SetPenColor(GUI_THISTLE);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(11);GUI_SetPenColor(GUI_PLUM);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(12);GUI_SetPenColor(GUI_OLIVE);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(13);GUI_SetPenColor(GUI_DARKVOILET);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(14);GUI_SetPenColor(GUI_PURPLE);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    GUI_SetPenSize(15);GUI_SetPenColor(GUI_PALETURQUOISE);
    GUI_DrawLine(rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH, rand()%GUI_X_WIDTH, rand()%GUI_Y_WIDTH);
    uint16_t blurSize = 60000 , brPersentage = 90;
    GUI_BlurRect(600,150,750,270,blurSize,brPersentage);
    blurSize = 60000 ; brPersentage = 60;
    GUI_BlurRect(213,121,451,324,blurSize,brPersentage);
    GUI_RefreashScreen();
 
    
    return 0;
}



    __AnyNode_t* pHead = __createHeadNode(); //pHead->ID = 0;
    __AnyNode_t* p1    = __createNode();     //p1->ID    = 1;
    __AnyNode_t* p2    = __createNode();     //p2->ID    = 2;
    __AnyNode_t* p3    = __createNode();     //p3->ID    = 3;
    __AnyNode_t* p4    = __createNode();
    __AnyNode_t* p5    = __createNode();
    __AnyNode_t* p6    = __createNode();
    __AnyNode_t* p7    = __createNode();
    
    __addNode(pHead, p1);
    __addNode(pHead, p2);
    __addNode(pHead, p3);
    __addNode(pHead, p4);
    __addNode(pHead, p5);
    __addNode(pHead, p6);

    __deleteNode(pHead, p4);
    __deleteNode(pHead, p2);
    __deleteNode(pHead, p6);
    
    __addNode(pHead, p3);
    __addNode(pHead, p3);
    __addNode(pHead, p7);

    __AnyNode_t* pTmp = pHead;
    
    __deleteAllNodes(pHead);
    
    // Search the entire chain.
    if(pHead != NULL){
        do{
            printf("ID = %d\n",pTmp->ID);
            pTmp = (__AnyNode_t*)pTmp->pNext;
        }while(pTmp != pHead);
    }




    GUI_FillRect( 0         , 0, width * 1  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_PINK             );
    GUI_FillRect( width * 1 , 0, width * 2  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_CRIMSON          );
    GUI_FillRect( width * 2 , 0, width * 3  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LAVENDERBLUSH    );
    GUI_FillRect( width * 3 , 0, width * 4  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_PALEVIOLATRED    );
    GUI_FillRect( width * 4 , 0, width * 5  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_HOTPINK          );
    GUI_FillRect( width * 5 , 0, width * 6  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MEDIUMVIOLATRED  );
    GUI_FillRect( width * 6 , 0, width * 7  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_ORCHID           );
    GUI_FillRect( width * 7 , 0, width * 8  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_THISTLE          );
    GUI_FillRect( width * 8 , 0, width * 9  - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_PLUM             );
    GUI_FillRect( width * 9 , 0, width * 10 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_VOILET           );
    GUI_FillRect( width * 10, 0, width * 11 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DARKVOILET       );
    GUI_FillRect( width * 11, 0, width * 12 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_PURPLE           );
    GUI_FillRect( width * 12, 0, width * 13 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MEDIUMORCHID     );
    GUI_FillRect( width * 13, 0, width * 14 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DARKVIOLET       );
    GUI_FillRect( width * 14, 0, width * 15 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_INDIGO           );
    GUI_FillRect( width * 15, 0, width * 16 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_BLUEVIOLET       );
    GUI_FillRect( width * 16, 0, width * 17 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MEDIUMPURPLE     );
    GUI_FillRect( width * 17, 0, width * 18 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MEDIUMSLATEBLUE  );
    GUI_FillRect( width * 18, 0, width * 19 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_SLATEBLUE        );
    GUI_FillRect( width * 19, 0, width * 20 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DARKSLATEBLUE    );
    GUI_FillRect( width * 20, 0, width * 21 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LAVENDER         );
    GUI_FillRect( width * 21, 0, width * 22 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_GHOSTWHITE       );
    GUI_FillRect( width * 22 ,0, width * 23 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MEDIUMBLUE       );
    GUI_FillRect( width * 23, 0, width * 24 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_MIDNIGHTBLUE     );
    GUI_FillRect( width * 24, 0, width * 25 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DARKBLUE         );
    GUI_FillRect( width * 25, 0, width * 26 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_NAVY             );
    GUI_FillRect( width * 26, 0, width * 27 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_ROYALBLUE        );
    GUI_FillRect( width * 27, 0, width * 28 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_CORNFLOWERBLUE   );
    GUI_FillRect( width * 28, 0, width * 29 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LIGHTSTEELBLUE   );
    GUI_FillRect( width * 29, 0, width * 30 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LIGHTSLATEGRAY   );
    GUI_FillRect( width * 30, 0, width * 31 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_SLATEGRAY        );
    GUI_FillRect( width * 31, 0, width * 32 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DODGERBLUE       );
    GUI_FillRect( width * 32, 0, width * 33 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_ALICEBLUE        );
    GUI_FillRect( width * 33, 0, width * 34 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_STEELBLUE        );
    GUI_FillRect( width * 34, 0, width * 35 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LIGHTSKYBLUE     );
    GUI_FillRect( width * 35, 0, width * 36 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_SKYBLUE          );
    GUI_FillRect( width * 36, 0, width * 37 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_DEEPSKYBLUE      );
    GUI_FillRect( width * 37, 0, width * 38 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_LIGHTBLUE        );
    GUI_FillRect( width * 38, 0, width * 39 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_POWDERBLUE       );
    GUI_FillRect( width * 39, 0, width * 40 - 1, GUI_Y_WIDTH-1); GUI_SetPenColor( GUI_CADETBLUE        );





    const char* __restrict__ src  = "/Users/randle_h/desktop/screen.bmp";
    const char* __restrict__ des  = "/Users/randle_h/desktop/screen_.bmp";

    __ImageRGB888_t* IMG_IN  = __LoadBMP_ImgRGB888(src);

    __ImageRGB888_t* IMG_OUT = __Create_ImgRGB888(IMG_IN->width, IMG_IN->height);
    __Blur_Average_ImgRGB888(IMG_IN,IMG_OUT,80000,100);
    __Blur_Average_ImgRGB888(IMG_OUT,IMG_IN,80000,100);
    __OutBMP_ImgRGB888(des, IMG_IN);



#endif




