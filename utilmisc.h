/* Created by Jochen Neubeck 05/25/2017 */

#include <intrin.h>

#define InterlockedCompareExchange64 _InterlockedCompareExchange64 /* for XP */

DECLSPEC_IMPORT ULONG DbgPrint(PCSTR, ...); /* from ntdll.lib */

#ifdef _UNICODE
#define TF "l"
#else
#define TF "h"
#endif

#ifdef _DEBUG
#define trace (void)DbgPrint
#define enter(fmt, ...) \
	eh_enum = \
	( \
		DbgPrint("[%08X] -> " fmt "\n", \
			GetCurrentThreadId(), __VA_ARGS__), \
		succeeded \
	); char const *eh_text = "succeeded"; int eh_diag = 0
#define leave(fmt, ...) \
	( \
		DbgPrint("[%08X] <- %d = %s(%d) = " fmt "\n", \
			GetCurrentThreadId(), eh_enum, eh_text, eh_diag, __VA_ARGS__), \
		eh_enum \
	)
#define goto(label) \
	{ eh_enum = label; eh_text = #label; eh_diag = GetLastError(); goto label; }
#else
#define trace (void)sizeof
#define enter(fmt, ...) eh_enum = succeeded
#define leave(fmt, ...) eh_enum
#define goto(label) { eh_enum = label; goto label; }
#endif

/* A const_cast for C */
#define const_cast(type, expr) (sizeof((type)(expr) - (expr)), (type)(expr))

/* A syntax for automatic nested block scopes in switch statements, like so:
 *
 *     switch (uMsg)
 *     {{
 *     case(:WM_INITDIALOG:)
 *         HICON hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(101));
 *         SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
 *         SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
 *         ShowWindow(hDlg, SW_SHOW);
 *         return TRUE;
 *
 *     case(:WM_COMMAND:)
 *         switch (wParam)
 *         {
 *         case IDCANCEL:
 *         case ~~((3 + 1) * 2):
 *             DestroyWindow(hwnd);
 *             break;
 *         }
 *         return TRUE;
 *
 *     case(:WM_DESTROY:)
 *         PostQuitMessage(0);
 *         break;
 *
 *     default(:)
 *         break;
 *     }}
 *
 * Note how ~~() fixes the keyword vs. macro confusion that can arise with
 * computed case labels inside a conventional switch statement.
 */
#define case(x) } case 0 ? 0 x {
#define default(x) } default x {
