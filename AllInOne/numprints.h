//Структура содержит имя гена, вектор значений его параметров-идентификаторов (типа string), вектор значений
// его параметров-тканей (типа double), вектор имен значений параметров и число параметров-идентификаторов
//далее num-структура
struct numProbe
{	
	numProbe(string inumName, vector<string> inumParamsID, vector<double> inumParamsV, int & iDimens): 
				numname(inumName), paramsID(inumParamsID), paramsV(inumParamsV), dim(iDimens){}
	int & dim;
	string numname;
	vector<string> paramsID;
	vector<double> paramsV;
	numProbe& numProbe::operator =(const numProbe &rhs)
	{
		numname = rhs.numname;
		for(int i=0; i<dim; i++)
		{
			paramsID[i] = rhs.paramsID[i];
		}
		for(int i=0; i<paramsID.size()+paramsV.size()-dim; i++)
		{
			paramsV[i] = rhs.paramsV[i+dim];
		}
		return *this;
	}
};

// функция печати num-структуры
void numstructPrint(const numProbe & numprobestr, vector<string> & numparams_name)
{
	cout<<" ----------------------------------------- "<<endl;
	cout<<"Probe name -- "<<numprobestr.paramsID[PROBE]<<endl;
	cout<<"Gene name -- "<<numprobestr.numname<<endl;
	for(int i=0; i<numprobestr.paramsID.size(); i++)
		cout<<numparams_name[i]<<" = "<<numprobestr.paramsID[i]<<endl;
	for(int i=0; i<numprobestr.paramsV.size(); i++)
		cout<<numparams_name[i+numprobestr.paramsID.size()]<<" = "<<numprobestr.paramsV[i]<<endl;
	cout<<" ----------------------------------------- "<<endl;
}


// Функция печати списка num-структур в один файл  - //notend
void numstructPrintFUni(const numProbe & numprobestr, vector<string> & numparams_name)
{
		char fname[MAXFILENAMELEN+4];
		cout<<"Enter file name *.txt, max length is "<<MAXFILENAMELEN<<endl;
		cin>>fname;
		ofstream file;
		file.open(fname);
		if(file == NULL) cout<<"Cannot open the file"<<endl;
		for(int i=0; i<numparams_name.size()-1; i++)
			file<<numparams_name[i]<<";";
		file<<numparams_name[numparams_name.size()-1]<<endl;
		for(int i=0; i<numprobestr.paramsID.size(); i++)
			file<<numprobestr.paramsID[i]<<";";
		for(int i=0; i<numprobestr.paramsV.size()-1; i++)
			file<<numprobestr.paramsV[i]<<";";
		file<<numprobestr.paramsV[numprobestr.paramsV.size()-1];
		file.close();
}


// Функция печати num-структуры в файл
void numstructPrintF(const numProbe & numprobestr, vector<string> & numparams_name)
{
		char fname[MAXFILENAMELEN+4];
		cout<<"Enter file name *.txt, max length is "<<MAXFILENAMELEN<<endl;
		cin>>fname;
		ofstream file;
		file.open(fname);
		if(file == NULL) cout<<"Cannot open the file"<<endl;
		for(int i=0; i<numparams_name.size()-1; i++)
			file<<numparams_name[i]<<";";
		file<<numparams_name[numparams_name.size()-1]<<endl;
		for(int i=0; i<numprobestr.paramsID.size(); i++)
			file<<numprobestr.paramsID[i]<<";";
		for(int i=0; i<numprobestr.paramsV.size()-1; i++)
			file<<numprobestr.paramsV[i]<<";";
		file<<numprobestr.paramsV[numprobestr.paramsV.size()-1];
		file.close();
}
// Функция печати мапа <string, string> // это вообще не используется теперь
void MMapStr_StrPrint(multimap<string, string> &mmapstrstr)
{
	cout<<"Multi-map string-string type printing ---------------------------------- "<<endl;
	for(multimap<string, string>::iterator iter = mmapstrstr.begin(); iter != mmapstrstr.end(); ++iter)
		if(iter->first == "Name")
			cout<<iter->first<<" = "<<iter->second<<endl;
	for(multimap<string, string>::iterator iter = mmapstrstr.begin(); iter != mmapstrstr.end(); ++iter)
		if(iter->first != "Name")
			cout<<iter->first<<" = "<<iter->second<<endl;
	cout<<"Multi-map string-string type printing ---------------------------------- "<<endl;
}

// Функция печати мапа <string, string> // это вообще не используется теперь
void MMapStr_StrPrintF(multimap<string, string> &mmapstrstr)
{
	char fname[MAXFILENAMELEN+4];
	cout<<"Enter file name *.txt, max length is "<<MAXFILENAMELEN<<endl;
	cin>>fname;
	ofstream file2;
	file2.open(fname);
	if(file2 == NULL) cout<<"Cannot open the file"<<endl;
	for(multimap<string, string>::iterator iter = mmapstrstr.begin(); iter != mmapstrstr.end(); ++iter)
		if(iter->first == "Name")
			file2<<iter->first<<" = "<<iter->second<<endl;
	for(multimap<string, string>::iterator iter = mmapstrstr.begin(); iter != mmapstrstr.end(); ++iter)
		if(iter->first != "Name")
			file2<<iter->first<<" = "<<iter->second<<endl;
}
////////////////////

// Функция печати мапа <string, double>
void MMapStr_DouPrint(multimap<string, double> &mmapstrdou)
{
	cout<<"Multi-map string-double type printing ---------------------------------- "<<endl;
	for(multimap<string, double>::iterator iter = mmapstrdou.begin(); iter != mmapstrdou.end(); ++iter)
		if(iter->first == "Name")
			cout<<iter->first<<" = "<<iter->second<<endl;
	for(multimap<string, double>::iterator iter = mmapstrdou.begin(); iter != mmapstrdou.end(); ++iter)
		if(iter->first != "Name")
			cout<<iter->first<<" = "<<iter->second<<endl;
	cout<<"Multi-map string-double type printing ---------------------------------- "<<endl;
}

void MMapStr_DouPrintF(multimap<string, double> &mmapstrdou)
{
	char fname[MAXFILENAMELEN+4];
	cout<<"Enter file name *.txt, max length is "<<MAXFILENAMELEN<<endl;
	cin>>fname;
	ofstream file;
	file.open(fname);
	if(file == NULL) cout<<"Cannot open the file"<<endl;
	for(multimap<string, double>::iterator iter = mmapstrdou.begin(); iter != mmapstrdou.end(); ++iter)
		if(iter->first == "Name")
			file<<iter->first<<" = "<<iter->second<<endl;
	for(multimap<string, double>::iterator iter = mmapstrdou.begin(); iter != mmapstrdou.end(); ++iter)
		if(iter->first != "Name")
			file<<iter->first<<";"<<iter->second<<endl;
}

void MMapStr_NumPrint(multimap<string, numProbe> &mmapstrnum, vector<string> & numparams_name)
{
	cout<<"Multi-map string-numProbe type printing ---------------------------------- "<<endl;
	for(multimap<string, numProbe>::iterator iter = mmapstrnum.begin(); iter != mmapstrnum.end(); ++iter)
	{
		numstructPrint(iter->second, numparams_name);
	}
	cout<<"Multi-map string-numProbe type printing ---------------------------------- "<<endl;
}

void MMapStr_numPrintF(multimap<string, numProbe> &mmapstrnum, vector<string> & numparams_name)
{
	char mmfname[MAXFILENAMELEN+4];
	cout<<"Enter file name *.txt, max length is "<<MAXFILENAMELEN<<endl;
	cin>>mmfname;
	ofstream mfile;
	mfile.open(mmfname);
	if(mfile == NULL) cout<<"Cannot open the file"<<endl;
	for(int i=0; i<numparams_name.size()-1; i++)
		mfile<<numparams_name[i]<<";";
	mfile<<numparams_name[numparams_name.size()-1]<<endl;
	for(multimap<string, numProbe>::iterator iter = mmapstrnum.begin(); iter != mmapstrnum.end(); ++iter)
	{
//		file2<<"Probe target name -- "<<iter->second.numname<<endl;
		for(int i=0; i<iter->second.paramsID.size(); i++)
			mfile<<iter->second.paramsID[i]<<";";
		for(int i=0; i<iter->second.paramsV.size()-1; i++)
			mfile<<iter->second.paramsV[i]<<";";
		mfile<<iter->second.paramsV[iter->second.paramsV.size()-1]<<endl;
	}
}
