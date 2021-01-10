#include "ApplicationCore.h"

#include <WinUser.h>

#include "Application.h"

using namespace ArtemisApplication;

Application::Application() :
    WindowHandle(nullptr),
    Direct2DFactory(nullptr),
    RenderTarget(nullptr),
    LightSlateGrayBrush(nullptr),
    CornflowerBlueBrush(nullptr)
{
}

void Application::RunMessageLoop()
{
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HRESULT Application::Initialize()
{
    // Initialize device-independent resources, such
    // as the Direct2D factory.
    HRESULT result = CreateDeviceIndependentResources();

    if (SUCCEEDED(result))
    {
        WNDCLASSEXW windowClass{ };
    	
        // Register the window class.
        WNDCLASSEXW wcex = { sizeof(WNDCLASSEXW) };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WindowProcedure;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = sizeof(LONG_PTR);
        wcex.hInstance = HINST_THISCOMPONENT;
        wcex.hbrBackground = nullptr;
        wcex.lpszMenuName = nullptr;
        wcex.hCursor = LoadCursor(nullptr, IDI_APPLICATION);
        wcex.lpszClassName = L"D2DDemoApp";

        RegisterClassEx(&wcex);
                       
        // Create the window.
        WindowHandle = CreateWindow(
            L"D2DDemoApp",
            L"Direct2D Demo App",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<UINT>(1920),
            static_cast<UINT>(1080),
            nullptr,
            nullptr,
            HINST_THISCOMPONENT,
            this
        );
        result = WindowHandle ? S_OK : E_FAIL;
        if (SUCCEEDED(result))
        {
            ShowWindow(WindowHandle, SW_SHOWNORMAL);
            UpdateWindow(WindowHandle);
        }
    }

    return result;
}

HRESULT Application::CreateDeviceIndependentResources()
{
    return D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, Direct2DFactory.GetAddressOf());
}

HRESULT Application::CreateDeviceResources()
{
    HRESULT renderTargetResult = S_OK;
    
    if (!RenderTarget)
    {
	    RECT windowSize;
	    GetClientRect(WindowHandle, &windowSize);

	    const D2D1_SIZE_U size = D2D1::SizeU(
	        windowSize.right - windowSize.left,
	        windowSize.bottom - windowSize.top);
        	    
	    // Create a Direct2D render target.
	    renderTargetResult = Direct2DFactory->CreateHwndRenderTarget(
	        D2D1::RenderTargetProperties(),
	        D2D1::HwndRenderTargetProperties(WindowHandle, size),
	        &RenderTarget);

	    if (SUCCEEDED(renderTargetResult))
	    {
	        // Create a gray brush.
	        renderTargetResult = RenderTarget->CreateSolidColorBrush(
	            D2D1::ColorF(D2D1::ColorF::LightSlateGray),
	            &LightSlateGrayBrush);

            // Create a blue brush.
            renderTargetResult = RenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
                &CornflowerBlueBrush);
	    }
    }

	return renderTargetResult;
}

void Application::DiscardDeviceResources()
{
    RenderTarget->Release();
	LightSlateGrayBrush->Release();
	CornflowerBlueBrush->Release();
}

HRESULT Application::OnRender()
{
    HRESULT result = S_OK;

    result = CreateDeviceResources();

    if (SUCCEEDED(result))
    {
        RenderTarget->BeginDraw();
        RenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        RenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

        D2D1_SIZE_F rtSize = RenderTarget->GetSize();

        // Draw a grid background.
        int width = static_cast<int>(rtSize.width);
        int height = static_cast<int>(rtSize.height);

        for (int x = 0; x < width; x += 10)
        {
            RenderTarget->DrawLine(
                D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
                D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
                LightSlateGrayBrush.Get(),
                0.5f
            );
        }

        for (int y = 0; y < height; y += 10)
        {
            RenderTarget->DrawLine(
                D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
                D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
                LightSlateGrayBrush.Get(),
                0.5f
            );
        }

        // Draw two rectangles.
        D2D1_RECT_F rectangle1 = D2D1::RectF(
            rtSize.width / 2 - 50.0f,
            rtSize.height / 2 - 50.0f,
            rtSize.width / 2 + 50.0f,
            rtSize.height / 2 + 50.0f
        );

        D2D1_RECT_F rectangle2 = D2D1::RectF(
            rtSize.width / 2 - 100.0f,
            rtSize.height / 2 - 100.0f,
            rtSize.width / 2 + 100.0f,
            rtSize.height / 2 + 100.0f
        );

        // Draw a filled rectangle.
        RenderTarget->FillRectangle(&rectangle1, LightSlateGrayBrush.Get());

        // Draw the outline of a rectangle.
        RenderTarget->DrawRectangle(&rectangle2, CornflowerBlueBrush.Get());

        result = RenderTarget->EndDraw();
    }

    if (result == D2DERR_RECREATE_TARGET)
    {
        result = S_OK;
        DiscardDeviceResources();
    }

	return result;
}

void Application::OnResize(UINT width, UINT height)
{
    if (RenderTarget)
    {
        // Note: This method can fail, but it's okay to ignore the
        // error here, because the error will be returned again
        // the next time EndDraw is called.
        RenderTarget->Resize(D2D1::SizeU(width, height));
    }
}

LRESULT Application::WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        auto pDemoApp = (Application*)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hWnd,
            GWLP_USERDATA,
            reinterpret_cast<LONG_PTR>(pDemoApp)
        );

        result = 1;
    }
    else
    {
        auto pDemoApp = reinterpret_cast<Application*>(static_cast<LONG_PTR>(
            ::GetWindowLongPtrW(
                hWnd,
                GWLP_USERDATA
            )));

        bool wasHandled = false;

        if (pDemoApp)
        {
            switch (message)
            {
	            case WM_SIZE:
		            {
		                UINT width = LOWORD(lParam);
		                UINT height = HIWORD(lParam);
		                pDemoApp->OnResize(width, height);
		            }
		            result = 0;
		            wasHandled = true;
		            break;

	            case WM_DISPLAYCHANGE:
		            {
		                InvalidateRect(hWnd, NULL, FALSE);
		            }
		            result = 0;
		            wasHandled = true;
		            break;

	            case WM_PAINT:
		            {
		                pDemoApp->OnRender();
		                ValidateRect(hWnd, NULL);
		            }
		            result = 0;
		            wasHandled = true;
		            break;

	            case WM_DESTROY:
		            {
		                PostQuitMessage(0);
		            }
		            result = 1;
		            wasHandled = true;
		            break;
            }
        }

        if (!wasHandled)
        {
            result = DefWindowProc(hWnd, message, wParam, lParam);
        }
    }

    return result;
}