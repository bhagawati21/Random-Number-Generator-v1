#include <windows.h>
#include "randnum.h"

#define BTN_GENERATE 1
#define CHKBOX_ALPHA 2
#define CHKBOX_NUM 3
#define CHKBOX_SCHAR 4
#define ACTION_EXIT 5
#define HELP_HELP 6
#define HELP_ABOUT 7

HWND hLength,hRandomNumber;
HMENU hMenu;
int flag = 0;

LRESULT CALLBACK winproc(HWND,UINT,WPARAM,LPARAM);
int AddControls(HWND);
int Output(HWND);
int AddMenus(HWND);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,LPSTR lpszarg,int nCmdShow)
{
    WNDCLASSW window = {0};
    window.hbrBackground = (HBRUSH)COLOR_WINDOW;
    window.hCursor = LoadCursor(NULL,IDC_ARROW);
    window.hInstance = hInst;
    window.lpfnWndProc = winproc;
    window.lpszClassName = (LPCWSTR)"MyWindow";

    if(!RegisterClassW(&window))
    {
        MessageBox(NULL,"Could not register the window class",NULL,MB_ICONERROR);
        return 0;
    }

    HWND hWnd = CreateWindowW((LPCWSTR)"MyWindow",(LPCWSTR)"Random Number Generator",
                      WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE,400,170,480,380,NULL,NULL,hInst,NULL);

    if(!(hWnd))
    {
        MessageBox(NULL,"Could not create a window",NULL,MB_ICONERROR);
        return 0;
    }

    MSG msg;

    while(GetMessage(&msg,NULL,0,0))
    {
        if(IsDialogMessage(hWnd,&msg) == 0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return msg.wParam;
}

LRESULT CALLBACK winproc(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    PAINTSTRUCT ps;
    HFONT hFont;
    switch(msg)
    {
    case WM_PAINT:
        BeginPaint(hWnd, &ps);

        hFont = CreateFont(20,0,0,0,FW_DONTCARE,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY, VARIABLE_PITCH,TEXT("Comic Sans MS"));

        SendMessage(hRandomNumber,WM_SETFONT,(WPARAM)hFont,MAKELPARAM(true,0));
        SendMessage(hLength,WM_SETFONT,(WPARAM)hFont,MAKELPARAM(true,0));

        EndPaint(hWnd, &ps);
        break;
    case WM_CREATE:
        AddControls(hWnd);
        AddMenus(hWnd);
        break;
    case WM_COMMAND:
        switch(wp)
        {
        case ACTION_EXIT:
            SendMessage(hWnd,WM_CLOSE,wp,lp);
            break;
        case HELP_ABOUT:
            MessageBox(hWnd,
            "\t    Welcome\n\nName : Random Number Generator\nDeveloper : Bhagawati Lal Ameta\nVersion : 1.0\n\nThanks For using this software",
            "About",MB_OK);
            break;
        case HELP_HELP:
            MessageBox(hWnd,
            "To use this software follow these steps :\n\nEnter the length of number and check the include boxes as your need and press Generate button \nIt'll show a random number according to your choice\n\nThanks for using this software."
            ,"Help",MB_OK);
            break;
        case BTN_GENERATE:
            Output(hWnd);
            break;
        case CHKBOX_ALPHA:
            if(IsDlgButtonChecked(hWnd,CHKBOX_ALPHA))
             {
                 CheckDlgButton(hWnd,CHKBOX_ALPHA,BST_UNCHECKED);
                 flag--;
             }
            else
            {
                CheckDlgButton(hWnd,CHKBOX_ALPHA,BST_CHECKED);
                flag++;
            }
            break;
        case CHKBOX_NUM:
            if(IsDlgButtonChecked(hWnd,CHKBOX_NUM))
             {
                 CheckDlgButton(hWnd,CHKBOX_NUM,BST_UNCHECKED);
                 flag--;
             }
            else
            {
                CheckDlgButton(hWnd,CHKBOX_NUM,BST_CHECKED);
                flag++;
            }
            break;
        case CHKBOX_SCHAR:
            if(IsDlgButtonChecked(hWnd,CHKBOX_SCHAR))
             {
                 CheckDlgButton(hWnd,CHKBOX_SCHAR,BST_UNCHECKED);
                 flag--;
             }
            else
            {
                CheckDlgButton(hWnd,CHKBOX_SCHAR,BST_CHECKED);
                flag++;
            }
            break;
        }
        break;
    case WM_DESTROY:
       PostQuitMessage(0);
       break;
    case WM_CLOSE:
        DeleteObject(hFont);
        DestroyWindow(hWnd);
        break;
    default:
        return DefWindowProc(hWnd,msg,wp,lp);
    }

    return 0;
}

int AddControls(HWND hWnd)
{
    //Edit Controls
    hRandomNumber = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY | ES_CENTER | ES_AUTOHSCROLL,50,80,250,25,hWnd,NULL,NULL,NULL);
    hLength = CreateWindowW(L"Edit",L"",WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP | ES_NUMBER | ES_CENTER,350,80,80,25,hWnd,NULL,NULL,NULL);
    //Static Controls
    CreateWindowW(L"Static",L"Random Number",WS_VISIBLE | WS_CHILD,110,55,110,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static",L"Length",WS_VISIBLE | WS_CHILD,365,55,60,25,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static",L"INCLUDE",WS_VISIBLE | WS_CHILD,210,160,70,25,hWnd,NULL,NULL,NULL);
    //Button Controls
    CreateWindowW(L"Button",L"Alphabets",WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_CHECKBOX,60,200,90,25,hWnd,(HMENU)CHKBOX_ALPHA,NULL,NULL);
    CreateWindowW(L"Button",L"Numbers",WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_CHECKBOX,170,200,80,25,hWnd,(HMENU)CHKBOX_NUM,NULL,NULL);
    CreateWindowW(L"Button",L"Special Characters",WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_CHECKBOX,270,200,160,25,hWnd,(HMENU)CHKBOX_SCHAR,NULL,NULL);
    HWND hGenerate = CreateWindowW(L"Button",L"Generate",WS_VISIBLE | WS_CHILD | WS_TABSTOP,200,260,80,30,hWnd,(HMENU)BTN_GENERATE,NULL,NULL);

    SetClassLong(hGenerate, GCL_HCURSOR, (LONG)LoadCursor (NULL, IDC_HAND));

    return 0;
}

int Output(HWND hWnd)
{
    char clength[10];
    GetWindowText(hLength,clength,10);
    unsigned int length = atoi(clength);

    bool Schar,Num,Alpha;
    Alpha = IsDlgButtonChecked(hWnd,CHKBOX_ALPHA);
    Num = IsDlgButtonChecked(hWnd,CHKBOX_NUM);
    Schar = IsDlgButtonChecked(hWnd,CHKBOX_SCHAR);

    string RandomNumber;
    RANDNUM RandomNum;

    if(length > 0 && length <= 99 && flag)
    {
        if(Alpha && !Num && !Schar)
            RandomNumber = RandomNum.GenerateRandNum(0,0,1,length);

        else if(Num && !Alpha && !Schar)
            RandomNumber = RandomNum.GenerateRandNum(0,1,0,length);

        else if(Schar && !Num && !Alpha)
            RandomNumber = RandomNum.GenerateRandNum(1,0,0,length);

        else if(Alpha && Num && !Schar)
            RandomNumber = RandomNum.GenerateRandNum(0,1,1,length);

        else if(Alpha && Schar && !Num)
            RandomNumber = RandomNum.GenerateRandNum(1,0,1,length);

        else if(Num && Schar && !Alpha)
            RandomNumber = RandomNum.GenerateRandNum(1,1,0,length);

        else
            RandomNumber = RandomNum.GenerateRandNum(1,1,1,length);

        SetWindowText(hRandomNumber,(LPCSTR)RandomNumber.c_str());
    }
    else if(length > 99)
        MessageBox(hWnd,"Too high Length\n\nPlease try with low length","High Length",MB_ICONERROR);
    else if(!strcmp(clength,"0"))
        MessageBox(hWnd,"Length can't be zero","Zero Length",MB_ICONERROR);
    else if(!flag)
        MessageBox(hWnd,"Please select at least one check box","No check box selected",MB_ICONERROR);
    else
        MessageBox(hWnd,"Please enter a length","No Length",MB_ICONERROR);

    return 0;
}

int AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hActionMenu = CreateMenu();
    HMENU hHelpMenu = CreateMenu();

    AppendMenu(hActionMenu,MF_STRING,BTN_GENERATE,"Generate");
    AppendMenu(hActionMenu,MF_SEPARATOR,0,NULL);
    AppendMenu(hActionMenu,MF_STRING,ACTION_EXIT,"Exit");

    AppendMenu(hHelpMenu,MF_STRING,HELP_HELP,"Help");
    AppendMenu(hHelpMenu,MF_STRING,HELP_ABOUT,"About");

    AppendMenu(hMenu, MF_POPUP,(UINT_PTR)hActionMenu,"Action");
    AppendMenu(hMenu, MF_POPUP,(UINT_PTR)hHelpMenu,"Help");

    SetMenu(hWnd,hMenu);

    return 0;
}
