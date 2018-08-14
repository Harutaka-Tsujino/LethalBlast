﻿/**
* @file DX9Lib.h
* @brief DirectX9のライブラリのヘッダー
* @author Harutaka Tsujino
* @date 22/07/2018
*/

#pragma once

#include <windows.h>
#include <stdio.h>
#include<d3dx9.h>
#include <dinput.h>
#include <memory.h>
#include "DX9Lib.h"

#pragma comment(lib,"d3dx9d.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"DX9Lib/DirectX9Library.lib")


#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720

/** @def
* LPDIRECTINPUTDEVICE8の変数g_pDirectInputDeviceの要素数に用いる
*/

#define KEY_AND_MOUSE 2

/** @def
* 安全にメモリ開放をするためのRelease関数をアドレスを渡すだけで呼べるようにする
*/
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

/** @def
* ポリゴンの頂点の設定
*/
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

typedef LPDIRECT3DTEXTURE9 TEXTUREID;
typedef LPD3DXFONT FONTID;

/**
* @enum RENDER_FUNC_RETURN_VAL
* 描画関係の関数の戻り値
*/
enum RENDER_FUNC_RETURN_VAL
{
	//! 関数正常終了
	FUNC_OK,
	
	//! テクスチャの生成失敗
	CREATE_TEX_ERR,
	
	//! テクスチャの貼り付け失敗
	SET_TEX_ERR,
	
	//! 画像の描画失敗
	DRAW_IMAGE_ERR,
	
	//! フォントの生成失敗
	CREATE_FONT_ERR,

	//! テキストの描画失敗
	DRAW_TEXT_ERR,
};

/**
* @enum INPUT_DEVICE
* 入力デバイス入力状態の取得に使う
*/
enum INPUT_DEVICE
{
	//! キーボード
	 KEY,

	 //! マウスとキーボード
	 MOUSE
};

/**
* @fn
* @brief ウィンドウを生成し引数に渡した関数を呼び出し続ける関数
* @param (hInst) HINSTANCE インスタンスハンドル
* @param (appName) const CHAR * アプリケーションの名前の先頭アドレス
* @param (func) VOID(*func)(VOID) リピートする関数のポインタ
* @param (displayWidth) INT ディスプレイの横幅 
* @param (displayHeight) INT ディスプレイの縦幅 
* @param (cullPolygon) BOOL ポリゴンの裏面を描画するかどうか デフォルトで TRUE
* @return INT MSG構造体のメンバwParam
* @detail ウィンドウの設定および作成を行い,Direct3Dオブジェクト,デバイス,ダイレクトインプットの初期化\n
*		  FPSを調整しながらメッセージループの中で,キーボードとマウスの入力状態取得,画面の削除,描画の準備,引数で渡された関数の呼び出し,\n 
*		  描画の終了宣言,バックバッファーに描画が行われたことの伝達,キーボードとマウスの入力状態の保存を行う
*/
INT CreateWindowAndRepeatToControlAndRender(HINSTANCE hInst, const CHAR *appName, VOID(*func)(VOID), 
	INT displayWidth = 1280, INT displayHeight = 720, BOOL cullPolygon = TRUE);

/**
* @fn
* @brief ウィンドウの登録および作成
* @param (hWnd) HWND * ウィンドウハンドル
* @param (msg) MSG * メッセージ構造体のアドレス
* @param (hInst) HINSTANCE インスタンスハンドル
* @param (appName) const CHAR * アプリケーションの名前の先頭アドレス
* @param (displayWidth) INT ディスプレイの横幅
* @param (displayHeight) INT ディスプレイの縦幅
* @return なし
* @detail wndclass構造体の初期化と登録,ウィンドウの生成,ウィンドウを表示することの設定,ウィンドウの更新をする設定\n
*		  MSG構造体のクリアを行う
*/
VOID CreateWindowOverall(HWND *hWnd, MSG *msg, HINSTANCE hInst, const CHAR *appName, INT displayWidth, INT displayHeight);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

INT ConfirmMessage(MSG *msg);

/**
* @enum COORDINATEFPS_ACTION
* CoordinateFPSの引数action
*/
enum COORDINATEFPS_ACTION
{
	//! フレーム数をチェックする
	CHECK_FPS,

	//! 現在の時間を更新する
	UPDATE_TIME
};

INT CoordinateFPS(INT action, UINT frame = 60);

HRESULT InitDirect3D(VOID);

VOID SetBuckBufferOverall(VOID);

HRESULT InitDirect3DDevice(HWND hWnd, BOOL cullPolygon);

VOID SetRenderStateOverall(BOOL cullPolygon);

VOID SetTextureStageStateOverall(VOID);

HRESULT InitDinput(HWND hWnd);

VOID PrepareRender(VOID);

VOID CleanUpRender(VOID);

VOID GetKeyInfo(VOID);

VOID UpdatePrevKeyInfo(VOID);

VOID GetMouseInfo(HWND hWnd);

VOID UpdatePrevMouseInfo(VOID);

//VOID SetCamera(VOID);

/**
* @struct ImageState
* 画像の位置と幅を保持する
*/
typedef struct
{
	//! 画像の中心のx座標
	FLOAT m_x;

	//! 画像の中心のy座標
	FLOAT m_y;

	//! 画像の中心からx方向の幅
	FLOAT m_scaleX;

	//! 画像の中心からy方向の幅
	FLOAT m_scaleY;

}ImageState;

/**
* @struct CustomVertex
* ポリゴンの頂点の位置と重みの逆数と色とテクスチャの貼り付け位置を保持する
*/
typedef struct
{
	//! 頂点のx座標
	FLOAT m_x;

	//! 頂点のy座標
	FLOAT m_y;

	//! 頂点のz座標
	FLOAT m_z;

	//! 頂点の重みの逆数
	FLOAT m_rhw;

	//! 頂点のカラー(ARBG)
	DWORD m_color;

	//! テクスチャのx座標の貼り付け位置
	FLOAT m_tu;

	//! テクスチャのy座標の貼り付け位置
	FLOAT m_tv;

}CustomVertex;

/**
* @struct KeyState
* キーボードの入力状態を保持する
*/
typedef struct
{
	//! 現在でフレームのキーボードのキーが押されていた場合上位ビットが立つ
	BYTE diks[256];

	//! 前回のでフレームのキーボードのキーが押されていた場合上位ビットが立つ
	BYTE prevDiks[256];

	//! キーボードのキーが押された瞬間のフレームだけTRUE
	BOOL keyPush[256];

	//! キーボードのキーが押され続けられている間TRUE
	BOOL keyHold[256];

	//! キーボードのキーが離された瞬間のフレームだけTRUE
	BOOL keyRelease[256];

	//! キーボードのキーが前回と現在のフレームで押されていない間TRUE
	BOOL keyUninput[256];

}KeyState;

//! キーボードの入力状態
extern KeyState g_keyState;

/**
* @struct MouseState
* マウスのカーソルの位置ボタンの入力状態を保持する
*/
typedef struct
{
	//! 現在のフレームでの前回のカーソル位置からの相対位置とボタンの入力状態
	DIMOUSESTATE directInputMouseState;

	//! 前回のフレームでの前回のカーソル位置からの相対位置とボタンの入力状態
	DIMOUSESTATE prevDirectInputMouseState;

	//! カーソルの絶対座標
	POINT absolutePos;

	//! マウスのボタンが押された瞬間のフレームだけTRUE
	BOOL mousePush[4];

	//! マウスのボタンが押され続けられている間TRUE
	BOOL mouseHold[4];

	//! マウスのボタンが離された瞬間のフレームだけTRUE
	BOOL mouseRelease[4];

	//! マウスのボタンが前回と現在のフレームで押されていない間TRUE
	BOOL mouseUninput[4];

}MouseState;

//! マウスのカーソル位置ボタンの入力状態
extern MouseState g_mouseState;

#define RECT_VERTEX_NUM 4

//startPosTuTv,scaleTuTvなどは画像の座標,scaleImageは画像のサイズ
VOID CustomImageVerticies(CustomVertex *pCustomVertex, FLOAT posX, FLOAT posY, FLOAT scaleX, FLOAT scaleY,
	DWORD color = 0xFFFFFFFF, FLOAT startPosTu = 0.f, FLOAT startPosTv = 0.f, FLOAT scaleTu = 1.f, FLOAT scaleTv = 1.f, FLOAT scaleImageX = 1.f, FLOAT scaleImageY = 1.f);

//startPosTuTv,scaleTuTvなどは画像の座標,scaleImageは画像のサイズ
VOID SetImageTuTv(CustomVertex *dest, CustomVertex *src, FLOAT startPosTu, FLOAT startPosTv, FLOAT scaleTu, FLOAT scaleTv, FLOAT scaleImageX, FLOAT scaleImageY);

DWORD GetColor(UCHAR alpha, UCHAR red, UCHAR blue, UCHAR green);

/**
* @enum AXIS
* RotateImageDegの引数axis(回転軸)
*/
enum AXIS
{
	//! x軸
	X_AXIS,

	//! y軸
	Y_AXIS,

	//! z軸
	Z_AXIS
};

//axisは回転軸,realativeCenterPosXYは画像の回転座標で画像の相対座標を入れる
VOID RotateImageDeg(CustomVertex *dest, CustomVertex *src, FLOAT degree, INT axis = Z_AXIS, FLOAT relativeCenterPosX = 0.f, FLOAT relativeCenterPosY = 0.f);

//moveXY画像の移動量
VOID MoveImage(CustomVertex *dest, CustomVertex *src, FLOAT moveX, FLOAT moveY);

//circulationCenterPosXYは円運動の中心座標
VOID CirculateImageDeg(CustomVertex *dest, CustomVertex *src, FLOAT degree, FLOAT circulationCenterPosX, FLOAT circulationCenterPosY);

//expansionRateXYは画像の縮小率 2.fなら二倍になる
VOID RescaleImage(CustomVertex *dest, CustomVertex *src, FLOAT expansionRateX, FLOAT expansionRateY);

RENDER_FUNC_RETURN_VAL RoadTexture(const CHAR *pTexturePass, TEXTUREID *pTextureId);

RENDER_FUNC_RETURN_VAL DrawImage(CustomVertex *pCustomVertex, TEXTUREID textureId);

//thicknessは文字の太さ
RENDER_FUNC_RETURN_VAL SetFont(INT scaleX, UINT scaleY, const CHAR *pFontType, FONTID *pFontId, UINT thickness, INT charSet = DEFAULT_CHARSET);

//pTextは文字列の先頭アドレス
RENDER_FUNC_RETURN_VAL WriteText(INT posX, INT posY, const CHAR *pText, UINT format, FONTID pFontId, DWORD color = 0xFFFFFFFF);
