#include "interpreter.h"
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

Interpreter::Interpreter(){

}

Interpreter::Interpreter(const Interpreter& itpt){
	tube = itpt.tube;
	bin = itpt.bin;
	sparebin = itpt.sparebin;
}

std::string Interpreter::execOp(std::string optr){
	
    if (optr == "+"){
        int fst = bin.pop();
        int sec = bin.pop(); 
        int sum;
        sum = fst + sec;
        tube.enqueue(toString(sum));
        //cout << sum << endl;
        return "";
    }
    else if (optr == "-"){
        int fst = bin.pop();
        int sec = bin.pop();
        int dif; 
        dif = fst - sec;
        tube.enqueue(toString(dif));
        return "";
    }
    else if (optr == "*"){
        
        int fst = bin.pop();
        int sec = bin.pop();
        int prod;
        prod = sec*fst;
        tube.enqueue(toString(prod));
        //cout << "prod" << prod << endl;
        return "";
    }
    else if (optr == "/"){
        
        int fst = bin.pop();
        int sec = bin.pop(); 
        int quo;
        quo = sec/fst;
        //cout << "quo" << endl;
        tube.enqueue(toString(quo));
        return "";
    }

    else if (optr == "^"){
        
        int fst = bin.pop();
        int sec = bin.pop(); 
        int exp;
        exp = recpow(sec,fst);
        //cout << "exp" << exp << endl;
        tube.enqueue(toString(exp));
        return "";
    }

    else if (optr == "RQ") {
        string sofar = "";
        while (!bin.isEmpty()){
            //cout << "here" << endl;
            int topush = bin.peek();
            if (sofar == ""){
                sofar = sofar + toString(topush);
            }
            else sofar = sofar + " " + toString(topush);
            tube.enqueue(toString(topush));
            //cout << "bin size 1 : " <<bin.size() << endl;
            sparebin.push(bin.pop());
            //cout << "spare  size : " <<sparebin.size() << endl;
            //cout << "bin size 2 : " <<bin.size() << endl;
        }
        while(!sparebin.isEmpty()){
            bin.push(sparebin.pop());
        }
        //cout << "spare ? " << sparebin.size()<< endl;
        
        return sofar ;
    }
    else if (optr == "PRINT") {
        string sofar = "";
        while (!tube.isEmpty()){
            //cout << "in print " << tube.dequeue() << endl;
            
            if (sofar == ""){
                sofar = sofar + tube.dequeue();
            }
            else sofar = sofar + " " + tube.dequeue();                       
        }
        //cout << "in print " << sofar << endl;
        return sofar;
        //cout << "in print " << tube.dequeue() << endl;
    }
    //else return "";
}

int Interpreter::recpow(int x, int y){
	if(y == 0){
		return 1;
	}
	else return x*recpow(x,y-1);
}

Interpreter& Interpreter::operator=(const Interpreter& itpt){
	tube = itpt.tube;
	bin = itpt.bin;
	sparebin = itpt.sparebin;
	return *this;
}

void Interpreter::load(std::string instruction){
	unsigned int i =0;
	std::string temp = "";
	for (char & c : instruction){
		if (c != ' '){
			temp += c;
		}
		else {
			tube.enqueue(temp);
            //cout << temp << endl;
			temp = "";
		}
	}
	tube.enqueue(temp);
    //cout << temp << endl;
	tube.enqueue("#");
    //cout << tube.size() << endl;

}

bool Interpreter::hasMoreInstructions(){
	return !tube.isEmpty();
}

std::string Interpreter::next(){ //throw caught excpetion

    std::string sofar= "";
	while (!tube.isEmpty()){
        //cout << "tubesize " << tube.size() << endl;
        string item = tube.dequeue();
        //cout << "item is "<< item << endl;}
        //cout << "H2 "<< Operator(item) << endl;
        
        if (Operator(item)){
            //cout << "item is "<< item << endl;            
            sofar = sofar + execOp(item); 
            //cout << "in next "<< sofar<< endl;                  
        }
        else {
            if (item == "#") return sofar;
            else {
            bin.push(toInt(item));
            //cout << "pushed " << toInt(item) << "to get " <<bin.size() << endl;
            }       
        }
    }
    return sofar;
}

std::string Interpreter::run(){
    string output = "";
    string temp = "";
    while (hasMoreInstructions())
    {   
        temp = next();
        //if (temp == "") temp = '\n';
        
        //if (output == "") output =  temp;
        output = output + '\n' + temp;
        
    }
    clear();
    return output.substr(1,-1);
}

void Interpreter::clear(){
    while (!tube.isEmpty()){
        tube.dequeue();
    }
    while (!bin.isEmpty()){
        bin.pop();
    }
    while (!sparebin.isEmpty()){
        sparebin.pop();
    }

}