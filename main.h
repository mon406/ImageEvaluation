#pragma once

/* 使用ディレクトリ指定及び定義 */
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>			// 標準入出力
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>			// 新しいC++のデータ構造と算術ルーチン群
#include <opencv2/imgproc/imgproc.hpp>		// 新しいC++の画像処理関数群
#include <opencv2/highgui/highgui.hpp>		// 画像データのウィンドウ表示
#include <time.h>			// 時刻
//#include <cmath>			// 算術計算
//#include <cstdlib>			// 数値変換,疑似乱数
//#include <array>			// 配列arrayクラス
//#include <vector>			// 配列vectorクラス

using namespace std;
using namespace cv;
string win_src = "src";				// 入力画像ウィンドウ
string win_dst = "dst";				// 出力画像ウィンドウ

/* 入出力画像 */
Mat Image_src;				// 入力画像
Mat Image_src_gray;			// 入力画像(グレースケール)
Mat Image_dst;				// 出力画像

/* 定数 */
int MAX_INTENSE = 255;	// 最大色値
int WIDTH;				// 入力画像の横幅（ピクセル数）
int HEIGHT;				// 入力画像の縦幅（ピクセル数）
int MAX_DATA;			// 入力画像の総ピクセル数

/* 入出力関数 */
void Input_Image();			// 画像の入力
void Output_Image();		// 画像の出力
