# Japanese_To_English_Parser
## Overview
This program recognizes and translates Japanese words in Romanji format. It implements a scanner, parser, and translator. Developed by 3 members. 

## Scanner 
DFA's were created for all Japanese syllables. An array of reserved basic words is written for basic Japanese sentences. Any recognized word in the array is assigned its pre-defined type. All other valid words are assigned the type WORD1. IF a word end in an uppercase letter, it is assinged type WORD2 for verb roots. Any words not recognized gives an ERROR.  

## Parser
Left factored rules were developed based on the grammar of the Japanese language. Parser starts with <story> and follows the grammar rules. A default case would result in a Syntax Error.

## Translator
A lexicon of English words is read in and saved in a matrix. The parser sends the words to be searched in the lexicon. If found, it is sent its translation to a text file.
