/* ����������: ������ �������� ������ �������� � ��������� ������� � ������������ �����, ����� �����; ����� �� ���������� ������ ������-���������*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <cstdio>
#include <map>
#include <conio.h>
#include <string>
#include <typeinfo.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>


#define DET ';' //�����������
#define DELBN '/'
#define LEN 10 //���������� ����������, ������� �� ��������� � ������
#define MAXFILENAMELEN 100
#define GNAME 1 //����� ������� �������� �� ��� ���� - ������������, ������������
#define PROBE 1 //����� ������� �������� �� ����� ����� - ����������
#define TITLE 1 //pr.paramID[0] �������� �� �������� probe ID �� ���������


using namespace std;

#include "numprints.h"
#include "valuefunc.h"

int main()
{	


	char filename[MAXFILENAMELEN+4];
	cout<<"Enter name of file with data, max length is "<<MAXFILENAMELEN<<endl;
	cin>>filename;



	string s, paramname;

	int M = 0, N = 0; //���������� ����� � �������� � �����

	ifstream sdata0;
	sdata0.open(filename);
	
	if (sdata0==NULL) 
	{
		printf("Cannot open the file with data");
		return 1;
	}
	else 
	{
		getline(sdata0,s);
		for(string::const_iterator it = s.begin(); it != s.end(); ++ it)
			if(*it == DET)
				N++;
	}
	sdata0.close();
	N++;
	ifstream sdata;
	int paramforpar = 0;
	vector<string> tissues(N);
	sdata.open(filename);
	for(int i=0; i<N-1; i++)
	{	
		getline(sdata, s, DET);
		if(s.size()> 0)
		{
			tissues.at(i) = s;
		}
		else
		{
			paramforpar++;
			paramname = "parameter"+(char)(paramforpar+48);
			tissues.at(i) = paramname;
		}
	}
	getline(sdata,s);
	tissues.at(N-1) = s;
//	for(int i=0; i<tissues.size(); i++)
//		cout<<tissues[i]<<endl;
/**************** ------------------------------------ ****************/

/**************** ���������� ���� ������ <���_����, �����> ****************/
	int chromnum;
	cout<<"Enter column with chromosome number"<<endl;
	cin>>chromnum;

	map<string, int> chromosome;
	vector<string> param;
	int numofID = LEN;
	vector<double> paramval;
	vector<string> paramident;
	multimap<string, numProbe> genemap;
	vector<string> allnames;
	while(getline(sdata, s)) 
	{
		paramval.clear();
		paramident.clear();
		param.clear();
		stringParse(s, param);
		string gname = param[GNAME];
		allnames.push_back(gname); //������� ��� �����
		for(int i=0; i<numofID; i++)
			paramident.push_back(param[i]);
		for(int i=0; i<param.size()-numofID; i++)
			paramval.push_back(atof(param[i+numofID].c_str()));
		numProbe b(gname, paramident, paramval, numofID);
		genemap.insert(pair<string, numProbe>(gname, b));
		
		if(chromosome.count(b.paramsID[chromnum]) == 0) 
			chromosome.insert(pair<string, int> (b.paramsID[chromnum], 1));
		else chromosome[b.paramsID[chromnum]] = chromosome[b.paramsID[chromnum]]+1;
//		cout<<chromosome[b.paramsID[chromnum]]<<endl;

	}
	M = allnames.size()+1;
	cout<<N<<" N -- M "<<M<<endl;
/**************** ------------------------------------ ****************/

/****************            "�������" �����            ****************/

	multimap<string, numProbe> insertMap;
	multimap<string, numProbe> insertMapUNI;

	start:
	string var;
	cout<<"1 - enter probe name and find max value"<<endl;
	cout<<"2 - enter probe name and find middle value"<<endl;
	cout<<"3 - enter tissue name and get all values"<<endl;
	cout<<"4 - enter probe name and get all probes"<<endl;
	cout<<"5 - enter names and get direct gene"<<endl;
	cout<<"6 - delete genes from map"<<endl;
	cout<<"7 - insert data column from one file to another"<<endl;
	cout<<"8 - delete doubles from data file"<<endl;
	cout<<"9 - corel matrix"<<endl;
	int answer;
	scanf("%d", &answer);


	if(answer == 1)
	{
		cout<<"Enter probe"<<endl;
		cin>>var;
		numProbe MaxProbe = valueCompareMax(genemap, var);
		cout<<"1 - print in file\n2 - print on screen"<<endl;
		scanf("%d", &answer);
		if(answer == 1)
		{
				numstructPrintF(MaxProbe, tissues);
		}
		else if(answer == 2)
		{
				numstructPrint(MaxProbe, tissues);
		}
		goto start;
	}
	else if(answer == 2) 
	{
		cout<<"Enter probe"<<endl;
		cin>>var;
		numProbe MiddleProbe = valueCompareMiddle(genemap, var);
		cout<<"1 - print in file\n2 - print on screen"<<endl;
		scanf("%d", &answer);
		if(answer == 1)
			numstructPrintF(MiddleProbe, tissues);
		else if(answer == 2)
			numstructPrint(MiddleProbe, tissues); 
		goto start;
	}
	else if(answer == 3)
	{
		cout<<"Enter tissue name"<<endl;
		cin>>var;
		cout<<var<<endl;
		multimap<string, double> TissList = getTissueValue(genemap, var, tissues);
		cout<<"1 - print in file\n2 - print on screen"<<endl;
		scanf("%d", &answer);
		if(answer == 1)
			MMapStr_DouPrintF(TissList);
		else if(answer == 2)
			MMapStr_DouPrint(TissList); 
		goto start;
	}
	else if(answer == 4)
	{
		cout<<"Enter gene name"<<endl;
		cin>>var;
		vector<numProbe> AllProbeV = numgetMapName(genemap, var);
		multimap<string, numProbe> AllProbeM;
		for(int i=0; i<AllProbeV.size(); i++)
			AllProbeM.insert(pair<string, numProbe>(var,AllProbeV[i]));
		cout<<"1 - print in file\n2 - print on screen"<<endl;
		scanf("%d", &answer);
		if(answer == 1)
			MMapStr_numPrintF(AllProbeM, tissues);
		else if(answer == 2)
			MMapStr_NumPrint(AllProbeM, tissues);
		goto start;
	} 
	else if(answer == 5)
	{
		vector<string> genelist;
		char filenamelist[MAXFILENAMELEN+4];
		cout<<"Enter name of file with list of genes, max length is "<<MAXFILENAMELEN<<endl;
		cin>>filenamelist;
		ifstream flist;
		flist.open(filenamelist);
		string geneL;
		getline(flist, geneL);
		stringParse(geneL, genelist);
		multimap<string, numProbe> genemaplist;

		for(int i=0; i<genelist.size(); i++)
		{
			vector<numProbe> ProbeList = numgetMapName(genemap, genelist[i]);
			for(int j=0; j<ProbeList.size(); j++)
				genemaplist.insert(pair<string, numProbe>(genelist[i],ProbeList[j]));
		}
		MMapStr_numPrintF(genemaplist, tissues);
		goto start;
	}

	else if(answer == 6)
	{
DOPF:
		char delfname[MAXFILENAMELEN+4];
		cout<<"Enter name of file with names to delete, max length is "<<MAXFILENAMELEN<<endl;
		cin>>delfname;
		ifstream delit;
		delit.open(delfname);
		if (delit==NULL) 
		{
			cout<<"Cannot open the file"<<endl;
			return 1;
			goto DOPF;
		}
		string sdel;
		vector<string> delvect;
		while(getline(delit, sdel)) 
		{
			delvect.push_back(sdel);
		}
		delit.close();
			for(int k=0; k<delvect.size(); k++)
			{
				if((k>100)&&(k%100==0)) cout<<k<<endl;
				string teststr = delvect[k];
				genemap.erase(teststr);
			}

		ofstream deletecop;
		deletecop.open("deleteincorr.txt");
		for(multimap<string, numProbe>::iterator iterbd = genemap.begin(); iterbd != genemap.end(); ++iterbd)
		{
			numProbe tmpmm = iterbd->second;
			for(int mm=0; mm<tmpmm.paramsID.size(); mm++)
				deletecop<<tmpmm.paramsID[mm]<<";";
			deletecop<<";";
			for(int mm=0; mm<tmpmm.paramsV.size(); mm++)
				deletecop<<tmpmm.paramsV[mm]<<";";
			deletecop<<endl;
		}
		deletecop.close();
	}

	else if(answer == 7)
	{
//������� �������� � ������� � ���� 
		cout<<genemap.size()<<endl;
		char fname[MAXFILENAMELEN+4];
	OPF1:
		cout<<"Enter file name [insdata]*.txt, max length is "<<MAXFILENAMELEN<<endl;
		cin>>fname;
		string sins, pinsname;
		int L = 0, H = 0, paramins = 0;
		ifstream Linins;
		Linins.open(fname);
		if (Linins==NULL) 
		{
			printf("Cannot open the file");
			goto OPF1;
			return 1;
		}
		else
		{
			getline(Linins,sins);
			for(string::const_iterator it = sins.begin(); it != sins.end(); ++ it)
				if(*it == DET)
					L++;
		}
		cout<<" L L L"<<endl;
		Linins.close();
		L++;
//		L++;
		cout<<" L = "<<L<<endl;
		vector<string> insparams(L);
		ifstream insdataf;
		insdataf.open(fname);
		if(insdataf == NULL)
		{
			cout<<"Error with file"<<endl;
			goto OPF1;
		}
		for(int i=0; i<L-1; i++)
		{	
			getline(insdataf, sins, DET);
			if(sins.size()> 0)
			{
				insparams.at(i) = sins;
			}
			else
			{
				paramins++;
				pinsname ="InParam"+(char)(paramins+48);
				insparams.at(i) = pinsname;
			}
		}
		getline(insdataf, sins);
		insparams.at(L-1) = sins;
		//�� ���� ����� ���� ������ � ���������� ��������
		vector <int> numbofcol(L); //����� - ������� � ��������� ������
		vector<string> namescol;
		for(int i=0; i<numbofcol.size(); i++)
			numbofcol[i] = 0;
		cout<<"1 - enter number of columns (0-...) to add and ctrl+d to end"<<endl;
		cout<<"2 - enter names of columns with"<<endl;
		cin>>answer;
		if(answer == 1)
		{
			int numcol;
			while(cin>>numcol)
				numbofcol.at(numcol) = 1;
			cout<<"0"<<endl;
		}
		else if (answer == 2)
		{
			cin>>sins;
			stringParse(sins, namescol);
			for(int i=0; i<namescol.size(); i++)
				for(int j=0; j<insparams.size(); j++)
					if(namescol[i] == insparams[j])
						numbofcol.at(j) = 1;
			cout<<"1"<<endl;

		}
		int numcolsize = 0;
		for(int i=0; i<numbofcol.size(); i++)
		{
			if(numbofcol[i]>0)
				numcolsize++;
		}
		cout<<"2"<<endl;
		numbofcol.at(TITLE) = 1;
	/*	numbofcol.at(3) = 1;
		numbofcol.at(4) = 1;
		numbofcol.at(2) = 1;
		numbofcol.at(5) = 1;
		numbofcol.at(7) = 1;
		numbofcol.at(1) = 1;*/
		cout<<"3"<<endl;
		//////////////////

		vector <vector<string>> insdatavec; //������� = ���������� ����
		while(getline(insdataf, sins)) 
		{	
	//		cout<<sins<<endl;
			vector<string> TMPins;
			stringParse(sins, TMPins);
			vector<string> tmpStr;
			for(int i=0; i<numbofcol.size(); i++)
			{
				
				if(numbofcol[i]==1)
				{	
				//	cout<<"i = "<<i<<endl;
					
					tmpStr.push_back(strchrcat(TMPins[i], DELBN));
			//		cout<<TMPins[i]<<endl;
				//	tmpStr.push_back(TMPins[i]);
					
				}
			}
			insdatavec.push_back(tmpStr);
		}
		cout<<"4"<<endl;
		H = insdatavec.size();
		insdataf.close();
		cout<<" H = "<<H<<endl;
		vector<string> swaptissues;
		for(int i=0; i<LEN; i++)
			swaptissues.push_back(tissues[i]);
		cout<<"5"<<endl;
		for(int i=0; i<numbofcol.size(); i++)
		{
			if((numbofcol[i]>0) && (i!=TITLE))
				swaptissues.push_back(insparams[i]);
		}
		for(int i=LEN; i<tissues.size(); i++)
			swaptissues.push_back(tissues[i]);
		cout<<"6"<<endl;


		//������� ������ � �����������
	//��� ���� ����� ������ ����������� ��������: insdataname[i] - i � ���� ����� ������
	//������ ����� ����������� ��� �������� � ����

		int count = 0;
	//	cout<<"insdatavec = "<<insdatavec.size()<<endl;
		vector<string> TMP000 = insdatavec[2];
		//cout<<" 000 "<<TMP000.size()<<endl;
	for (multimap<string, numProbe>::iterator iter = genemap.begin(); iter != genemap.end(); ++iter)
		{
			count++;
			string str = iter->first;
			numProbe pr = iter->second;
			cout<<genemap.size()-count<<endl;
			for(int k=0; k<insdatavec.size(); k++)
			{
		//		cout<<k<<endl;
				
				vector<string> TMP0 = insdatavec[k];
			//	cout<<TMP0.size()<<endl;
				if(TMP0[TITLE]==pr.paramsID[PROBE]) // �������, ��� ��� ���������� �����
				{
			//		cout<<TMP0[TITLE]<<endl;
					for(int i=0; i<TMP0.size(); i++)
					{
				//		if(i!=TITLE)
						pr.paramsID.push_back(TMP0[i]);
					}
				//	cout<<"-- 7 -- "<<endl;
					pr.dim = pr.dim+numbofcol.size();
					insertMap.insert(pair<string, numProbe>(str, pr));
			//		cout<<"-- 8 -- "<<endl;

				}
			}
		}

	
		ofstream file;
		file.open("instxSTtxEnd.txt");
		if(file == NULL) cout<<"Cannot open the file 9 "<<endl;
		for(int i=0; i<swaptissues.size()-1; i++)
			file<<swaptissues[i]<<";";
		file<<swaptissues[swaptissues.size()-1]<<endl;
		
		for (multimap<string, numProbe>::iterator iter = insertMap.begin(); iter != insertMap.end(); ++iter)
		{
			numProbe numprobestr = iter->second;
			for(int i=0; i<numprobestr.paramsID.size(); i++)
				file<<numprobestr.paramsID[i]<<";";
			for(int i=0; i<numprobestr.paramsV.size()-1; i++)
				file<<numprobestr.paramsV[i]<<";";
			file<<numprobestr.paramsV[numprobestr.paramsV.size()-1];
			file<<endl;
		}
		file.close();
		cout<<insertMap.size()<<endl;
		cout<<swaptissues.size()<<endl;
	//	MMapStr_numPrintF(insertMap, swaptissues); /// �� ������� ------------------------
		goto start;
	}
	else if(answer == 8) // ������� �����
	{
			int choic;
	CHOICE:
			cout<<"1 - get max from all doubles\n2 - ged middle from all doubles"<<endl;
			cout<<"3 - get first random probe"<<endl;
			cin>>choic;
			if((choic != 1) && (choic != 2) && (choic != 3))
			{
				cout<<"Wrong answer, try again"<<endl;
				goto CHOICE;
			}
			multimap<string, numProbe> nodoubles; 	
			vector<string> allnames2;
			int allch = 0;
			for(int itt = 0; itt<allnames.size(); itt++)
			{
				allch = 0;
				string tmpall = allnames[itt];
				for(int itt1 = 0; itt1<allnames2.size(); itt1++)
				{
					if(allnames2[itt1] == tmpall)
					{
						allch = allch+1;
						break;
					}
				}
				if(allch==0)
				{
					allnames2.push_back(tmpall);
				}
				cout<<itt<<endl;
			}
			allnames.swap(allnames2);  // ������� ������������� ����� �� ������ ����
			for(int itt = 0; itt<allnames.size(); itt++)
			{	
				if(genemap.size() == 0) 
					break;
				string teststr = allnames[itt];
				vector<numProbe> douvectorf = numgetMapName(genemap, teststr);
				if(douvectorf.size() > 1)
				{
					if(choic == 1)
					{
						numProbe testpr = valueCompareMaxVect(douvectorf);
						nodoubles.insert(pair<string, numProbe>(teststr, testpr));
					}
					else if(choic == 2)
					{
						numProbe testpr = valueCompareMiddleVect(douvectorf);
						nodoubles.insert(pair<string, numProbe>(teststr, testpr));
					}
					else if(choic == 3)
					{
						numProbe testpr = douvectorf[0];
						nodoubles.insert(pair<string, numProbe>(teststr, testpr));
					}
					
				}
				else if(douvectorf.size() == 1)
				{
					nodoubles.insert(pair<string, numProbe>(teststr, douvectorf[0]));
				}
				genemap.erase(teststr);
			}
			ofstream maxdoubles;
			maxdoubles.open("maxwodoub.txt");
			if(maxdoubles == NULL)
				cout<<"Error cannot open file"<<endl;

			for(multimap<string, numProbe>::iterator iterbd = nodoubles.begin(); iterbd != nodoubles.end(); ++iterbd)
			{
				numProbe tmpmm = iterbd->second;
				for(int mm=0; mm<tmpmm.paramsID.size(); mm++)
					maxdoubles<<tmpmm.paramsID[mm]<<";";
				maxdoubles<<";";
				for(int mm=0; mm<tmpmm.paramsV.size(); mm++)
					maxdoubles<<tmpmm.paramsV[mm]<<";";
				maxdoubles<<endl;
			}
		}

		

	else if(answer== 9)
	{
		int choic;
	LIST:
		cout<<"1 - one sample"<<endl;
		cout<<"2 - two samples"<<endl;
		cin>>choic;
		if((choic != 1) && (choic != 2))
		{
			cout<<"Wrong answer, try again"<<endl;
			goto LIST;
		}

		string nmlst;
		double period;
		cout<<"Enter a period"<<endl;
		cin>>period;
		int numper = 1/period;
		double thres;
		cout<<"Set threshold value"<<endl;
		cin>>thres;

		double aver = 0;
		int pos = 0, neg = 0, upthr = 0;
		

		vector<string> namelist;
		vector<numProbe> forcorel;
		vector<string> namelistcorel;
		vector<int> gistpos(numper);
		vector<int> gistneg(numper);

		for(int i=0; i<numper; i++)
		{
			gistpos[i]=0;
			gistneg[i]=0;
		}

	//	cout<<namelist.size()<<" - nmlst sz"<<endl;
		if(choic == 2) cout<<"Set first sample"<<endl;
		double **corelmatr;
		map<string, int> chromo;
		for(map<string, int>::iterator it = chromosome.begin(); it != chromosome.end(); ++it)
		{
			string chtmp = it->first;
			chromo.insert(pair<string, int>(chtmp, 0));
		}

		corelmatr = correlation(genemap, chromo, allnames, namelist, forcorel, gistpos, gistneg, thres, period, namelistcorel, chromnum, numper, neg, pos, upthr, aver);		

	//	cout<<chromo["chr15"]<<" - chr15 "<<endl;

		char corrname[MAXFILENAMELEN+4];
		cout<<"Enter output correlation file name"<<endl;
		cin>>corrname;
		ofstream corelmatrixfle;
		corelmatrixfle.open(corrname);

		if(choic == 2) corelmatrixfle<<"First sample:"<<endl;

		corelmatrixfle<<"	  ;";
		for(int i=0; i<namelistcorel.size(); i++)
			corelmatrixfle<<namelistcorel[i]<<"; ";
		corelmatrixfle<<endl;
		for(int i=0; i<namelistcorel.size(); i++)
		{
			corelmatrixfle<<namelistcorel[i]<<"; ";
			for(int j=0; j<namelistcorel.size(); j++)
				corelmatrixfle<<corelmatr[i][j]<<"; ";
			corelmatrixfle<<endl;
		}



			
			vector<string> namelist2;
			vector<numProbe> forcorel2;
			int choic2;
			vector<string> namelistcorel2;
			double aver2 = 0;
			int pos2 = 0, neg2 = 0, upthr2 = 0;
			vector<int> gistpos2(numper);
			vector<int> gistneg2(numper);

			for(int i=0; i<numper; i++)
			{
				gistpos2[i]=0;
				gistneg2[i]=0;
			}

		map<string, int> chromo2;
		if(choic == 2)
		{
			corelmatrixfle<<endl;
			corelmatrixfle<<"Second sample:"<<endl;
			if(choic == 2) cout<<"Set second sample"<<endl;
			double **corelmatr2;	
			
			for(map<string, int>::iterator it = chromosome.begin(); it != chromosome.end(); ++it)
			{
				string chtmp = it->first;
				chromo2.insert(pair<string, int>(chtmp, 0));
			}

			corelmatr2 = correlation(genemap, chromo2, allnames, namelist2, forcorel2, gistpos2, gistneg2, thres, period, namelistcorel2, chromnum, numper, neg2, pos2, upthr2, aver2);
			corelmatrixfle<<"	  ;";
			for(int i=0; i<namelistcorel2.size(); i++)
			corelmatrixfle<<namelistcorel2[i]<<"; ";
			corelmatrixfle<<endl;
			for(int i=0; i<namelistcorel2.size(); i++)
			{
				corelmatrixfle<<namelistcorel2[i]<<"; ";
				for(int j=0; j<namelistcorel2.size(); j++)
					corelmatrixfle<<corelmatr2[i][j]<<"; ";
				corelmatrixfle<<endl;
			}
		}

	//	cout<<forcorel.size()<<endl;
	//	cout<<(forcorel.size()*forcorel.size() - forcorel.size())/2<<endl;
		corelmatrixfle<<endl;
		int numofcoef = (forcorel.size()*forcorel.size() - forcorel.size())/2;
		cout<<numofcoef<<endl;
		int numofcoef2 = (forcorel2.size()*forcorel2.size() - forcorel2.size())/2;
		corelmatrixfle<<"Number of coefficients: "<<numofcoef;
		if(choic==2) 
			corelmatrixfle<<" / "<<numofcoef2<<endl;
		else corelmatrixfle<<endl;

		corelmatrixfle<<"Positive: "<<pos<<"("<<((double)(1000*pos/numofcoef))/10<<"%)";
		if(choic==2) 
			corelmatrixfle<<" / "<<pos2<<"("<<((double)(1000*pos2/numofcoef2))/10<<"%)"<<endl;
		else corelmatrixfle<<endl;

		corelmatrixfle<<"Negative: "<<neg<<"("<<((double)(1000*neg/numofcoef))/10<<"%)";
		if(choic==2) 
			corelmatrixfle<<" / "<<neg2<<"("<<((double)(1000*neg2/numofcoef2))/10<<"%)"<<endl;
		else corelmatrixfle<<endl;

		corelmatrixfle<<"Greater than "<<thres<<": "<<upthr<<"("<<((double)(1000*upthr/numofcoef))/10<<"%)";
		if(choic==2) 
			corelmatrixfle<<" / "<<upthr2<<"("<<((double)(1000*upthr2/numofcoef2))/10<<"%)"<<endl;
		corelmatrixfle<<endl;

		
		int countnf = 0;
		for(int i=0; i<namelist.size(); i++)
		{
			int counter = 0;
			for(int j=0; j<forcorel.size(); j++)
			{
				if(namelist[i] == forcorel[j].numname)
					counter++;
			}
			if(counter == 0)
			{
				if(countnf == 0) corelmatrixfle<<"Not found in first sample:"<<endl;
				corelmatrixfle<<namelist[i]<<endl;
				countnf++;
			}

		}
		if(choic == 2)
		{
			corelmatrixfle<<endl;
			int countnf2 = 0;
			
			for(int i=0; i<namelist2.size(); i++)
			{
				int counter = 0;
				for(int j=0; j<forcorel2.size(); j++)
				{
					if(namelist2[i] == forcorel2[j].numname)
						counter++;
				}
				if(counter == 0)
				{
					if(countnf2 == 0) corelmatrixfle<<"Not found in second sample:"<<endl;
					corelmatrixfle<<namelist2[i]<<endl;
				}

			}
		}


		corelmatrixfle<<"Bar graph:"<<endl;
		for(int i=numper; i>0; i--)
			corelmatrixfle<<"-"<<period*i<<";";
		for(int i=0; i<numper+1; i++)
			corelmatrixfle<<period*i<<";";
		corelmatrixfle<<endl;
		for(int i=numper-1; i>=0; i--)
			corelmatrixfle<<gistneg[i]<<";";
		corelmatrixfle<<"0;";
		for(int i=0; i<numper; i++)
			corelmatrixfle<<gistpos[i]<<";";
		

		if(choic == 2)
		{
			corelmatrixfle<<endl;
			for(int i=numper-1; i>=0; i--)
				corelmatrixfle<<gistneg2[i]<<";";
			corelmatrixfle<<"0;";
			for(int i=0; i<numper; i++)
				corelmatrixfle<<gistpos2[i]<<";";
		}

		corelmatrixfle<<endl<<endl;
		corelmatrixfle<<"Location on chromosomes:"<<endl;
		for(map<string, int>::iterator it = chromo.begin(); it != chromo.end(); ++it)
		{
			string chrtmp = it->first;
			corelmatrixfle<<chrtmp<<";";
		}
		corelmatrixfle<<endl;
		for(map<string, int>::iterator it = chromo.begin(); it != chromo.end(); ++it)
		{
			int chrint = it->second;
			corelmatrixfle<<chrint<<";";
		}
		corelmatrixfle<<endl;
		if(choic == 2)
		{
			for(map<string, int>::iterator it = chromo2.begin(); it != chromo2.end(); ++it)
			{
				int chrint = it->second;
				corelmatrixfle<<chrint<<";";
			}
		}

		corelmatrixfle<<endl;
		corelmatrixfle.close();
//		delete [] corelmatr[namelistcorel.size()];

		cout<<"Now your data in "<<corrname<<endl;
		goto start;
	}
	else 
	{
		cout<<"Wrong answer"<<endl;
		goto start;
	}
	getch();
}
