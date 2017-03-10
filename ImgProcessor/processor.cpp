// drone.cpp : �������̨Ӧ�ó������ڵ㡣
//

// #include <stdafx.h>
#include <fstream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/stitcher.hpp"
#include <iostream>

using namespace cv;
using namespace std;

vector<Mat> imgs; //����ƴ�ӵ�ԭʼͼ������

				  //��������ԭʼƴ��ͼ����
void parseCmdArgs(int argc, char** argv);

// ConsoleApplication3.cpp : �������̨Ӧ�ó������ڵ㡣
//




int main(int argc, char* argv[])
{
	//����ƴ��ͼ��


	parseCmdArgs(argc, argv);
	Mat pano;
	Stitcher stitcher = Stitcher::createDefault(false);
	Stitcher::Status status = stitcher.stitch(imgs, pano);//ƴ��
	if (status != Stitcher::OK) //�ж�ƴ���Ƿ�ɹ�
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return -1;
	}
	vector<int>compression_params;
	compression_params.push_back(CV_IMWRITE_JPEG_QUALITY); //PNG��ʽͼƬ��ѹ������
	compression_params.push_back(50);
	namedWindow("ȫ��ƴ��", 0);
	imshow("ȫ��ƴ��", pano);
	imwrite("./out.jpg", pano, compression_params);
	waitKey();
	return 0;
}

//��������ԭʼƴ��ͼ����
void parseCmdArgs(int argc, char** argv)
{
	for (int i = 1; i<argc; i++)
	{
		Mat img = imread(argv[i]);
		if (img.empty())
		{
			cout << "Can't read image '" << argv[i] << "'\n";
		}
		imgs.push_back(img);
	}
}
