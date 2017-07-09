// TPlayGame_Main.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TPlayGame_Main.h"
#include "TFileOption.h"
#include "mysql_t.h"

BOOL CMainFrameWnd::Create() //创建窗口和按钮
{
	//m_hWindow=XWnd_CreateWindow(0,0,0,0,L"视频监控系统",NULL,XC_SY_BORDER | /*XC_SY_ROUND|*/XC_SY_CENTER);
	m_hWindow = XWnd_CreateWindow(0,0,0,0,L"炫彩界面库-窗口",NULL, XC_SY_BORDER | XC_SY_ROUND | XC_SY_CENTER); //创建窗口
	if(m_hWindow)
	{
		XWnd_SetBorderSize(m_hWindow,0,0,0,0);
		XWnd_SetRoundSize(m_hWindow,0);

		m_hThemeBackground=XImage_LoadFile(L"skin\\main\\frame.jpg");
		XImage_SetDrawType(m_hThemeBackground,XC_IMAGE_TILE);
		XWnd_SetImageNC(m_hWindow,m_hThemeBackground);

		if (TFile_Option->parse_file("./svc.ini") != 0)
		{
			MessageBox(0, _T("读取配置文件失败"), _T("警告"), MB_OK);
			exit(1);
		}

		if (!(mysql_connect_db( 
			TFile_Option->mysql_host.c_str(),
			TFile_Option->mysql_user.c_str(),
			TFile_Option->mysql_pass.c_str(),
			TFile_Option->mysql_dbname.c_str(),
			TFile_Option->mysql_port)))
		{
			MessageBox(0, _T("连接数据库失败,检查参数"), _T("警告"), MB_OK);
			exit(1);
		}

		mysql_update_user_picture(1, _T("F:\\killer.png"));

		m_hPlayGameHouseWnd.Create(m_hWindow);

		//27*22
		m_hBtnSysClose=XBtn_Create(0,0,0,0,NULL,m_hWindow);
		XEle_SetBkTransparent(m_hBtnSysClose,TRUE);
		XEle_EnableFocus(m_hBtnSysClose,FALSE);
		XBtn_SetImageLeave(m_hBtnSysClose,XImage_LoadFileRect(L"skin\\main\\sys_button_close.png",1,2,28,24));
		XBtn_SetImageStay(m_hBtnSysClose,XImage_LoadFileRect(L"skin\\main\\sys_button_close.png",33,2,60,24));
		XBtn_SetImageDown(m_hBtnSysClose,XImage_LoadFileRect(L"skin\\main\\sys_button_close.png",65,2,92,24));

		//27*22
		m_hBtnSysMin=XBtn_Create(0,0,0,0,NULL,m_hWindow);
		XEle_SetBkTransparent(m_hBtnSysMin,TRUE);
		XEle_EnableFocus(m_hBtnSysMin,FALSE);
		XBtn_SetImageLeave(m_hBtnSysMin,XImage_LoadFileRect(L"skin\\main\\sys_button_min.png",0,0,27,22));
		XBtn_SetImageStay(m_hBtnSysMin,XImage_LoadFileRect(L"skin\\main\\sys_button_min.png",27,0,54,22));
		XBtn_SetImageDown(m_hBtnSysMin,XImage_LoadFileRect(L"skin\\main\\sys_button_min.png",54,0,81,22));

		/*m_hBtnSysMenu=XBtn_Create(0,0,0,0,NULL,m_hWindow);
		XEle_SetBkTransparent(m_hBtnSysMenu,TRUE);
		XEle_EnableFocus(m_hBtnSysMenu,FALSE);
		XBtn_SetImageLeave(m_hBtnSysMenu,XImage_LoadFileRect(L"skin\\main\\sys_button_menu.png",0,0,27,22));
		XBtn_SetImageStay(m_hBtnSysMenu,XImage_LoadFileRect(L"skin\\main\\sys_button_menu.png",27,0,54,22));
		XBtn_SetImageDown(m_hBtnSysMenu,XImage_LoadFileRect(L"skin\\main\\sys_button_menu.png",54,0,81,22));*/

		LOGFONT fontInfo;
		XC_InitFont(&fontInfo,L"宋体",18,TRUE);
		m_hLogoTitleFont=XFont_CreateEx(&fontInfo);

		m_hLogoTitle = XStatic_Create(0,0,0,0,_T("Super Detective Online"),m_hWindow);
		XEle_SetBkTransparent(m_hLogoTitle,TRUE);
		//XEle_SetFont(m_hLogoTitle,m_hLogoTitleFont);

		m_hVersion = XStatic_Create(0,0,0,0,_T("版本：1.0.0.1"),m_hWindow);
		XEle_SetBkTransparent(m_hVersion,TRUE);

		/// logo
		m_hLogoEle=XPic_Create(0,0,0,0,m_hWindow);
		XEle_SetBkTransparent(m_hLogoEle,TRUE);
		XPic_SetImage(m_hLogoEle,XImage_LoadFile(L"skin\\main\\logo.png"));

		m_hImageLeave=XImage_LoadFile(GetMainCustIcon(L"toolbar_normal"));
		m_hImageStay=XImage_LoadFile(GetMainCustIcon(L"toolbar_hover"));
		m_hImageDown=XImage_LoadFile(GetMainCustIcon(L"toolbar_pushed"));

		m_hEleGameStart=XBtn_Create(0,0,0,0,L"游戏开始",m_hWindow);
		XBtn_SetIcon(m_hEleGameStart,XImage_LoadFile(GetMainCustIcon(L"game_start")));
		XBtn_SetIconAlign(m_hEleGameStart,XC_ICON_ALIGN_TOP);
		XEle_SetBkTransparent(m_hEleGameStart,TRUE);
		XEle_EnableFocus(m_hEleGameStart,FALSE);
		XBtn_SetImageLeave(m_hEleGameStart,m_hImageLeave);
		XBtn_SetImageStay(m_hEleGameStart,m_hImageStay);
		XBtn_SetImageDown(m_hEleGameStart,m_hImageDown);

		m_hEleGamerKill=XBtn_Create(0,0,0,0,L"结束游戏",m_hWindow);
		XBtn_SetIcon(m_hEleGamerKill,XImage_LoadFile(GetMainCustIcon(L"game_kill")));
		XBtn_SetIconAlign(m_hEleGamerKill,XC_ICON_ALIGN_TOP);
		XEle_SetBkTransparent(m_hEleGamerKill,TRUE);
		XEle_EnableFocus(m_hEleGamerKill,FALSE);
		XBtn_SetImageLeave(m_hEleGamerKill,m_hImageLeave);
		XBtn_SetImageStay(m_hEleGamerKill,m_hImageStay);
		XBtn_SetImageDown(m_hEleGamerKill,m_hImageDown);

		m_hEleGameSet=XBtn_Create(0,0,0,0,L"游戏设置",m_hWindow);
		XEle_SetBkTransparent(m_hEleGameSet,TRUE);
		XBtn_SetIcon(m_hEleGameSet,XImage_LoadFile(GetMainCustIcon(L"game_set")));
		XBtn_SetIconAlign(m_hEleGameSet,XC_ICON_ALIGN_TOP);
		XEle_EnableFocus(m_hEleGameSet,FALSE);
		XBtn_SetImageLeave(m_hEleGameSet,m_hImageLeave);
		XBtn_SetImageStay(m_hEleGameSet,m_hImageStay);
		XBtn_SetImageDown(m_hEleGameSet,m_hImageDown);

		m_hEleGameUser=XBtn_Create(0,0,0,0,L"玩家增加",m_hWindow);
		XEle_SetBkTransparent(m_hEleGameUser,TRUE);
		XBtn_SetIcon(m_hEleGameUser,XImage_LoadFile(GetMainCustIcon(L"game_user")));
		XBtn_SetIconAlign(m_hEleGameUser,XC_ICON_ALIGN_TOP);
		XEle_EnableFocus(m_hEleGameUser,FALSE);
		XBtn_SetImageLeave(m_hEleGameUser,m_hImageLeave);
		XBtn_SetImageStay(m_hEleGameUser,m_hImageStay);
		XBtn_SetImageDown(m_hEleGameUser,m_hImageDown);

		m_hEleGameQuery=XBtn_Create(0,0,0,0,L"玩家管理",m_hWindow);
		XEle_SetBkTransparent(m_hEleGameQuery,TRUE);
		XBtn_SetIcon(m_hEleGameQuery,XImage_LoadFile(GetMainCustIcon(L"game_query")));
		XBtn_SetIconAlign(m_hEleGameQuery,XC_ICON_ALIGN_TOP);
		XEle_EnableFocus(m_hEleGameQuery,FALSE);
		XBtn_SetImageLeave(m_hEleGameQuery,m_hImageLeave);
		XBtn_SetImageStay(m_hEleGameQuery,m_hImageStay);
		XBtn_SetImageDown(m_hEleGameQuery,m_hImageDown);

		m_hSwitchGridEle=XBtn_Create(0,0,0,0,L"切换",m_hWindow);
		XEle_SetBkTransparent(m_hSwitchGridEle,TRUE);
		XBtn_SetIcon(m_hSwitchGridEle,XImage_LoadFile(GetMainCustIcon(L"SwitchGrid")));
		XBtn_SetIconAlign(m_hSwitchGridEle,XC_ICON_ALIGN_TOP);
		XEle_EnableFocus(m_hSwitchGridEle,FALSE);
		XBtn_SetImageLeave(m_hSwitchGridEle,m_hImageLeave);
		XBtn_SetImageStay(m_hSwitchGridEle,m_hImageStay);
		XBtn_SetImageDown(m_hSwitchGridEle,m_hImageDown);

		m_hEleAllQuery=XBtn_Create(0,0,0,0,L"综合查询",m_hWindow);
		XEle_SetBkTransparent(m_hEleAllQuery,TRUE);
		XBtn_SetIcon(m_hEleAllQuery,XImage_LoadFile(GetMainCustIcon(L"all_query")));
		XBtn_SetIconAlign(m_hEleAllQuery,XC_ICON_ALIGN_TOP);
		XEle_EnableFocus(m_hEleAllQuery,FALSE);
		XBtn_SetImageLeave(m_hEleAllQuery,m_hImageLeave);
		XBtn_SetImageStay(m_hEleAllQuery,m_hImageStay);
		XBtn_SetImageDown(m_hEleAllQuery,m_hImageDown);

		m_hEleResetScore=XBtn_Create(0,0,0,0,L"积分重置",m_hWindow);
		XEle_SetBkTransparent(m_hEleResetScore,TRUE);
		XBtn_SetIcon(m_hEleResetScore,XImage_LoadFile(GetMainCustIcon(L"reset_score")));
		XBtn_SetIconAlign(m_hEleResetScore,XC_ICON_ALIGN_TOP);
		XEle_EnableFocus(m_hEleResetScore,FALSE);
		XBtn_SetImageLeave(m_hEleResetScore,m_hImageLeave);
		XBtn_SetImageStay(m_hEleResetScore,m_hImageStay);
		XBtn_SetImageDown(m_hEleResetScore,m_hImageDown);

		XCGUI_RegEleEvent(m_hBtnSysClose,XE_BNCLICK,&CMainFrameWnd::OnEventBtnSysClick);
		XCGUI_RegEleEvent(m_hBtnSysMin,XE_BNCLICK,&CMainFrameWnd::OnEventBtnSysClick);
		
		XCGUI_RegEleEvent(m_hEleGameStart,XE_BNCLICK,&CMainFrameWnd::OnEventBtnSysClick);
		XCGUI_RegEleEvent(m_hEleGamerKill,XE_BNCLICK,&CMainFrameWnd::OnEventBtnSysClick);
		XCGUI_RegEleEvent(m_hEleGameSet,XE_BNCLICK,&CMainFrameWnd::OnEventBtnSysClick);
		XCGUI_RegEleEvent(m_hEleGameUser,XE_BNCLICK,&CMainFrameWnd::OnEventBtnSysClick);
		XCGUI_RegEleEvent(m_hEleGameQuery,XE_BNCLICK,&CMainFrameWnd::OnEventBtnSysClick);
		XCGUI_RegEleEvent(m_hSwitchGridEle,XE_BNCLICK,&CMainFrameWnd::OnEventBtnSysClick);
		XCGUI_RegEleEvent(m_hEleAllQuery,XE_BNCLICK,&CMainFrameWnd::OnEventBtnSysClick);
		XCGUI_RegEleEvent(m_hEleResetScore,XE_BNCLICK,&CMainFrameWnd::OnEventBtnSysClick);

		XCGUI_RegWndMessage(m_hWindow,XWM_MENUSELECT,&CMainFrameWnd::OnEventMenuSelect);
		XCGUI_RegWndMessage(m_hWindow,WM_SIZE,&CMainFrameWnd::OnWndSize);


		XWnd_ShowWindow(m_hWindow,SW_MAXIMIZE); //显示窗口

		//XWnd_SetWindowPos(m_hWindow, NULL, 0, 0, 900, 800, SWP_SHOWWINDOW);
		//XWnd_SetWindowPos(HWINDOW hWindow,HWND hWndInsertAfter,int x,int y,int cx,int cy,UINT uFlags);

		return TRUE;
	}
	return FALSE;
}

BOOL CMainFrameWnd::OnWndSize(HWINDOW hWindow,UINT flags,SIZE *pSize)
{
	RECT rect = {0,0,pSize->cx,pSize->cy};

	RECT rc = rect;

	rc.left += 50;
	rc.right = rc.left+58;
	rc.top += 30;
	rc.bottom = rc.top+78;
	XEle_SetRect(m_hEleGameStart,&rc);

	rc.left = rc.right + 20;
	rc.right = rc.left + 58;
	XEle_SetRect(m_hEleGamerKill,&rc);

	rc.left = rc.right + 20;
	rc.right = rc.left + 58;
	XEle_SetRect(m_hEleGameSet,&rc);

	rc.left = rc.right + 20;
	rc.right = rc.left + 58;
	XEle_SetRect(m_hEleGameUser,&rc);

	rc.left = rc.right + 20;
	rc.right = rc.left + 58;
	XEle_SetRect(m_hEleGameQuery,&rc);

	rc.left = rc.right + 20;
	rc.right = rc.left + 58;
	XEle_SetRect(m_hSwitchGridEle,&rc);

	rc.left = rc.right + 20;
	rc.right = rc.left + 58;
	XEle_SetRect(m_hEleAllQuery,&rc);

	rc.left = rc.right + 20;
	rc.right = rc.left + 58;
	XEle_SetRect(m_hEleResetScore,&rc);

	rc = rect;

	rc.left += 10;
	rc.right = rc.left+300;
	rc.top += 10;
	rc.bottom = rc.top+22;
	XEle_SetRect(m_hLogoTitle,&rc);

	rc = rect;
	rc.right -= 4;
	rc.left = rc.right-27;
	rc.bottom = rc.top+22;
	XEle_SetRect(m_hBtnSysClose,&rc);

	rc.left -= 27;
	rc.right -= 27;
	XEle_SetRect(m_hBtnSysMin,&rc);

	rc.left -= 27;
	rc.right -= 27;
	//XEle_SetRect(m_hBtnSysMenu,&rc);

	rc = rect;

	rc.left = rc.right-155;
	rc.top += 35;
	rc.right = rc.left+140;
	rc.bottom = rc.top+67;
	XEle_SetRect(m_hLogoEle,&rc);

	rc.left = 0;
	rc.top = 110;
	rc.right = rect.right;
	rc.bottom = rect.bottom - 20;
	m_hPlayGameHouseWnd.SetWindowPos(&rc);

	rc = rect;
	rc.top = rc.bottom - 19;
	rc.left += 10;
	rc.right = rc.left + 200;
	XEle_SetRect(m_hVersion,&rc);

	return FALSE;
}

BOOL CMainFrameWnd::OnEventBtnSysClick(HELE hEle,HELE hEleEvent)
{
	if (hEle == m_hBtnSysClose)
	{
		mysql_close(mysql_t);
		XWnd_CloseWindow(m_hWindow);
	}
	else if (hEle == m_hBtnSysMin)
	{
		XWnd_ShowWindow(m_hWindow, SW_SHOWMINIMIZED);
	}
	else if (hEle == m_hEleGameStart)
	{
		m_hPlayGameHouseWnd.GameStart();
	}
	else if (hEle == m_hEleGamerKill)
	{
		m_hPlayGameHouseWnd.GameKill();
	}
	else if (hEle == m_hEleGameSet)
	{
		m_hPlayGameHouseWnd.GameSet();
	}
	else if (hEle == m_hEleGameUser)
	{
		m_hPlayGameHouseWnd.NewGamer();
	}
	else if (hEle == m_hEleGameQuery)
	{
		m_hPlayGameHouseWnd.GamerQuery();
	}
	else if (hEle == m_hSwitchGridEle)
	{
		m_hPlayGameHouseWnd.SwitchGrid();
	}
	else if (hEle == m_hEleAllQuery)
	{
		m_hPlayGameHouseWnd.AllQuery();
	}
	else if (hEle == m_hEleResetScore)
	{
		m_hPlayGameHouseWnd.ResetScore();
	}
	return FALSE;
}

BOOL CMainFrameWnd::OnEventMenuSelect(HWINDOW hWindow,int id)
{
	switch (id)
	{
	/*case 201: /// 游戏开始
		break;

	case 202: /// 游戏设置
		break;*/

	case 203: /// 退出系统
		XWnd_CloseWindow(m_hWindow);
		return FALSE;
	}

	return TRUE;
}

CMainFrameWnd m_MainFrame;

int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	if(m_MainFrame.Create())
	{
		XRunXCGUI();
	}

	return 0;
}