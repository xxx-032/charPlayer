#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<vector>
#include<windows.h>
#include<atlimage.h>
#include<io.h>
#include <conio.h>
#include<commdlg.h>
#include<atlconv.h>
using namespace std;
typedef void(*printChar)(char *, UINT , UINT , UINT , UINT , UINT );
typedef void(*ClearScreen)(UINT, UINT);
#define MAXCOL 368
#define MAXROW 280

void getFiles(string path, vector<string>& files)
 {
	     //文件句柄  
		     long   hFile = 0;
	    //文件信息  
		     struct _finddata_t fileinfo;
	     string p;
	     if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		     {
		         do
			         {
			             //如果是目录,迭代之  
				             //如果不是,加入列表  
				             if ((fileinfo.attrib &  _A_SUBDIR))
				             {
				                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					                     getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				             }
			             else
				             {
				                 files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				             }
			         }while (_findnext(hFile, &fileinfo) == 0);
			         _findclose(hFile);
			     }
	 }


void GetFile(void) {
	CImage img;
	CRect rect;
	ofstream outfile;
	ifstream infile;


	//生成文本字节流保存路径
	string s = "C:/Users/Administrator/Desktop/backup/text/";
	string openFile;
	char backup[5];
	int cx, cy;
	int x, y, grayVal;
	int pitch, pixelDepth, bitCount;
	BYTE * pDataDst, *pDataSrc;
	CString loadPicture;
	COLORREF pixel;
	vector<string>files;


	//由ffmpeg剪辑所得图片所在路径 本人设置的是路径+%4d.
	getFiles("C:/Users/Administrator/Desktop/backup/picture", files);
	int size = files.size();
	for (int i = 0; i < size; i++)
	{

		loadPicture = files[i].c_str();
		img.Load(loadPicture);

		cx = img.GetWidth();
		cy = img.GetHeight();

		//GetPitch( ) 图像的间距。 如果返回值为负，位图是一个从下到上 DIB，并且原点是左下角。 
		//如果返回值为正的，位图是一组 DIB，并且原点为左上角
		pitch = img.GetPitch();

		//返回位深  
		pixelDepth = img.GetBPP();

		bitCount = pixelDepth / 8;

		pDataDst = new BYTE[cx*cy*bitCount];
		pDataSrc = (BYTE *)img.GetBits();


		//文件名，有需要可自己修改
		_itoa(i + 1, backup,10);
		openFile = s + backup + ".txt";


		outfile.open(openFile.c_str(), ofstream::out);

		for (y = 0; y < cy; y++) {
			for (x = 0; x < cx; x++) {
				
				pixel = img.GetPixel(x, y);
				grayVal = GetRValue(pixel) + GetGValue(pixel) + GetBValue(pixel) / 3;

				if (grayVal < 120)
				{
					outfile << " ";
				}
				else
				{
					outfile << "M";
				}
			}
			outfile << "\n";
		}
		img.Destroy();
		outfile.close();
	}
}



void readTxt(string FILE, printChar Charprint, ClearScreen ScreenClean) {
	ifstream infile;
	vector<string>files;
	string openFile;
	char backup[5];
	char buffer[MAXCOL + 1];
	int length;
	int y=0;
	getFiles(FILE.c_str(), files);
	int size = files.size();
	string s;
	for (int i = 0; i < size; i++)
	{
		_itoa(i + 1, backup, 10);
		openFile = FILE + backup + ".txt";
		infile.open(openFile.c_str());
		
		y = 0;
		
		for (y = 0; y < MAXROW; y++) {
			infile.read(buffer, MAXCOL + 1);
			Charprint(buffer, MAXCOL, 0, y,MAXCOL,MAXROW);
		}
		Sleep(15);
		ScreenClean(MAXCOL, MAXROW);
		infile.close();
	}
}







int main(void) {
	system("mode con cols=368 lines=200");
	string f = "C:/Users/Administrator/Desktop/backup/text/";
	HINSTANCE mydll = LoadLibrary(L"Dll_charPrint.dll");
	printChar Charprint = (printChar)GetProcAddress(mydll, "PrintChar");
	ClearScreen ScreenClean = (ClearScreen)GetProcAddress(mydll, "ClearScreen");

	
	readTxt(f, Charprint, ScreenClean);

	return 0;
}




