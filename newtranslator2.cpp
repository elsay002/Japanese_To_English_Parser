#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 25
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Ahmed El Sayed
// RE: (vowel | vowel n | consonant vowel | consonant vowel n |consonant-pair vowel | consonant-pair vowel n)^+              
bool word (string s)
{
  
  int state = 0;
  int charpos = 0;
  /*replace the following todo the word dfa  */
  while (s[charpos] != '\0') 
    {
      //      cout << "State is: " << state << endl;
      //cout << "Letter at: " << s[charpos] << endl;
      if (state == 0 && s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j')
	{state = 5;}
      else if(state ==0 && s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'E' || s[charpos] == 'I'|| s[charpos] == 'o' || s[charpos] == 'u')
	{state = 6;}
      else if(state ==0 && s[charpos]== 'b' || s[charpos]== 'm' || s[charpos]== 'k' || /*s[charpos]== 'n' ||*/ s[charpos]== 'h' || s[charpos]== 'p' || s[charpos]== 'r')
	{state = 4;}
      else if(state == 0 && s[charpos] == 'c')
	{state = 1;}
      else if(state == 0 && s[charpos] == 's')
	{state = 2;}
      else if(state == 0 && s[charpos] == 't')
	{state =3;}
      else if(state == 1 && s[charpos] == 'h')
	state = 5;
      else if(state == 2 && s[charpos] == 'h')
	state = 5;
      else if(state == 2 && s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'E' || s[charpos] == 'I'|| s[charpos] == 'o' || s[charpos] == 'u')
	state = 6;
      else if(state == 3 && s[charpos] == 's')
	state = 5;
      else if(state == 3 && s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'E' || s[charpos] == 'I'|| s[charpos] == 'o' || s[charpos] == 'u')
	state = 6;
      else if(state == 4 && s[charpos] == 'y')
	state = 5;
      else if(state == 4 && s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'E' || s[charpos] == 'I'|| s[charpos] == 'o' || s[charpos] == 'u')
	state = 6;
      else if(state == 5 && s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'E' || s[charpos] == 'I'|| s[charpos] == 'o' || s[charpos] == 'u')
	state = 6;
      else if(state == 6 && s[charpos] == 'n')
	{//cout << "HERE" << endl;
	state = 0;}
      else if(state == 6 && s[charpos] == 'c')
	state = 1;
      else if(state == 6 && s[charpos] == 's')
	state = 2;
      else if(state == 6 && s[charpos] == 't')
	state = 3;
      else if(state == 6 && s[charpos] == 'b'||s[charpos] == 'm'|| s[charpos] =='k' || s[charpos] == 'n' || s[charpos] == 'h' || s[charpos] == 'p' || s[charpos] == 'r' || s[charpos] == 'g')
	state = 4;
      else if(state == 6 && s[charpos] == 'd' || s[charpos] == 'w' || s[charpos] == 'z' || s[charpos] == 'y' || s[charpos] == 'j')
	state = 5;
      else if(state == 6 && s[charpos] == 'a' || s[charpos] == 'e' || s[charpos] == 'i' || s[charpos] == 'E' || s[charpos] == 'I'|| s[charpos] == 'o' || s[charpos] == 'u')
	state = 6;
      else
	{
	  return(false);
	}
      charpos++;
    }//end of while


  
  // where did I end up????
  if (state == 0 || state == 6) return(true);  // end in a final state
  else return(false);
}

// PERIOD DFA 
// Done by: Ahmed El Sayed
bool period (string s)
{  
  if (s == ".")return(true);
  else return(false); 
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: David Fairhurst

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum tokentype {ERROR,EOFM,WORD1,WORD2,PERIOD,VERB,VERBNEG,VERBPAST,VERBPASTNEG,IS,WAS,OBJECT,SUBJECT,DESTINATION,PRONOUN,CONNECTOR};


// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = {"Error","EOFM","WORD1","WORD2","PERIOD","VERB","VERBNEG","VERBPAST","VERBPASTNEG","IS","WAS","OBJECT","SUBJECT","DESTINATION","PRONOUN","CONNECTOR"}; 

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
string reservedwords[18]={"masu","masen","mashita","masendeshita","desu","deshita","o","wa","ni","watashi","anata","kare","kanojo","sore","mata","soshite","shikashi","dakara"};

tokentype reservedtokens[18]= {VERB,VERBNEG,VERBPAST,VERBPASTNEG,IS,WAS,OBJECT,SUBJECT,DESTINATION,PRONOUN,PRONOUN,PRONOUN,PRONOUN,PRONOUN,CONNECTOR,CONNECTOR,CONNECTOR,CONNECTOR}; 

// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Ariel Aquino 
void scanner(tokentype& tt, string& w)
{
  // ** Grab the next word from the file via fin
  // 1. If it is eofm, return right now.   
  /*  **
  2. Call the token functions (word and period) 
     one after another (if-then-else).
     Generate a lexical error message if both DFAs failed.
     Let the tokentype be ERROR in that case. 
  3. If it was a word,
     check against the reservedwords list.
     If not reserved, tokentype is WORD1 or WORD2
     decided based on the last character.

  4. Return the token type & string  (pass by reference)
  */

    fin >> w;
    cout << "Scanner called using word: " << w << endl;

    if(w == "eofm")
      tt = EOFM;
    else if( word(w))
      {
	for(int i = 0; i < 18; i++)
 	  {
	    if(w == reservedwords[i])
	      {
		tt= reservedtokens[i];
		return;
	      }
	  }
	if( w[w.size()-1] == 'I' || w[w.size()-1] == 'E')
	  tt= WORD2;
	else
	  tt= WORD1;
      }
    else if(period(w))
      tt = PERIOD;
    else
      {
	cout << "Lexical Error: " << w << " is not a valid token" << endl;
	tt = ERROR;
      }
        
}//the end of scanner


/* INSTRUCTION:  Complete all ** parts.
   You may use any method to connect this file to scanner.cpp
   that you had written.  
  e.g. You can copy scanner.cpp here by:
          cp ../ScannerFiles/scanner.cpp .  
       and then append the two files into one: 
          cat scanner.cpp parser.cpp > myparser.cpp
*/

//=================================================
// File parser.cpp written by Group Number: 25
//=================================================

string saved_lexeme;
tokentype saved_token;
bool token_available;

// ----- Four Utility Functions and Globals -----------------------------------

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me.  

// Type of error: match fails
// Done by: Ahmed El Sayed
void syntaxerror1(tokentype expected, string found) {
  cout << "SYNTAX ERROR: expected " << tokenName[expected] << " but found " << found << endl;
  exit(1);
}
// Type of error: default switch in parser
// Done by: Ahmed El Sayed
void syntaxerror2(string badstring, string parserfunction) {
  cout << "SYNTAX ERROR: unexpected " << badstring << " in " << parserfunction << endl;
  exit(1);

}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: Looks ahead to see what token comes next from the scanner
// Done by: David Fairhurst
tokentype next_token(){
  if(!token_available) {
    scanner(saved_token, saved_lexeme);
    token_available = true;
  }
  return saved_token;
}

// Purpose: Checks and eats up the expected token.
// Done by: David Fairhurst
bool match(tokentype expected) {
  if (next_token() != expected)  // mismatch has occurred with the next token
    { 
      syntaxerror1(expected, saved_lexeme);
    }
  else
    {  
      cout << "MATCHED " << tokenName[expected] << endl;
      token_available = false;
      return true; 
    }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

void s();
void after_subject();
void after_noun();
void after_object();
void noun();
void verb();
void be();
void tense();
void getEword();
void gen(string lt);

// Grammar: <story> ::= <s> { <s> }
// Done by: David Fairhurst
void story() {
  cout << "Processing <story>" << endl;
  s();
  while(true) {
    switch(next_token()) {
    case CONNECTOR:
    case WORD1:
    case PRONOUN:
      s();
      break;
    default:
      return;
    }
  }
}

// Grammar: <s> :: = [CONNECTOR #getEword# #gen(CONNECTOR)#] <noun> #getEword# SUBJECT #gen(ACTOR)# <after subject>
// Done by: Ahmed El Sayed
void s() {
  cout << "Processing <s>" << endl;
  if(next_token() == CONNECTOR){
    match(CONNECTOR);
    getEword();
    gen("CONNECTOR");
  }
  noun();
  getEword();
  match(SUBJECT);
  gen("ACTOR");
  after_subject();
}

// Grammar: <after subject> :== <verb>  #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD | <noun> #getEword# <after noun>
// Done by: Ariel Aquino
void after_subject() {
  cout << "Processing <after_subject>" << endl;
  switch(next_token()) {
  case WORD2:
    verb();
    getEword();
    gen("ACTION");
    tense();
    gen("TENSE");
    match(PERIOD);
    break;
  case WORD1:
  case PRONOUN:
    noun();
    getEword();
    after_noun();
    break;
  default:
    syntaxerror2(saved_lexeme, "after_subject");
  }
}

// Grammar: <after noun> :== <be> #gen(DESCRIPTION)# #gen(TENSE)# PERIOD  | DESTINATION #gen(TO)# <verb>   #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD | OBJECT #gen(OBJECT)# <after OBJECT>
// Done by: David Fairhurst
void after_noun() {
  cout << "Processing <after_noun>" << endl;
  switch(next_token()) {
  case IS:
  case WAS:
    be();
    gen("DESCRIPTION");
    gen("TENSE");
    match(PERIOD);
    break;
  case DESTINATION:
    match(DESTINATION);
    gen("TO");
    verb();
    getEword();
    gen("ACTION");
    tense();
    gen("TENSE");
    match(PERIOD);
    break;
  case OBJECT:
    match(OBJECT);
    gen("OBJECT");
    after_object();
    break;
  default:
   syntaxerror2(saved_lexeme, "after_noun");
  }
}

// Grammar: <after OBJECT> :== <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD | <noun> #getEword# DESTINATION #gen(TO)# <verb>   #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD 
// Done by: Ahmed El Sayed
void after_object() {
  cout << "Processing <after_object>" << endl;
  switch(next_token()) {
  case WORD2:
    verb();
    getEword();
    gen("ACTION");
    tense();
    gen("TENSE");
    match(PERIOD);
    break;
  case WORD1:
  case PRONOUN:
    noun();
    getEword();
    match(DESTINATION);
    gen("TO");
    verb();
    getEword();
    gen("ACTION");
    tense();
    gen("TENSE");
    match(PERIOD);
    break;
  default:
    syntaxerror2(saved_lexeme, "after_object");
  }
}

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Ariel Aquino
void noun() {
  cout << "Processing <noun>" << endl;
  switch(next_token()) {
  case WORD1:
    match(WORD1);
    break;
  case PRONOUN:
    match(PRONOUN);
    break;
  default:
    syntaxerror2(saved_lexeme, "noun");
  }
}

// Grammar: <verb> ::= WORD2
// Done by: David Fairhurst
void verb() {
  cout << "Processing <verb>" << endl;
  match(WORD2);
}

// Grammar: <be> ::=   IS | WAS
// Done by: Ahmed El Sayed
void be() {
  cout << "Processing <be>" << endl;
  switch(next_token()) {
  case IS:
    match(IS);
    break;
  case WAS:
    match(WAS);
    break;
  default:
    syntaxerror2(saved_lexeme, "be");
  }
}

// Grammar: <tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
// Done by: Ariel Aquino
void tense() {
  cout << "Processing <tense>" << endl;
  switch(next_token()) {
  case VERBPAST:
    match(VERBPAST);
    break;
  case VERBPASTNEG:
    match(VERBPASTNEG);
    break;
  case VERB:
    match(VERB);
    break;
  case VERBNEG:
    match(VERBNEG);
    break;
  default:
    syntaxerror2(saved_lexeme, "tense");
  }
}

/* INSTRUCTION:  copy your parser.cpp here
      cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: ** 25
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: ** David Fairhurst
string lexicon[48][2];
string saved_E_word;
 
// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: ** Ariel Aquino
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: ** Ahmed El Sayed

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.
ofstream fout;

void getEword()
{
  for(int i = 0; i < 49; i++)
    {
      if(lexicon[i][0] == saved_lexeme)
	{
	  saved_E_word = lexicon[i][1];
	  return;
	}
    }
  saved_E_word = saved_lexeme;
}

void gen(string lType)
{
  if(lType == "CONNECTOR"|| lType == "ACTOR"|| lType == "OBJECT"|| lType == "ACTION" || lType == "DESCRIPTION" || lType == "TO")
    fout << lType << ": " << saved_E_word << "\n";
  else if(lType == "TENSE")
    fout << lType << " " << tokenName[saved_token] << "\n\n";
}

// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  ** David Fairhurst
int main()
{
  //** opens the lexicon.txt file and reads it into Lexicon
  //** closes lexicon.txt 
  string word1;
  string word2;
  int index = 0;
  fin.open("lexicon.txt");
  while(fin >> word1 >> word2) 
    {
      lexicon[index][0] = word1;
      lexicon[index][1] = word2;
      index++;
    }
  fin.close();

  //** opens the output file translated.txt
  fout.open("translated.txt");
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  //** closes the input file
  fin.close(); 
  //** closes traslated.txt
  fout.close();
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions

