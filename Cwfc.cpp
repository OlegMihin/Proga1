#include "pch.h"
#include "Cwfc.h"



void DrowFrame(CDC* odc, int left, int top, int cols, int rows, BYTE* data)
{
	BYTE pxl;
	CBitmap bmp;
	CDC dcMem;

	BYTE* framebmp;
	framebmp = (BYTE*)malloc(4 * cols * rows* sizeof(BYTE));

	for (int i = 0;i < rows; i++)
		for (int j = 0;j < cols; j++) {
			pxl = *data++;
			framebmp[i * cols * 4 + j * 4] = pxl;
			framebmp[i * cols * 4 + j * 4 + 1] = pxl;
			framebmp[i * cols * 4 + j * 4 + 2] = pxl;
		}

	dcMem.CreateCompatibleDC(odc);
	bmp.CreateBitmap(cols,rows, 1, 32, framebmp);
	dcMem.SelectObject(&bmp);
	odc->BitBlt(left, top, cols, rows, &dcMem, 0, 0, SRCCOPY);
	bmp.DeleteObject();
	DeleteDC(dcMem);
	free(framebmp);
}

void LoadSubaperture(std::string filmpth, int frmwdth, int frmhght, int frmid, int subapertureIndex, BYTE* data)
{
	std::ifstream in(filmpth, std::ios::in | std::ios::binary);
	in.seekg(0, std::ios::beg);
	in.seekg(frmwdth * frmhght * frmid + subapertureIndex * 64 * 64, std::ios::cur);
	in.read((char*)data, 64 * 64);
}

void DrowSubaperture(CDC* odc, int left, int top, int size, BYTE* data)
{
	CBitmap bmp;
	CRect rect(left, top, left + size, top + size);

	bmp.CreateBitmap(size, size, 1, 32, data);

	odc->SelectObject(&bmp);
	odc->BitBlt(left, top, size, size, odc, 0, 0, SRCCOPY);

	bmp.DeleteObject();
}


void LoadFilmFrame(std::string filmpth, int frmwdth, int frmhght, int frmid,BYTE* data)
{
	std::ifstream in(filmpth, std::ios::in | std::ios::binary);
    in.seekg(0, std::ios::beg);
	in.seekg(frmwdth * frmhght * frmid, std::ios::cur);
	in.read((char*) data, frmwdth * frmhght);
}



