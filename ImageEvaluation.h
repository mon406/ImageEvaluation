#ifndef __INCLUDED_H_ImageEvaluation__
#define __INCLUDED_H_ImageEvaluation__

#include "main.h"

/* 関数宣言 */
void checkMat(Mat& checkImg);			// Mat関数のサイズと型の確認
void checkMat_detail(Mat& checkImg);		// Mat関数のサイズと型の確認(詳細表示)

void Evaluation_MSE_PSNR_SSIM(Mat& Original, Mat& Inpaint);	// MSE&PSNR&SSIMによる画像評価
void SSIMcalc(double& ssim, Mat& image_1, Mat& image_2);


/* 関数 */

// Mat関数の確認
void checkMat(Mat& checkImg) {
	cout << "##############################" << endl;
	cout << " cols = " << checkImg.cols << endl;
	cout << " rows = " << checkImg.rows << endl;
	cout << " type = " << (
		checkImg.type() == CV_8UC1 ? "CV_8UC1" :
		checkImg.type() == CV_8UC3 ? "CV_8UC3" :
		checkImg.type() == CV_32FC1 ? "CV_32FC1" :
		checkImg.type() == CV_32FC3 ? "CV_32FC3" :
		checkImg.type() == CV_64FC1 ? "CV_64FC1" :
		checkImg.type() == CV_64FC2 ? "CV_64FC2" :
		checkImg.type() == CV_64FC3 ? "CV_64FC3" :
		"other"
		) << endl;
	cout << "##############################" << endl;
	cout << endl;
}

// Mat関数の確認(詳細表示)
void checkMat_detail(Mat& checkImg) {
	cout << "##############################" << endl;
	cout << " cols = " << checkImg.cols << endl;
	cout << " rows = " << checkImg.rows << endl;
	cout << " type = " << (
		checkImg.type() == CV_8UC1 ? "CV_8UC1" :
		checkImg.type() == CV_8UC3 ? "CV_8UC3" :
		checkImg.type() == CV_64FC1 ? "CV_64FC1" :
		checkImg.type() == CV_64FC2 ? "CV_64FC2" :
		checkImg.type() == CV_64FC3 ? "CV_64FC3" :
		"other"
		) << endl;
	cout << "##############################" << endl;
	cout << checkImg << endl;
	cout << endl;
}


// MSE&PSNR&SSIMによる画像評価
void Evaluation_MSE_PSNR_SSIM(Mat& Original, Mat& Inpaint) {
	double MSE = 0.0, PSNR = 0.0, SSIM = 0.0;
	Mat beforeIMG, afterIMG;
	Original.copyTo(beforeIMG);
	Inpaint.copyTo(afterIMG);

	double MSE_sum = 0.0;	// MSE値
	double image_cost;		// 画素値の差分
	int compare_size = 1, color_ind;
	int occ_pix_count = 0;

	if (Original.size() != Inpaint.size()) { cout << "ERROR! MSE_PSNR_SSIM() : Can't calculate because of wrong size." << endl; }
	else if (Original.channels() != Inpaint.channels()) { cout << "ERROR! MSE_PSNR_SSIM() : Can't calculate because of wrong channels." << endl; }
	else {
		if (Original.channels() == 3) {
			/* MSE計算(RGB) */
			for (int i = 0; i < Original.rows; i++) {
				for (int j = 0; j < Original.cols; j++) {
					image_cost = 0.0;
					color_ind = i * Original.cols * 3 + j * 3;
					for (int k = 0; k < 3; k++) {
						image_cost += pow((double)Inpaint.data[color_ind] - (double)Original.data[color_ind], 2.0);
						color_ind++;
					}
					MSE_sum += (double)image_cost;
					occ_pix_count++;
				}
			}
			compare_size = occ_pix_count * 3;
		}
		else if (Original.channels() == 1) {
			/* MSE計算(Grayscale) */
			for (int i = 0; i < Original.rows; i++) {
				for (int j = 0; j < Original.cols; j++) {
					image_cost = 0.0;
					color_ind = i * Original.cols + j;
					image_cost += pow((double)Inpaint.data[color_ind] - (double)Original.data[color_ind], 2.0);
					MSE_sum += (double)image_cost;
					occ_pix_count++;
				}
			}
			compare_size = occ_pix_count;
		}
		MSE = (double)MSE_sum / (double)compare_size;

		/* PSNR計算 */
		if (MSE == 0) { PSNR = -1; }
		else { PSNR = 20 * (double)log10(MAX_INTENSE) - 10 * (double)log10(MSE); }

		/* SSIM計算 */
		SSIMcalc(SSIM, beforeIMG, afterIMG);

		/* 評価結果表示 */
		cout << "--- 評価 ------------------------------------------" << endl;
		cout << " MSE  : " << MSE << endl;
		if (PSNR >= 0) { cout << " PSNR : " << PSNR << endl; }
		else { cout << " PSNR : inf" << endl; }
		cout << " SSIM : " << SSIM << endl;
		cout << "---------------------------------------------------" << endl;
	}
	cout << endl;
}

// SSIM算出
void SSIMcalc(double& ssim, Mat& image_1, Mat& image_2) {
	const double C1 = pow(0.01 * 255, 2), C2 = pow(0.03 * 255, 2);

	Mat I1, I2;
	image_1.convertTo(I1, CV_32F);	// cannot calculate on one byte large values
	image_2.convertTo(I2, CV_32F);
	Mat I2_2 = I2.mul(I2);			// I2^2
	Mat I1_2 = I1.mul(I1);			// I1^2
	Mat I1_I2 = I1.mul(I2);			// I1 * I2

	Mat mu1, mu2;   // PRELIMINARY COMPUTING
	GaussianBlur(I1, mu1, Size(11, 11), 1.5);
	GaussianBlur(I2, mu2, Size(11, 11), 1.5);
	Mat mu1_2 = mu1.mul(mu1);
	Mat mu2_2 = mu2.mul(mu2);
	Mat mu1_mu2 = mu1.mul(mu2);

	Mat sigma1_2, sigma2_2, sigma12;
	GaussianBlur(I1_2, sigma1_2, Size(11, 11), 1.5);
	sigma1_2 -= mu1_2;
	GaussianBlur(I2_2, sigma2_2, Size(11, 11), 1.5);
	sigma2_2 -= mu2_2;
	GaussianBlur(I1_I2, sigma12, Size(11, 11), 1.5);
	sigma12 -= mu1_mu2;

	Mat t1, t2, t3;
	t1 = 2 * mu1_mu2 + C1;
	t2 = 2 * sigma12 + C2;
	t3 = t1.mul(t2);              // t3 = ((2*mu1_mu2 + C1).*(2*sigma12 + C2))
	t1 = mu1_2 + mu2_2 + C1;
	t2 = sigma1_2 + sigma2_2 + C2;
	t1 = t1.mul(t2);               // t1 =((mu1_2 + mu2_2 + C1).*(sigma1_2 + sigma2_2 + C2))

	Mat ssim_map;
	divide(t3, t1, ssim_map);      // ssim_map =  t3./t1;
	Scalar mssim = mean(ssim_map); // mssim = average of ssim map

	/* SSIM平均(RGB or Gray) */
	double SSIM;
	SSIM = (double)mssim[0] + (double)mssim[1] + (double)mssim[2];
	if (image_1.channels() == 3) { SSIM = (double)SSIM / 3.0; }
	ssim = (double)SSIM;
}

#endif
