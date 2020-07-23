/////////////////////////////////////////////////
//Name: MUSTAFA TARIK SANIC
//Student ID:119033990012
////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <deque>
using namespace std;

struct cubeList{
	public:
		vector<vector<string>> list, pc, nc;
		vector<string> ind;
		cubeList *back;
};

class cubetree{
	private:
		cubeList *root;
		vector<vector<string>> cans, rans, test, ans;
		vector<string> testhelp;
		vector<int> index;
		deque<cubeList*> total;
	public:
	cubetree(cubeList *nlist){
			root=new cubeList;
			root->list=nlist->list;
			root->back=root;
			for(int i=0;i<nlist->list[0].size();i++){
				root->ind.push_back("00");
			}
	}
		
	void Complement(cubeList *a){
	 	vector<vector<string>> temp, emptyplay;
	 	vector<string> temp2, emptyhelp;
	 	emptyplay.empty();
	 	emptyhelp.empty();
		 		 	 	
	 	if(a->list.size()==1){
	 		ans=easy_Complement(a);
	 	}
	 	else{
	 		temp=a->list;
	 		int var=split_var(a->list), pcounter=0, ncounter=0, pflag=0, nflag=0;
	 		for(int i=0;i<temp.size();i++){
	 			temp2=temp[i];
	 			if(temp2[var]=="10"){
	 				a->nc.push_back(temp2);
	 			}
	 			if(temp2[var]=="01"){
	 				a->pc.push_back(temp2);
	 			}
	 			if(temp2[var]=="11"){
	 				a->pc.push_back(temp2);
	 				a->nc.push_back(temp2);
	 			}
	 			temp2.clear();
	 		}
	 		
	 		for(int q=0;q<a->pc.size();q++){
	 				a->pc[q][var]="11";
	 		}
	 		for(int q=0;q<a->nc.size();q++){
	 				a->nc[q][var]="11";
	 		}
	 		
	 		for(int q=0;q<a->pc.size();q++){
	 			pcounter=0;
	 			for(int w=0;w<a->pc[q].size();w++){
	 				if(a->pc[q][w]=="11")
	 				pcounter++;	
	 			}
	 			if(pcounter==a->pc[q].size()){
	 				a->pc.clear();
	 				pflag=1;
	 				break;
	 			}
	 		}
	 		for(int q=0;q<a->nc.size();q++){
	 			ncounter=0;
	 			for(int w=0;w<a->nc[q].size();w++){
	 				if(a->nc[q][w]=="11")
	 				ncounter++;	
	 			}
	 			if(ncounter==a->nc[q].size()){
	 				nflag=1;
	 				a->nc.clear();
	 				break;
	 			}
	 		}	

	 			if(!a->pc.empty()){
	 				cubeList *plist=new cubeList;
	 				plist->list=a->pc;
	 				plist->ind=a->ind;
	 				plist->ind[var]="01";
	 				plist->back=a;
	 				if(plist->list.size()==1){
	 					total.push_back(plist);
	 				}
	 				else{
	 					Complement(plist);
	 				}
	 			}
	 			if(!pflag&&a->pc.empty()){
	 				cubeList *plist=new cubeList;
	 				for(int i=0;i<a->list[0].size();i++){
	 					emptyhelp.push_back("00");
	 				}
	 				emptyplay.push_back(emptyhelp);
	 				plist->list=emptyplay;
	 				plist->ind=a->ind;
	 				plist->ind[var]="01";
	 				plist->back=a;
	 				pflag=0;
	 				total.push_back(plist);
	 			    }
	 			
	 			 if(!a->nc.empty()){
	 				cubeList *nlist=new cubeList;
	 				nlist->list=a->nc;
	 				nlist->ind=a->ind;
	 				nlist->ind[var]="10";
	 				nlist->back=a;	 				
	 				if(nlist->list.size()==1){
	 					total.push_back(nlist);
	 				}
	 				else{
	 					Complement(nlist);
	 				}
	 			}
				if(!nflag&&a->nc.empty()){
	 				cubeList *nlist=new cubeList;
	 				for(int i=0;i<a->list[0].size();i++){
	 					emptyhelp.push_back("00");
	 				}
	 				emptyplay.push_back(emptyhelp);
	 				nlist->list=emptyplay;
	 				nlist->ind=a->ind;
	 				nlist->ind[var]="10";
	 				nlist->back=a;
	 				nflag=0;
	 				total.push_back(nlist);
				}
				if(a->pc.empty()&&a->nc.empty()&&pflag&&nflag){
					cubeList *nnlist=new cubeList;
	 				for(int i=0;i<a->list[0].size();i++){
	 					emptyhelp.push_back("11");
	 				}
					 for(int i=0;i<a->list[0].size();i++){
						nnlist->ind.push_back("00");
					}
	 				emptyplay.push_back(emptyhelp);
	 				nnlist->list=emptyplay;
	 				nnlist->back=a;
	 				nflag=0;
	 				total.push_back(nnlist);
				} 	
	 }
	 return;
	 
	}
	vector<vector<string>> easy_Complement(cubeList *ea){
			vector<string> temp;
			vector<vector<string>> rep;
			int zerocounter=ea->list[0].size(), onecounter=ea->list[0].size();
			for(int i=0;i<ea->list[0].size();i++){
				if(ea->list[0][i]=="00"){
					zerocounter--;
				}
				else if(ea->list[0][i]=="11"){
					onecounter--;
				}
				else break;
			}
			if(zerocounter==0){
				for(int j=0;j<ea->list[0].size();j++){
					temp.push_back("11");
				}
				rep.push_back(temp);
			}
			else if(onecounter==0){
				for(int j=0;j<ea->list[0].size();j++){
					temp.push_back("00");
				}
				rep.push_back(temp);
			}
			else{
				for(int j=0;j<ea->list[0].size();j++){
					if(ea->list[0][j]=="10"){
						for(int o=0;o<ea->list[0].size();o++){
							if(o==j){
								temp.push_back("01");
								continue;
							}								
							temp.push_back("11");
						}
						rep.push_back(temp);
					}
						
					else if(ea->list[0][j]=="01"){
						for(int o=0;o<ea->list[0].size();o++){
							if(o==j){
								temp.push_back("10");
								continue;
							}
							temp.push_back("11");
						}
						rep.push_back(temp);
					}
					temp.clear();
				}			
			}
			return rep;
	}
	
	int split_var(vector<vector<string>> sa){
			int index=-1, sum=-1, counter=0;
			vector<int> T,F,unate,bt, binate, ut;
			for(int r=0;r<sa[0].size();r++){
				T.push_back(0);
				F.push_back(0);
				bt.push_back(0);
				unate.push_back(0);
				binate.push_back(0);
				ut.push_back(0);
			}
			for(int i=0;i<sa.size();i++){
				for(int j=0; j<sa[i].size();j++){
						if(sa[i][j]=="01")
							T[j]+=1;
						if(sa[i][j]=="10")
							F[j]+=1;
				}
			}
			for(int q=0;q<T.size();q++){
				if(T[q]!=0&&F[q]!=0){
					binate[q]=T[q]+F[q];
					bt[q]=T[q]-F[q];
					if(bt[q]<0)
						bt[q]=bt[q]*(-1);
				}
				else if(T[q]!=0&&F[q]==0){
					unate[q]=T[q];
					ut[q]=T[q];
				}
				else if(T[q]==0&&F[q]!=0){
					unate[q]=F[q];
					ut[q]=F[q];
				}
				
			}			
			
			for(int aa=0;aa<binate.size();aa++){
				if(binate[aa]>0){
					if(binate[aa]>sum){
					sum=binate[aa];
					index=aa;
					continue;
				}	
				else if(binate[aa]==sum){
					if(bt[aa]<bt[index])
						index=aa;
						continue;
					}
				}
				else{
					counter++;					
				}
			}
			
			if(counter==binate.size()){
				index=-1; sum=-1;
				for(int b=0;b<unate.size();b++){
						if(unate[b]>0){
							if(unate[b]>sum){
								sum=unate[b];
								index=b;
								continue;
							}	
						else if(unate[b]==sum){
							if(ut[b]<ut[index])
							index=b;
							continue;
						}
					}	
			}				
			}
			
		
		T.clear();F.clear();bt.clear();unate.clear();binate.clear();ut.clear();
			return index;
		}
		
	void callComp(){
	Complement(root);
	return;
	}
	
	void callrealans(){
		if(!ans.empty()){
			for(int i=0;i<ans.size();i++){
				for(int j=0;j<ans[i].size();j++){
					if(ans[i][j]=="00"){
						testhelp.clear();
						break;
					}
					else if(ans[i][j]=="01"){
						testhelp.push_back("1");
						continue;
					}
					else if(ans[i][j]=="10"){
						testhelp.push_back("0");
						continue;
					}
					else if(ans[i][j]=="11"){
						testhelp.push_back("-");
						continue;
					}
				}
				rans.push_back(testhelp);
				testhelp.clear();
			}
		}
		else{
			while(!total.empty()){
				test=easy_Complement(total.front());
				for(int i=0;i<total.front()->ind.size();i++){
					if(total.front()->ind[i]!="00"){
						for(int j=0;j<test.size();j++){
							test[j][i]=total.front()->ind[i];
					}						
					}
				}
				for(int u=0;u<test.size();u++){
	 					testhelp=test[u];
	 					cans.push_back(testhelp);
	 					testhelp.clear();
	 				}
	 			test.clear();
	 			total.pop_front();
			}
		
		for(int i=0;i<cans.size();i++){
				for(int j=0;j<cans[i].size();j++){
					if(cans[i][j]=="00"){
						break;
					}
					else if(cans[i][j]=="01"){
						testhelp.push_back("1");
						continue;
					}
					else if(cans[i][j]=="10"){
						testhelp.push_back("0");
						continue;
					}
					else if(cans[i][j]=="11"){
						testhelp.push_back("-");
						continue;
					}
				}
				rans.push_back(testhelp);
				testhelp.clear();
			}
		}
		
		
			
		return;
	}
	
	
	void print(){		
		for(int i=0;i<rans.size();i++){
			for(int j=0;j<rans[i].size();j++){
				cout<<rans[i][j];
			}
			cout<<endl;	
		}
	}
};


int main(int argc, char* ar[]){
	string line;
	ifstream myfile(ar[1]);
	if(myfile.is_open()){
		getline(myfile,line);
		cout<<line<<endl;
		int a=atoi(line.c_str());
		vector<vector<string>> v;
		int row_size=0;
		while(!myfile.eof()){
			vector<string> temp;
			getline(myfile,line);
			if(line==""&&row_size==0){
				for(int i=0;i<a;i++){
					temp.push_back("00");	
				}
				v.push_back(temp);
				row_size++;
				break;
			}
			else if(line==""&&row_size!=0){
				break;
			}
			else{
			for(int i=0;i<line.length();i++){
				if(line[i]=='-')
					temp.push_back("11");
				else if(line[i]=='1')
						temp.push_back("01");
				else if(line[i]=='0')
						temp.push_back("10");
			}
			row_size++;
			v.push_back(temp);
			}
		}
		cubeList *c=new cubeList;
		c->list=v;
		cubetree *L= new cubetree(c);
		L->callComp();
		L->callrealans();
		L->print();
		}
	else cout << "Unable to open value file";
	return 0;
}
