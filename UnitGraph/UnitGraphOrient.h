	//---------------------------------------------------------------------------

	#ifndef UnitGraphOrientH
	#define UnitGraphOrientH
	//---------------------------------------------------------------------------

	//������������ ��� ������ ������
	//#include <Classes.hpp>
	//#include <Controls.hpp>
	//#include <StdCtrls.hpp>
	//#include <Forms.hpp>
	//#include <Chart.hpp>
	//#include <ExtCtrls.hpp>
	//#include <Series.hpp>
	//#include <TeEngine.hpp>
	//#include <TeeProcs.hpp>
	//#include <ComCtrls.hpp>
	//#include <Dialogs.hpp>
	//#include <Grids.hpp>
	//#include <Menus.hpp>
	//#include "ArrowCha.hpp"
	//#include "BubbleCh.hpp"
	//#include "GanttCh.hpp"
	//#include "TeeShape.hpp"

	//��� XE7
	#include <Classes.hpp>
	#include <Controls.hpp>
	#include <StdCtrls.hpp>
	#include <Forms.hpp>
	#include <VCLTee.Chart.hpp>
	#include <ExtCtrls.hpp>
	#include <VCLTee.Series.hpp>
	#include <VCLTee.TeEngine.hpp>
	#include <VCLTee.TeeProcs.hpp>
	#include <ComCtrls.hpp>
	#include <Dialogs.hpp>
	#include <Grids.hpp>
	#include <Menus.hpp>
	#include "VCLTee.ArrowCha.hpp"
	#include "VCLTee.BubbleCh.hpp"
	#include "VCLTee.GanttCh.hpp"
	#include "VCLTee.TeeShape.hpp"
	#include <VclTee.TeeGDIPlus.hpp>
	#include <Vcl.ExtCtrls.hpp>
	#include <vector>
	#include <Classes.hpp>
	#include <Controls.hpp>
	#include <StdCtrls.hpp>
	#include <Forms.hpp>
	#include <Menus.hpp>
	#include <Dialogs.hpp>
	#include "MathM.h"
	#include "StatLib.h"
	#include "InfoCadrFormat.h"
	#include "ReadFlashFormat.h"
	#include <limits.h>
	#include <ComCtrls.hpp>
	#include <IniFiles.hpp>
	#include "..\\UnitMain.h"
	#include "UnitAnimateSetting.h"
	#include <vcl.h>
	#include <System.IOUtils.hpp>
	#include <System.StrUtils.hpp>
	#include <stdio.h>
	#include <memory>




	#define MaxSeries 6
	#define NumGraph 15

	#define MaxBlockSeries 8
	#define MaxFrameSeries 30

	//---------------------------------------------------------------------------

	class TFormAnimateSetting;

	 struct RawFileInfo
	{
	long int Pos;
	int Size;
	int SecuenceCounter;
	}  ;

	class TFormGraphOrient : public TForm
	{
	__published:	// IDE-managed Components
		TButton *ButtonAdd;
		TButton *ButtonClear;
		TOpenDialog *OpenDialogG;
		TPageControl *PageControl2;
		TTabSheet *TabSheet5;
		TChart *ChartAl;
		TChart *ChartDl;
		TChart *ChartAz;
		TTabSheet *TabSheet6;
		TChart *ChartWx;
		TChart *ChartWy;
		TChart *ChartWz;
		TTabSheet *TabSheet7;
		TChart *ChartMx;
		TChart *ChartMy;
		TChart *ChartNst;
		TTabSheet *TabSheet8;
		TChart *ChartFoc;
		TChart *ChartX0;
		TChart *ChartY0;
		TTabSheet *TabSheet9;
		TChart *ChartFone;
		TChart *ChartNoise;
		TChart *ChartNloc;
		TMainMenu *MainMenu1;
		TMenuItem *MenuSave;
		TMenuItem *MenuClear;
		TTabSheet *TabSheet10;
		TChart *Chart1;
		TLineSeries *Series2;
		TArrowSeries *Series3;
		TLineSeries *Series1;
		TLabel *Label1;
		TLabel *Label2;
		TLabel *Label3;
		TLabel *Label4;
		TLabel *Label5;
		TLabel *Label6;
		TEdit *EditSizeX;
		TEdit *EditSizeY;
		TTabSheet *TabSheet1;
		TChart *Chart2;
		TBarSeries *Series4;
		TLabel *Label10;
		TEdit *EditTimeDev;
		TLabel *Label11;
		TEdit *EditNumCadr;
		TUpDown *UpDown1;
		TChart *Chart3;
		TBarSeries *Series6;
		TChart *Chart4;
		TBarSeries *Series5;
		TStringGrid *TableWindowsInfo;
		TTabSheet *TabSheet2;
		TChart *Chart5;
		TBarSeries *Series7;
		TChart *Chart6;
		TBarSeries *Series8;
		TStringGrid *TableObjectsInfo;
		TMenuItem *MenuOptions;
		TBubbleSeries *Series9;
		TTabSheet *ShowFragmentTab;
		TMenuItem *MenuOpen;
		TOpenDialog *OpenDialog1;
		TCheckBox *SortFileCheckBox;
	TScrollBox *FragmentShowScrollBox;

		void __fastcall MenuSaveClick(TObject *Sender);
		void __fastcall MenuClearClick(TObject *Sender);
		void __fastcall FormCreate(TObject *Sender);
		void __fastcall UpDown1Click(TObject *Sender, TUDBtnType Button);
		void __fastcall EditNumCadrChange(TObject *Sender);
		void __fastcall TableObjectsInfoDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
			  TGridDrawState State);
		void __fastcall TableWindowsInfoDrawCell(TObject *Sender, int ACol, int ARow, TRect &Rect,
			  TGridDrawState State);
		void __fastcall MenuOptionsClick(TObject *Sender);
		void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
		void __fastcall MenuOpenClick(TObject *Sender);





	private:	// User declarations
		void InitStartColorOptions();
		void InitTableObjects(void);
		void PrintTableObjects(const struct CadrInfo &mCadr);
		void InitTableWindows(void);
		void PrintTableWindows(const struct CadrInfo &mCadr);
		void ClearAnimate(void);
		void DrawAnimate(const struct CadrInfo &mCadr);
		void DrawBlock(const struct CadrInfo &mCadr);
		void DrawFragment(const struct CadrInfo &mCadr);
		AnsiString SortRawFlashFile(const AnsiString &RawFileName);

		unique_ptr<TFormAnimateSetting> FormAnimateSetting;
		TLineSeries *LineSeries[MaxSeries*NumGraph];
		TChartShape *BlockSeries[MaxBlockSeries];
		TChartShape *FrameSeries[MaxFrameSeries];

		int FragID;
		unsigned short NumLine;

		AnsiString FileName;
		AnsiString FileTitle;
		AnsiString CurDir;
		AnsiString FragDir;
		AnsiString LocDir;


		vector <CadrInfo> vCadrInfo;
		vector <TImage*> ImageVector;
		vector <TBitmap*> BitmapVector;

	public:		// User declarations

			__fastcall TFormGraphOrient(TComponent* Owner);
			void CreateGraph(int CurLine);
			void DeleteGraph(int CurLine);
			void SaveGraph(TChart *Chart, AnsiString suff);
			void SetVisible(int CheckLine, bool tf);
			void ApplySeriesSetting(int CheckLine, AnsiString Title, TColor color);
			void SetVisibleLabelFrame(bool isVisible);
			int GetCadrInfo(int NC, struct CadrInfo &mCadr);


	};
	//---------------------------------------------------------------------------
	extern PACKAGE TFormGraphOrient *FormGraphOrient;
	//---------------------------------------------------------------------------
	#endif
