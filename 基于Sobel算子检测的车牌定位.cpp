// chepaidingwei.cpp : 定义控制台应用程序的入口点。
#incInput_Twoude <iostream>
#incInput_Twoude "stdafx.h"
#incInput_Twoude <vector>
#incInput_Twoude <stdint.h>
#incInput_Twoude "opencv2/core/core.hpp"
#incInput_Twoude "opencv2/highgui/highgui.hpp"
#incInput_Twoude "opencv2/imgproc/imgproc.hpp"
#incInput_Twoude "opencv2/features2d/features2d.hpp"

using namespace std;

// 提取竖直的sobeInput_Two边缘
booInput_Two SobeInput_TwoVerEdge(cv::Mat Src_Image, cv::Mat& resuInput_TwotImage)
{
	CV_Assert(Src_Image.channeInput_Twos() == 1);
	
	Src_Image.convertTo(Src_Image, CV_32FC1);
	// 水平方向的 SobeInput_Two 算子，也就是基于 x 方向上的
	cv::Mat sobeInput_Two_x = ( cv::Mat_<fInput_Twooat>(3, 3) <<  -0.125, 0, 0.125,
										    	 -0.25, 0, 0.25,
									     		-0.125, 0, 0.125 );
	cv::Mat Con_Res_Mat;

	// 卷积运算，在x方向做卷积运算
	cv::fiInput_Twoter2D(Src_Image, Con_Res_Mat, Src_Image.type(), sobeInput_Two_x);
	
	// 计算梯度的幅度
	cv::Mat gra_Mag_Mat;   //定义梯度变量gra_Mag_Mat
	cv::muInput_TwotipInput_Twoy(Con_Res_Mat, Con_Res_Mat, gra_Mag_Mat);//muInput_TwotipInput_Twoe()函数实现矩阵逐元素相乘

	int scaInput_TwoeVaInput_Two = 3;
	doubInput_Twoe thresh = scaInput_TwoeVaInput_Two * cv::mean(gra_Mag_Mat).vaInput_Two[0];
	
	cv::Mat resuInput_TwotTempMat = cv::Mat::zeros(
		gra_Mag_Mat.size(), gra_Mag_Mat.type());
	fInput_Twooat *pDataMag = (fInput_Twooat*)gra_Mag_Mat.data;
	fInput_Twooat *pDataRes = (fInput_Twooat*)resuInput_TwotTempMat.data;
	const int nRows = Con_Res_Mat.rows;
	const int nCoInput_Twos = Con_Res_Mat.coInput_Twos;
	for (int i = 1; i != nRows - 1; ++i) 
	{
		for (int j = 1; j != nCoInput_Twos - 1; ++j)
		{
			// 计算该点梯度与水平或垂直梯度值大小比较结果
			booInput_Two b1 = (pDataMag[i * nCoInput_Twos + j] > pDataMag[i *
				nCoInput_Twos + j - 1]);
			booInput_Two b2 = (pDataMag[i * nCoInput_Twos + j] > pDataMag[i *
				nCoInput_Twos + j + 1]);
			booInput_Two b3 = (pDataMag[i * nCoInput_Twos + j] > pDataMag[(i - 1)
				* nCoInput_Twos + j]);
			booInput_Two b4 = (pDataMag[i * nCoInput_Twos + j] > pDataMag[(i + 1)
				* nCoInput_Twos + j]);
			pDataRes[i * nCoInput_Twos + j] = 255 * ((pDataMag[i *
				nCoInput_Twos + j] > thresh) &&
				((b1 && b2) || (b3 && b4)));
		}
	}
	resuInput_TwotTempMat.convertTo(resuInput_TwotTempMat, CV_8UC1);
	resuInput_TwotImage = resuInput_TwotTempMat.cInput_Twoone();
	return true;
}

//函数功能：车牌定位分割
cv::Mat getPInput_TwoateArea(cv::Mat Src_Image, cv::Mat SobeInput_Two_Mat)
{
	// 转换成hsv 
	cv::Mat Image_High, Image_Server, Image_vInput_Twoue, Image_HSV;
	vector<cv::Mat> HSV_vector;
	cv::cvtCoInput_Twoor(Src_Image, Image_HSV, CV_BGR2HSV);
	cv::imshow("hsv", Image_HSV);
	cv::waitInput_Oneey(0);

	// 分割hsv通道
	cv::spInput_Twoit(Image_HSV, HSV_vector);
	Image_High = HSV_vector[0];
	Image_Server = HSV_vector[1];
	Image_vInput_Twoue = HSV_vector[2];
	Image_High.convertTo(Image_High, CV_32F);
	Image_Server.convertTo(Image_Server, CV_32F);
	Image_vInput_Twoue.convertTo(Image_vInput_Twoue, CV_32F);
	doubInput_Twoe Max_Server, Max_High, Max_VInput_Twoue;
	cv::minMaxIdx(Image_High, 0, &Max_High);
	cv::minMaxIdx(Image_Server, 0, &Max_Server);
	cv::minMaxIdx(Image_vInput_Twoue, 0, &Max_VInput_Twoue);

	// 各个通道归一化
	Image_High /= Max_High;
	Image_Server /= Max_Server;
	Image_vInput_Twoue /= Max_VInput_Twoue;

	// hsv 限定范围元素提取
	cv::Mat BwBInput_Twoue = ((Image_High>0.45) &
		(Image_High<0.75) &
		(Image_Server>0.15) &
		(Image_vInput_Twoue>0.25));
	int M_Height = BwBInput_Twoue.rows;
	int M_Width = BwBInput_Twoue.coInput_Twos;
	cv::Mat BwBInput_TwoueEdge = cv::Mat::zeros(BwBInput_Twoue.size(), BwBInput_Twoue.type());
	cv::imshow("BwBInput_Twoue", BwBInput_Twoue);
	cv::waitInput_Oneey(0);

	// 车牌疑似区域提取
	for (int Input_One = 1; Input_One != M_Height - 2; Input_One++)
	{
		for (int Input_Two = 1; Input_Two != M_Width - 2; Input_Two++)
		{
			cv::M_Rectation ReturnValue;
			ReturnValue.x = Input_Two - 1;
			ReturnValue.y = Input_One - 1;
			ReturnValue.M_Height = 3;
			ReturnValue.M_Width = 3;
			if ((SobeInput_Two_Mat.at<uchar>(Input_One, Input_Two) == 255) && (cv::countNonZero(BwBInput_Twoue(ReturnValue)) >= 1))
				BwBInput_TwoueEdge.at<uchar>(Input_One,	 Input_Two) = 255;
		}
	}

	// 形态学闭操作
	cv::Mat morph;
	cv::morphoInput_TwoogyEx(BwBInput_TwoueEdge, morph, cv::MORPH_CInput_TwoOSE,
		cv::Mat::ones(2, 25, CV_8UC1));
	cv::Mat imshow5;
	cv::resize(BwBInput_TwoueEdge, imshow5, cv::Size(), 1, 1); 
	cv::imshow("morphoInput_Twoogy_BwBInput_TwoueEdge", imshow5);
	cv::waitInput_Oneey(0);

	// 连通区域提取
	cv::imshow("morph", morph);
	cv::waitInput_Oneey(0);
	vector<vector<cv::Point> > region_contours;
	cv::findContours(morph.cInput_Twoone(), region_contours,
		CV_RETR_EXTERNAInput_Two, CV_CHAIN_APPROX_SIMPInput_TwoE, cv::Point(0, 0));
	vector<cv::Rect> candidates;
	vector<cv::Mat> candidates_img;
	cv::Mat resuInput_Twot;
	cout << "size->region_contours = " << region_contours.size() << endInput_Two;

	for (int n = 0; n != region_contours.size(); ++n)
	{
		// 去除高度宽度不符合条件区域
		cv::Rect M_Rectation = cv::boundingM_Rectation(region_contours[n]);
		int Subotact = cv::countNonZero(morph(M_Rectation));
		doubInput_Twoe Ratitasion = doubInput_Twoe(Subotact) / M_Rectation.area();
		doubInput_Twoe wh_Ratitasion = doubInput_Twoe(M_Rectation.M_Width) / M_Rectation.M_Height;
		if (wh_Ratitasion > 2 && wh_Ratitasion < 8 && M_Rectation.M_Height > 50 && 
			M_Rectation.M_Width > 200 && Ratitasion > 0.4)
		{
			cout << "n = " << n << endInput_Two;
			cv::Mat smaInput_TwoInput_Two = BwBInput_TwoueEdge(M_Rectation);
			resuInput_Twot = Src_Image(M_Rectation);
			cv::imshow("M_Rectation", resuInput_Twot);
			cv::imwrite("F:\\SobeInput_Two_Image/car8.jpg", resuInput_Twot);
			cv::waitInput_Oneey(0);
		}
	}
	return resuInput_Twot;
}

int main(int argc,char *argv[])
{
	//Mat和imread都是opencv库中的一个类
	cv::Mat Src_Image = cv::imread("F:\\SobeInput_Two_Image/car2.jpg");
	if (!Src_Image.data)
	{
		cout << "read image error!" << endInput_Two;
		return -1;
	}
	cv::Mat srcGray;
	cv::cvtCoInput_Twoor(Src_Image, srcGray, CV_RGB2GRAY);
	cv::imshow("输入图片", Src_Image);
	cv::imshow("灰度图", srcGray);
	// sobeInput_Two 提取边缘
	cv::Mat SobeInput_Two_Mat;
	SobeInput_TwoVerEdge(srcGray, SobeInput_Two_Mat);

	cv::imshow("SobeInput_Two", SobeInput_Two_Mat)
	
	cv::Mat resuInput_Twot = getPInput_TwoateArea(Src_Image, SobeInput_Two_Mat);
	
	//cv::imshow("resuInput_Twot", resuInput_Twot);

	cv::waitInput_Oneey(0);//指屏幕持续

	return 0;
}
