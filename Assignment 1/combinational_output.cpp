#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

class wire{
	private:
		string name;
		bool val;
	public:	
		wire(string s){
			name=s;
		}
		wire(string s, bool a){
			name=s;
			val=a;
		}
		
		wire();
		
		void print(){
			cout<<name<<" "<<val<<endl;
		}
		
		bool compare(string a){
			if(!name.compare(a))
				return true;
			else
				return false;
		}
		
		
		void and_gate(wire a){
			val=a.val&val;
			return;
		}
		
		void or_gate(wire a){
				val=a.val|val;
				return;
		}

		void xor_gate(wire a){
				val=a.val^val;
				return;
		}

		void not_gate(wire a){
			val=!a.val;
			return;
		}
		
		void buff_gate(wire a){
			val=a.val;
			return;
		}
		
		void nand_gate(wire a){
				val=!(a.val&val);
				return;
		}
		
		void nor_gate(wire a){
				val=!(a.val|val);
				return;
		}
		
		void xnor_gate(wire a){
				val=!(a.val^val);
				return;
		}

};



int main(int argc, char* ar[]){	
	string line, nline;
	ifstream myfile (ar[1]);
	vector<wire> allwires;
	vector<int> counter;
	vector<string> outputs;
	int inputcounter=0;
	
  if (myfile.is_open())
  {
    while(!myfile.eof()){
    	getline(myfile,line);   
		int found = line.find_first_of(" ");
  		while (found!=line.npos)
  		{
  			nline=line.substr(found+1);
 			int k=0;
 			for(int i=found;i<line.length();i++){
 				line[i]=nline[k];
 				k++;
 			}
    		found=line.find_first_of(" ",found+1);
  		}	
    	if(!line.empty()&&!line.find_first_not_of("#")){
    		if(!line.find("INPUT")||!line.find("input")){
    			int spos=line.find("(");
    			int epos=line.find(")");
    			string iname;
    			int i=spos+1;
    			while(i!=epos){
    				iname+=line[i];
    				i++;
    			}
    				ifstream valfile(ar[2]);
    				string valline;
    				if (valfile.is_open())
 					 {
    					while(!valfile.eof()){
    					getline(valfile,valline);
    					string k;
    					int j;
    					char c;
    					bool q;
    					if(!valline.empty()&&!valline.find(iname)){
    						c=valline[valline.length()-1];
    						j=int(c)-48;
    						q=bool(j);
    						wire a(iname,q);
							allwires.push_back(a);
							inputcounter++;    						
    					}
    				}
    				valfile.close();
  					}
  					else cout << "Unable to open value file";
    			
    		}
    		
			else if(!line.find("OUTPUT")||!line.find("output")){
    			int spos=line.find("(");
    			int epos=line.find(")");
    			string oname;
    			int i=spos+1;
    			while(i<epos){
    				oname+=line[i];
    				i++;
    			}
    			outputs.push_back(oname);

    		}
    		
    		else if(line.find("=")){
    			int t=line.find("=");
    			int e=0;
    			string wirename;
    			while(e<t){
    				wirename+=line[e];
    				e++;
    			}
    			wire v(wirename);
    			int r=0;
    			int falsecounter=0;
    			while(r<allwires.size()){
    				if(allwires[r].compare(wirename)){
    					falsecounter=0;
    					break;
    				}
    				falsecounter++;
    				r++;
    			}
    			if(falsecounter){
    				allwires.push_back(v);
    			}
    			int y=line.find("(");
    			string mode;
    			int p=t+1;
    			while(p<y){
    				mode+=line[p];
    				p++;
    			}
    				string nparse;
    				string parse=line.substr(y+1);
    				int commacounter=0;
    				for(int f=0;f<parse.length();f++){
    					if(parse[f]==',')
    						commacounter++;
    				}
    				int comma = parse.find_first_of(",");
    				int	para= parse.find_first_of(")");
 					for(int i=0;i<para;i++){
 					nparse+=parse[i];
 					if(i==comma-1||i==para-1){
 						i++;
 							for(int sz=0;sz<allwires.size();sz++){
 								if(allwires[sz].compare(nparse)){
 									counter.push_back(sz);
 								}
 							}

					}

						if(commacounter!=0&&i==comma){
							commacounter--;
  							comma=parse.find_first_of(",",comma+1);
  							nparse.erase(nparse.begin(),nparse.end());
  						}

  					}
  				while(!counter.empty()){
  					if(falsecounter){
						if (mode == "NOT" || mode == "not")
							v.not_gate(allwires[counter.back()]);
						else
							v.buff_gate(allwires[counter.back()]);
  					
					  falsecounter=0;	
  					}
  					
  					else{	
 					if(mode=="AND"||mode=="and")
  						v.and_gate(allwires[counter.back()]);  	
  					else if(mode=="OR"||mode=="or")
  						v.or_gate(allwires[counter.back()]);
  					else if(mode=="NOR"||mode=="nor")
  						v.nor_gate(allwires[counter.back()]);
  					else if(mode=="NAND"||mode=="nand")
  						v.nand_gate(allwires[counter.back()]);
  					else if(mode=="XOR"||mode=="xor")
  						v.xor_gate(allwires[counter.back()]);
  					else if(mode=="XNOR"||mode=="xnor")
  						v.xnor_gate(allwires[counter.back()]);
  					else if(mode=="NOT"||mode=="not")
  						v.not_gate(allwires[counter.back()]);
  					else if(mode=="BUF"||mode=="buf")
  						v.buff_gate(allwires[counter.back()]);
  					}
				counter.pop_back();	  	
  				}
  				for(int fd=0;fd<allwires.size();fd++){
  							if(allwires[fd].compare(wirename))
  								allwires[fd]=v;								
  						}
    			
    		}   			
    	}
    }
    myfile.close();
}
else cout<<"Unable to open bench file"<<endl;


					for(int i=0;i<allwires.size();i++){
						for(int j=0;j<outputs.size();j++){
							if(allwires[i].compare(outputs[j]))
								allwires[i].print();
						}
					}

  
	return 0;
}
