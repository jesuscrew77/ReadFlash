
#include "ReadFlashFormat.h"


float GetFloat(float ptr)
{
unsigned short ss[2];
unsigned short *sh, buf_s;

  sh=(unsigned short *)&ptr;
  ss[0]=*sh;
  ss[1]=*(sh+1);
  buf_s=ss[0];
  ss[0]=ss[1];
  ss[1]=buf_s;
  return *(float*)ss;
}

int GetInt(int ptr)
{
unsigned short ss[2];
unsigned short *sh, buf_s;

  sh=(unsigned short *)&ptr;
  ss[0]=*sh;
  ss[1]=*(sh+1);
  buf_s=ss[0];
  ss[0]=ss[1];
  ss[1]=buf_s;
  return *(int*)ss;
}

void ChangeWordSingleReg(struct DataSingleReg &data)
{
	data.T = GetInt(data.T);
	data.Tbshv = GetInt(data.Tbshv);
	data.Tpr_sec = GetInt(data.Tpr_sec);
	data.Tpr_msec = GetInt(data.Tpr_msec);
}

void ChangeWordPix(struct DataPixHeader &data)
{
	data.T = GetInt(data.T);
	data.Tbshv = GetInt(data.Tbshv);
	data.Tpr_sec = GetInt(data.Tpr_sec);
	data.Tpr_msec = GetInt(data.Tpr_msec);
}

void ChangeWordFrag(struct DataFragHeader &data)
{
	data.Tpr_sec = GetInt(data.Tpr_sec);
	data.Tpr_msec = GetInt(data.Tpr_msec);
	data.NumPix = GetInt(data.NumPix);
}

void ChangeWordNO(struct DataNO &data)
{
	data.T = GetInt(data.T);
	data.Tbshv = GetInt(data.Tbshv);
	data.Tpr_sec = GetInt(data.Tpr_sec);
	data.Tpr_msec = GetInt(data.Tpr_msec);
	data.Temp=GetFloat(data.Temp);

	for (int i = 0; i < 4; i++)
		data.QuatBoart[i]=GetFloat(data.QuatBoart[i]);

	for (int k = 0; k < 2; k++)
		for (int i = 0; i < data.NumL[k]; i++)
			for (int j = 0; j < 4; j++)
				data.RsLocT[k][i][j]=GetFloat(data.RsLocT[k][i][j]);

	for (int i = 0; i < MaxDetHO; i++) {
		for (int j = 0; j < 4; j++) {
			data.RsLoc[i][j]=GetFloat(data.RsLoc[i][j]);
			data.Coord[i][j]=GetFloat(data.Coord[i][j]);
			data.D_cos[i][j]=GetFloat(data.D_cos[i][j]);
		}
		data.Dx[i]=GetFloat(data.Dx[i]);
		data.Dy[i]=GetFloat(data.Dy[i]);
	}

	data.m_cur=GetFloat(data.m_cur);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			data.M_ornt[i][j]=GetFloat(data.M_ornt[i][j]);
		}
	}
	for (int i = 0; i < 4; i++)
		data.Quat[i]=GetFloat(data.Quat[i]);

	data.TimeExp=GetFloat(data.TimeExp);
	for (int i = 0; i < 3; i++)
		data.Wop[i]=GetFloat(data.Wop[i]);
	data.EPOCH=GetFloat(data.EPOCH);
}

void ChangeWordSLEZH(struct DataSLEZH &data)
{
	data.T = GetInt(data.T);
	data.Tbshv = GetInt(data.Tbshv);
	data.Tpr_sec = GetInt(data.Tpr_sec);
	data.Tpr_msec = GetInt(data.Tpr_msec);
	data.Temp=GetFloat(data.Temp);

	data.mean=GetFloat(data.mean);
	data.sigma=GetFloat(data.sigma);

	for (int i = 0; i < MaxStarCad; i++)
		for (int j = 0; j < 2; j++)
			data.XYcProg[i][j]=GetFloat(data.XYcProg[i][j]);

		for (int i = 0; i < data.NumLoc  ; i++)
			for (int j = 0; j < 4; j++)
				data.RsLocT[i][j]=GetFloat(data.RsLocT[i][j]);

	for (int i = 0; i < MaxOrnt; i++) {
		for (int j = 0; j < 2; j++)
			data.MeanFrag[i][j]=GetFloat(data.MeanFrag[i][j]);
		for (int j = 0; j < 4; j++) {
			data.XYc[i][j]=GetFloat(data.XYc[i][j]);
			data.RsLoc[i][j]=GetFloat(data.RsLoc[i][j]);
			data.Coord[i][j]=GetFloat(data.Coord[i][j]);
			data.D_cos[i][j]=GetFloat(data.D_cos[i][j]);
		}
		data.Dx[i]=GetFloat(data.Dx[i]);
		data.Dy[i]=GetFloat(data.Dy[i]);
	}

	data.m_cur=GetFloat(data.m_cur);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			data.M_prog[i][j]=GetFloat(data.M_prog[i][j]);
			data.M_ornt[i][j]=GetFloat(data.M_ornt[i][j]);
		}
	}
	for (int i = 0; i < 4; i++)
		data.Quat[i]=GetFloat(data.Quat[i]);

	data.TimeExp=GetFloat(data.TimeExp);
	for (int i = 0; i < 3; i++)
		data.Wop[i]=GetFloat(data.Wop[i]);
	data.EPOCH=GetFloat(data.EPOCH);
}

void ConvertDataSLEZH(struct DataSLEZH data, struct CadrInfo &mCadr)
{
	mCadr.IsBinary=true;
//	mCadr.IsReverse=true;
	mCadr.ImageHeight=1024;
	mCadr.ImageWidth=1024;
	mCadr.Time=data.Tpr_sec+data.Tpr_msec/1000.;
	mCadr.CountLocalObj=data.NumLoc;
	mCadr.CountDeterObj=data.NumDet;
	mCadr.ObjectsList = new struct ObjectsInfo[mCadr.CountLocalObj];
	for (int i=0; i<mCadr.CountLocalObj; i++) {
		mCadr.ObjectsList[i].X=data.RsLocT[i][0];
		mCadr.ObjectsList[i].Y=data.RsLocT[i][1];
		mCadr.ObjectsList[i].Bright=data.RsLocT[i][2];
		mCadr.ObjectsList[i].Square  =abs(data.RsLocT[i][3]);
		mCadr.ObjectsList[i].StarID=0;
		mCadr.ObjectsList[i].Mv=0;
		mCadr.ObjectsList[i].Sp[0]='_';
		mCadr.ObjectsList[i].Sp[1]='_';
		mCadr.ObjectsList[i].Dx=0;
		mCadr.ObjectsList[i].Dy=0;
	}

	if (!data.res_stat)
	{
		for (int i=0; i<mCadr.CountDeterObj; i++) {
			int iloc=data.MasRes[i][0];
			int ifrag=data.MasRes[i][1];
			mCadr.ObjectsList[iloc].StarID=(unsigned int)data.XYc[ifrag][2];
			mCadr.ObjectsList[iloc].Mv=data.XYc[ifrag][3];
			mCadr.ObjectsList[iloc].Dx=data.Dx[i];
			mCadr.ObjectsList[iloc].Dy=data.Dy[i];
		}
	}

	mCadr.CountBlock=data.CountBlock;
	mCadr.CountLines=data.EndBufFrag;
	mCadr.LinesList = new struct LinesInfo[mCadr.CountLines];
	for (int i=0; i<mCadr.CountBlock; i++) {
		mCadr.LinesList[i].Start=data.TabTakeAway[i][0];
		mCadr.LinesList[i].Height=data.TabTakeAway[i][1];
	}

	mCadr.CountStars=data.NumProgFrag;
	mCadr.StarsList = new struct StarsInfo[mCadr.CountStars];
	for (int i = 0; i < mCadr.CountStars; i++) {
		mCadr.StarsList[i].X=data.XYcProg[i][0];
		mCadr.StarsList[i].Y=data.XYcProg[i][1];
//		mCadr.StarsList[i].Mv=data.XYcProg[i][2];
//		mCadr.StarsList[i].StarID=data.XYcProg[i][2];
	}
	mCadr.CountWindows=data.NumFrag;
	mCadr.WindowsList = new struct WindowsInfo[data.NumFrag];
	for (int i = 0; i < mCadr.CountWindows; i++) {
		mCadr.WindowsList[i].Xstart = data.FragYX[i][1]-data.PfragXY[i][0]+1;
		mCadr.WindowsList[i].Ystart = data.YendLoc[i]-data.PfragXY[i][1]+1;
		mCadr.WindowsList[i].Width = data.PfragXY[i][0];
		mCadr.WindowsList[i].Height = data.PfragXY[i][1];
		mCadr.WindowsList[i].Mean = data.MeanFrag[i][0];
		mCadr.WindowsList[i].Sigma = data.MeanFrag[i][1];
		mCadr.WindowsList[i].Level = data.ThFrag[i];
		mCadr.WindowsList[i].CountObj = data.ObjFrag[i];
		mCadr.WindowsList[i].StarID = data.XYc[i][2];
		mCadr.WindowsList[i].Mv = data.XYc[i][3];
	}
}

void ConvertDataNO(struct DataNO data, struct CadrInfo &mCadr, int NC)
{
	mCadr.IsBinary=true;
//	mCadr.IsReverse=true;
	mCadr.ImageHeight=1024;
	mCadr.ImageWidth=1024;
	mCadr.Time=data.Tpr_sec+data.Tpr_msec/1000.;
	mCadr.CountLocalObj=data.NumLoc[NC];
	mCadr.CountDeterObj=data.NumDet;
	mCadr.ObjectsList = new struct ObjectsInfo[mCadr.CountLocalObj];
	for (int i=0; i<mCadr.CountLocalObj; i++) {
		mCadr.ObjectsList[i].X=data.RsLocT[NC][i][0];
		mCadr.ObjectsList[i].Y=data.RsLocT[NC][i][1];
		mCadr.ObjectsList[i].Bright=data.RsLocT[NC][i][2];
		mCadr.ObjectsList[i].Square  = abs(data.RsLocT[NC][i][3]);
		mCadr.ObjectsList[i].StarID=0;
		mCadr.ObjectsList[i].Mv=0;
		mCadr.ObjectsList[i].Sp[0]='_';
		mCadr.ObjectsList[i].Sp[1]='_';
		mCadr.ObjectsList[i].Dx=0;
		mCadr.ObjectsList[i].Dy=0;
	}

	if (NC) {
		if (!data.res_stat)
		{
			for (int i=0; i<data.NumDet; i++) {
				int iloc=data.MasRes[i][0];
		//			mCadr.ObjectsList[iloc].StarID=(unsigned int)data.XYc[ifrag][2];
		//			mCadr.ObjectsList[iloc].Mv=data.XYc[ifrag][3];
					mCadr.ObjectsList[iloc].Dx=data.Dx[i];
					mCadr.ObjectsList[iloc].Dy=data.Dy[i];
			}
		}
	}

	mCadr.CountStars=0;
	mCadr.CountWindows=0;
	mCadr.CountLines=0;
	mCadr.CountBlock=0;
}


void PrintReg(FILE *ftxt, unsigned char *mas)
{
  fprintf(ftxt,"\n\n//---------------��������-----------------------//\n");
  fprintf(ftxt,"��������:\n");
  for (int i=0; i<COUNT_REG; i++)
  {
	fprintf(ftxt,"%d 0x%02x\n",i+1,mas[i]);
  }
  fprintf(ftxt,"//----------------------------------------------//\n");
}

void PrintSingleReg(FILE *ftxt, struct DataSingleReg data)
{
  fprintf(ftxt,"\n\n//---------------������ ������ ��������-----------------------//\n");
  fprintf(ftxt,"��������� �����: %02d\n",data.SerNum);
  fprintf(ftxt,"������ ��������� � %d\n",data.CntRecord);
  fprintf(ftxt,"����� ��������: Tep=%ld, Tbshv=%ld\n",data.T,data.Tbshv);
  fprintf(ftxt,"����� ��������: Ts=%ld, Tms=%ld\n",data.Tpr_sec,data.Tpr_msec);
  fprintf(ftxt,"���������� ����� ���������: %d\n",data.CntErr);
  fprintf(ftxt,"����� ��������: %d\n",data.Nreg);
  fprintf(ftxt,"�������� ��������: %d\n",data.RegVal);
  fprintf(ftxt,"//----------------------------------------------//\n");
}

void PrintDataPix(FILE *ftxt, struct DataPixHeader data, int NumCadr)
{
fprintf(ftxt,"\n\n//----������� ���� ������ �� %d-� �����---------//\n",NumCadr);
if (NumCadr==1) {
  fprintf(ftxt,"��������� �����: %02d\n",data.SerNum);
  fprintf(ftxt,"������ �������� � %d\n",data.CntRecord);
}
fprintf(ftxt,"����� ��������: Tep=%ld, Tbshv=%ld\n",data.T,data.Tbshv);
fprintf(ftxt,"����� ��������: Ts=%ld, Tms=%ld\n",data.Tpr_sec,data.Tpr_msec);
fprintf(ftxt,"����� ����������: %d\n",data.StarExp);
fprintf(ftxt,"����� ��������: %d\n",data.NumPix);
fprintf(ftxt,"//----------------------------------------------//\n");
}

void PrintDataFrag(FILE *ftxt, struct DataFragHeader data)
{
fprintf(ftxt,"\n\n//-----------������ ����������--------------//\n");
fprintf(ftxt,"��������� �����: %02d\n",data.SerNum);
fprintf(ftxt,"������ ���������� � %d\n",data.CntRecord);
fprintf(ftxt,"����� ��������: Ts=%ld, Tms=%ld\n",data.Tpr_sec,data.Tpr_msec);
fprintf(ftxt,"����� ��������: %ld\n",data.NumPix);
fprintf(ftxt,"//----------------------------------------------//\n");
}

void PrintDataNO(FILE *ftxt, struct DataNO data)
{
fprintf(ftxt,"\n\n//---------------����� ��/��--------------------//\n");
fprintf(ftxt,"��������� �����: %02d\n",data.SerNum);
fprintf(ftxt,"������ � ������ ��/�� � %d\n",data.CntRecord);
fprintf(ftxt,"����� ��������: Tep=%ld, Tbshv=%ld\n",data.T,data.Tbshv);
fprintf(ftxt,"����� ��������: Ts=%ld, Tms=%ld\n",data.Tpr_sec,data.Tpr_msec);
fprintf(ftxt,"�����������: %f\n",data.Temp);
fprintf(ftxt,"����� ����������: %d\n",data.StarExp);
fprintf(ftxt,"������ �������: 0x%04x\n",data.res_stat);
fprintf(ftxt,"��������� ����������: %d\n",data.NumApr);
fprintf(ftxt,"���������� ����������� ��������: %d\n",data.NumStore);

fprintf(ftxt,"��������� ����������: %f; %f; %f; %f;\n",
		data.QuatBoart[0],data.QuatBoart[1],
		data.QuatBoart[2],data.QuatBoart[3]);
fprintf(ftxt,"���������� ��������������� ��������: %d/%d\n",data.NumL[0],data.NumL[1]);

fprintf(ftxt,"RsLocT[0]\n");
for (int i=0; i<data.NumL[0];i++)
{
  fprintf(ftxt,"%4d %10.4f %10.4f %10.2f %8.0f\n",i+1,
		  data.RsLocT[0][i][0],data.RsLocT[0][i][1],
		  data.RsLocT[0][i][2],data.RsLocT[0][i][3]);
}
fprintf(ftxt,"RsLocT[1]\n");
for (int i=0; i<data.NumL[1];i++)
{
  fprintf(ftxt,"%4d %10.4f %10.4f %10.2f %8.0f\n",i+1,
		  data.RsLocT[1][i][0],data.RsLocT[1][i][1],
		  data.RsLocT[1][i][2],data.RsLocT[1][i][3]);
}
fprintf(ftxt,"����� ����� ��������: %d/%d\n",data.NumLoc[0],data.NumLoc[1]);

fprintf(ftxt,"���������� ��������� ��������:\n");
fprintf(ftxt,"RsLoc\n");
for (int i=0; i<MaxDetHO;i++)
{
  fprintf(ftxt,"%4d %10.4f %10.4f %10.2f %8.0f\n",i+1,
		  data.RsLoc[i][0],data.RsLoc[i][1],
		  data.RsLoc[i][2],data.RsLoc[i][3]);
}
fprintf(ftxt,"���������� ������������ ��������: NumDet=%d\n",data.NumDet);
fprintf(ftxt,"������������ �������� �� ���� �����������: %d/%d\n",data.dxmaxH,data.dymaxH);
fprintf(ftxt,"�������� ����������: %d\n",data.maxH);

fprintf(ftxt,"MasRes\n");
for (int i=0; i<MaxDetHO;i++)
{
  fprintf(ftxt,"%4d %4d %4d\n",i+1, data.MasRes[i][0], data.MasRes[i][1]);  //�� ������ �������
}

fprintf(ftxt,"Coord\n");
for (int i=0; i<MaxDetHO;i++)
{
  fprintf(ftxt,"%4d %12.8f %12.8f %12.8f %10.2f\n",i+1,
		  data.Coord[i][0],data.Coord[i][1],
		  data.Coord[i][2],data.Coord[i][3]);
}

fprintf(ftxt,"D_cos\n");
for (int i=0; i<MaxDetHO;i++)
{
  fprintf(ftxt,"%4d %12.8f %12.8f %12.8f %8.0f\n",i+1,
		  data.D_cos[i][0],data.D_cos[i][1],
		  data.D_cos[i][2],data.D_cos[i][3]);
}

fprintf(ftxt,"Dx&Dy\n");
for (int i=0; i<MaxDetHO;i++)
{
  fprintf(ftxt,"%4d %10.6f %10.6f\n",i+1, data.Dx[i],data.Dy[i]);
}

fprintf(ftxt,"������ ������� ����: %f\n",data.m_cur);
fprintf(ftxt,"������� ����������:\n");
fprintf(ftxt,"%16.8f %16.8f %16.8f\n",data.M_ornt[0][0],data.M_ornt[0][1],data.M_ornt[0][2]);
fprintf(ftxt,"%16.8f %16.8f %16.8f\n",data.M_ornt[1][0],data.M_ornt[1][1],data.M_ornt[1][2]);
fprintf(ftxt,"%16.8f %16.8f %16.8f\n",data.M_ornt[2][0],data.M_ornt[2][1],data.M_ornt[2][2]);

fprintf(ftxt,"���������� ����������:%f %f %f %f\n",
		data.Quat[0],data.Quat[1],
		data.Quat[2],data.Quat[3]);

fprintf(ftxt,"����� ����� �������: %f\n",data.TimeExp);
fprintf(ftxt,"������� ��������, ���.�./�: %f %f %f\n",
		data.Wop[0]*RTS,data.Wop[1]*RTS,data.Wop[2]*RTS);
fprintf(ftxt,"����� ����������: %12.8f\n",data.EPOCH);

fprintf(ftxt,"�������� ��������, ��/�:\n");
fprintf(ftxt,"%f %f %f\n",GetFloat(data.Vline[0]),GetFloat(data.Vline[1]),
						  GetFloat(data.Vline[2]));
fprintf(ftxt,"//----------------------------------------------//\n");
}

void PrintDataSLEZH(FILE *ftxt,  struct DataSLEZH data)
{
fprintf(ftxt,"\n\n//---------------����� ��������--------------------//\n");
fprintf(ftxt,"��������� �����: %02d\n",data.SerNum);
fprintf(ftxt,"������ � ������ �������� � %d\n",data.CntRecord);
fprintf(ftxt,"����� ��������: Tep=%ld, Tbshv=%ld\n",data.T,data.Tbshv);
fprintf(ftxt,"����� ��������: Ts=%ld, Tms=%ld\n",data.Tpr_sec,data.Tpr_msec);
fprintf(ftxt,"�����������: %f\n",data.Temp);
fprintf(ftxt,"����� ����������: %d\n",data.StarExp);
fprintf(ftxt,"������ �������: 0x%04x\n",data.res_stat);
fprintf(ftxt,"���������� �� �����: mean=%f, sigma=%f\n",data.mean, data.sigma);

fprintf(ftxt,"�������������� ������� ����������: \n");
fprintf(ftxt,"%16.8f %16.8f %16.8f\n",data.M_prog[0][0], data.M_prog[0][1], data.M_prog[0][2]);
fprintf(ftxt,"%16.8f %16.8f %16.8f\n",data.M_prog[1][0], data.M_prog[1][1], data.M_prog[1][2]);
fprintf(ftxt,"%16.8f %16.8f %16.8f\n",data.M_prog[2][0], data.M_prog[2][1], data.M_prog[2][2]);

fprintf(ftxt,"��������� ������ ��������: %d\n",data.NumSec);
fprintf(ftxt,"����� �������������� �����: %d\n",data.NumProgFrag);

//XYcProg
fprintf(ftxt,"XYcProg\n");
for (int i=0; i<MaxStarCad;i++)
{
	fprintf(ftxt,"%4d %10.4f %10.4f\n",i+1,
			data.XYcProg[i][0], data.XYcProg[i][1]);
}
fprintf(ftxt,"����� ���������� �� �����: %d\n",data.NumFrag);
fprintf(ftxt,"XYc\n");
for (int i=0; i<MaxOrnt;i++)
{
	fprintf(ftxt,"%4d %10.4f %10.4f %8.0f %8.2f\n",i+1,
		  data.XYc[i][0],data.XYc[i][1],
		  data.XYc[i][2],data.XYc[i][3]);
}

fprintf(ftxt,"MeanFrag&ThFrag\n");
for (int i=0; i<MaxOrnt;i++)
{
	fprintf(ftxt,"%4d %10.4f %10.4f %6d\n",i+1, data.MeanFrag[i][0],
			data.MeanFrag[i][1], data.ThFrag[i]);
}

fprintf(ftxt,"������������ ����� �� �������� ����������: %d\n",data.ThMax);

fprintf(ftxt,"���������� ������ � ������: %d\n",data.CountBlock);
fprintf(ftxt,"���������� ����� � ������: %d\n",data.EndBufFrag);

fprintf(ftxt,"TabTakeAway\n");
for (int i=0; i<8;i++)
{
 fprintf(ftxt,"%4d %6d %6d\n",i+1, data.TabTakeAway[i][0],data.TabTakeAway[i][1]); //�� ������ �������
}
fprintf(ftxt,"PfragXY0\n");
for (int i=0; i<MaxOrnt;i++)
{
 fprintf(ftxt,"%4d %6d %6d\n",i+1, data.PfragXY0[i][0],data.PfragXY0[i][1]);  //�� ������ �������
}

fprintf(ftxt,"PfragXY\n");
for (int i=0; i<MaxOrnt;i++)
{
 fprintf(ftxt,"%4d %6d %6d\n",i+1, data.PfragXY[i][0],data.PfragXY[i][1]);  //�� ������ �������
}

fprintf(ftxt,"ZipXY\n");
for (int i=0; i<MaxOrnt;i++)
{
 fprintf(ftxt,"%4d %6d %6d\n",i+1, data.ZipXY[i][0],data.ZipXY[i][1]);   //�� ������ �������
}

fprintf(ftxt,"FragYX\n");
for (int i=0; i<MaxOrnt;i++)
{
 fprintf(ftxt,"%4d %6d %6d\n",i+1, data.FragYX[i][0],data.FragYX[i][1]);  //�� ������ �������
}

fprintf(ftxt,"YendLoc\n");
for (int i=0; i<MaxOrnt;i++)
{
 fprintf(ftxt,"%4d %6d\n",i+1, data.YendLoc[i]);
}

fprintf(ftxt,"ObjFrag\n");
for (int i=0; i<MaxOrnt;i++)
{
 fprintf(ftxt,"%4d %6d\n",i+1, data.ObjFrag[i]);
}

fprintf(ftxt,"���������� �������������� ��������: %d\n",data.NumLoc);
fprintf(ftxt,"���������� �������� � ���������: %d\n",data.NumStore);
fprintf(ftxt,"���������� ������������ ��������: %d\n",data.NumDet);

fprintf(ftxt,"RsLocT\n");
for (int i=0; i<data.NumLoc;i++)
{
  fprintf(ftxt,"%4d %10.4f %10.4f %10.2f %8.0f\n",i+1,
		  data.RsLocT[i][0],data.RsLocT[i][1],
		  data.RsLocT[i][2],data.RsLocT[i][3]);
}

fprintf(ftxt,"���������� ��������� ��������:\n");
fprintf(ftxt,"RsLoc\n");
for (int i=0; i<MaxOrnt;i++)
{
  fprintf(ftxt,"%4d %10.4f %10.4f %10.2f %8.0f\n",i+1,
		  data.RsLoc[i][0],data.RsLoc[i][1],
		  data.RsLoc[i][2],data.RsLoc[i][3]);
}

fprintf(ftxt,"������������ �������� �� ���� �����������: %d/%d\n",data.dxmaxH,data.dymaxH);
fprintf(ftxt,"�������� ����������: %d\n",data.maxH);

fprintf(ftxt,"MasRes\n");
for (int i=0; i<MaxOrnt;i++)
{
  fprintf(ftxt,"%4d %4d %4d\n",i+1, data.MasRes[i][1], data.MasRes[i][0]);  //������ �������
}

fprintf(ftxt,"Coord\n");
for (int i=0; i<MaxOrnt;i++)
{
  fprintf(ftxt,"%4d %12.8f %12.8f %12.8f %10.2f\n",i+1,
		  data.Coord[i][0],data.Coord[i][1],
		  data.Coord[i][2],data.Coord[i][3]);
}

fprintf(ftxt,"D_cos\n");
for (int i=0; i<MaxOrnt;i++)
{
  fprintf(ftxt,"%4d %12.8f %12.8f %12.8f %8.0f\n",i+1,
		  data.D_cos[i][0],data.D_cos[i][1],
		  data.D_cos[i][2],data.D_cos[i][3]);
}

fprintf(ftxt,"Dx&Dy\n");
for (int i=0; i<MaxOrnt;i++)
{
  fprintf(ftxt,"%4d %10.6f %10.6f\n",i+1, data.Dx[i],data.Dy[i]);
}

fprintf(ftxt,"������ ������� ����: %f\n",data.m_cur);
fprintf(ftxt,"������� ����������:\n");
fprintf(ftxt,"%16.8f %16.8f %16.8f\n",data.M_ornt[0][0],data.M_ornt[0][1],data.M_ornt[0][2]);
fprintf(ftxt,"%16.8f %16.8f %16.8f\n",data.M_ornt[1][0],data.M_ornt[1][1],data.M_ornt[1][2]);
fprintf(ftxt,"%16.8f %16.8f %16.8f\n",data.M_ornt[2][0],data.M_ornt[2][1],data.M_ornt[2][2]);

fprintf(ftxt,"���������� ����������:%f %f %f %f\n",
		data.Quat[0],data.Quat[1],
		data.Quat[2],data.Quat[3]);

fprintf(ftxt,"����� ����� �������: %f\n",data.TimeExp);
fprintf(ftxt,"������� ��������, ���.�./�: %f %f %f\n",
		data.Wop[0]*RTS,data.Wop[1]*RTS,data.Wop[2]*RTS);
fprintf(ftxt,"����� ����������: %12.8f\n",data.EPOCH);

fprintf(ftxt,"�������� ��������, ��/�:\n");
fprintf(ftxt,"%f %f %f\n",GetFloat(data.Vline[0]),GetFloat(data.Vline[1]),
						  GetFloat(data.Vline[2]));
fprintf(ftxt,"//----------------------------------------------//\n");
}

