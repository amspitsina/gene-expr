/* ѕринимает в качестве вход€щего параметра мап с парами <им€_пробы, num-структура>
	выдает вектор, содержащий все num-структуры с именем этой пробы */
vector<numProbe> numgetMapName(multimap <string, numProbe> &getName, string &stringname)
{
	int count = 0;
	vector<numProbe> countgenes;
	for (multimap<string, numProbe>::iterator iter = getName.begin(); iter != getName.end(); ++iter)
		{
			string str = iter->first;
			numProbe pr = iter->second;
			if(str == stringname)
			{
				
				countgenes.push_back(pr);
			}
		}
	return countgenes;
}

/* ѕринимает им€ ткани и мап с парами <им€_пробы, num-структура> , выдает мап с парами <им€_пробы, значение заданной ткани дл€ этой пробы> */
multimap<string, double> getTissueValue (multimap <string, numProbe> &getName, string &tissname, vector<string> numpname)
{
	int tissnumber;
	double tar = 0.0; //пометить в мапе то им€, которое соответствует имени ткани
	for(int i=0; i<numpname.size(); i++)
		if(numpname[i]==tissname)
			tissnumber=i;
	multimap<string, double> tissvalue;
	tissvalue.insert(pair<string, double>(tissname, tar));
	for (multimap<string, numProbe>::iterator iter = getName.begin(); iter != getName.end(); ++iter)
		{
			string str = iter->first;
			numProbe pr = iter->second;
			tissvalue.insert(pair<string, double>(str, pr.paramsV[tissnumber-LEN]));
		}
	return tissvalue;
}


/* ѕринимает на вход им€ пробы и мап с парами <им€_пробы, num-структура>, 
    выдает вектор, содержащий все "максимальные по значению" num-структуры с именем этой пробы  */
numProbe valueCompareMax (multimap <string, numProbe> & genecompare, string & nametocomp)
{
	vector<numProbe> comparevec = numgetMapName(genecompare, nametocomp);
	vector<double> normProbe(comparevec.size());
	double normTMP=0;
	for(int i=0; i<comparevec.size(); i++)
	{
		numProbe tmp = comparevec[i];
		for(int j=0; j<tmp.paramsV.size(); j++)
			normTMP = normTMP+tmp.paramsV[j];
		normTMP = normTMP/tmp.paramsV.size();
		normProbe.at(i) = normTMP;
	} //заполнили вектор норм дл€ проб
	int Imax=0;
	double Pmax=0;
	for(int i=0; i<normProbe.size(); i++)
	{

		if(normProbe[i]>Pmax)
		{
			Pmax = normProbe[i];
			Imax = i;
		}
	}
	numProbe maxProbe = comparevec[Imax];
	return maxProbe;
}

/* ѕринимает на вход им€ пробы и мап с парами <им€_пробы, num-структура>, 
    выдает "среднюю по значению" num-структуру */
numProbe valueCompareMiddle (multimap <string, numProbe> & genecomparemid, string & nametocompmid)
{
		vector<numProbe> comparevec = numgetMapName(genecomparemid, nametocompmid);
		int quanprob = comparevec.size(); //количество проб с одинаковой меткой (кол-во строк)
		numProbe middlepr = comparevec[0];
		middlepr.numname = "MiddleName";
		string p = "Middle";
		int count=0;
		for(int i=0; i<middlepr.paramsID.size(); i++)
		{
			count++;
			middlepr.paramsID[i] = p+(char)(count+48);
		}
		int quanval = middlepr.paramsV.size(); //количество значений дл€ сравнени€ (кол-во столбцов)
		for(int i=0; i<quanval; i++)
		{
			for(int j=1; j<quanprob; j++)
			{
				numProbe tmp1 = comparevec[j];
				middlepr.paramsV[i] = middlepr.paramsV[i]+tmp1.paramsV[i];
			}
		}
		for(int i=0; i<quanval; i++)
			middlepr.paramsV[i] = middlepr.paramsV[i]/quanprob;
	
		return middlepr;
}

/* ѕринимает на вход !! вектор с пробами по имени,
    выдает вектор, содержащий все "максимальные по значению" num-структуры с именем этой пробы  */
numProbe valueCompareMaxVect (vector<numProbe> & comparevec)
{

	vector<double> normProbe(comparevec.size());
	double normTMP=0;
	for(int i=0; i<comparevec.size(); i++)
	{
		numProbe tmp = comparevec[i];
		for(int j=0; j<tmp.paramsV.size(); j++)
			normTMP = normTMP+tmp.paramsV[i];
		normTMP = normTMP/tmp.paramsV.size();
		normProbe.at(i) = normTMP;
	} //заполнили вектор норм дл€ проб
	int Imax=0;
	double Pmax=0;
	for(int i=0; i<normProbe.size(); i++)
		if(normProbe[i]>Pmax)
		{
			Pmax = normProbe[i];
			Imax = i;
		}
	numProbe maxProbe = comparevec[Imax];
	return maxProbe;
}

/* ѕринимает на вход !! вектор с пробами по имени, 
    выдает "среднюю по значению" num-структуру */
numProbe valueCompareMiddleVect (vector<numProbe> & comparevec)
{
		int quanprob = comparevec.size(); //количество проб с одинаковой меткой (кол-во строк)
		numProbe middlepr = comparevec[0];
		int quanval = middlepr.paramsV.size(); //количество значений дл€ сравнени€ (кол-во столбцов)
		for(int i=0; i<quanval; i++)
		{
			for(int j=1; j<quanprob; j++)
			{
				numProbe tmp1 = comparevec[j];
				middlepr.paramsV[i] = middlepr.paramsV[i]+tmp1.paramsV[i];
			}
		}
		for(int i=0; i<quanval; i++)
			middlepr.paramsV[i] = middlepr.paramsV[i]/quanprob;
	
		return middlepr;
}


/* ‘ункци€, котора€ обрезает слово до определенного символа*/
string strchrcat(string &s, char del)
{
	s = s.substr(0,s.find(del));
	return s;
}

/* ѕарсинг строки - разбиение строки на слова */
void stringParse(string const & str, vector<string> & vec_str)
{
	unsigned int beg = 0;
	unsigned int end = 0;
	int pos = 0;
	for(string::const_iterator it = str.begin(); it != str.end(); ++ it, ++ pos)
	{
		if(*it == DET)
		{
			end = pos - beg;
			vec_str.push_back(str.substr(beg,end));
			beg = pos + 1;        
		}
	}
	vec_str.push_back( str.substr( beg, str.size() - 1 ) );
}

void InsInVec(vector<string> & vec1, int S, int Q) // начина€ с позиции S, вставить Q штук с конца, сместив остальные
{
	vector <string> TMP;
	for(int i=vec1.size()-Q; i<vec1.size(); i++)
		TMP.push_back(vec1[i]);
	for(int i=vec1.size()-1; i>S+1-Q; i--)
	{
		vec1.at(i) = vec1[i-Q];
	}
	for(int i=S; i<S+Q; i++)
		vec1.at(i) = TMP[i-S];
}
 

void gist(vector<int> & gistpos, vector<int> & gistneg, int & gistnum, double & corij)
{
	int gistij = (int)(corij*gistnum);
	if(corij > 0)
		gistpos[gistij]++;
	else if(corij < 0)
		gistneg[abs(gistij)]++;
}

double **correlation(	multimap<string, numProbe> genemap, map<string, int> & chromo, vector<string> &allnames,
					vector<string> &namelist, vector<numProbe> & forcorel, 
					vector<int> &gistpos, vector<int> &gistneg,
					double & thres, double & giststep,
					 vector<string> &namelistcorel, 
					 int chromnum,
					int &numper, int &neg, int &pos, int &upthr, double &aver
				)
{

	
//	cout<<"test 1"<<endl;
	
//	corelmatr[0][0] = 1;

		

//	cout<<"test 2"<<endl;
	string nmlst;
	int choice;
CORELLIST:
	cout<<"1 - add names from file"<<endl;
	cout<<"2 - for all names"<<endl;
	cout<<"3 - random sample"<<endl;
	cin>>choice;
	if((choice != 1) && (choice != 2) && (choice != 3))
	{
		cout<<"Wrong answer, try again"<<endl;
		goto CORELLIST;
	}
	if(choice == 1)
	{
	//имена из файла
		char corfname[MAXFILENAMELEN+4];
	OPFCOR:
		cout<<"Enter file name [list_of_genes]*.txt, max length is "<<MAXFILENAMELEN<<endl;
		cin>>corfname;
		ifstream fnamesl;
		fnamesl.open(corfname);
		if(fnamesl == NULL) 
		{
			cout<<"Error cannot open file"<<endl;
			goto OPFCOR;
		}
//		cout<<" -- 0"<<endl;
		while(getline(fnamesl, nmlst))
		{
			cout<<nmlst<<endl;
			namelist.push_back(nmlst);
	//		cout<<" --- 0"<<endl;

		}
//		cout<<" -- 1"<<endl;
		fnamesl.close();
//		cout<<" -- 2"<<endl;
	} 
	else if(choice == 2)
	{
	//имена по всему списку
			for(int i=0; i<allnames.size(); i++)
				namelist.push_back(allnames[i]);
	}
	else if(choice == 3)
	{
	//рандомные имена
		cout<<"Enter sample size"<<endl;
		int ssize;
		cin>>ssize;
		while(namelist.size()<ssize)
		{
			int randname  = rand() % allnames.size();
		//	cout<<randname<<endl;
			vector<string>::iterator it;
			it = find (namelist.begin(), namelist.end(), allnames[randname]);
			if(it == namelist.end())
				namelist.push_back(allnames[randname]);

		}
	}

	
//	cout<<namelist.size()<<"size of namelist"<<endl;
//	cout<<" -- 3"<<endl;
	// на этом шаге есть вектор с именами
	for(multimap<string, numProbe>::iterator it = genemap.begin(); it != genemap.end(); ++it)
	{
		string tempstr = it->first;
		numProbe tmp = it->second;
		int cou = 0;
//		cout<<" -- 4"<<endl;
		if((choice == 1) || (choice == 3))
		{
			for(int i=0; i<namelist.size(); i++)
			{
				int prov = 0;
				if(tempstr == namelist[i])
				{
			//		cout<<tempstr<<endl;
					forcorel.push_back(tmp);
					chromo[tmp.paramsID[chromnum]] = chromo[tmp.paramsID[chromnum]]+1;
			//		cout<<chromo[tmp.paramsID[chromnum]]<<endl;
		//			prov++;
					break;
				}
			//	if(prov>1) cout<<namelist[i]<<endl;
			}
		}
		
		else if(choice == 2)
		{	
	//		cout<<" -- 5"<<endl;
			forcorel.push_back(tmp);
			chromo[tmp.paramsID[chromnum]] = chromo[tmp.paramsID[chromnum]]+1;
		}
	}
	
	cout<<forcorel.size()<<endl;
	double **corelmatr;
		corelmatr = new double*[forcorel.size()];
		for(int i=0; i<forcorel.size(); i++)
			corelmatr[i] = new double[forcorel.size()];

		for(int i=0; i<forcorel.size(); i++)
			for(int j=0; j<forcorel.size(); j++)
				corelmatr[i][j] = 0;

	//на этом шаге есть вектор, в котором пробы дл€ коррел€ции
//	cout<<" -- 6"<<endl;
	for(int i=0; i<forcorel.size(); i++)
		{
//			cout<<" -- 7"<<endl;
			numProbe X = forcorel[i];
	//		cout<<" -- 8"<<endl;
			namelistcorel.push_back(X.numname);
	//		cout<<" -- 9"<<endl;
			double AvX = 0;
			for(int k=0; k<X.paramsV.size(); k++)
				AvX = AvX+X.paramsV[k]; //верно
	//		cout<<" -- 10"<<endl;
			AvX = AvX/X.paramsV.size(); //верно
			double sumX = 0;
			for(int k=0; k<X.paramsV.size(); k++)
				sumX = sumX + (X.paramsV[k]-AvX)*(X.paramsV[k]-AvX);
	//		cout<<" -- 11"<<endl;
			sumX = sqrt(sumX);
	//		cout<<" -- 12"<<endl;
			for(int j=0; j<forcorel.size(); j++)
			{	
//			cout<<" -- 13"<<endl;
				if(j==i) 
				{
		//			cout<<" -- 13 -- "<<endl;
					corelmatr[i][j] = 1;
		//			cout<<" -- 13 --- "<<endl;
					break;
			//		cout<<" -- 13 ---- "<<endl;
				}
		//		cout<<" -- 13 -- 0"<<endl;
				numProbe Y = forcorel[j];
		//		cout<<" -- 13 -- 1"<<endl;
				double AvY = 0;
		//		cout<<" -- 13 -- 2"<<endl;
				for(int k=0; k<Y.paramsV.size(); k++)
					AvY = AvY+Y.paramsV[k]; //верно
			//	cout<<" -- 13 -- 3"<<endl;
				AvY = AvY/Y.paramsV.size(); //верно
			//	cout<<" -- 14"<<endl;
				double sumY = 0;
				for(int k=0; k<Y.paramsV.size(); k++)
					sumY = sumY + (Y.paramsV[k]-AvY)*(Y.paramsV[k]-AvY);
				sumY = sqrt(sumY);
				double sumXY = 0; 
				for(int t=0; t<X.paramsV.size(); t++)
						sumXY = sumXY + (X.paramsV[t]-AvX)*(Y.paramsV[t]-AvY);
				corelmatr[i][j] = sumXY/(sumX*sumY);
			//	cout<<" -- 15"<<endl;
				gist(gistpos, gistneg, numper, corelmatr[i][j]);
			//	cout<<" -- 16"<<endl;
				if((abs(corelmatr[i][j]) > thres) && (i!=j))
					upthr++;
				if(corelmatr[i][j] > 0) 
					pos++;
				else if(corelmatr[i][j] < 0)
					neg++;
				aver = aver + corelmatr[i][j];
				corelmatr[j][i] = sumXY/(sumX*sumY);
			}
		}
	return corelmatr;
}