#include "main.h"
#include "ImageEvaluation.h"
//#include "ImageHistgram.h"		// ヒストグラム取得


int main() {
	/* 画像の入力 */
	Input_Image();

	clock_t start, end;	// 処理時間表示用
	start = clock();
	//--- 画像処理 -------------------------------------------------------------------------------
	Image_src.copyTo(Image_dst);
	GaussianBlur(Image_src, Image_dst, Size(5, 5), 0);	// ガウシアンフィルター
	checkMat(Image_dst);								// Mat関数のサイズと型の確認

	//DrawHist(Image_src);			// ヒストグラム取得
	//DrawHist(Image_src, Image_dst);		// ヒストグラム取得
	//--------------------------------------------------------------------------------------------
	end = clock();
	double time_difference = (double)end - (double)start;
	const double time = time_difference / CLOCKS_PER_SEC * 1000.0;
	cout << "time : " << time << " [ms]" << endl;
	cout << endl;

	/* 画像の評価 */
	cout << "出力画像 と 入力画像" << endl;				// 実行確認用
	Evaluation_MSE_PSNR_SSIM(Image_src, Image_dst);

	/* 画像の出力 */
	Output_Image();

	return 0;
}

// 画像の入力
void Input_Image() {
	string file_src = "src.jpg";	// 入力画像のファイル名
	Image_src = imread(file_src, 1);		// 入力画像（カラー）の読み込み
	Image_src_gray = imread(file_src, 0);	// 入力画像（グレースケール）の読み込み

	/* パラメータ定義 */
	WIDTH = Image_src.cols;
	HEIGHT = Image_src.rows;
	MAX_DATA = WIDTH * HEIGHT;
	cout << "INPUT : WIDTH = " << WIDTH << " , HEIGHT = " << HEIGHT << endl;
	cout << endl;

	Image_dst = Mat(Size(WIDTH, HEIGHT), CV_8UC3);	// 出力画像（カラー）の初期化
}
// 画像の出力
void Output_Image() {
	string file_dst = "dst.jpg";	// 出力画像のファイル名

	/* ウィンドウ生成 */
	namedWindow(win_src, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	/* 画像の表示 & 保存 */
	imshow(win_src, Image_src);				// 入力画像を表示
	imshow(win_dst, Image_dst);				// 出力画像を表示
	imwrite(file_dst, Image_dst);			// 処理結果の保存

	waitKey(0); // キー入力待ち
}
