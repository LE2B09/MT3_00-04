#include <Novice.h>
#include <cmath>
#include "Vector3.h"

using namespace std;

//間隔
static const int kRowHeight = 20;
static const int kColumnWidth = 60;

struct Matrix4x4
{
	float m[4][4];
};

//行列の積
static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result{};
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}
	return result;
}

//X軸の回転行列
static Matrix4x4 MakeRotateXMatrix(float radian)
{
	Matrix4x4 result{};
	result.m[0][0] = 1.0f;
	result.m[1][1] = cos(radian);
	result.m[1][2] = sin(radian);
	result.m[2][1] = -sin(radian);
	result.m[2][2] = cos(radian);
	result.m[3][3] = 1.0f;
	return result;
}

//Y軸の回転行列
static Matrix4x4 MakeRotateYMatrix(float radian)
{
	Matrix4x4 result{};
	result.m[0][0] = cos(radian);
	result.m[0][2] = -sin(radian);
	result.m[1][1] = 1.0f;
	result.m[2][0] = sin(radian);
	result.m[2][2] = cos(radian);
	result.m[3][3] = 1.0f;
	return result;
}

//Z軸の回転行列
static Matrix4x4 MakeRotateZMatrix(float radian)
{
	Matrix4x4 result{};
	result.m[0][0] = cos(radian);
	result.m[0][1] = sin(radian);
	result.m[1][0] = -sin(radian);
	result.m[1][1] = cos(radian);
	result.m[2][2] = 1.0f;
	result.m[3][3] = 1.0f;
	return result;
}

//行列のコメント
static void MatrixScreenPrint(int x, int y, Matrix4x4 matrix, const char* label)
{
	for (int row = 0; row < 4; row++)
	{
		for (int colum = 0; colum < 4; colum++)
		{
			Novice::ScreenPrintf(x + colum * kColumnWidth, y + row * kRowHeight + 20, "%6.02f", matrix.m[row][colum]);
		}
	}
	Novice::ScreenPrintf(x, y, "%s", label);
}

const char kWindowTitle[] = "LC1C_11_キクチ_ケンタ_提出用課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 rotate = { 0.4f,1.43f,-0.8f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		//MakeRotateMatrix関数の（x, y, z）それぞれを呼び出す
		Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
		Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
		Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);

		//（x, y, z）を合わせる
		Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrint(0, 0, rotateXMatrix, "rotateXMatrix");
		MatrixScreenPrint(0, kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		MatrixScreenPrint(0, kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");
		MatrixScreenPrint(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
