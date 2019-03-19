#ifndef R3BWHITERABBITREADERIMPL_H
#define R3BWHITERABBITREADERIMPL_H

#define R3B_WHITERABBIT_READER_IMPL(ClassName, struct_name, id)\
R3B##ClassName##Reader::R3B##ClassName##Reader(EXT_STR_h101_##struct_name *a_data,\
    UInt_t a_offset)\
	: R3BReader("R3B"#ClassName"Reader")\
	, fNEvent(0)\
	, fData(a_data)\
	, fOffset(a_offset)\
	, fLogger(FairLogger::GetLogger())\
	, fWhiterabbitId(id)\
	, fEventHeader(nullptr)\
{\
}\
\
Bool_t R3B##ClassName##Reader::Init(ext_data_struct_info *a_struct_info)\
{\
	int ok;\
\
	EXT_STR_h101_##struct_name##_ITEMS_INFO(ok, *a_struct_info, fOffset,\
	    EXT_STR_h101_##struct_name, 0);\
\
	if (!ok) {\
		perror("ext_data_struct_info_item");\
		LOG(ERROR) << "Failed to setup structure information.";\
		return kFALSE;\
	}\
\
	FairRootManager* mgr = FairRootManager::Instance();\
	fEventHeader = (R3BEventHeader *)mgr->GetObject("R3BEventHeader");\
\
	return kTRUE;\
}\
\
Bool_t R3B##ClassName##Reader::Read()\
{\
	if (fData->TIMESTAMP_MASTER_ID != 0\
	    && fWhiterabbitId != fData->TIMESTAMP_MASTER_ID) {\
		LOG(ERROR) <<\
		    "Event " << fEventHeader->GetEventno() << ": "\
		    "Whiterabbit ID mismatch: expect " << fWhiterabbitId <<\
		    ", got " << fData->TIMESTAMP_MASTER_ID << "\n";\
	}\
\
	if (fEventHeader) {\
		uint64_t timestamp\
		    = ((uint64_t) fData->TIMESTAMP_MASTER_WR_T4 << 48)\
		    | ((uint64_t) fData->TIMESTAMP_MASTER_WR_T3 << 32)\
		    | ((uint64_t) fData->TIMESTAMP_MASTER_WR_T2 << 16)\
		    | ((uint64_t) fData->TIMESTAMP_MASTER_WR_T1 <<  0);\
\
		fEventHeader->SetTimeStamp(timestamp);\
		fNEvent = fEventHeader->GetEventno();\
	} else {\
		fNEvent++;\
	}\
\
	return kTRUE;\
}\
\
void R3B##ClassName##Reader::Reset()\
{\
	fNEvent = 0;\
}\
\
ClassImp(R3B##ClassName##Reader)

#endif
