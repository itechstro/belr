
#include "belr/grammarbuilder.h"
#include "belr/abnf.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <memory>


using namespace belr;
using namespace std;

long savePosition = 0;
long loadPosition = 0;

std::list<std::shared_ptr<RecognizerPointer>> mRecognizerPointersLoaded;
std::list<shared_ptr<RecognizerPointer>>::iterator rcptrItBegin ;
std::list<shared_ptr<RecognizerPointer>>::iterator rcptrItEnd ;


template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


int main(int argc, char *argv[]){

//Selector with 4 characters
	shared_ptr<Selector> selector1 = Foundation::selector(false);
	shared_ptr<CharRecognizer> characterSel1 = Foundation::charRecognizer('a', false);
  shared_ptr<CharRecognizer> characterSel2 = Foundation::charRecognizer('b', false);
  shared_ptr<CharRecognizer> characterSel3 = Foundation::charRecognizer('c', false);
  shared_ptr<CharRecognizer> characterSel4 = Foundation::charRecognizer('d', false);
  selector1->addRecognizer(characterSel1);
  selector1->addRecognizer(characterSel2);
  selector1->addRecognizer(characterSel3);
  selector1->addRecognizer(characterSel4);

//Selector with a loop of one character
	shared_ptr<Selector> selector2 = Foundation::selector(false);
	shared_ptr<Loop> loopCar = Foundation::loop();
	shared_ptr<CharRecognizer> characterLoop2 = Foundation::charRecognizer('a', false);
	loopCar->setRecognizer(characterLoop2, 0, 3);
	selector2->addRecognizer(loopCar);

//Selector with a sequence of 4 characters
	shared_ptr<Selector> selector3 = Foundation::selector(false);
	shared_ptr<Sequence> sequence1 = Foundation::sequence();
	shared_ptr<CharRecognizer> characterSequence1 = Foundation::charRecognizer('a', false);
	shared_ptr<CharRecognizer> characterSequence2 = Foundation::charRecognizer('b', false);
	shared_ptr<CharRecognizer> characterSequence3 = Foundation::charRecognizer('c', false);
	shared_ptr<CharRecognizer> characterSequence4 = Foundation::charRecognizer('d', false);
	sequence1->addRecognizer(characterSequence1);
	sequence1->addRecognizer(characterSequence2);
	sequence1->addRecognizer(characterSequence3);
	sequence1->addRecognizer(characterSequence4);
	selector3->addRecognizer(sequence1);

//Selector with a CharRange
	shared_ptr<Selector> selector4 = Foundation::selector(false);
	const shared_ptr<CharRange> charRange1 = dynamic_pointer_cast<CharRange>(Utils::char_range(97, 100));
  const shared_ptr<CharRange> charRange2 = dynamic_pointer_cast<CharRange>(Utils::char_range(98, 101));
  const shared_ptr<CharRange> charRange3 = dynamic_pointer_cast<CharRange>(Utils::char_range(99, 102));
	selector4->addRecognizer(charRange1);
  selector4->addRecognizer(charRange2);
  selector4->addRecognizer(charRange3);

// Selector with a Literal
	shared_ptr<Selector> selector5 = Foundation::selector(false);
	const shared_ptr<Literal> stringBasic = dynamic_pointer_cast<Literal>(Utils::literal("abcd"));
	selector5->addRecognizer(stringBasic);


//Selector with an Exclusive Selector inside
shared_ptr<Selector> selector6 = Foundation::selector(false);
shared_ptr<Selector> ExclusiveSelector1 = Foundation::selector(true);
shared_ptr<CharRecognizer> characterExclusiveSelector1 = Foundation::charRecognizer('a', false);
shared_ptr<CharRecognizer> characterExclusiveSelector2 = Foundation::charRecognizer('b', false);
shared_ptr<CharRecognizer> characterExclusiveSelector3 = Foundation::charRecognizer('c', false);
shared_ptr<CharRecognizer> characterExclusiveSelector4 = Foundation::charRecognizer('d', false);
ExclusiveSelector1->addRecognizer(characterExclusiveSelector1);
ExclusiveSelector1->addRecognizer(characterExclusiveSelector2);
ExclusiveSelector1->addRecognizer(characterExclusiveSelector3);
ExclusiveSelector1->addRecognizer(characterExclusiveSelector4);
selector6->addRecognizer(ExclusiveSelector1);



//Selector with a RecognizerPointer
shared_ptr<Selector> selector7 = Foundation::selector(false);
shared_ptr<RecognizerPointer> recognizptrCar = make_shared<RecognizerPointer>();
recognizptrCar->setName("@rule");
shared_ptr<CharRecognizer> characterRecognizerPtr2 = Foundation::charRecognizer('a', false);
recognizptrCar->setPointed(characterRecognizerPtr2);
selector7->addRecognizer(recognizptrCar);
mRecognizerPointersLoaded.push_back(recognizptrCar);
rcptrItEnd = (mRecognizerPointersLoaded.end());
rcptrItBegin = (mRecognizerPointersLoaded.begin());

//verification avec feed
	cout << "*********FEEDING THE ORIGINAL RECOGNIZERS*********" << endl;
	if ((selector1->feed(NULL, "a", 0) == 1) && (selector1->feed(NULL, "b", 0) == 1) && (selector1->feed(NULL, "c", 0) == 1) && (selector1->feed(NULL, "d", 0) == 1))cout << "SUCESS : 4 CharacterRecognize Selector feed successfull" << endl;
	else cout << "FAILED : 4 CharacterRecognize Selector feed gone wrong" << endl;
	if (selector2->feed(NULL, "a", 0) == 1)cout << "SUCESS : Loop Selector feed successfull" << endl;
	else cout << "FAILED :  Loop Selector feed gone wrong" << endl;
	if (selector3->feed(NULL, "abcd", 0) == 4)cout << "SUCESS : Sequence Selector feed successfull" << endl;
	else cout << "FAILED : Sequence Selector feed gone wrong" << endl;
	if ((selector4->feed(NULL, "a", 0) == 1)&& (selector4->feed(NULL, "b", 0) == 1) && (selector4->feed(NULL, "c", 0) == 1) && (selector4->feed(NULL, "d", 0) == 1))cout << "SUCESS : CharRange Selector feed successfull" << endl;
	else cout << "FAILED : CharRange Selector feed gone wrong" << endl;
	if (selector5->feed(NULL, "abcd", 0) == 4)cout << "SUCESS : Literal Selector feed successfull" << endl;
	else cout << "FAILED : Literal Selector feed gone wrong" << endl;
	if ((selector6->feed(NULL, "a", 0) == 1) && (selector6->feed(NULL, "b", 0) == 1) && (selector6->feed(NULL, "c", 0) == 1) && (selector6->feed(NULL, "d", 0) == 1))cout << "SUCESS : Exclusive Selector feed successfull" << endl;
	else cout << "FAILED : Exclusive Selector feed gone wrong" << endl;
	if (selector7->feed(NULL, "a", 0) == 1)cout << "SUCESS : RecognizerPointer Selector feed successfull" << endl;
	else cout << "FAILED : RecognizerPointer feed gone wrong" << endl;

  remove("test-sel.bin");


  //SAVE AND LOAD
	ofstream ofichier ("test-sel.bin", ios::out | ios::app);
  selector1->save(ofichier, savePosition);
  selector2->save(ofichier, savePosition);
	selector3->save(ofichier, savePosition);
	selector4->save(ofichier, savePosition);
	selector5->save(ofichier, savePosition);
	selector6->save(ofichier, savePosition);
	selector7->save(ofichier, savePosition);
	ofichier.close();

	ifstream ifichier ("test-sel.bin", ios::in);
  string contenu;  // déclaration d'une chaîne qui contiendra la ligne lue
  getline(ifichier, contenu);  // on met dans "contenu" la ligne

  std::vector<std::string> result = split(contenu, ' ');
  vector<string>::const_iterator i = result.begin();

	const shared_ptr<Selector> selectorLoaded1 = Selector::loadVect(i, rcptrItBegin, rcptrItEnd);
	const shared_ptr<Selector> selectorLoaded2 = Selector::loadVect(i, rcptrItBegin, rcptrItEnd);
	const shared_ptr<Selector> selectorLoaded3 = Selector::loadVect(i, rcptrItBegin, rcptrItEnd);
	const shared_ptr<Selector> selectorLoaded4 = Selector::loadVect(i, rcptrItBegin, rcptrItEnd);
	const shared_ptr<Selector> selectorLoaded5 = Selector::loadVect(i, rcptrItBegin, rcptrItEnd);
	const shared_ptr<Selector> selectorLoaded6 = Selector::loadVect(i, rcptrItBegin, rcptrItEnd);
	const shared_ptr<Selector> selectorLoaded7 = Selector::loadVect(i, rcptrItBegin, rcptrItEnd);

	ifichier.close();

	cout << "*********VERIFIYING IF RECOGNIZERS MATCH*********" << endl;

	if(*(selector1.get()) == *(selectorLoaded1.get())) cout << "SUCESS : Character Selector matches loaded" << endl;
  else cout << "FAILED : original selector does not match" << endl;
	if(*selector2.get() == *selectorLoaded2.get()) cout << "SUCESS : Loop Selector matches loaded" << endl;
  else cout << "FAILED : original selector does not match" << endl;
	if(*selector3.get() == *selectorLoaded3.get()) cout << "SUCESS : Sequence Selector matches loaded" << endl;
  else cout << "FAILED : original selector does not match" << endl;
	if(*selector4.get() == *selectorLoaded4.get()) cout << "SUCESS : CharRange Selector matches loaded" << endl;
  else cout << "FAILED : original selector does not match" << endl;
	if(*selector5.get() == *selectorLoaded5.get()) cout << "SUCESS : Literal selector matches loaded" << endl;
  else cout << "FAILED : original selector does not match" << endl;
	if(*selector6.get() == *selectorLoaded6.get()) cout << "SUCESS : ExclusiveSelector Selector matches loaded" << endl;
  else cout << "FAILED : original selector does not match" << endl;
	if(*selector7.get()== *selectorLoaded7.get()) cout << "SUCESS : RecognizerPointer Selector matches loaded" << endl;
  else cout << "FAILED : original selector does not match" << endl;


	cout << "*********FEEDING THE LOADED RECOGNIZERS*********" << endl;

	if ((selectorLoaded1->feed(NULL, "a", 0) == 1) && (selectorLoaded1->feed(NULL, "b", 0) == 1) && (selectorLoaded1->feed(NULL, "c", 0) == 1) && (selectorLoaded1->feed(NULL, "d", 0) == 1))cout << "SUCESS : 4 CharacterRecognize Selector feed successfull" << endl;
	else cout << "FAILED : 4 CharacterRecognize Selector feed gone wrong" << endl;
	if (selectorLoaded2->feed(NULL, "a", 0) == 1)cout << "SUCESS : Loop Selector feed successfull" << endl;
	else cout << "FAILED :  Loop Selector feed gone wrong" << endl;
	if (selectorLoaded3->feed(NULL, "abcd", 0) == 4)cout << "SUCESS : Sequence Selector feed successfull" << endl;
	else cout << "FAILED : Sequence Selector feed gone wrong" << endl;
	if ((selectorLoaded4->feed(NULL, "a", 0) == 1)&& (selectorLoaded4->feed(NULL, "b", 0) == 1) && (selectorLoaded4->feed(NULL, "c", 0) == 1) && (selectorLoaded4->feed(NULL, "d", 0) == 1))cout << "SUCESS : CharRange Selector feed successfull" << endl;
	else cout << "FAILED : CharRange Selector feed gone wrong" << endl;
	if (selectorLoaded5->feed(NULL, "abcd", 0) == 4)cout << "SUCESS : Literal Selector feed successfull" << endl;
	else cout << "FAILED : Literal Selector feed gone wrong" << endl;
	if ((selectorLoaded6->feed(NULL, "a", 0) == 1) && (selectorLoaded6->feed(NULL, "b", 0) == 1) && (selectorLoaded6->feed(NULL, "c", 0) == 1) && (selectorLoaded6->feed(NULL, "d", 0) == 1))cout << "SUCESS : Exclusive Selector feed successfull" << endl;
	else cout << "FAILED : Exclusive Selector feed gone wrong" << endl;
	if (selectorLoaded7->feed(NULL, "a", 0) == 1)cout << "SUCESS : RecognizerPointer Selector feed successfull" << endl;
	else cout << "FAILED : RecognizerPointer feed gone wrong" << endl;


}
