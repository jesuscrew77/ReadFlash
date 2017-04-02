//---------------------------------------------------------------------------


#pragma hdrstop


#include "UnitGraphOrient.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
// ����������������� ��� ������ ������
//#pragma link "ArrowCha"
//#pragma link "BubbleCh"
//#pragma link "GanttCh"
//#pragma link "TeeShape"
#pragma resource "*.dfm"



//---------------------------------------------------------------------------
__fastcall TFormGraphOrient::TFormGraphOrient(TComponent* Owner)
		: TForm(Owner),FragID(0),FormAnimateSetting(new TFormAnimateSetting(this))
{

}
//��������� ������� �������� �� �����
//---------------------------------------------------------------------------
void TFormGraphOrient::CreateGraph(int CurLine)
{
int num;

		if (NumLine<MaxSeries)
        {
				  num=NumGraph*CurLine;
				  LineSeries[num]= new TLineSeries(ChartAl);
				  ChartAl->AddSeries(LineSeries[num]);
				  num++;
				  LineSeries[num]= new TLineSeries(ChartDl);
				  ChartDl->AddSeries(LineSeries[num]);
				  num++;
				  LineSeries[num]= new TLineSeries(ChartAz);
				  ChartAz->AddSeries(LineSeries[num]);
                  num++;
				  LineSeries[num]= new TLineSeries(ChartWx);
				  ChartWx->AddSeries(LineSeries[num]);
				  num++;
				  LineSeries[num]= new TLineSeries(ChartWy);
				  ChartWy->AddSeries(LineSeries[num]);
				  num++;
				  LineSeries[num]= new TLineSeries(ChartWz);
				  ChartWz->AddSeries(LineSeries[num]);
                  num++;
				  LineSeries[num]= new TLineSeries(ChartMx);
				  ChartMx->AddSeries(LineSeries[num]);
				  num++;
				  LineSeries[num]= new TLineSeries(ChartMy);
				  ChartMy->AddSeries(LineSeries[num]);
				  num++;
				  LineSeries[num]= new TLineSeries(ChartNst);
				  ChartNst->AddSeries(LineSeries[num]);
				  num++;
				  LineSeries[num]= new TLineSeries(ChartFoc);
				  ChartFoc->AddSeries(LineSeries[num]);
				  num++;
				  LineSeries[num]= new TLineSeries(ChartX0);
				  ChartX0->AddSeries(LineSeries[num]);
				  num++;
				  LineSeries[num]= new TLineSeries(ChartY0);
				  ChartY0->AddSeries(LineSeries[num]);
                  num++;
				  LineSeries[num]= new TLineSeries(ChartFone);
				  ChartFone->AddSeries(LineSeries[num]);
				  num++;
				  LineSeries[num]= new TLineSeries(ChartNoise);
				  ChartNoise->AddSeries(LineSeries[num]);
				  num++;
				  LineSeries[num]= new TLineSeries(ChartNloc);
				  ChartNloc->AddSeries(LineSeries[num]);
        }

}

void TFormGraphOrient::DeleteGraph(int CurLine)
{
int num;

  if ((NumLine<MaxSeries)&&(CurLine>=0)&&(CurLine<NumLine))
  {
	for (int num=NumGraph*CurLine; num<NumGraph*(CurLine+1);num++)
    {
      LineSeries[num]->Clear();
      delete LineSeries[num];
	}
  }
}

//---------------------------------------------------------------------------
void __fastcall TFormGraphOrient::MenuClearClick(TObject *Sender)
{
//  for (int i=0; i<FormSetting->ListBoxSeries->Count;i++) {
	for (int i=0; i<NumLine;i++) {
	DeleteGraph(i);
  }

//  for (int i=0; i<MaxSeries; i++) {
//    ColorArr[i]=DefColors[i%NumColor];
//	FreeIndex[i]=0;
//  }

  NumLine=0;
//  FormSetting->ListBoxSeries->Clear();
//  FormSetting->EditFileName->Text="";
//  FormSetting->EditSeriesName->Text="";
}
//---------------------------------------------------------------------------

void TFormGraphOrient::SaveGraph(TChart *Chart, AnsiString suff)
{
unsigned int SaveHeigth, SaveWidth;

//        if (FormSetting->CheckBoxLabelVisible->Checked)
//        {
//            Chart->Title->Visible=false;
//        }
		Chart->Legend->Alignment = laBottom;
		SaveHeigth=Chart->Height;  // save visible size image
		SaveWidth=Chart->Width;
		Chart->Visible=false;      // paint user's size image
		Chart->Height=StrToInt(this->EditSizeY->Text);
		Chart->Width=StrToInt(this->EditSizeX->Text);
		Chart->SaveToBitmapFile(suff+".bmp");   // save image
		Chart->Visible=true;      // return souse size image
		Chart->Height=SaveHeigth;
		Chart->Width=SaveWidth;
		Chart->Legend->Alignment = laRight;

//        if (FormSetting->CheckBoxLabelVisible->Checked)
//        {
//            Chart->Title->Visible=true;
//        }
}

void __fastcall TFormGraphOrient::MenuSaveClick(TObject *Sender)
{
   SaveGraph(ChartAl, "Alpha");
   SaveGraph(ChartDl, "Delta");
   SaveGraph(ChartAz, "Azimut");
   SaveGraph(ChartMx, "Mx");
   SaveGraph(ChartMy, "My");
   SaveGraph(ChartNst, "Nst");
   SaveGraph(ChartFoc, "Foc");
   SaveGraph(ChartX0, "Xg");
   SaveGraph(ChartY0, "Yg");
}
//---------------------------------------------------------------------------
void TFormGraphOrient::ApplySeriesSetting(int CheckLine, AnsiString Title, TColor color)
{
//  int CheckLine=MainForm->SeriesID[ListBoxSeries->ItemIndex];
//  MainForm->FilesName[CheckLine]=EditFileName->Text;
//  MainForm->SeriesTitle[CheckLine]=EditSeriesName->Text;
//  ListBoxSeries->Items->Strings[ListBoxSeries->ItemIndex]=EditSeriesName->Text;   //???

//  MainForm->SeriesColor[CheckLine]=ColorBoxSeries->Selected;
//  MainForm->SeriesLineWidth[CheckLine]=StrToInt(EditLineWidth->Text);

  for (int num=NumGraph*CheckLine; num<NumGraph*(CheckLine+1); num++)
  {
	if (LineSeries[num]!=NULL)
	{
	  LineSeries[num]->Title=Title;
	  LineSeries[num]->SeriesColor=color;
	  LineSeries[num]->Pointer->Visible=true;
	  LineSeries[num]->Pointer->Style=psCircle;
	  LineSeries[num]->Pointer->Size=3;
	  LineSeries[num]->Pointer->Pen->Visible=false;
	  LineSeries[num]->Pen->Visible=false;
//	  LineSeries[num]->LinePen->Width=StrToInt(EditLineWidth->Text);
	}
  }
}
//---------------------------------------------------------------------------
void TFormGraphOrient::SetVisible(int CheckLine, bool tf)
{
  for (int num=NumGraph*CheckLine; num<NumGraph*(CheckLine+1); num++)
  {
	if (LineSeries[num]!=NULL)
	{
	  LineSeries[num]->Visible=tf;
	}
  }
}

//��������� �������� �� ������ �����
//---------------------------------------------------------------------------
void __fastcall TFormGraphOrient::FormCreate(TObject *Sender)
{
  Label1->Caption="����� � ���� ������: 0";
  Label2->Caption="���������� � ���������: 0";
  Label3->Caption="������������ ��������: 0";
  Label4->Caption="���������� ��������: 0";
  Label5->Caption="������ ��� ������: 0";
  Label6->Caption="����� ����� �����: 0";

//InitFrameSeries
	for (int i=0; i < MaxBlockSeries; i++) {
		BlockSeries[i]= new TChartShape(this->Chart1);
		Chart1->AddSeries(this->BlockSeries[i]);
		BlockSeries[i]->Style=chasRectangle;
		BlockSeries[i]->X0=0;
		BlockSeries[i]->X1=1024;
		BlockSeries[i]->Y0=0;
		BlockSeries[i]->Y1=0;
		BlockSeries[i]->Color=clYellow;
		BlockSeries[i]->Transparency=70;
	}

//InitFrameSeries
	for (int i=0; i < MaxFrameSeries; i++) {
		FrameSeries[i]= new TChartShape(this->Chart1);
		Chart1->AddSeries(this->FrameSeries[i]);
		FrameSeries[i]->Style=chasRectangle;
		FrameSeries[i]->X0=0;
		FrameSeries[i]->X1=0;
		FrameSeries[i]->Y0=0;
		FrameSeries[i]->Y1=0;
		FrameSeries[i]->Color=clGreen;
		FrameSeries[i]->Transparency=70;
	}

	InitTableWindows();
	InitTableObjects();
}
//---------------------------------------------------------------------------
void TFormGraphOrient::InitTableWindows(void)
{
	int k=0;

	TableWindowsInfo->RowCount=2;
	TableWindowsInfo->ColCount=8;
	TableWindowsInfo->FixedCols=0;
	TableWindowsInfo->FixedRows=1;
/**/
	TableWindowsInfo->Cells[k++][0]="�";
	TableWindowsInfo->Cells[k++][0]="Mv";
	TableWindowsInfo->Cells[k++][0]="Xstart";
	TableWindowsInfo->Cells[k++][0]="Ystart";
//	TableWindowsInfo->Cells[k++][0]="Width";
//	TableWindowsInfo->Cells[k++][0]="Height";
//	TableWindowsInfo->Cells[k++][0]="� CAT";
	TableWindowsInfo->Cells[k++][0]="Mean";
	TableWindowsInfo->Cells[k++][0]="Sigma";
	TableWindowsInfo->Cells[k++][0]="Level";
	TableWindowsInfo->Cells[k++][0]="CountObj";
/**/
}
void TFormGraphOrient::PrintTableWindows(const struct CadrInfo &mCadr)
{
	if (mCadr.CountWindows) {
		TableWindowsInfo->RowCount=mCadr.CountWindows+TableWindowsInfo->FixedRows;
		/**/
		for (int i=0; i<mCadr.CountWindows; i++) {
			int k=0;
			TableWindowsInfo->Cells[k++][i+1]=String(i+1);
			TableWindowsInfo->Cells[k++][i+1]=FloatToStrF(mCadr.WindowsList[i].Mv, ffFixed,6,2);
			TableWindowsInfo->Cells[k++][i+1]=String(mCadr.WindowsList[i].Xstart);
			TableWindowsInfo->Cells[k++][i+1]=String(mCadr.WindowsList[i].Ystart);
			TableWindowsInfo->Cells[k++][i+1]=FloatToStrF(mCadr.WindowsList[i].Mean, ffFixed,6,2);
			TableWindowsInfo->Cells[k++][i+1]=FloatToStrF(mCadr.WindowsList[i].Sigma, ffFixed,6,2);
			TableWindowsInfo->Cells[k++][i+1]=String(mCadr.WindowsList[i].Level);
			TableWindowsInfo->Cells[k++][i+1]=String(mCadr.WindowsList[i].CountObj);
	//		TableWindowsInfo->Cells[3][i]=String(mCadr.WindowsList[i].Width);
	//		TableWindowsInfo->Cells[4][i]=String(mCadr.WindowsList[i].Height);
	//		TableWindowsInfo->Cells[4][i]=String(mCadr.WindowsList[i].StarID);
		}  /**/
	}
	else
	{
		TableWindowsInfo->RowCount=TableWindowsInfo->FixedRows+1;
		for (int k=0; k<TableWindowsInfo->ColCount; k++) {
			TableWindowsInfo->Cells[k][1]="";
        }
    }
}

void TFormGraphOrient::InitTableObjects(void)
{
	int k=0;

	TableObjectsInfo->RowCount=2;
	TableObjectsInfo->ColCount=10;
	TableObjectsInfo->FixedCols=0;
	TableObjectsInfo->FixedRows=1;

	TableObjectsInfo->Cells[k++][0]="�";
	TableObjectsInfo->Cells[k++][0]="Xloc";
	TableObjectsInfo->Cells[k++][0]="Yloc";
	TableObjectsInfo->Cells[k++][0]="Bright";
	TableObjectsInfo->Cells[k++][0]="CountPix";
	TableObjectsInfo->Cells[k++][0]="Star �";
	TableObjectsInfo->Cells[k++][0]="Mv";
	TableObjectsInfo->Cells[k++][0]="Sp";
	TableObjectsInfo->Cells[k++][0]="Dx, mkm";
	TableObjectsInfo->Cells[k++][0]="Dy, mkm";
}

void TFormGraphOrient::PrintTableObjects(const struct CadrInfo &mCadr)
{
	if (mCadr.CountLocalObj) {
		TableObjectsInfo->RowCount=mCadr.CountLocalObj+TableWindowsInfo->FixedRows;

		for (int i=0; i<mCadr.CountLocalObj; i++) {
			if (mCadr.ObjectsList[i].StarID) {
//				for (int j=0; j<TableObjectsInfo->ColCount; j++)
//					TableObjectsInfo->Cells[j][i+1]->Color=clRed;
			}
			int k=0;
			TableObjectsInfo->Cells[k++][i+1]=String(i+1);
			TableObjectsInfo->Cells[k++][i+1]=FloatToStrF(mCadr.ObjectsList[i].X, ffFixed,10,4);
			TableObjectsInfo->Cells[k++][i+1]=FloatToStrF(mCadr.ObjectsList[i].Y, ffFixed,10,4);
			TableObjectsInfo->Cells[k++][i+1]=FloatToStrF(mCadr.ObjectsList[i].Bright, ffFixed,10,2);
			TableObjectsInfo->Cells[k++][i+1]=String(mCadr.ObjectsList[i].Square);
			TableObjectsInfo->Cells[k++][i+1]=String(mCadr.ObjectsList[i].StarID);
			TableObjectsInfo->Cells[k++][i+1]=FloatToStrF(mCadr.ObjectsList[i].Mv, ffFixed,6,2);
			TableObjectsInfo->Cells[k++][i+1]=String(mCadr.ObjectsList[i].Sp);
			TableObjectsInfo->Cells[k++][i+1]=FloatToStrF(mCadr.ObjectsList[i].Dx*1000., ffFixed,8,2);
			TableObjectsInfo->Cells[k++][i+1]=FloatToStrF(mCadr.ObjectsList[i].Dy*1000., ffFixed,8,2);
		}
	}
	else
	{
		TableObjectsInfo->RowCount=TableObjectsInfo->FixedRows+1;
		for (int k=0; k<TableObjectsInfo->ColCount; k++) {
			TableObjectsInfo->Cells[k][1]="-";
        }
    }
}

void TFormGraphOrient::ClearAnimate(void)
{
//AnimateShapes
	for (int i=0; i<MaxBlockSeries; i++)
		this->BlockSeries[i]->Visible=false;
	for (int i=0; i<MaxFrameSeries; i++)
		this->FrameSeries[i]->Visible=false;

//AnimatePoints
	Series9->Clear();
	Series1->Clear();
	Series2->Clear();
	Series3->Clear();
//WindowsBar
	Series4->Clear();
	Series5->Clear();
	Series6->Clear();
//ObjectsBar
	Series7->Clear();
	Series8->Clear();

}

void TFormGraphOrient::SetVisibleLabelFrame(bool isVisible)
{
	for (int i=0; i<MaxFrameSeries; i++)
	{
		FrameSeries[i]->Marks->Visible=isVisible;
	}
}

void TFormGraphOrient::DrawBlock(const struct CadrInfo &mCadr)
{
unsigned short CountLines, CountBlock, TabTakeAway[MaxBlockSeries][2];
unsigned short Border=10;

	Chart1->LeftAxis->Automatic=false;
	Chart1->LeftAxis->Minimum=-Border;
	Chart1->LeftAxis->Maximum=mCadr.ImageHeight+Border;
	Chart1->BottomAxis->Automatic=false;
	Chart1->BottomAxis->Minimum=-Border;
	Chart1->BottomAxis->Maximum=mCadr.ImageWidth+Border;

//DrawBlocks()
	CountLines=0;
	CountBlock=mCadr.CountBlock;
	if (CountBlock>MaxBlockSeries) {
		ShowMessage("��������� ����� ���������� ������!");
		CountBlock=MaxBlockSeries;
	}

	for (int i=0; i<CountBlock; i++)
	{
		if (mCadr.IsBinary)
		{
			TabTakeAway[i][0]=mCadr.LinesList[i].Start>>1;
			TabTakeAway[i][1]=mCadr.LinesList[i].Height>>1;
		}
		BlockSeries[i]->Visible=true;
		BlockSeries[i]->Y0=TabTakeAway[i][0];
		BlockSeries[i]->Y1=TabTakeAway[i][0]+TabTakeAway[i][1];
		CountLines+=mCadr.LinesList[i].Height;
	}

//DrawWindows()
	for (int i=0; i<mCadr.CountWindows; i++)
	{
		FrameSeries[i]->X0=mCadr.WindowsList[i].Xstart;
		FrameSeries[i]->X1=mCadr.WindowsList[i].Xstart
							  +mCadr.WindowsList[i].Width;
		FrameSeries[i]->Y0=mCadr.WindowsList[i].Ystart;
		FrameSeries[i]->Y1=mCadr.WindowsList[i].Ystart
							  +mCadr.WindowsList[i].Height;
	}

//ShowLabelWindows()
	AnsiString LabelWindow;
	for (int i=0; i<mCadr.CountWindows; i++)
	{
		FrameSeries[i]->Marks->Item[0]->Visible=false;
		FrameSeries[i]->Marks->Item[1]->Visible=true;
		FrameSeries[i]->Marks->Item[1]->Text->Clear();

		LabelWindow.sprintf("%d) Mv = %.2f,\r\n � CAT = %ld", i+1,
					mCadr.WindowsList[i].Mv, mCadr.WindowsList[i].StarID);
		FrameSeries[i]->Marks->Item[1]->Text->Add(LabelWindow);
		FrameSeries[i]->Visible=true;
	}

//DrawBarWindows()
	for (int i=0; i<mCadr.CountWindows; i++)
	{
		Series4->AddXY(i+1,mCadr.WindowsList[i].Mean);
		Series5->AddXY(i+1,mCadr.WindowsList[i].Sigma);
		Series6->AddXY(i+1,mCadr.WindowsList[i].CountObj);
	}

//DrawBarObjects()
	if (mCadr.CountWindows)
	{
		unsigned short *ObjShiftWnd, CountLocalObj;
		TColor CurColor, ColorBrightDef=Series7->Color;
		TColor ColorBright[]={ColorBrightDef, clYellow, clRed};
		ObjShiftWnd=new unsigned short [mCadr.CountWindows];
		CountLocalObj=0;
		for (int k=0;k<mCadr.CountWindows; k++)
		{
			if (!k) ObjShiftWnd[k]=0;
			else ObjShiftWnd[k]=ObjShiftWnd[k-1]+mCadr.WindowsList[k-1].CountObj;

			int j=0;
			for (int i=ObjShiftWnd[k]; i<ObjShiftWnd[k]+mCadr.WindowsList[k].CountObj; i++)
			{
				if (FormAnimateSetting->CheckBoxApplyWindowsSeries->Checked) {
					switch (j+1)
					{
						case 1: {
							CurColor=FormAnimateSetting->ShapeColorOneObjTable->Brush->Color;
							break;
						}
						case 2: {
							CurColor=FormAnimateSetting->ShapeColorTwoObjTable->Brush->Color;
							break;
						}
						default:
						{
							CurColor=FormAnimateSetting->ShapeColorThreeObjTable->Brush->Color;
							break;
						}
					}
				}
				else CurColor=ColorBright[j];
				Series7->AddXY((k+1)+0.2*j,mCadr.ObjectsList[i].Bright, "", CurColor);
				Series8->AddXY((k+1)+0.2*j,mCadr.ObjectsList[i].Square, "", CurColor);
				CountLocalObj++;
				j++;
	//			WndObj[i]=k;
			}
		}

		if (CountLocalObj!=mCadr.CountLocalObj) {
			ShowMessage("�������������� ����� ���������� � ������� ObjFrag[]!");
		}
		delete [] ObjShiftWnd;

	}
	else
	{
		for (int i=0; i<mCadr.CountLocalObj; i++)
		{
			Series7->AddXY(i+1,mCadr.ObjectsList[i].Bright);
			Series8->AddXY(i+1,mCadr.ObjectsList[i].Square);
		}
	}

  AnsiString LabelStar;
//  Series1->Marks->Visible=true;
  for (int i=0; i<mCadr.CountStars; i++){

//	  LabelStar="Mv="+FloatToStrF(mCadr.StarsList[i].Mv,ffFixed,8,2);
	  Series1->AddXY(mCadr.StarsList[i].X,mCadr.StarsList[i].Y);//,LabelStar);
  }

  Label1->Caption="����� � ���� ������: "+IntToStr(mCadr.CountStars);
  Label2->Caption="���������� � ���������: "+IntToStr(mCadr.CountWindows);
  Label3->Caption="������������ ��������: "+IntToStr(mCadr.CountLocalObj);
  Label4->Caption="���������� ��������: "+IntToStr(mCadr.CountDeterObj);
  Label5->Caption="������ ��� ������: "+IntToStr(mCadr.CountBlock);

  if (CountLines==mCadr.CountLines)
	this->Label6->Caption="����� ����� �����: "+IntToStr(mCadr.CountLines);
  else
	this->Label6->Caption="������! ����� �����: "+IntToStr(CountLines)
	+" ������ "+IntToStr(mCadr.CountLines);
}

void TFormGraphOrient::DrawAnimate(const struct CadrInfo &mCadr)
{
double X0, Y0, X1, Y1, Dx, Dy, Ist, Nel;

  EditTimeDev->Text=FloatToStrF(mCadr.Time,ffFixed, 10,3);
  ClearAnimate();

  for (int i = 0; i < mCadr.CountLocalObj; i++) {
	   X0=mCadr.ObjectsList[i].X;
	   Y0=mCadr.ObjectsList[i].Y;
	   Nel=mCadr.ObjectsList[i].Square;
	   Dx=mCadr.ObjectsList[i].Dx;
	   Dy=mCadr.ObjectsList[i].Dy;
	   if ((!mCadr.ObjectsList[i].StarID)&&(!Dx)&&(!Dy)) {
//		   Series2->AddXY(X0, Y0, "", clBlue);
		   Series9->AddBubble(X0, Y0,(int)(3*sqrtm(Nel)+0.5),"",clBlue);
	   }
	   else
	   {
		   X1=X0-mCadr.ObjectsList[i].Dx*10000.;
		   Y1=Y0-mCadr.ObjectsList[i].Dy*10000.;
//		   Series2->AddXY(X0, Y0, "", clGreen);
		   Series9->AddBubble(X0, Y0,(int)(3*sqrtm(Nel)+0.5),"",clGreen);
		   Series3->AddArrow(X0, Y0, X1, Y1, "", clRed);
	   }
//	   Series9->AddBubble(mCadr.StarsList[i].X,mCadr.StarsList[i].Y,
//						(int)(sqrtm(mCadr.StarsList[i].Square)+1));

  }
  DrawBlock(mCadr);
  PrintTableWindows(mCadr);
  PrintTableObjects(mCadr);
  DrawFragment(mCadr);
}


void TFormGraphOrient::DrawFragment(const struct CadrInfo &mCadr)
{
	for(unsigned int i=0;i<ImageVector.size();i++)
	{
     	ImageVector[i]->Free();
	}
	ImageVector.clear();

	for(unsigned int i=0;i<BitmapVector.size();i++)
	{
		delete BitmapVector[i];
	}
	BitmapVector.clear();

	AnsiString NeededDirectory=GetCurrentDir()+"\\Frag_"+FileTitle;
	if (!TDirectory::Exists(NeededDirectory))
	{
		Application->MessageBox(L"������ �������� ���� � ���������� ����������", L"������", MB_OK);
		return;
	}

   TStringDynArray FileNameList;
   FileNameList=TDirectory::GetFiles(NeededDirectory);
   AnsiString TimePrStr=FloatToStrF(mCadr.Time,ffFixed,10,10);
   TStringDynArray TimePrTwoParts=System::Strutils::SplitString(TimePrStr,",");
   TimePrTwoParts[1].Delete(4,TimePrTwoParts[1].Length()-1);
   TimePrTwoParts[1]="00000"+TimePrTwoParts[1];

   AnsiString FragmentFileStr;
   for(int CurrentFileName=0;CurrentFileName<FileNameList.Length;CurrentFileName++)
   {

		if(System::Strutils::AnsiContainsStr(FileNameList[CurrentFileName],TimePrTwoParts[0]) &&
		  System::Strutils::AnsiContainsStr(FileNameList[CurrentFileName],TimePrTwoParts[1]))
		  {
				 FragmentFileStr=FileNameList[CurrentFileName];
				 break;
		  }

   }

   if(FragmentFileStr!="")
   {

   FILE *FragmentFile;
   FragmentFile=fopen(FragmentFileStr.c_str(),"rb");
   if(!FragmentFile)
   {
		ShowMessage(AnsiString("�� ������� ������� ���� ")+FragmentFileStr.c_str());
		return;
   }

	int HeightOffset=0;
	int WidthOffset=0;
	const int OffsetStep=150;
	for(int CurrentFragment=0;CurrentFragment<mCadr.CountWindows;CurrentFragment++)
	{


		int FragmentWidth=mCadr.WindowsList [CurrentFragment].Width;
		int FragmentHeight=mCadr.WindowsList [CurrentFragment].Height;
		int FragmentSize= FragmentWidth*FragmentHeight;
		unique_ptr<unsigned short[]> RawFragment(new unsigned short [FragmentSize]);
		fread(RawFragment.get(),sizeof(unsigned short),FragmentSize,FragmentFile);
		BitmapVector.push_back(new TBitmap());
		BitmapVector.back()->PixelFormat= pf24bit;
		BitmapVector.back()->Width = FragmentWidth;
		BitmapVector.back()->Height = FragmentHeight;

		TRGBTriple *BitmapLine;
	for (int currentColumn = 0; currentColumn < FragmentWidth; currentColumn++)
	{
		BitmapLine = (TRGBTriple*) BitmapVector.back()->ScanLine[currentColumn];
		for (unsigned int currentRow = 0, adress = 0; currentRow < FragmentHeight; currentRow++, adress = currentColumn * 24 + currentRow)
		{           // ������� �������� 255=4095/16
					BitmapLine[currentRow].rgbtBlue = RawFragment[adress]/16;
					BitmapLine[currentRow].rgbtGreen = RawFragment[adress]/16;
					BitmapLine[currentRow].rgbtRed = RawFragment[adress]/16;
		}
	}

	ImageVector.push_back(new TImage(ShowFragmentTab));
	ImageVector.back()->Width=BitmapVector.back()->Width*5;
	ImageVector.back()->Height=BitmapVector.back()->Height*5;
	ImageVector.back()->Left=OffsetStep*WidthOffset;

	// ����������� �������� �� ������
	++WidthOffset;

	// ���� ���������� ������� ���� �������� ��������� �����������
	// ���������� ������� ���� ���� ���������, ���������� �������� �� ������,
	// ����������� �������� �� ������

	if(ImageVector.back()->Left+ImageVector.back()->Width >
	 ShowFragmentTab->Width)
	{
		WidthOffset=0;
		HeightOffset+=150;
	}

	ImageVector.back()->Top=HeightOffset;


	ImageVector.back()->Canvas->
	StretchDraw(Rect(0, 0, ImageVector.back()->Width, ImageVector.back()->Height),BitmapVector.back());
	ImageVector.back()->SetParentComponent(ShowFragmentTab);
	}

   }


}

void __fastcall TFormGraphOrient::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
	EditNumCadrChange(this);
}
//---------------------------------------------------------------------------


void __fastcall TFormGraphOrient::EditNumCadrChange(TObject *Sender)
{
struct CadrInfo CurCadr;
int cnt=StrToInt(EditNumCadr->Text);


	if (!this->GetCadrInfo(cnt, CurCadr))
	{
		  DrawAnimate(CurCadr);
	}

}
//---------------------------------------------------------------------------


void __fastcall TFormGraphOrient::TableObjectsInfoDrawCell(TObject *Sender, int ACol,
		  int ARow, TRect &Rect, TGridDrawState State)
{

	TStringGrid *thisGrid=(TStringGrid*)Sender;

	if (FormAnimateSetting->CheckBoxFillTableWindows->Checked) {
		if (ARow)
		{
			unsigned long StarID;
			float Dx, Dy;
			StarID=StrToInt(thisGrid->Cells[5][ARow]);
			Dx=StrToFloat(thisGrid->Cells[8][ARow]);
			Dy=StrToFloat(thisGrid->Cells[9][ARow]);
			if ((!StarID)&&(!Dx)&&(!Dy))
				thisGrid->Canvas->Brush->Color=FormAnimateSetting->ShapeColorLocObjTable->Brush->Color;
			else thisGrid->Canvas->Brush->Color=FormAnimateSetting->ShapeColorDetObjTable->Brush->Color;

			thisGrid->Canvas->FillRect(Rect);
			thisGrid->Canvas->TextOutW(Rect.Left, Rect.Top, thisGrid->Cells[ACol][ARow]);
		}
	}
}
//---------------------------------------------------------------------------


void __fastcall TFormGraphOrient::TableWindowsInfoDrawCell(TObject *Sender, int ACol,
		  int ARow, TRect &Rect, TGridDrawState State)
{

	TStringGrid *thisGrid=(TStringGrid*)Sender;

	if (FormAnimateSetting->CheckBoxFillTableWindows->Checked) {
		if ((ARow)&&(thisGrid->Cells[7][ARow]!=""))
		{

			if (thisGrid->Cells[7][ARow]=="0")
				thisGrid->Canvas->Brush->Color=FormAnimateSetting->ShapeColorZeroObjTable->Brush->Color;
			else if ((thisGrid->Cells[7][ARow]=="1"))
				thisGrid->Canvas->Brush->Color=FormAnimateSetting->ShapeColorOneObjTable->Brush->Color;
			else if ((thisGrid->Cells[7][ARow]=="2"))
				thisGrid->Canvas->Brush->Color=FormAnimateSetting->ShapeColorTwoObjTable->Brush->Color;
			else
				thisGrid->Canvas->Brush->Color=FormAnimateSetting->ShapeColorThreeObjTable->Brush->Color;

			thisGrid->Canvas->FillRect(Rect);
			thisGrid->Canvas->TextOutW(Rect.Left, Rect.Top, thisGrid->Cells[ACol][ARow]);
		}
	}
}
//---------------------------------------------------------------------------


void GetFileTitles(AnsiString file_name, AnsiString *file_title)
{
	  AnsiString file_ext;

	  file_ext =ExtractFileName(file_name);
	  if (file_ext.LastDelimiter("."))
		*file_title=file_ext.SubString(0,file_ext.LastDelimiter(".")-1);
	  else *file_title=file_ext.SubString(0,file_ext.Length());
}


	// ��������� � �������������� �������� ����
			AnsiString TFormGraphOrient::SortRawFlashFile(const AnsiString &RawFileName)
			{
			   FILE* RawFlashFile;
			   RawFlashFile=fopen(RawFileName.c_str(),"rb");
			   if(!RawFlashFile)
			   {
					return "";
			   }

			  std::vector<RawFileInfo>  RawFileInfoVector;
			  int Marker;
			   while(!feof(RawFlashFile))
			   {
					fread(&Marker,sizeof(int),1,RawFlashFile);
					if (GetInt(Marker)==0x55550000)
					{
							RawFileInfo CurrentInfo;

							// ������� ������� �� ������ ������������ ���������
							CurrentInfo.Pos =  ftell(RawFlashFile)-4 ;

							if(RawFileInfoVector.size()==0)
							{
								CurrentInfo.Size = 0;
							}
							else
							{
								CurrentInfo.Size=CurrentInfo.Pos - RawFileInfoVector.back().Pos;
							}

							unsigned short SequenceCounterAndAdress [2];
							fread(&SequenceCounterAndAdress,sizeof(short),2,RawFlashFile);
							CurrentInfo.SecuenceCounter = SequenceCounterAndAdress[0];
							RawFileInfoVector.push_back(CurrentInfo);

					}
			   }

			   // �������� ������� ��� ��������� ���������
				fseek (RawFlashFile, 0, SEEK_END);
				RawFileInfo LastInfo;
				LastInfo.Pos= ftell(RawFlashFile);
				LastInfo.Size=LastInfo.Pos - RawFileInfoVector.back().Pos;
				// ��� ���� ����� ����� ���������� ������ ��� � �����
				LastInfo.SecuenceCounter= LONG_MAX;
				RawFileInfoVector.push_back(LastInfo);


			   // ������� ��� ����������
			struct {

				bool operator()(const RawFileInfo& a,const RawFileInfo& b)
				{
					return a.SecuenceCounter < b.SecuenceCounter;
				}

			} FlashCompare ;


			   std::sort(RawFileInfoVector.begin(),RawFileInfoVector.end(),FlashCompare);

			   FILE * SortedFile;
			   AnsiString SortedFlashFileName= GetCurrentDir()+"\\flash_sorted.dat";
			   SortedFile = fopen(SortedFlashFileName.c_str(),"wb");

			   if(!SortedFile)
			   {
					return "";
			   }

			   // -1 �.� ������ ����� � ��������� ��������
			   for(unsigned int CurrentFlashStruct=0; CurrentFlashStruct< RawFileInfoVector.size()-1 ;CurrentFlashStruct++)
			   {
					fseek(RawFlashFile,RawFileInfoVector[CurrentFlashStruct].Pos,SEEK_SET);
					char* CurrentStructBuffer= new char [RawFileInfoVector[CurrentFlashStruct+1].Size];
					fread(CurrentStructBuffer,sizeof(char),RawFileInfoVector[CurrentFlashStruct+1].Size,RawFlashFile);
					fwrite(CurrentStructBuffer,sizeof(char),RawFileInfoVector[CurrentFlashStruct+1].Size,SortedFile);
					delete [] CurrentStructBuffer;
			   }

			   fclose(RawFlashFile);
			   fclose(SortedFile);
			   return SortedFlashFileName;
			}




int TFormGraphOrient::GetCadrInfo(int NC, struct CadrInfo &mCadr)
{
	if ((NC>=0)&&(NC<vCadrInfo.size()))
		mCadr=vCadrInfo[NC];
	else
		return -1;

	return 0;
}


void __fastcall TFormGraphOrient::MenuOptionsClick(TObject *Sender)
{
   FormAnimateSetting->Show();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphOrient::FormClose(TObject *Sender, TCloseAction &Action)

{
		vCadrInfo.clear();
		Action=caFree;
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphOrient::MenuOpenClick(TObject *Sender)
{
  if (OpenDialog1->Execute()) {
		vCadrInfo.clear();
		FileName=OpenDialog1->FileName;
		SetCurrentDir(ExtractFileDir(FileName));
		GetFileTitles(FileName,&FileTitle);

		if(this->SortFileCheckBox->Checked)
		{
			FileName=SortRawFlashFile(FileName);
			if(FileName=="")
			{
				ShowMessage("�� ������� ������������� ����. ��������, �������� ���� �� ������� �������");
				return;
			}
		}

		FILE *ffrag;
		FILE *fflesh;
		FILE *ftxt;
		FILE *floc;

		fflesh=fopen(FileName.c_str(),"rb");
		FileName=FileTitle+"_sec.dat";
		ffrag =fopen(FileName.c_str(),"wb");
		ftxt= fopen((FileTitle+"_LogSec.txt").c_str(),"wt");

		unsigned short buf[2];
		unsigned int CntWord=0;

		int Marker;
		while(!feof(fflesh))
		{
			fread(&Marker,sizeof(int),1,fflesh);
			if (GetInt(Marker)==0x55550000)
			{
				fread(&buf,sizeof(short),2,fflesh);
				fprintf(ftxt,"%6d 0x%04x %10d\n",buf[0],buf[1], CntWord*sizeof(CntWord));
				CntWord=2;
			}
			else    {
				fwrite(&Marker,sizeof(int),1,ffrag);
				CntWord++;
			}
		}
		fclose(fflesh);
		fclose(ffrag);
		fclose(ftxt);

		fflesh=fopen(FileName.c_str(),"rb");
		ftxt=fopen((FileTitle+".txt").c_str(),"wt");
		
		
		
		CurDir=GetCurrentDir();
		FragDir=CurDir+"\\Frag_"+FileTitle;
	    LocDir=CurDir+"\\Loc_"+FileTitle;
		CreateDir(FragDir);
		CreateDir(LocDir);

		
		FILE *flog_pix;
		flog_pix=fopen((FileTitle+"_LogPix.txt").c_str(),"wt");
		fprintf(flog_pix,"%6s  NC  %6s %10s %10s %10s %8s\n",
						"SerNum","CntRec","T","Tbshv","Tpr","NumPix");


		FILE *flog_reg;
		flog_reg=fopen((FileTitle+"_LogReg.txt").c_str(),"wt");
		fprintf(flog_reg,"%6s %6s %10s %10s %10s %8s %4s %4s\n",
						"SerNum","CntRec","T","Tbshv","Tpr","CntErr", "Reg", "Val");

		FILE *flog_orient;
		flog_orient=fopen((FileTitle+"_LogOrient.txt").c_str(),"wt");
		fprintf(flog_orient,"%6s RG %6s %10s %10s %10s %6s %8s %8s %8s %8s %10s %10s %10s ",
						"SerNum","CntRec","T","Tbshv","Tpr","Stat","NumProg",
						"NumFrag","NumLoc","NumDet","al,deg","dl,deg","Az,deg");

		
		fprintf(flog_orient,"%10s %8s %8s %8s %12s %12s %12s %8s %8s %8s %8s\n",
						"m_cur,mm","Temp","Texp,ms","dT,c","Wx","Wy","Wz",
						"mean_bf","sigma_bf","mean_fr","sigma_fr");


		this->NumLine=0;
		this->CreateGraph(this->NumLine);
		this->ApplySeriesSetting(this->NumLine, "�����-2�",
											clBlue);//ColorRes[FormGraphOrient->NumLine]);
		DataPixHeader mDataPixHdr;
		while (!feof(fflesh))
		{
		  fread(&Marker,sizeof(int),1,fflesh);
		  int NumPixH, PixMas[3];

		  switch (GetInt(Marker))
		  {
			case PIX_0_MARKER:
			{

			  fread(&mDataPixHdr,sizeof(struct DataPixHeader),1,fflesh);
			  ChangeWordPix(mDataPixHdr);
			  PrintDataPix(ftxt, mDataPixHdr, 1);

			  NumPixH=mDataPixHdr.NumPix;
			  if (mDataPixHdr.NumPix%2) NumPixH++;

			  for (int i=0; i<NumPixH; i=i+2)
			  {
				fread(PixMas, sizeof (int),3, fflesh);
				fprintf(ftxt,"%6d %6d %6d %6d\n",i+1, PixMas[0]>>16,PixMas[0]&0x0000FFFF, PixMas[1]>>16);
				fprintf(ftxt,"%6d %6d %6d %6d\n",i+2, PixMas[1]&0x0000FFFF,PixMas[2]>>16, PixMas[2]&0x0000FFFF);
			  }
			  fprintf(flog_pix,"    %02d PIX1 %6d %10ld %10ld %6ld.%03ld %8d\n",
					  mDataPixHdr.SerNum, mDataPixHdr.CntRecord, mDataPixHdr.T, mDataPixHdr.Tbshv,
					  mDataPixHdr.Tpr_sec, mDataPixHdr.Tpr_msec, mDataPixHdr.NumPix);
			  break;
			}

			case PIX_1_MARKER:
			{
//			  DataPixHeader mDataPixHdr;
			  fread(&mDataPixHdr.T,sizeof(struct DataPixHeader)-4,1,fflesh);
			  ChangeWordPix(mDataPixHdr);
			  PrintDataPix(ftxt, mDataPixHdr,2);

			  NumPixH=mDataPixHdr.NumPix;
			  if (mDataPixHdr.NumPix%2) NumPixH++;

			  for (int i=0; i<NumPixH; i=i+2)
			  {
				fread(PixMas, sizeof (int),3, fflesh);
				fprintf(ftxt,"%6d %6d %6d %6d\n",i+1, PixMas[0]>>16,PixMas[0]&0x0000FFFF, PixMas[1]>>16);
				fprintf(ftxt,"%6d %6d %6d %6d\n",i+2, PixMas[1]&0x0000FFFF,PixMas[2]>>16, PixMas[2]&0x0000FFFF);
			  }
			  fprintf(flog_pix,"    %02d PIX2 %6d %10ld %10ld %6ld.%03ld %8d\n",
					  mDataPixHdr.SerNum, mDataPixHdr.CntRecord, mDataPixHdr.T, mDataPixHdr.Tbshv,
					  mDataPixHdr.Tpr_sec, mDataPixHdr.Tpr_msec, mDataPixHdr.NumPix);
			  break;
			}

			case HO_MARKER:
			{
              DataNO mDataNO;
			  fread(&mDataNO,sizeof(struct DataNO_st),1,fflesh);
			  if ((mDataNO.NumL[0]>MaxObj)||(mDataNO.NumL[1]>MaxObj))
			  {
				fprintf(ftxt,"\n������ ������ ������!\n");
				break;
	          }

			  fread(&mDataNO.RsLocT[0][0][0],sizeof(float)*4,mDataNO.NumL[0],fflesh);
			  fread(&mDataNO.RsLocT[1][0][0],sizeof(float)*4,mDataNO.NumL[1],fflesh);
			  fread(&mDataNO.NumLoc[0],sizeof(struct DataNO_fin),1,fflesh);

			  ChangeWordNO(mDataNO);
			  PrintDataNO(ftxt, mDataNO);

			  CadrInfo mCadrInfo;
			  ConvertDataNO(mDataNO, mCadrInfo,0);
			  vCadrInfo.push_back(mCadrInfo);
			  ConvertDataNO(mDataNO, mCadrInfo,1);
			  vCadrInfo.push_back(mCadrInfo);

			  double al=0;
			  double dl=0;
			  double Az=0;

			  if (!mDataNO.res_stat)
			  {
				dl=asinm(mDataNO.M_ornt[2][2])*RTD;
				al=atan2m(mDataNO.M_ornt[2][1],mDataNO.M_ornt[2][0])*RTD;   if (al<0)  al+=360.;
				Az=atan2m(mDataNO.M_ornt[0][2],mDataNO.M_ornt[1][2])*RTD;   if (Az<0)  Az+=360.;
			  }


			  fprintf(flog_orient,"    %02d NO %6d %10ld %10ld %6ld.%03ld 0x%04x %8d ",
					  mDataNO.SerNum, mDataNO.CntRecord, mDataNO.T, mDataNO.Tbshv,
					  mDataNO.Tpr_sec, mDataNO.Tpr_msec, mDataNO.res_stat, 0);
			  fprintf(flog_orient,"%8d %8d %8d %10.6f %10.6f %10.6f %10.6f %8.2f %8d %8.2f ",
					  mDataNO.NumL[0], mDataNO.NumL[1], mDataNO.NumDet, al, dl, Az,
					  mDataNO.m_cur, mDataNO.Temp, mDataNO.StarExp, mDataNO.TimeExp);
			  fprintf(flog_orient,"%12.4f %12.4f %12.4f %8.2f %8.2f %8.2f %8.2f\n",
			  mDataNO.Wop[0]*RTS,mDataNO.Wop[1]*RTS,mDataNO.Wop[2]*RTS, 0., 0., 0., 0.);
/**
			  for (int j=0; j<2; j++)
	          {
				sprintf(loc_name,"%s\\Loc_%06d_%08d_%02d.txt",LocDir.c_str(),mDataNO.T,mDataNO.Tbshv,j+1);
				floc=fopen(loc_name,"wt");
				for (int i=0; i<mDataNO.NumL[j]; i++)
	            {
				  fprintf(floc,"%4d %12.4f %12.4f %6.0f %6.0f\n", i+1, mDataNO.RsLocT[j][i][0],mDataNO.RsLocT[j][i][1],
				  mDataNO.RsLocT[j][i][2],mDataNO.RsLocT[j][i][3]);
				}
	            fclose(floc);
	          }
/**/
	          break;
			}

	        case SL_MARKER:
			{
              DataSLEZH mDataSLEZH;
	          fread(&mDataSLEZH,sizeof(struct DataSLEZH_st),1,fflesh);
	          if (mDataSLEZH.NumLoc>MaxObj)
			  {
	            fprintf(ftxt,"\n������ ������ ������!\n");
				break;
			  }

			  fread(&mDataSLEZH.RsLocT[0][0],sizeof(float)*4,mDataSLEZH.NumLoc,fflesh);
	          fread(&mDataSLEZH.RsLoc[0][0],sizeof(struct DataSLEZH_fin),1,fflesh);

			  ChangeWordSLEZH(mDataSLEZH);
			  PrintDataSLEZH(ftxt, mDataSLEZH);

			  CadrInfo mCadrInfo;
			  ConvertDataSLEZH(mDataSLEZH, mCadrInfo);
			  vCadrInfo.push_back(mCadrInfo);


				double al=0;
				double dl=0;
				double Az=0;

			  if (!mDataSLEZH.res_stat)
			  {
				dl=asinm(mDataSLEZH.M_ornt[2][2])*RTD;
				al=atan2m(mDataSLEZH.M_ornt[2][1],mDataSLEZH.M_ornt[2][0])*RTD;   if (al<0)  al+=360.;
				Az=atan2m(mDataSLEZH.M_ornt[0][2],mDataSLEZH.M_ornt[1][2])*RTD;   if (Az<0)  Az+=360.;
			  }


			  double mean_frag=0;
			  double sigma_frag=0;
			  for (int i=0; i<mDataSLEZH.NumFrag; i++)
	          {
				mean_frag+=mDataSLEZH.MeanFrag[i][0];
				sigma_frag+=mDataSLEZH.MeanFrag[i][1];
	          }
			  if (mDataSLEZH.NumFrag>0)
			  {
	            mean_frag/=mDataSLEZH.NumFrag;
				sigma_frag/=mDataSLEZH.NumFrag;
	          }

			  fprintf(flog_orient,"    %02d SL %6d %10ld %10ld %6ld.%03ld 0x%04x %8d ",
					  mDataSLEZH.SerNum, mDataSLEZH.CntRecord, mDataSLEZH.T, mDataSLEZH.Tbshv,
					  mDataSLEZH.Tpr_sec, mDataSLEZH.Tpr_msec, mDataSLEZH.res_stat, mDataSLEZH.NumProgFrag);
			  fprintf(flog_orient,"%8d %8d %8d %10.6f %10.6f %10.6f %10.6f %8.2f %8d %8.2f ",
					  mDataSLEZH.NumFrag,mDataSLEZH.NumLoc, mDataSLEZH.NumDet, al, dl, Az,
					  mDataSLEZH.m_cur, mDataSLEZH.Temp, mDataSLEZH.StarExp, mDataSLEZH.TimeExp);
			  fprintf(flog_orient,"%12.4f %12.4f %12.4f %8.2f %8.2f %8.2f %8.2f\n",
					  mDataSLEZH.Wop[0]*RTS,mDataSLEZH.Wop[1]*RTS,mDataSLEZH.Wop[2]*RTS,
					  mDataSLEZH.mean, mDataSLEZH.sigma,mean_frag, sigma_frag);

	//		  delete [] mCadrInfo.pLocObj;

	//SaveSLEZH_IKI
/**
			  for (int i=0; i<mDataSLEZH.NumLoc; i++) {
				StructIKI->StarsData.StarsList[i].X_coordinate=mDataSLEZH.RsLocT[i][0];
				StructIKI->StarsData.StarsList[i].Y_coordinate=mDataSLEZH.RsLocT[i][1];
				StructIKI->StarsData.StarsList[i].BrightnessObject=mDataSLEZH.RsLocT[i][2];
				StructIKI->StarsData.StarsList[i].PixelsCount=mDataSLEZH.RsLocT[i][3];
				StructIKI->StarsData.StarsList[i].NumberStar=0;
				StructIKI->StarsData.StarsList[i].StellarMagnitude=0;
	//            StructIKI->StarsData.StarsList[i].SpectralClass='';
				StructIKI->StarsData.StarsList[i].SpectralClass[0]='_';
				StructIKI->StarsData.StarsList[i].SpectralClass[1]='_';
				StructIKI->StarsData.StarsList[i].DX=0;
				StructIKI->StarsData.StarsList[i].DY=0;
			  }
			  if (!mDataSLEZH.res_stat)
			  {
				for (int i=0; i<mDataSLEZH.NumDet; i++) {
				  int iloc=mDataSLEZH.MasRes[i][1]; //������ �������  0-1
				  int ifrag=mDataSLEZH.MasRes[i][0]; //������ �������  0-1
				  StructIKI->StarsData.StarsList[iloc].NumberStar=
									(unsigned int)mDataSLEZH.XYc[ifrag][2];
				  StructIKI->StarsData.StarsList[iloc].StellarMagnitude=
												  mDataSLEZH.XYc[ifrag][3];
				  StructIKI->StarsData.StarsList[iloc].DX=mDataSLEZH.Dx[i];
				  StructIKI->StarsData.StarsList[iloc].DY=mDataSLEZH.Dy[i];
				}
				}
/**/
			  double Tpr=mDataSLEZH.Tpr_sec+mDataSLEZH.Tpr_msec/1000.;
			  if (mDataSLEZH.NumDet>=3) {
				this->LineSeries[this->NumLine*NumGraph+0]->AddXY(Tpr,al);
				this->LineSeries[this->NumLine*NumGraph+1]->AddXY(Tpr,dl);
				this->LineSeries[this->NumLine*NumGraph+2]->AddXY(Tpr,Az);
				this->LineSeries[this->NumLine*NumGraph+3]->AddXY(Tpr,mDataSLEZH.Wop[0]*RTS);
				this->LineSeries[this->NumLine*NumGraph+4]->AddXY(Tpr,mDataSLEZH.Wop[1]*RTS);
				this->LineSeries[this->NumLine*NumGraph+5]->AddXY(Tpr,mDataSLEZH.Wop[2]*RTS);
	//			FormGraphOrient->LineSeries[FormGraphOrient->NumLine*NumGraph+6]->AddXY(Tpr,mx); //����������
	//			FormGraphOrient->LineSeries[FormGraphOrient->NumLine*NumGraph+7]->AddXY(Tpr,my); //����������
				this->LineSeries[this->NumLine*NumGraph+8]->AddXY(Tpr,mDataSLEZH.m_cur);
				this->LineSeries[this->NumLine*NumGraph+9]->AddXY(Tpr,mDataSLEZH.NumFrag);
				this->LineSeries[this->NumLine*NumGraph+11]->AddXY(Tpr,mDataSLEZH.NumDet);
			  }
			  this->LineSeries[this->NumLine*NumGraph+10]->AddXY(Tpr,mDataSLEZH.NumLoc);
			  this->LineSeries[this->NumLine*NumGraph+12]->AddXY(Tpr,mean_frag);
			  this->LineSeries[this->NumLine*NumGraph+13]->AddXY(Tpr,sigma_frag);
			  this->LineSeries[this->NumLine*NumGraph+14]->AddXY(Tpr,mDataSLEZH.Temp);
/**
			  sprintf(loc_name,"%s\\Loc_%06d_%08d.txt",LocDir.c_str(),mDataSLEZH.T,mDataSLEZH.Tbshv);
			  floc=fopen(loc_name,"wt");
			  for (int i=0; i<mDataSLEZH.NumLoc; i++)
			  {
				fprintf(floc,"%4d %12.4f %12.4f %6.0f %6.0f\n", i+1, mDataSLEZH.RsLocT[i][0],mDataSLEZH.RsLocT[i][1],
				mDataSLEZH.RsLocT[i][2],mDataSLEZH.RsLocT[i][3]);
			  }
			  fclose(floc);
//**/
	//SavedataIKI()
/**
	          StructIKI = new IKI_img();

			  StructIKI->ImageData.ExposureTime=(float)mDataSLEZH.StarExp;
	          StructIKI->ImageData.WindowsData.WindowCount=mDataSLEZH.NumFrag;
	          StructIKI->ImageData.WindowsData.BottomRight=true;
			  StructIKI->ImageData.WindowsData.Info= new datawindow[mDataSLEZH.NumFrag];
	          for (int i=0; i<mDataSLEZH.NumFrag; i++) {
	            StructIKI->ImageData.WindowsData.Info[i].WindowWidth =mDataSLEZH.PfragXY0[i][1]; //������ ������� 0-1
				StructIKI->ImageData.WindowsData.Info[i].WindowHeight=mDataSLEZH.PfragXY0[i][0]; //������ ������� 0-1
				StructIKI->ImageData.WindowsData.Info[i].Average=mDataSLEZH.MeanFrag[i][1];  //������ ������� 0-1
				StructIKI->ImageData.WindowsData.Info[i].SKO=mDataSLEZH.MeanFrag[i][0];      //������ ������� 0-1
				StructIKI->ImageData.WindowsData.Info[i].Limit=mDataSLEZH.ThFrag[i];
				StructIKI->ImageData.WindowsData.Info[i].ObjCount=mDataSLEZH.ObjFrag[i];
				StructIKI->ImageData.WindowsData.Info[i].X=mDataSLEZH.FragYX[i][0];          //������ ������� 0-1
				StructIKI->ImageData.WindowsData.Info[i].Y=mDataSLEZH.YendLoc[i];
			  }

			  StructIKI->StarsData.RezStat=mDataSLEZH.res_stat;
			  StructIKI->StarsData.LocalizedCount=mDataSLEZH.NumLoc;
			  StructIKI->StarsData.StarsList = new starinfo[mDataSLEZH.NumLoc];
			  for (int i=0; i<mDataSLEZH.NumLoc; i++) {
	            StructIKI->StarsData.StarsList[i].X_coordinate=mDataSLEZH.RsLocT[i][0];
				StructIKI->StarsData.StarsList[i].Y_coordinate=mDataSLEZH.RsLocT[i][1];
				StructIKI->StarsData.StarsList[i].BrightnessObject=mDataSLEZH.RsLocT[i][2];
				StructIKI->StarsData.StarsList[i].PixelsCount=mDataSLEZH.RsLocT[i][3];
				StructIKI->StarsData.StarsList[i].NumberStar=0;
				StructIKI->StarsData.StarsList[i].StellarMagnitude=0;
	//            StructIKI->StarsData.StarsList[i].SpectralClass='';
				StructIKI->StarsData.StarsList[i].SpectralClass[0]='_';
				StructIKI->StarsData.StarsList[i].SpectralClass[1]='_';
				StructIKI->StarsData.StarsList[i].DX=0;
				StructIKI->StarsData.StarsList[i].DY=0;
			  }
			  if (!mDataSLEZH.res_stat)
			  {
				for (int i=0; i<mDataSLEZH.NumDet; i++) {
				  int iloc=mDataSLEZH.MasRes[i][1]; //������ �������  0-1
				  int ifrag=mDataSLEZH.MasRes[i][0]; //������ �������  0-1
				  StructIKI->StarsData.StarsList[iloc].NumberStar=
									(unsigned int)mDataSLEZH.XYc[ifrag][2];
				  StructIKI->StarsData.StarsList[iloc].StellarMagnitude=
												  mDataSLEZH.XYc[ifrag][3];
				  StructIKI->StarsData.StarsList[iloc].DX=mDataSLEZH.Dx[i];
				  StructIKI->StarsData.StarsList[iloc].DY=mDataSLEZH.Dy[i];
				}
	            StructIKI->StarsData.RecognizedCount=mDataSLEZH.NumDet;
				for (int i=0; i<4; i++) {
	              StructIKI->StarsData.RecognizedOrientationQuaternion[i]=mDataSLEZH.Quat[i];
	            }
	            for (int i=0; i<3; i++)  {
	              for (int j=0; j<3; j++) {
					StructIKI->StarsData.RecognizedOrientationMatrix[i][j]=mDataSLEZH.M_ornt[i][j];
				  }
				}
			  }
	//          StructIKI->WriteFormat("C:\\TestStructIKI_data.txt");
	//          delete [] StructIKI->StarsData.StarsList;
	//          delete [] StructIKI->ImageData.WindowsData.Info;
	//          delete StructIKI;
/**/
	          break;
			}

			case SINGLE_REG_MARKER:
			{
              DataSingleReg mDataSingleReg;
			  fread(&mDataSingleReg,sizeof(struct DataSingleReg),1,fflesh);
			  ChangeWordSingleReg(mDataSingleReg);
			  PrintSingleReg(ftxt, mDataSingleReg);
			  fprintf(flog_reg,"    %02d %6d %10ld %10ld %6ld.%03ld %8d %4d %4d\n",
				  mDataSingleReg.SerNum, mDataSingleReg.CntRecord, mDataSingleReg.T,
				  mDataSingleReg.Tbshv, mDataSingleReg.Tpr_sec, mDataSingleReg.Tpr_msec,
				  mDataSingleReg.CntErr, mDataSingleReg.Nreg, mDataSingleReg.RegVal);
			  break;
			}

			case ALL_REG_MARKER:
			{
			  unsigned char Reg[COUNT_REG];
			  fread(Reg,sizeof(Reg),1,fflesh);
			  PrintReg(ftxt, Reg);
			  break;
			}

			case FRAG_MARKER:
			{
			  DataFragHeader mDataFragHdr;
			  fread(&mDataFragHdr,sizeof(struct DataFragHeader),1,fflesh);
	//          NumPixF*=2; // ����� ��������!!!
			  ChangeWordFrag(mDataFragHdr);
			  if (mDataFragHdr.NumPix%2) mDataFragHdr.NumPix--;
			  if (mDataFragHdr.NumPix>MaxPix) mDataFragHdr.NumPix=MaxPix;
			  PrintDataFrag(ftxt, mDataFragHdr);

			  FragID++;
              int NumPixF=0;
			  NumPixF=mDataFragHdr.NumPix;
			  unsigned short buf_frag[MaxPix];
			  fread(buf_frag, sizeof(short),NumPixF, fflesh);

			  char frag_name[300];
			  sprintf(frag_name,"%s\\Frag_%06d.%08d_%03d.bin",FragDir.c_str(),
					 mDataFragHdr.Tpr_sec,mDataFragHdr.Tpr_msec,FragID);
			  ffrag=fopen(frag_name,"wb");
			  fwrite(buf_frag,sizeof(short),NumPixF,ffrag);
			  fclose(ffrag);
	//SaveFragIKI
/**
	//          StructIKI = new IKI_img();
			  StructIKI->ImageData.WindowsData.DataType=1; //unsigned short
			  StructIKI->ImageData.WindowsData.DegreeBinning=1;
			  StructIKI->ImageData.WindowsData.SizeData=NumPixF;
			  StructIKI->ImageData.WindowsData.Data = (void*)new unsigned short[NumPixF];
			  memcpy((unsigned short*)StructIKI->ImageData.WindowsData.Data,buf_frag,NumPixF*sizeof(unsigned short));
			  StructIKI->WriteFormat("C:\\TestStructIKI_data_frag"+IntToStr(FragID)+".iki");
			  delete [] StructIKI->ImageData.WindowsData.Info;
			  delete [] StructIKI->ImageData.WindowsData.Data;
			  delete [] StructIKI->StarsData.StarsList;
			  delete StructIKI;
	/**/

			  break;
			}
		  }
		}
		fclose(fflesh);
		fclose(ftxt);
		fclose(flog_reg);
		fclose(flog_pix);
		fclose(flog_orient);
		this->NumLine=1;

		this->UpDown1Click(MainForm,NULL);
		this->UpDown1->Max=vCadrInfo.size();
	 }
}


//void __fastcall TFormGraphOrient::Image1MouseDown(TObject *Sender, TMouseButton Button,
//		  TShiftState Shift, int X, int Y)
//{
//	if(Button==mbLeft)
//	{
//	 Image1->Width=Image1->Width*2 ;
//	 Image1->Height=Image1->Height*2;
//	}
//	else if(Button==mbRight)
//	{
//	 Image1->Width=Image1->Width/2 ;
//	 Image1->Height=Image1->Height/2;
//	}
//}


