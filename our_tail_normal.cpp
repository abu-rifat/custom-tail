#include<bits/stdc++.h>
using namespace std;

//option 1=-c,2=-n,val<0=-x,val>0=+x

void tailFile(fstream& file, int option=-1, int val=-1){
	vector<string>s;
	string tmp;
	int chCt=0;
	while(getline(file,tmp)){
		s.push_back(tmp);
		chCt+=tmp.size();
	}
	int l=0,r=s.size();
	chCt+=r;
	if(option==-1){
		option=2;
		val=+10;
	}
	if(option==2){

		if(val==0)val++;
		if(val<0){
			val=abs(val);
			for(int i=val-1;i<r;i++){
				cout<<s[i]<<endl;
			}
		}else{
			val=abs(val);
			val=val=min(val,r);
			for(int i=r-val;i<r;i++){
				cout<<s[i]<<endl;
			}
		}
	}else if(option==1){
		if(val==0)val++;
		if(val<0){
			val=abs(val);
			int ct=0;
			for(int i=0;i<s.size();i++){
				for(int j=0;j<s[i].size();j++){
					ct++;
					if(val>ct)continue;
					cout<<s[i][j];
				}
				ct++;
				if(val<=ct)cout<<endl;
			}
		}else{
			val=abs(val);
			val=chCt-val;
			int ct=0;
			for(int i=0;i<s.size();i++){
				for(int j=0;j<s[i].size();j++){
					ct++;
					if(val>ct)continue;
					cout<<s[i][j];
				}
				ct++;
				if(val<=ct)cout<<endl;
			}
		}
	}
}

int main(int argc, char *argv[]){
	int option=-1;
	int val=-1;
	for(int i=1;i<argc;i++){
		string s=argv[i];
		if(s=="-c"){
			option=1;
			val=stoi(argv[i+1]);
			i++;
			continue;
		}else if(s=="-n"){
			option=2;
			val=stoi(argv[i+1]);
			i++;
			continue;
		}
		fstream file;
		file.open(argv[i],ios::out|ios::in);
		if ( file.is_open() ){
			cout<<"\n>>>> ("<<argv[i]<<") <<<<\n\n";
			tailFile(file,option,val);
		}
		file.close();
	}
	return 0;
}