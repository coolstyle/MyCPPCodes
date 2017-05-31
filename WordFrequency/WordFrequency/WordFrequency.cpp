// WordFrequency.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<map>
#include<vector>
#include<iostream>  
#include<algorithm>  
#include<fstream>  
#include<iomanip>  
#include<string>  
#include<sstream>
using namespace std;
class HashEntry {
public:
	string words_;                  
	int totalTimes_;              
	bool operator<(HashEntry const&a) {
		return totalTimes_ > a.totalTimes_;
	}
};
class HashTable {
private:
	HashEntry*hash;
	int nextPrime_;             
	int numberOfWords_;         
public:
	HashTable(int size);
	int getNumberofwords() { return numberOfWords_; }
	int hashFunction(string key);   
	void insertKey(string key);            
	void showWord(double percentage);     
};
HashTable::HashTable(int size) {
	int i;
	bool flag;
	if (size % 2 == 0)
		size--;        
	while (size) {
		flag = true;
		for (i = 2; i*i <= size; i += 1) {
			if (size%i == 0) {
				flag = false;
				break;
			}
		}
		if (flag)
			break;
		size -= 2;
	}

	nextPrime_ = size;
	numberOfWords_ = 0;
	hash = new HashEntry[nextPrime_];         
	for (i = 0; i < nextPrime_; i++)
		hash[i].totalTimes_ = 0;               
}
int HashTable::hashFunction(string key) {     
	int i, num = 0, length;
	length = key.size()>8 ? 8 : key.size();    
	for (i = length - 1; i >= 0; i--)
	{
		num = num * 10 + key[i];
		if (num > nextPrime_)
			num = num%nextPrime_;
	}
	return num;
}

void HashTable::insertKey(string key) {
	int k1, k2, position, i;
	int hashValue = hashFunction(key);
	k1 = hashValue%nextPrime_;                  
	k2 = hashValue % (nextPrime_ - 2) + 1;      
	for (i = 0; i < nextPrime_; i++) {
		position = (k1 + i*k2) % nextPrime_;             
		if (hash[position].totalTimes_ == 0 || hash[position].words_ == key) {
			if (hash[position].totalTimes_ == 0)
				numberOfWords_++;
			hash[position].words_ = key;
			hash[position].totalTimes_++;
			break;
		}
	}
}

void HashTable::showWord(double percentage) {
	int i;
	int words = int(percentage*numberOfWords_);   
	sort(hash, hash + nextPrime_);               
	for (i = 0; i < words; i++) {
		cout << setw(15) << setfill(' ') << hash[i].words_ << "       " << hash[i].totalTimes_ << endl;
	}
}

bool CheckWords(string &key) {   

	if (key[0]<'A' || key[0]>'z' || (key[0]<'a'&& key[0]>'Z'))
		return false;
	if (key.size() < 1)
		return false;
	if (key[key.size() - 1] == '.' || key[key.size() - 1] == ',') {
		string::iterator it = key.begin();
		key.erase(it + key.size() - 1);
	}
	return true;
}
          
void erasePunct(string &s)
 {
	     string::iterator it = s.begin();
	     while (it != s.end())
		     {
		         if (ispunct(*it))
			             it = s.erase(it);
		        else
			             ++it;
		    }
	 }
int main() {
	string s="";
	char c;
	HashTable Hash(5000);
	ifstream sin("C:\\Users\\yujie\\Documents\\file.txt");
	bool flag=false;

	while (sin >> s) {

		erasePunct(s);
		Hash.insertKey(s);

	}
	Hash.showWord(10.00 / 100);
	return 0;
}