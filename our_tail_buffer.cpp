#include<bits/stdc++.h>
#include <sys/stat.h>
using namespace std;

//option 1=-c,2=-n,val<0=-x,val>0=+x

void tailFile(fstream& file, string bufferName, int option=-1, int val=-1){
    ofstream buffer(bufferName);
    if(buffer.is_open()){
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
                    std::cout<<s[i]<<endl;
                    buffer<<s[i]<<endl;
                }
            }else{
                val=abs(val);
                val=val=min(val,r);
                for(int i=r-val;i<r;i++){
                    std::cout<<s[i]<<endl;
                    buffer<<s[i]<<endl;
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
                        std::cout<<s[i][j];
                        buffer<<s[i][j];
                    }
                    ct++;
                    if(val<=ct){
                        std::cout<<endl;
                        buffer<<endl;
                    }
                }
            }else{
                val=abs(val);
                val=chCt-val;
                int ct=0;
                for(int i=0;i<s.size();i++){
                    for(int j=0;j<s[i].size();j++){
                        ct++;
                        if(val>ct)continue;
                        std::cout<<s[i][j];
                        buffer<<s[i][j];
                    }
                    ct++;
                    if(val<=ct){
                        std::cout<<endl;
                        buffer<<endl;
                    }
                }
            }
        }
        buffer.flush();
    }
    buffer.close();
}

int main(int argc, char *argv[]){
    struct stat filestat;
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
        stat(argv[i],&filestat);
        string fileMod=ctime(&filestat.st_mtime);
        for(int i=0;i<fileMod.size();i++){
            if(fileMod[i]==':')fileMod[i]='-';
            else if(fileMod[i]==' ')fileMod[i]='_';
            else if(fileMod[i]=='\n')fileMod[i]='_';
        }
        string fileName=argv[i];
        string ckBuffer="buff"+to_string(option)+to_string(val)+fileMod+fileName;
        int okBuffer = stat(ckBuffer.c_str(),&filestat);
        if(okBuffer==0){
            ifstream buffer(ckBuffer);
            if(buffer.is_open()){
                std::cout<<"\n>>>> ("<<argv[i]<<") <<<<\n\n";
                string s;
                while(getline(buffer,s)){
                    cout<<s<<endl;
                }
            }
            buffer.close();
        }else{
            fstream file;
            file.open(argv[i],ios::out|ios::in);
            if ( file.is_open() ){
                std::cout<<"\n>>>> ("<<argv[i]<<") <<<<\n\n";
                tailFile(file,ckBuffer,option,val);
            }
            file.close();
        }
	}
	return 0;
}