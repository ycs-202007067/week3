#ifdef _DEBUG_   
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif
#include <windows.h>
// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
bool isDragging = false; //드래그중인지 여부를 나타내는 전역변수
RECT rect = { 0,0,0,0 }; // 사각형의 좌표를 나타내는 전역변수
HBRUSH hBrush; // 분홍색 브러쉬 핸들
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {

    case WM_CREATE:
        hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성
        break;

    case WM_LBUTTONDOWN:
        // 마우스 왼쪽 버튼이 눌린 경우
        isDragging = true;
        rect.left = LOWORD(lParam);
        rect.top = HIWORD(lParam);
        rect.right = rect.left;
        rect.bottom = rect.top;
        break;

    case WM_MOUSEMOVE:
        // 마우스 이동 중인 경우
        if (isDragging) {
            // 이전에 그렸던 사각형을 지우기 위해 InvalidateRect 호출
            InvalidateRect(hwnd, &rect, TRUE);
            rect.right = LOWORD(lParam);
            rect.bottom = HIWORD(lParam);
            // 새로운 사각형을 그리기 위해 다시 그림
            InvalidateRect(hwnd, &rect, TRUE);
        }
        break;

    case WM_LBUTTONUP:
        // 마우스 왼쪽 버튼이 놓여진 경우
        isDragging = false;
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        SelectObject(hdc, hBrush); // 브러시 선택
        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        DeleteObject(hBrush); // 브러시 삭제
        PostQuitMessage(0);
        break;
    default:

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
    /* 윈도우 클래스 선언.*/
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));   // 모두 0으로 초기화.

    // 윈도우 클래스 값 설정
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("Computer Software");
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;

    // 윈도우 클래스 등록.
    if (RegisterClass(&wc) == 0)
    {
        MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
        exit(-1);   //예외
    }

    // Window viewport 영역 조정
    RECT rect = { 150, 100, 800, 600 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    // 윈도우 생성
    HWND hwnd = CreateWindow(
        wc.lpszClassName,
        TEXT("202007067 문현민"),
        WS_OVERLAPPEDWINDOW,
        0, 0,
        width, height,
        NULL, NULL,
        hInstance,
        NULL
    );

    // 오류 검사.
    if (hwnd == NULL)
    {
        MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
        exit(-1);
    }

    // 창 보이기.
    ShowWindow(hwnd, SW_SHOW); // 창 띄우고
    UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.



    // 메시지 처리 루프.
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));

    while (msg.message != WM_QUIT)
    {
        // 메시지 처리.
        if (GetMessage(&msg, hwnd, 0, 0))
            //if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
        {

            // 메시지 해석해줘.
            TranslateMessage(&msg);
            // 메시지를 처리해야할 곳에 전달해줘.
            DispatchMessage(&msg);

        }
        /*else
        {

        }*/
    }

    //종료 메시지 보내기
    return (int)msg.wParam;
}