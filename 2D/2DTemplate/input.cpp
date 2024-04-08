//=============================================
//
//2DTemplate[input.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "input.h"
#include "Xinput.h"
//マクロ定義
#define NUM_KEY_MAX	(256)
#define NUM_MOUSE_MAX	(3)
//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;	//directInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL; //入力デバイスへのポインタ

//キーボード
BYTE g_aKeyStateTrigger[NUM_KEY_MAX]; //キーボードのトリガー情報
BYTE g_aKeyState[NUM_KEY_MAX]; //キーボードのプレス情報

//マウス
LPDIRECTINPUTDEVICE8 g_pDIMouse = NULL;	// マウスデバイス
DIMOUSESTATE g_zdiMouseStateTrigger;	// マウストリガー状態
DIMOUSESTATE g_zdiMouseState;			// マウスプレス状態
DIMOUSESTATE g_zdiMouseMove; //マウスムーブ
D3DXVECTOR3 g_MousePos;
D3DXVECTOR3 g_MouseMove;

//コントローラー
XINPUT_STATE g_joyKeyState; //ジョイパッドのプレス情報
XINPUT_STATE g_joyKeyStateTrigger; //ジョイパッドのトリガー情報
XINPUT_STATE g_joyKeyStateRepeat; //ジョイパッドのリピート情報
XINPUT_STATE g_ajoyKeyStateRelease; //コントローラーのリリース情報
XINPUT_STATE g_aJoypadCurrentTime; //コントローラーの現在の時間
XINPUT_STATE g_aJoypadExecLastTime; //コントローラーの最後に真を返した時間
XINPUT_STATE g_JoypadInput; //コントローラーの入力情報
D3DXVECTOR3 g_joyStickPos; //スティックの傾き
bool g_bAngle[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの入力情報
DWORD g_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの現在の時間
DWORD g_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの現在の時間
STICKINPUT g_stick; //スティックの入力情報
XINPUT_STATE g_XInput; //入力情報
XINPUT_VIBRATION g_JoypadMotor;
int g_nCntkey;
//=============================================
//キーボードの初期化処理
//=============================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイスの生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	//キーボードのアクセス権を獲得
	g_pDevKeyboard->Acquire();
	return S_OK;
}

//=============================================
//キーボードの終了処理
//=============================================
void UninitKeyboard(void)
{
	//入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================
//キーボードの更新処理
//=============================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX]; //入力情報
	int nCntKey;
	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			g_aKeyState[nCntKey] = aKeyState[nCntKey]; //キーボードのプレス情報を保存
		}
	}
	else
	{
		g_pDevKeyboard->Acquire(); //キーボードのアクセス権を獲得
	}
}

//=============================================
//キーボードの情報を取得
//=============================================
bool GetKeyboardPress(int nKey)
{
	return(g_aKeyState[nKey] & 0x80) != 0;
}
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) != 0;
}

//===========================================================================================================================================================================
//マウス
//===========================================================================================================================================================================
//=============================================
//マウスの初期化処理
//=============================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}
	//入力デバイスの生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDIMouse, NULL)))
	{
		return E_FAIL;
	}
	//データフォーマットを設定
	if (FAILED(g_pDIMouse->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}
	//協調モードを設定
	if (FAILED(g_pDIMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// デバイスの設定
	DIPROPDWORD diprop;
	g_MousePos = { 0.0f,0.0f,0.0f };
	g_MouseMove = { 0.0f,0.0f,0.0f };
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;


	if (FAILED(g_pDIMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		// デバイスの設定に失敗
		return E_FAIL;
	}

	//マウスのアクセス権を獲得
	g_pDevKeyboard->Acquire();
	return S_OK;
}

//=============================================
//マウスの終了処理
//=============================================
void UninitMouse(void)
{
	//入力デバイスの破棄
	if (g_pDIMouse != NULL)
	{
		g_pDIMouse->Unacquire();
		g_pDIMouse->Unacquire();
		g_pDIMouse = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}


//=============================================
//マウスの更新処理
//=============================================
void UpdateMouse(void)
{
	BYTE aMouseState[NUM_MOUSE_MAX]; //入力情報
	DIMOUSESTATE zdiMouseState;
	int nCntMouse;
	for (nCntMouse = 0; nCntMouse < NUM_MOUSE_MAX; nCntMouse++)
	{
		//入力デバイスからデータを取得
		if (SUCCEEDED(g_pDIMouse->GetDeviceState(sizeof(zdiMouseState), &zdiMouseState)))
		{

			g_zdiMouseStateTrigger.rgbButtons[nCntMouse] = (g_zdiMouseState.rgbButtons[nCntMouse] ^ zdiMouseState.rgbButtons[nCntMouse]) & zdiMouseState.rgbButtons[nCntMouse];
			g_zdiMouseState.rgbButtons[nCntMouse] = zdiMouseState.rgbButtons[nCntMouse]; //キーボードのプレス情報を保存
		}
		else
		{
			g_pDIMouse->Acquire(); //キーボードのアクセス権を獲得
		}
	}

	//ZeroMemory(&pMouseMove, sizeof(POINT));

	D3DXVECTOR3 OldMousePos = g_MousePos;

	POINT pMouseMove;

	GetCursorPos(&pMouseMove);

	g_MousePos.x = (float)pMouseMove.x;
	g_MousePos.y = (float)pMouseMove.y;

	g_MouseMove.x = g_MousePos.x - OldMousePos.x;
	g_MouseMove.y = g_MousePos.y - OldMousePos.y;
	g_MouseMove.z = g_MousePos.z - OldMousePos.z;

}

//=============================================
//キーボードの情報を取得
//=============================================
bool GetMousePress(int nKey)
{
	return(g_zdiMouseState.rgbButtons[nKey] & 0x80) != 0;
}
bool GetMouseTrigger(int nKey)
{
	return(g_zdiMouseStateTrigger.rgbButtons[nKey] & 0x80) != 0;
}
D3DXVECTOR3 GetMouseMove(void)
{
	return(g_MouseMove);
}



//===========================================================================================================================================================================
//PAD
//===========================================================================================================================================================================

//=============================================
//joyパッド初期化
//=============================================
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//メモリのクリア
	memset(&g_JoypadMotor, 0, sizeof(XINPUT_VIBRATION));

	//XInputのステートを設定(有効にする)
	XInputEnable(true);

	return S_OK;
}

//=============================================
//joyパッド終了
//=============================================
void UninitJoypad(void)
{
	//XInputのステートを設定(無効にする)
	XInputEnable(false);
}

//=============================================
// スティック
//=============================================

// スティックの入力を方向パッドフラグに変換
WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}

	return wButtons;
}

//=============================================
//ジョイパッドの更新処理
//=============================================
void UpdateJoypad(void)
{
	XINPUT_STATE joykeyState; //ジョイパッドの入力情報

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;
		WORD OldButton = g_joyKeyState.Gamepad.wButtons;
		g_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;    // トリガー処理
		g_ajoyKeyStateRelease.Gamepad.wButtons = ~Button & OldButton;    // リリース処理
		joykeyState.Gamepad.wButtons |= GetJoypadStick(g_joyKeyState.Gamepad.sThumbLX, g_joyKeyState.Gamepad.sThumbLY, JOYPAD_ZONE);

		// 現在の時間を取得する
		g_aJoypadCurrentTime.Gamepad.wButtons = timeGetTime();

		if (joykeyState.Gamepad.wButtons && ((g_aJoypadCurrentTime.Gamepad.wButtons - g_aJoypadExecLastTime.Gamepad.wButtons) > JOYPAD_SPEED))
		{
			// 最後に真を返した時間を保存
			g_aJoypadExecLastTime.Gamepad.wButtons = g_aJoypadCurrentTime.Gamepad.wButtons;

			// キーボードのリピート情報を保存
			g_joyKeyStateRepeat = joykeyState;
		}
		else
		{
			// キーボードのリピート情報を保存
			g_joyKeyStateRepeat.Gamepad.wButtons = 0;
		}

		g_joyKeyState = joykeyState;                // プレス処理
	}
}

//=====================================
//ジョイパッドのプレス情報を取得
//=====================================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//=====================================
//ジョイパッドのトリガー情報を取得
//=====================================
bool GetJoypadTrigger(JOYKEY key)
{
	return (g_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//=====================================
//ジョイパッドのリピート情報を取得
//=====================================
bool GetJoypadRepeat(JOYKEY key)
{
	//キーを押している間
	if (GetJoypadPress(key) == true)
	{
		if (GetJoypadTrigger(key) == true)
		{
			g_nCntkey = 0;
			return true;
		}

		g_nCntkey++; //押している間をカウント

		if (g_nCntkey >= JOYPAD_SPEED) //押し続ける間
		{
			g_nCntkey = 0;
			return true;
		}
	}
}

void UpdateStick(void)
{
	//キーボードの状態を取得
	if (XInputGetState(0, &g_XInput) == ERROR_SUCCESS)
	{
		for (int nCntStick = 0; nCntStick < STICKTYPE_MAX; nCntStick++)
		{
			float fX, fY; //スティックのX軸、Y軸

			switch (nCntStick)
			{
			case STICKTYPE_LEFT:
				fX = (GetXInputState()->Gamepad.sThumbLX);
				fY = (GetXInputState()->Gamepad.sThumbLY);
				break;
			case STICKTYPE_RIGHT:
				fX = (GetXInputState()->Gamepad.sThumbRX);
				fY = (GetXInputState()->Gamepad.sThumbRY);
				break;
			}

			//角度を取得
			g_stick.afAngle[nCntStick] = FindAngle(D3DXVECTOR3(fX, fY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;

			//スティックの倒し具合を取得
			g_stick.afTplDiameter[nCntStick] = fabsf(fX);

			if (g_stick.afTplDiameter[nCntStick] < fabsf(fY))
			{
				g_stick.afTplDiameter[nCntStick] = fabsf(fY);
			}

			g_stick.afTplDiameter[nCntStick] /= 32768.0f; //倒している状態の初期値

			//方向入力フラグを初期化
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				g_bAngle[nCntStick][nCntAngle] = false;
			}

			if (g_stick.afTplDiameter[nCntStick] > 0.1f)
			{
				//角度が四分割で上に位置する時、上フラグを真にする
				if ((g_stick.afAngle[nCntStick] < D3DX_PI * -0.75) || (g_stick.afAngle[nCntStick] > D3DX_PI * 0.75))
				{
					g_bAngle[nCntStick][STICKANGLE_UP] = true;
				}

				//角度が四分割で下に位置する時、下フラグを真にする
				else if ((g_stick.afAngle[nCntStick] > D3DX_PI * -0.25) && (g_stick.afAngle[nCntStick] < D3DX_PI * 0.25))
				{
					g_bAngle[nCntStick][STICKANGLE_DOWN] = true;
				}

				//角度が四分割で左に位置する時、左フラグを真にする
				else if ((g_stick.afAngle[nCntStick] > D3DX_PI * -0.75) && (g_stick.afAngle[nCntStick] < D3DX_PI * -0.25))
				{
					g_bAngle[nCntStick][STICKANGLE_LEFT] = true;
				}

				//角度が四分割で右に位置する時、右フラグを真にする
				else if ((g_stick.afAngle[nCntStick] > D3DX_PI * 0.25) && (g_stick.afAngle[nCntStick] < D3DX_PI * 0.75))
				{
					g_bAngle[nCntStick][STICKANGLE_RIGHT] = true;
				}
			}

			//角度に応じた入力処理
			for (int nCntAngle = 0; nCntAngle < STICKANGLE_MAX; nCntAngle++)
			{
				//スティックのトリガー情報を保存
				g_stick.abAngleTrigger[nCntStick][nCntAngle] = (g_stick.abAnglePress[nCntStick][nCntAngle] ^ g_bAngle[nCntStick][nCntAngle]) & g_bAngle[nCntStick][nCntAngle];

				//スティックのリリース情報を保存
				g_stick.abAngleRelease[nCntStick][nCntAngle] = (g_stick.abAnglePress[nCntStick][nCntAngle] ^ g_bAngle[nCntStick][nCntAngle]) & ~g_bAngle[nCntStick][nCntAngle];

				//現在の時間を取得
				g_aStickCurrentTime[nCntStick][nCntAngle] = timeGetTime();

				if (g_bAngle[nCntStick][nCntAngle] && ((g_aStickCurrentTime[nCntStick][nCntAngle] - g_aStickExecLastTime[nCntStick][nCntAngle]) > JOYPAD_SPEED))
				{
					//最後に真を返した時間を保存
					g_aStickExecLastTime[nCntStick][nCntAngle] = g_aStickCurrentTime[nCntStick][nCntAngle];

					//スティックのリピート情報を保存
					g_stick.abAngleRepeat[nCntStick][nCntAngle] = g_bAngle[nCntStick][nCntAngle];
				}
				else
				{
					//スティックのリピート情報を保存
					g_stick.abAngleRepeat[nCntStick][nCntAngle] = 0;
				}

				//スティックのプレス情報を保存
				g_stick.abAnglePress[nCntStick][nCntAngle] = g_bAngle[nCntStick][nCntAngle];
			}
		}
	}
}

//2点の角度を求める
float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos)
{
	float fAngle; //角度

	fAngle = atan2f(TargetPos.y - pos.y, TargetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1.0f;

	return fAngle;
}

// コントローラーの入力情報の取得
XINPUT_STATE* GetXInputState(void)
{
	return &g_XInput;
}

// スティックの入力情報を取得
STICKINPUT GetStick(void)
{
	return g_stick;
}