
/*  
 * Project to find the frequency of words in a text in increasing and decreasing order.
 */


#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>



using namespace std;

//structure definition: Token and Frequency
struct TokenFreq
{
   string value;
   int freq;
};

//function declarations
vector<TokenFreq>getTokenFreq(string inFile_name);
void selectionSort(vector<TokenFreq> &tokFreqVector);
void insertionSort(vector<TokenFreq> &tokFreqVector);
void writeToFile(vector<TokenFreq> &tokFreqVector, string outFileName);



int main(int argc, char** argv) {

   // local variable declarations
  string filename ; // input file
  string outfilename1 ; //output file (increasing order of frequency)
  string outfilename2 ; //output file (decreasing order of frequency)
  

  //ask the user to type the input filename.
  cout << "Type the input file name  or press Enter to use the default file" << endl;

  getline(cin,filename);

  //if no filename is entered use default filename.
  if (filename.length() == 0) {
   
    
    filename = "SteveJobsSpeech2005.txt";
    cout << "Filename used :  " << filename << endl; 
   
  }
  
  //ask the user to type the output filename.
  cout << "Type the output file name (increasing frequency) or press Enter to use the default file" << endl;

  getline(cin,outfilename1);

  //if no filename is entered use default filename.
  if (outfilename1.length() == 0) {
   
    
    outfilename1 = "OutFileIncreasing.txt";
    cout << "Filename used for increasing order :  " << outfilename1 << endl; 
   
  }
  
  
  //ask the user to type the output filename.
  cout << "Type the output file name (decreasing frequency) or press Enter to use the default file" << endl;

  getline(cin,outfilename2);

  //if no filename is entered use default filename.
  if (outfilename2.length() == 0) {
   
    
    outfilename2 = "OutFileDecreasing.txt";
    cout << "Filename used for decreasing order :  " << outfilename2 << endl; 
   
  }
  
   
  vector<TokenFreq> tf1 = getTokenFreq(filename); // get the frequency of each value
  cout << "  " << endl;
 
  
  
  //save this vector to use also with insertion sort )
  vector<TokenFreq> tf1_saved = tf1;
 
  
  //sort the values by frequency using the selection sort algorithm, passing the vector by reference.
  
  selectionSort(tf1);// sort in increasing order
  
  cout << "  " << endl;
  
 
  
  
  //sort the values by frequency using the insertion sort algorithm, returning the vector by reference.  
  //pass as argument the saved copy of tf1, that is, tf1_saved  
  
  insertionSort(tf1_saved); // sort in decreasing order
  
  cout << "  "  << endl;
  
 
  
  
  writeToFile(tf1, outfilename1); //write to a file the output of selectionSort
          
          
  writeToFile(tf1_saved, outfilename2);    //write to a file the output of insertionSort
  
  return(0);
}


//Functions: 
//finds the value frequency
vector<TokenFreq>getTokenFreq(string inFile_name){
    
    string s;
    ifstream inFile;
    string linestr;
    

     inFile.open(inFile_name.c_str() );

     if (inFile.fail()){
        cout << "Fail to open the file " << inFile_name << "\n";
        exit(EXIT_FAILURE);
     }

     while ( !inFile.eof() ){
      getline(inFile,  linestr);    
       
            s = s + linestr;
          
      }
     
     for (int i = 0; i<s.length(); i++){
      s[i] = tolower(s[i]);
     }  
      
  
   int iBeg = 0;
   int iEnd;
   char aDelimiter = ' ';
   
   vector <string> newWord;
  
    // loop through all the characters of string s
    for (int i = 0; i <= s.length(); i++){

      if  (s[i] == aDelimiter) {
         iEnd = i;         
         
         newWord.push_back(s.substr(iBeg,iEnd-iBeg)) ;
         
         iBeg = i+1;
      }

    }
    // get the last value
   
      newWord.push_back(s.substr(iBeg,s.length()-iBeg)) ;
    
    
    vector<TokenFreq> tf; // declare vector tf
   
    
    //use vectors to hold the value and the freq
    vector<string> tempToken;
    vector<int> tempFreq;     

    
    
    tempToken.push_back(newWord[0]); // add new word
    tempFreq.push_back(1); // set frequency = 1
   
    
    
    for (int i = 1; i < newWord.size(); i++){    
        bool foundWord = false;
        for (int j=0; j < tempToken.size(); j++)  {
           if (tempToken.at(j) == newWord[i]   ){ // if the value equals an existing word, increase the frequency by 1 
               tempFreq.at(j) += 1;
               foundWord = true;
               } // close if
        } // close for in j
           if (!foundWord) {  //if a new value is found, start counting it.
               tempToken.push_back(newWord[i]);
               tempFreq.push_back(1);
           } //close if
       
    } //close for in i
    
    
    for (int j=0; j < tempToken.size(); j++)  {
     //copy the tempToken and tempFreq to the TokenFreq vector
      tf.push_back(TokenFreq()); //push back new TokenFreq with default constructor     
      tf[j].value = tempToken.at(j); // add new value
      tf[j].freq = tempFreq.at(j); // add new frequency    
     
    }    

    inFile.close();
    return tf;
}

//selection sort passing by reference (sorts in increasing order)
void selectionSort(vector<TokenFreq> &tokFreqVector){
    
    int n = tokFreqVector.size();
    int i, j,  tmp, minIndx;    
    for (i = 0; i < n - 1; i++) {
            minIndx = i; 
            for (j = i + 1; j < n; j++)
                  if (tokFreqVector.at(j).freq < tokFreqVector.at(minIndx).freq)
                        minIndx = j;
            if (minIndx != i) {
                  int tmp_freq = tokFreqVector.at(i).freq;
                  string tmp_value = tokFreqVector.at(i).value;
                  tokFreqVector.at(i).freq = tokFreqVector.at(minIndx).freq;
                  tokFreqVector.at(i).value = tokFreqVector.at(minIndx).value;
                  tokFreqVector.at(minIndx).freq = tmp_freq;
                  tokFreqVector.at(minIndx).value = tmp_value;
                  
            } // close if
      } // close for
   
   
    
}




//insertion sort passing by reference (sorts in decreasing order)
void insertionSort(vector<TokenFreq> &tokFreqVector){
    
 
    
    int n = tokFreqVector.size();
    int i, j;    
    for (i = 0; i < n ; i++) {
        j=i;
        while (j > 0 && tokFreqVector.at(j-1).freq < tokFreqVector.at(j).freq){
            int tmp_freq = tokFreqVector.at(j).freq;
            string tmp_value = tokFreqVector.at(j).value;
            tokFreqVector.at(j).freq = tokFreqVector.at(j-1).freq;
            tokFreqVector.at(j).value = tokFreqVector.at(j-1).value;
            tokFreqVector.at(j-1).freq = tmp_freq;
            tokFreqVector.at(j-1).value = tmp_value;
            j--;
        } // end of while loop
    } // end of for loop
    
    //testing:
    // for (int j=0; j < tokFreqVector.size(); j++)  {
   //   cout << " word " << tokFreqVector.at(j).value  << " freq " << tokFreqVector.at(j).freq << endl;
   // } 
}
      

//writing values and frequencies to a file
void writeToFile(vector<TokenFreq> &tokFreqVector, string outFileName){
    
  ofstream myfile (outFileName.c_str());  
  if (myfile.is_open())
  {
      
      for (int j=0; j < tokFreqVector.size(); j++)  {      
      
         myfile << "( ' " << tokFreqVector.at(j).value << " ', " <<  tokFreqVector.at(j).freq << "), " << '\n' ;
         
      } // close for
      
  
    myfile.close();
  } //close if
  else cout << "Unable to open file " <<  outFileName << endl;

}




