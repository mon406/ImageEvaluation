#include "main.h"
#include "ImageEvaluation.h"
//#include "ImageHistgram.h"		// �q�X�g�O�����擾


int main() {
	/* �摜�̓��� */
	Input_Image();

	clock_t start, end;	// �������ԕ\���p
	start = clock();
	//--- �摜���� -------------------------------------------------------------------------------
	Image_src.copyTo(Image_dst);
	GaussianBlur(Image_src, Image_dst, Size(5, 5), 0);	// �K�E�V�A���t�B���^�[
	checkMat(Image_dst);								// Mat�֐��̃T�C�Y�ƌ^�̊m�F

	//DrawHist(Image_src);			// �q�X�g�O�����擾
	//DrawHist(Image_src, Image_dst);		// �q�X�g�O�����擾
	//--------------------------------------------------------------------------------------------
	end = clock();
	double time_difference = (double)end - (double)start;
	const double time = time_difference / CLOCKS_PER_SEC * 1000.0;
	cout << "time : " << time << " [ms]" << endl;
	cout << endl;

	/* �摜�̕]�� */
	cout << "�o�͉摜 �� ���͉摜" << endl;				// ���s�m�F�p
	Evaluation_MSE_PSNR_SSIM(Image_src, Image_dst);

	/* �摜�̏o�� */
	Output_Image();

	return 0;
}

// �摜�̓���
void Input_Image() {
	string file_src = "src.jpg";	// ���͉摜�̃t�@�C����
	Image_src = imread(file_src, 1);		// ���͉摜�i�J���[�j�̓ǂݍ���
	Image_src_gray = imread(file_src, 0);	// ���͉摜�i�O���[�X�P�[���j�̓ǂݍ���

	/* �p�����[�^��` */
	WIDTH = Image_src.cols;
	HEIGHT = Image_src.rows;
	MAX_DATA = WIDTH * HEIGHT;
	cout << "INPUT : WIDTH = " << WIDTH << " , HEIGHT = " << HEIGHT << endl;
	cout << endl;

	Image_dst = Mat(Size(WIDTH, HEIGHT), CV_8UC3);	// �o�͉摜�i�J���[�j�̏�����
}
// �摜�̏o��
void Output_Image() {
	string file_dst = "dst.jpg";	// �o�͉摜�̃t�@�C����

	/* �E�B���h�E���� */
	namedWindow(win_src, WINDOW_AUTOSIZE);
	namedWindow(win_dst, WINDOW_AUTOSIZE);

	/* �摜�̕\�� & �ۑ� */
	imshow(win_src, Image_src);				// ���͉摜��\��
	imshow(win_dst, Image_dst);				// �o�͉摜��\��
	imwrite(file_dst, Image_dst);			// �������ʂ̕ۑ�

	waitKey(0); // �L�[���͑҂�
}
