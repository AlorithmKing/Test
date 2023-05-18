#pragma once
#include <ProToolkit.h>
#include <ProUtil.h>
#include <ProArray.h>
#include <ProDimension.h>
#include <ProWindows.h>
#include <ProSolid.h>
#include <ProParameter.h>
#include <ProParamval.h>
#include <ProMessage.h>
#include <ProMenu.h>
#include <ProMenuBar.h>
#include <ProMdl.h>
#include <ProModelitem.h>
#include <ProDrawing.h>
#include <ProFeature.h>
#include <ProFeatType.h>
#include <ProDrawing.h>
#include <ProNotify.h>
#include <ProRefInfo.h>
#include <ProRelSet.h>
#include <ProSelection.h>
#include <ProGtol.h>
#include <ProSurface.h>
/*---------------------- Pro/Toolkit Includes ------------------------*/
#include <ProCollect.h>
#include <ProParameter.h>
#include <ProParamval.h>
#include <ProSrfcollection.h>
#include <ProTKRunTime.h>
#include <ProAsmcomp.h>
#include <ProEdgedata.h>
#include <ProEdge.h>
#include <ProObjects.h>
/*---------------------- Application Includes ------------------------*/
// #include <TestError.h>
#include <ProToolkit.h>
#include <ProMdl.h>
#include <ProMenuBar.h>
#include <ProArray.h>
#include <ProObjects.h>
#include <ProSurfacedata.h>
#include <ProSurface.h>
#include <ProAxis.h>
#include <ProDtmAxis.h>
#include <ProElemId.h>
#include <ProValue.h>
#include <ProElement.h>
#include <ProFeature.h>
#include <ProFeatType.h>
#include <ProFeatType.h>
#include <ProSelection.h>
#include <ProElempath.h>
#include <ProAsmcomp.h>
#include <ProGroup.h>
#include <math.h>
#include <ProTKRunTime.h>
#include <ProQuilt.h>
#include <ProQuilt.h>
#include <ProXsec.h>
#include <ProSetDatumTag.h>
#include <ProAnnotation.h>
#include <ProGtolAttach.h>
#include <ProDisplist.h>
#include <ProAnnotationFeat.h>
#include <ProGraphic.h>
#include <ProMode.h>
#include <ProView.h>

inline FILE* PTApplsUnicodeFopen(const char* filename, const char* mode)
{
	FILE* handle;
	wchar_t wFilename[256];
	wchar_t wmode[5];
	// Convert filename to wide character format
	swprintf(wFilename, 256, L"%hs", filename);
	swprintf(wmode, 5, L"%hs", mode);
	// Open file in Unicode mode
	handle = _wfopen(wFilename, wmode);

	return handle;
}
	