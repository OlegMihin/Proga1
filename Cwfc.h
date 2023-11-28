#pragma once

#include <string>
#include <fstream>

void DrowFrame(CDC* odc, int left, int top, int cols, int rows, BYTE* data);
void LoadFilmFrame(std::string filmpth, int frmwdth, int frmhght, int frmid, BYTE* data);
void DrowSubaperture(CDC* odc, int left, int top, int size, BYTE* data);
void LoadSubaperture(std::string filmpth, int frmwdth, int frmhght, int frmid, int subapertureIndex, BYTE* data);
