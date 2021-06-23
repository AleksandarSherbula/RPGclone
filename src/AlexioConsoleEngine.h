#ifndef ALEXIOCONSOLEENGINE_H
#define ALEXIOCONSOLEENGINE_H

#include <fcntl.h>
#include <io.h>
#include <string>
#include <cmath>
#include <memory>
#include <algorithm>

#include <Windows.h>

namespace alexio
{
	enum COLOR
	{
		FG_BLACK = 0x0000,
		FG_BLUE = 0x0001,
		FG_GREEN = 0x0002,
		FG_CYAN = 0x0003,
		FG_RED = 0x0004,
		FG_MAGENTA = 0x0005,
		FG_YELLOW = 0x0006,
		FG_LIGHT_GREY = 0x0007,
		FG_GREY = 0x0008,
		FG_LIGHT_BLUE = 0x0009,
		FG_LIGHT_GREEN = 0x000A,
		FG_LIGHT_CYAN = 0x000B,
		FG_LIGHT_RED = 0x000C,
		FG_LIGHT_MAGENTA = 0x000D,
		FG_LIGHT_YELLOW = 0x000E,
		FG_WHITE = 0x000F,
		BG_BLACK = 0x0000,
		BG_BLUE = 0x0010,
		BG_GREEN = 0x0020,
		BG_CYAN = 0x0030,
		BG_RED = 0x0040,
		BG_MAGENTA = 0x0050,
		BG_YELLOW = 0x0060,
		BG_LIGHT_GREY = 0x0070,
		BG_GREY = 0x0080,
		BG_LIGHT_BLUE = 0x0090,
		BG_LIGHT_GREEN = 0x00A0,
		BG_LIGHT_CYAN = 0x00B0,
		BG_LIGHT_RED = 0x00C0,
		BG_LIGHT_MAGENTA = 0x00D0,
		BG_LIGHT_YELLOW = 0x00E0,
		BG_WHITE = 0x00F0,
	};

	enum Key
	{
		BACK = VK_BACK,
		TAB = VK_TAB,
		CLEAR = VK_CLEAR,
		RETURN = VK_RETURN,
		SHIFT = VK_SHIFT,
		CONTROL = VK_CONTROL,
		MENU = VK_MENU,
		PAUSE = VK_PAUSE,
		CAPITAL = VK_CAPITAL,

		KANA = VK_KANA,
		HANGEUL = VK_HANGEUL,
		HANGUL = VK_HANGUL,
		IME_ON = VK_IME_ON,
		JUNJA = VK_JUNJA,
		FINAL = VK_FINAL,
		HANJA = VK_HANJA,
		KANJI = VK_KANJI,
		IME_OFF = VK_IME_OFF,

		ESCAPE = VK_ESCAPE,

		CONVERT = VK_CONVERT,
		NONCONVERT = VK_NONCONVERT,
		ACCEPT = VK_ACCEPT,
		MODECHANGE = VK_MODECHANGE,

		SPACE = VK_SPACE,
		PRIOR = VK_PRIOR,
		NECT = VK_NEXT,
		END = VK_END,
		HOME = VK_HOME,
		LEFT = VK_LEFT,
		UP = VK_UP,
		RIGHT = VK_RIGHT,
		DOWN = VK_DOWN,
		SELECT = VK_SELECT,
		PRINT = VK_PRINT,
		EXECUTE = VK_EXECUTE,
		SNAPSHOT = VK_SNAPSHOT,
		INSERT = VK_INSERT,
		Delete = VK_DELETE,	// DELETE is a already taken macro :/
		HELP = VK_HELP,

        NUM0 = VK_NUMPAD0,
        NUM1 = VK_NUMPAD1,
        NUM2 = VK_NUMPAD2,
        NUM3 = VK_NUMPAD3,
        NUM4 = VK_NUMPAD4,
        NUM5 = VK_NUMPAD5,
        NUM6 = VK_NUMPAD6,
        NUM7 = VK_NUMPAD7,
        NUM8 = VK_NUMPAD8,
        NUM9 = VK_NUMPAD9,
        MULTIPLY = VK_MULTIPLY,
        ADD = VK_ADD,
        SEPARATOR = VK_SEPARATOR,
        SUBTRACT = VK_SUBTRACT,
        DECIMAL = VK_DECIMAL,
        DIVIDE = VK_DIVIDE,
        F1 = VK_F1,
        F2 = VK_F2,
        F3 = VK_F3,
        F4 = VK_F4,
        F5 = VK_F5,
        F6 = VK_F6,
        F7 = VK_F7,
        F8 = VK_F8,
        F9 = VK_F9,
        F10 = VK_F10,
        F11 = VK_F11,
        F12 = VK_F12,
        F13 = VK_F13,
        F14 = VK_F14,
        F15 = VK_F15,
        F16 = VK_F16,
        F17 = VK_F17,
        F18 = VK_F18,
        F19 = VK_F19,
        F20 = VK_F20,
        F21 = VK_F21,
        F22 = VK_F22,
        F23 = VK_F23,
        F24 = VK_F24,

		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A
	};


	struct vec2
	{
		int x;
		int y;

		inline vec2() : x(0), y(0) {}
		inline vec2(int value) : x(value), y(value) {}
		inline vec2(int x, int y) : x(x), y(y) {}

		inline vec2 operator+(int scaler) { return vec2(this->x + scaler, this->y + scaler); }
		inline vec2 operator-(int scaler) { return vec2(this->x - scaler, this->y - scaler); }
		inline vec2 operator*(int scaler) { return vec2(this->x * scaler, this->y * scaler); }
		inline vec2 operator/(int scaler) { return vec2(this->x / scaler, this->y / scaler); }

		inline vec2 operator+(const vec2& other) { return vec2(this->x + other.x, this->y + other.y); }
		inline vec2 operator-(const vec2& other) { return vec2(this->x - other.x, this->y - other.y); }

		inline bool operator==(const vec2& other) { return (x == other.x && y == other.y); }
		inline bool operator!=(const vec2& other) { return (x != other.x || y != other.y); }

		inline vec2& operator+=(int scaler) { this->x += scaler; this->y += scaler; return *this; }
		inline vec2& operator-=(int scaler) { this->x -= scaler; this->y -= scaler; return *this; }
		inline vec2& operator*=(int scaler) { this->x *= scaler; this->y *= scaler; return *this; }
		inline vec2& operator/=(int scaler) { this->x /= scaler; this->y /= scaler; return *this; }

		inline vec2& operator+=(const vec2& other) { this->x += other.x; this->y += other.y; return *this; }
		inline vec2& operator-=(const vec2& other) { this->x -= other.x; this->y -= other.y; return *this; }
		const std::string str() const { return std::string("(") + std::to_string(this->x) + "," + std::to_string(this->y) + ")"; }

		inline int length() { return std::sqrt(x * x + y * y); }
		inline int length2() { return x * x + y * y; }
		inline int dot(const vec2& other) { return this->x * other.x + this->y * other.y; }
	};


	class ConsoleEngine
	{
	private:
		struct sKeyState
		{
			bool bIsPressed;
			bool bIsUp;
			bool bIsDown;
		} m_keys[256] = { 0 };

		short m_keyOldState[256] = { 0 };
		short m_keyNewState[256] = { 0 };

		HANDLE m_hOut;
		HANDLE m_hIn;
		HANDLE m_hOutOriginal;
		SMALL_RECT m_rectWindow;
		CHAR_INFO* mCharBuffer;
		bool mIsRunning;
	protected:
		std::wstring sAppName;
		int nConsoleScreenWidth;
		int nConsoleScreenHeight;
	public:
		ConsoleEngine();
		~ConsoleEngine();
	public:
		bool CreateConsole();
		void Run();

		inline bool GetKeyPressed(int key) { return m_keys[key].bIsPressed; }
		inline bool GetKeyUp(int key) { return m_keys[key].bIsUp; }
		inline bool GetKeyDown(int key) { return m_keys[key].bIsDown; }		

		void ErrorInfo(const std::wstring& msg);
		void ErrorMessageBox(const std::wstring& msg);
	private:
		void UpdateEngine();
	protected:

		void Clear();

		void DrawChar(const vec2& pos, char c, int color = FG_WHITE);
		void DrawString(const vec2& pos, const std::string& str, int color = FG_WHITE);
		void DrawWideString(const vec2& pos, const std::wstring& str, int color = FG_WHITE);
	protected:
		virtual bool Start() = 0;
		virtual bool Update() = 0;

	};
}

#ifdef ALEXIO_CONSOLE_APP
#undef ALEXIO_CONSOLE_APP

namespace alexio
{
	ConsoleEngine::ConsoleEngine()
	{
		m_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		m_hIn = GetStdHandle(STD_INPUT_HANDLE);

		memset(m_keyNewState, 0, 256 * sizeof(short));
		memset(m_keyOldState, 0, 256 * sizeof(short));
		memset(m_keys, 0, 256 * sizeof(sKeyState));

		nConsoleScreenWidth = 80;
		nConsoleScreenHeight = 30;

		sAppName = L"Console App";	
	}

	ConsoleEngine::~ConsoleEngine()
	{
		SetConsoleActiveScreenBuffer(m_hOutOriginal);
		delete[] mCharBuffer;
	}

	bool ConsoleEngine::CreateConsole()
	{
		_setmode(_fileno(stdout), _O_U16TEXT);	

		if (m_hOut == INVALID_HANDLE_VALUE)
		{
			ErrorMessageBox(L"Incorrect Handle");
			return false;
		}

		if (m_hIn == INVALID_HANDLE_VALUE)
		{
			ErrorMessageBox(L"Incorrect Handle");
			return false;
		}		

		m_rectWindow = { 0, 0, 1, 1 };
		SetConsoleWindowInfo(m_hOut, TRUE, &m_rectWindow);

		COORD coord = { (short)nConsoleScreenWidth, (short)nConsoleScreenHeight };
		if (!SetConsoleScreenBufferSize(m_hOut, coord))
			ErrorInfo(L"SetConsoleScreenBufferSize");

		// Assign screen buffer to the console
		if (!SetConsoleActiveScreenBuffer(m_hOut))
			ErrorInfo(L"SetConsoleActiveScreenBuffer");

		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = FALSE;
		SetConsoleCursorInfo(m_hOut, &info);

		// Get screen buffer info and check the maximum allowed window size. Return
		// error if exceeded, so user knows their dimensions/fontsize are too large
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(m_hOut, &csbi))
		{
			ErrorInfo(L"GetConsoleScreenBufferInfo");
			return false;
		}
		if (nConsoleScreenWidth > csbi.dwMaximumWindowSize.X)
		{
			ErrorMessageBox(L"Screen Width Too Big");
			return false;
		}
		else if (nConsoleScreenWidth < 20)
		{
			ErrorMessageBox(L"Screen Width Too Small");
			return false;
		}
		if (nConsoleScreenHeight > csbi.dwMaximumWindowSize.Y)
		{
			ErrorMessageBox(L"Screen Height Too Big");
			return false;
		}
		else if (nConsoleScreenHeight < 20)
		{
			ErrorMessageBox(L"Screen Height Too Small");
			return false;
		}

		m_rectWindow = { 0, 0, (short)nConsoleScreenWidth - 1, (short)nConsoleScreenHeight - 1 };
		if (!SetConsoleWindowInfo(m_hOut, TRUE, &m_rectWindow))
		{
			ErrorMessageBox(L"SetConsoleWindowInfo's parameter are incorrect");
			return false;
		}

		if (!SetConsoleMode(m_hIn, ENABLE_WINDOW_INPUT))
		{
			ErrorInfo(L"SetConsoleMode for Window Input");
			return false;
		}

		mCharBuffer = new CHAR_INFO[nConsoleScreenWidth * nConsoleScreenHeight];
		memset(mCharBuffer, 0, sizeof(CHAR_INFO) * nConsoleScreenWidth * nConsoleScreenHeight);

		return true;
	}

	void ConsoleEngine::Run()
	{
		mIsRunning = true;

		if (!Start())
		{
			mIsRunning = false;
			return;
		}

		UpdateEngine();
	}

	void ConsoleEngine::UpdateEngine()
	{
		while (mIsRunning)
		{
			// Handle Keyboard Input
			for (int i = 0; i < 256; i++)
			{
				m_keyNewState[i] = GetKeyState(i);

				m_keys[i].bIsPressed = false;
				m_keys[i].bIsUp = false;

				if (m_keyNewState[i] != m_keyOldState[i])
				{
					if (m_keyNewState[i] & 0x8000)
					{
						m_keys[i].bIsPressed = !m_keys[i].bIsDown;
						m_keys[i].bIsDown = true;
					}
					else
					{
						m_keys[i].bIsUp = true;
						m_keys[i].bIsDown = false;
					}
				}

				m_keyOldState[i] = m_keyNewState[i];
			}

			if (!Update())
				mIsRunning = false;

			SetConsoleTitle(sAppName.c_str());
			WriteConsoleOutput(m_hOut, mCharBuffer, { (short)nConsoleScreenWidth, (short)nConsoleScreenHeight }, { 0,0 }, &m_rectWindow);
		}
	}

	void ConsoleEngine::Clear()
	{
		for (int i = 0; i < nConsoleScreenWidth * nConsoleScreenHeight; i++)
		{
			mCharBuffer[i].Char.UnicodeChar = ' ';
			mCharBuffer[i].Attributes = FG_BLACK;
		}
	}

	void ConsoleEngine::DrawChar(const vec2& pos, char c, int color)
	{
		if (pos.x >= 0 && pos.x < nConsoleScreenWidth && pos.y >= 0 && pos.y < nConsoleScreenHeight)
		{
			mCharBuffer[pos.y * nConsoleScreenWidth + pos.x].Char.UnicodeChar = c;
			mCharBuffer[pos.y * nConsoleScreenWidth + pos.x].Attributes = color;
		}
	}

	void ConsoleEngine::DrawString(const vec2& pos, const std::string& str, int color)
	{
		if (pos.x >= 0 && pos.x < nConsoleScreenWidth && pos.y >= 0 && pos.y < nConsoleScreenHeight &&
			pos.x + (str.size() - 1) < nConsoleScreenWidth)
		{
			for (int i = 0; i < str.size(); i++)
			{
				mCharBuffer[pos.y * nConsoleScreenWidth + pos.x + i].Char.UnicodeChar = str[i];
				mCharBuffer[pos.y * nConsoleScreenWidth + pos.x + i].Attributes = color;
			}
		}
	}

	void ConsoleEngine::DrawWideString(const vec2& pos, const std::wstring& str, int color)
	{
		if (pos.x >= 0 && pos.x < nConsoleScreenWidth && pos.y >= 0 && pos.y < nConsoleScreenHeight &&
			pos.x + (str.size() - 1) < nConsoleScreenWidth)
		{
			for (int i = 0; i < str.size(); i++)
			{
				mCharBuffer[pos.y * nConsoleScreenWidth + pos.x + i].Char.UnicodeChar = str[i];
				mCharBuffer[pos.y * nConsoleScreenWidth + pos.x + i].Attributes = color;
			}
		}
	}

	void ConsoleEngine::ErrorInfo(const std::wstring& msg)
	{
		wchar_t buf[256];
		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), buf, 256, NULL);
		SetConsoleActiveScreenBuffer(m_hOutOriginal);
		wprintf(L"ERROR WITH %s\n\t%s\n", msg.c_str(), buf);
	}

	void ConsoleEngine::ErrorMessageBox(const std::wstring& msg)
	{
		MessageBox(NULL, msg.c_str(), L"ERROR!!!", MB_OK);
		SetConsoleActiveScreenBuffer(m_hOutOriginal);
	}

}
#endif // CONSOLE_ENGINE_APP

#endif // !ALEXIOCONSOLEENGINE_H