#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

bool isAlpha(char ch){
	if (ch >= 'a' && ch <= 'z')
		return true;
	if (ch >= 'A' && ch <= 'Z')
		return true;
	return false;
}
bool isDelimiter(char ch){
	if (ch == '.' || ch == '!' || ch == ':' || ch == ';' || ch == '?')
		return true;
	return false;
}

bool isPunc(char ch){
	if (ch == '.' || ch == '?' || ch == '!' || ch == ':' ||
		ch == ';' || ch == ',' || ch == '\"'|| ch == '-' ||
		ch == '\'')
		return true;
	return false;
}

bool isVowel(char ch){
	if (ch == 'a' || ch == 'e' || ch == 'i' || 
		ch == 'o' || ch == 'u' || ch == 'y' ||
		ch == 'A' || ch == 'E' || ch == 'I' ||
		ch == 'O' || ch == 'U' || ch == 'Y')
		return true;
	return false;
}

int main(){
	string line;
	int words = 0, sentences = 0, syllables = 0;
	while (getline(cin, line)){
		string word;
		int line_index = 0;
		while (line_index < line.size()){
			word = "";
			while (line_index < line.size() && line[line_index] != ',' && line[line_index] != ' '){
					if (isDelimiter(line[line_index]))
						sentences++;
					if (isAlpha(line[line_index]))
						word += line[line_index];
					line_index++;
			}
			
			if (word.empty()){
				line_index++;
				continue;
			}

			words++;
			
			if (word.size() <= 3)
				syllables++;
			else{
				if (word.substr(word.size() - 2) == "es")
					word = word.substr(0, word.size() - 2);
				else if (word.substr(word.size() - 2) == "ed")
					word = word.substr(0, word.size() - 2);
				else if (word.substr(word.size() - 2) != "le" &&
					word[word.size() - 1] == 'e')
					word = word.substr(0, word.size() - 1);
				//cout << word << "\n";
				int index = 0;
				while (index < word.size()){
					if (isVowel(word[index])){
						while (index + 1 < word.size() && isVowel(word[index + 1]))
							index++;
						syllables++;
					}
					index++;
				}
			}
			line_index++;
		}
	}
	//printf("word:%d sentence:%d syllable:%d\n", words, sentences, syllables);
	printf("%.2f\n", 206.835 - 1.015 * (double)(words) / (double)(sentences) - 84.6 * (double)(syllables) / (double)(words));
	return 0;
}
