#define TOMORROW_IS_TODAY false


#if TOMORROW_IS_TODAY
typedef uint8_t BYTE;



struct GUI_Trace_t{
	BYTE         ID;
	Macro_t      GUI_TRACE_xxxx;

	size_t       recordSize; // !!!
	int*         *dataSource;
	const char*  *dataName; 
	size_t       dataNum;

	unsigned int x_pos;
	unsigned int y_pos;
	unsigned int height;
	unsigned int width;  // !!!

	bool         GridON;
	bool         LegacyON;
	Pixel_t      themeColor;
};
typedef struct GUI_Trace_t GUI_Trace_t;

struct __TraceWatchConfigChain{
	struct GUI_Trace_t config;
	struct __TraceWatchConfigChain* nextConfig;

};

void GUI_CreateTraceWatchSocket(struct GUI_Trace_t* config){

}

void GUI_ChangeTraceWatchSocket(BYTE ID){

}

void GUI_RecordTrace(BYTE ID){

}

void GUI_ShowTraceWatch(BYTE ID,size_t probe){

}

void GUI_HideTraceWatch(BYTE ID){

}

void GUI_DeleteTraceWatchScoket(BYTE ID){

}

#endif
