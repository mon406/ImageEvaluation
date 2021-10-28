#pragma once

/* �g�p�f�B���N�g���w��y�ђ�` */
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#include <iostream>			// �W�����o��
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>			// �V����C++�̃f�[�^�\���ƎZ�p���[�`���Q
#include <opencv2/imgproc/imgproc.hpp>		// �V����C++�̉摜�����֐��Q
#include <opencv2/highgui/highgui.hpp>		// �摜�f�[�^�̃E�B���h�E�\��
#include <time.h>			// ����
//#include <cmath>			// �Z�p�v�Z
//#include <cstdlib>			// ���l�ϊ�,�^������
//#include <array>			// �z��array�N���X
//#include <vector>			// �z��vector�N���X

using namespace std;
using namespace cv;
string win_src = "src";				// ���͉摜�E�B���h�E
string win_dst = "dst";				// �o�͉摜�E�B���h�E

/* ���o�͉摜 */
Mat Image_src;				// ���͉摜
Mat Image_src_gray;			// ���͉摜(�O���[�X�P�[��)
Mat Image_dst;				// �o�͉摜

/* �萔 */
int MAX_INTENSE = 255;	// �ő�F�l
int WIDTH;				// ���͉摜�̉����i�s�N�Z�����j
int HEIGHT;				// ���͉摜�̏c���i�s�N�Z�����j
int MAX_DATA;			// ���͉摜�̑��s�N�Z����

/* ���o�͊֐� */
void Input_Image();			// �摜�̓���
void Output_Image();		// �摜�̏o��
