#include "ProHeader.h"
////#include"note.h"
#include"Datum.h"
#include"ColorDisplay.h"
#include"GtolCreate.h"
#include"DimSelect.h"
//#include"viewsave.h"
//访问控制函数
static uiCmdAccessState UsrAccessDefault(uiCmdAccessMode access_mode)
{
	return (ACCESS_AVAILABLE);
}


//extern "C" 
extern "C"  int user_initialize(int argc
	, char* argv[]
	, char* version
	, char* build
	, wchar_t errbuf[80])
{
	ProError status;
	ProFileName MsgFile;
	ProStringToWstring(MsgFile, (char*)"IconMessage.txt"); //注意此处的 IconMessage 与后面的txt 文件夹下的 IconMessage.txt 文件名必须相同
	uiCmdCmdId PushButton1_cmd_id, PushButton2_cmd_id, PushButton3_cmd_id;
	status = ProMenubarMenuAdd((char*)"MainMenu", (char*)"Function", (char*)"Help", PRO_B_TRUE, MsgFile);
	ProCmdActionAdd((char*)"PushButton1_Act", (uiCmdCmdActFn)TagDatumLabel, 12, UsrAccessDefault, PRO_B_TRUE, PRO_B_TRUE, &PushButton1_cmd_id);
	ProMenubarmenuPushbuttonAdd((char*)"MainMenu", (char*)"PushButton", (char*)"FirstButton", (char*)"this button will show a message", NULL, PRO_B_TRUE, PushButton1_cmd_id, MsgFile);
	ProCmdActionAdd(const_cast <char*>("PushButton2_Act"), (uiCmdCmdActFn)DimensionTest, uiCmdPrioDefault, UsrAccessDefault, PRO_B_TRUE, PRO_B_TRUE, &PushButton2_cmd_id);
	ProMenubarmenuPushbuttonAdd(const_cast <char*>("MainMenu"), const_cast <char*>("PushButton2"), const_cast <char*>("SecondButton"), const_cast <char*>("this button will show a message"), NULL, PRO_B_TRUE, PushButton2_cmd_id, MsgFile);
	ProCmdActionAdd(const_cast <char*>("PushButton3_Act"), (uiCmdCmdActFn)DimensionTest, uiCmdPrioDefault, UsrAccessDefault, PRO_B_TRUE, PRO_B_TRUE, &PushButton3_cmd_id);
	ProMenubarmenuPushbuttonAdd(const_cast <char*>("MainMenu"), const_cast <char*>("PushButton3"), const_cast <char*>("ThirdButton"), const_cast <char*>("this button will show a message"), NULL, PRO_B_TRUE, PushButton2_cmd_id, MsgFile);

	return 0;
}

//extern "C"
extern "C"  void user_terminate(void)
{
	return;
}
