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
	     //�ļ����  
		     long   hFile = 0;
	    //�ļ���Ϣ  
		     struct _finddata_t fileinfo;
	     string p;
	     if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		     {
		         do
			         {
			             //�����Ŀ¼,����֮  
				             //�������,�����б�  
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


	//�����ı��ֽ�������·��
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


	//��ffmpeg��������ͼƬ����·�� �������õ���·��+%4d.
	getFiles("C:/Users/Administrator/Desktop/backup/picture", files);
	int size = files.size();
	for (int i = 0; i < size; i++)
	{

		loadPicture = files[i].c_str();
		img.Load(loadPicture);

		cx = img.GetWidth();
		cy = img.GetHeight();

		//GetPitch( ) ͼ��ļ�ࡣ �������ֵΪ����λͼ��һ�����µ��� DIB������ԭ�������½ǡ� 
		//�������ֵΪ���ģ�λͼ��һ�� DIB������ԭ��Ϊ���Ͻ�
		pitch = img.GetPitch();

		//����λ��  
		pixelDepth = img.GetBPP();

		bitCount = pixelDepth / 8;

		pDataDst = new BYTE[cx*cy*bitCount];
		pDataSrc = (BYTE *)img.GetBits();


		//�ļ���������Ҫ���Լ��޸�
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




