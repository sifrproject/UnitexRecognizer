#include "Unitex.h"

/**
 * \file Unitex.cpp
 * \brief Unitex/GramLab library handler
 * \author Stella Zevio
 * \date May 2017
 *
 * Use Unitex/GramLab library to construct a semantic annotation workflow for (biomedical) texts by exploiting BioPortal's ontologies' concepts dictionary.
 *
 */

/**
 * \namespace unitex - Unitex/GramLab library
 */
using namespace unitex;


Unitex::Unitex(std::string text, std::string language, bool replace, bool longestOnly) {
    this->environment.initialize(text); // create intermediary files handled by Unitex
    if (language == "English") {
        this->configuration.initializeEnglish(); // configure Unitex for English text
    } else if (language == "French") {
        this->configuration.initializeFrench(); // configure Unitex for French text
    } else {
        perror("Configuration error : could not recognize language");
    }
    this->replace = replace;
    this->longest_only = longestOnly;
}

bool Unitex::getReplace() {
    return this->replace;
}

bool Unitex::getLongestOnly() {
    return this->longest_only;
}

std::string Unitex::getText() {
    return this->environment.getTextPath().str();
}

std::string Unitex::getTokenizedText() {
    return this->environment.getTokenizedText();
}

std::string Unitex::getNormalizeOffsets() {
    return this->environment.getNormalizeOffsets();
}

std::string Unitex::getTokenizeOffsets() {
    return this->environment.getTokenizeOffsets();
}

std::string Unitex::getDlc() {
    return this->environment.getDlc();
}

std::string Unitex::getDlcN() {
    return this->environment.getDlcN();
}

std::string Unitex::getDlf() {
    return this->environment.getDlf();
}

std::string Unitex::getDlfN() {
    return this->environment.getDlfN();
}

std::string Unitex::getErr() {
    return this->environment.getErr();
}

std::string Unitex::getErrN() {
    return this->environment.getErrN();
}

std::string Unitex::getTagsErr() {
    return this->environment.getTagsErr();
}

std::string Unitex::getTagsErrN() {
    return this->environment.getTagsErrN();
}

std::string Unitex::getConcord() {
    return this->environment.getConcord();
}

std::string Unitex::getConcordTxt() {
    return this->environment.getConcordTxt();
}

std::string Unitex::getConcordOffsets() {
    return this->environment.getConcordOffsets();
}

std::string Unitex::getTextTfst() {
    return this->environment.getTextTfst();
}

std::string Unitex::getAlphabet() {
    return this->configuration.getAlphabet();
}

std::string Unitex::getNorm() {
    return this->configuration.getNorm();
}

std::string Unitex::getMergeGrf() {
    return this->configuration.getMergeGrf();
}

std::string Unitex::getMergeFst() {
    return this->configuration.getMergeFst();
}

std::string Unitex::getReplaceGrf() {
    return this->configuration.getReplaceGrf();
}

std::string Unitex::getReplaceFst() {
    return this->configuration.getReplaceFst();
}

std::string Unitex::getDictionaryBin() {
    return this->configuration.getDictionaryBin();
}

std::string Unitex::getAlphabetSort() {
    return this->configuration.getAlphabetSort();
}

std::string Unitex::getNormGrf() {
    return this->configuration.getNormGrf();
}

std::string Unitex::getNormFst() {
    return this->configuration.getNormFst();
}

std::string Unitex::getLocateFst() {
    return this->configuration.getLocateFst();
}

std::string Unitex::getLocateGrf() {
    return this->configuration.getLocateGrf();
}

void Unitex::normalize() {
    std::ostringstream stringStream;
    stringStream << "UnitexToolLogger Normalize " << getText()
                 << " -r " << filesystem::path::getcwd().str() << "/" << getNorm()
                 << " --output_offsets=" << getNormalizeOffsets()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
}

void Unitex::tokenize() {
    std::ostringstream stringStream;
    stringStream << "UnitexToolLogger Tokenize " << getTokenizedText()
                 << " -a " << filesystem::path::getcwd().str() << "/" << getAlphabet()
                 << " --input_offsets=" << getNormalizeOffsets()
                 << " --output_offsets=" << getTokenizeOffsets()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
}

void Unitex::applyGraphMerge() {
    std::ostringstream stringStream;
    stringStream << "UnitexToolLogger Grf2Fst2 " << filesystem::path::getcwd().str() << "/" << getMergeGrf()
                 << " -y --alphabet=" << filesystem::path::getcwd().str() << "/" << getAlphabet()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
    stringStream.str(std::string());
    stringStream << "UnitexToolLogger Flatten " << filesystem::path::getcwd().str() << "/" << getMergeFst()
                 << " --rtn -d5 -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
    stringStream.str(std::string());
    stringStream << "UnitexToolLogger Fst2Txt -t" << getTokenizedText()
                 << " " << filesystem::path::getcwd().str() << "/" << getMergeFst()
                 << " -a" << filesystem::path::getcwd().str() << "/" << getAlphabet()
                 << "  -M --input_offsets=" << getNormalizeOffsets()
                 << " --output_offsets=" << getNormalizeOffsets()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
}

void Unitex::applyGraphReplace() {
    std::ostringstream stringStream;
    stringStream << "UnitexToolLogger Grf2Fst2 " << filesystem::path::getcwd().str() << "/" << getReplaceGrf()
                 << " -y --alphabet=" << filesystem::path::getcwd().str() << "/" << getAlphabet()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
    stringStream.str(std::string());
    stringStream << "UnitexToolLogger Fst2Txt -t" << getTokenizedText()
                 << " " << filesystem::path::getcwd().str() << "/" << getReplaceFst()
                 << " -a" << filesystem::path::getcwd().str() << "/" << getAlphabet()
                 << " -R --input_offsets=" << getNormalizeOffsets()
                 << " --output_offsets=" << getNormalizeOffsets()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
}

void Unitex::applyDictionary() {
    std::ostringstream stringStream;
    stringStream << "UnitexToolLogger Dico -t" << getTokenizedText()
                 << " -a" << filesystem::path::getcwd().str() << "/" << getAlphabet()
                 << " -m" << filesystem::path::getcwd().str() << "/" << getDictionaryBin()
                 << " " << filesystem::path::getcwd().str() << "/" << getDictionaryBin()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
    stringStream.str(std::string());
    stringStream << "UnitexToolLogger SortTxt " << getDlf()
                 << " -l" << getDlfN()
                 << " -o" << filesystem::path::getcwd().str() << "/" << getAlphabetSort()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
    stringStream.str(std::string());
    stringStream << "UnitexToolLogger SortTxt " << getDlc()
                 << " -l" << getDlcN()
                 << " -o" << filesystem::path::getcwd().str() << "/" << getAlphabetSort()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
    stringStream.str(std::string());
    stringStream << "UnitexToolLogger SortTxt " << getErr()
                 << " -l" << getErrN()
                 << " -o" << filesystem::path::getcwd().str() << "/" << getAlphabetSort()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
    stringStream.str(std::string());
    stringStream << "UnitexToolLogger SortTxt " << getTagsErr()
                 << " -l" << getTagsErrN()
                 << " -o" << getAlphabetSort()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
}

void Unitex::constructAutomaton() {
    std::ostringstream stringStream;
    stringStream << "UnitexToolLogger Grf2Fst2 " << filesystem::path::getcwd().str() << "/" << getNormGrf()
                 << " -y --alphabet=" << filesystem::path::getcwd().str() << "/" << getAlphabet()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
    stringStream.str(std::string());
    stringStream << "UnitexToolLogger Txt2Tfst " << getTokenizedText()
                 << " -a" << filesystem::path::getcwd().str() << "/" << getAlphabet()
                 << " --clean -n" << filesystem::path::getcwd().str() << "/" << getNormFst()
                 << " -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
    stringStream.str(std::string());
    stringStream << "UnitexToolLogger Tfst2Grf " << getTextTfst()
                 << " -s1 -fArial -z10 -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
}


void Unitex::preprocessing() {
    normalize();
    applyGraphMerge();
    if (getReplace()) {
        applyGraphReplace();
    }
    tokenize();
    applyDictionary();
    constructAutomaton();
}


std::string Unitex::split(std::string str, char separator, int number) {
    std::string section;
    std::istringstream split(str);
    for (; number >= 0; number--) {
        std::getline(split, section, separator);
    }
    return section;
}


std::vector<std::string> Unitex::splitElements(std::string str) {
    std::istringstream iss(str);
    std::vector<std::string> elements;
    std::string first = "";
    std::string second = "";
    std::string third = "";
    if (iss) {
        iss >> first;
    }
    if (iss) {
        iss >> second;
    }
    while (iss) {
        std::string sub;
        iss >> sub;
        if (iss && sub != "\0" && third != "") {
            third += " ";
        }
        third += sub;
    }
    elements.push_back(first);
    elements.push_back(second);
    elements.push_back(third);
    return elements;
}


void Unitex::locatePattern() {
    std::ostringstream stringStream;

    stringStream << "UnitexToolLogger Grf2Fst2 " << filesystem::path::getcwd().str() << "/" << getLocateGrf()
                 << " -y --alphabet=" << filesystem::path::getcwd().str() << "/" << getAlphabet()
                 << " -o " << filesystem::path::getcwd().str() << "/" << getLocateFst()
                 << " -qutf8-no-bom";
//    stringStream
//            << "UnitexToolLogger Grf2Fst2 /Users/stealthxwing/CLionProjects/recognizer/data/French/Graphs/locate.grf "
//                    "-y --alphabet=/Users/stealthxwing/CLionProjects/recognizer/data/French/Alphabet.txt "
//                    "-o /Users/stealthxwing/CLionProjects/recognizer/data/French/Graphs/locate.fst2 "
//                    "-qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
    std::cerr << stringStream.str() << std::endl;
    stringStream.str(std::string());
    stringStream << "UnitexToolLogger Locate -t" << getTokenizedText()
                 << " " << filesystem::path::getcwd().str() << "/" << getLocateFst()
                 << " -a" << filesystem::path::getcwd().str() << "/" << getAlphabet()
                 << (getLongestOnly() ? " -L" : " -A") << " -M -l --all -x -m"
                 << filesystem::path::getcwd().str() << "/" << getDictionaryBin()
                 << " -b -Y -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
    stringStream.str(std::string());
    stringStream << "UnitexToolLogger Concord "
                 << "-t "
                 << "--uima=" << getTokenizeOffsets()
                 << " --TO -qutf8-no-bom "
                 << getConcord();
    UnitexTool_public_run_string(stringStream.str().c_str());
}


std::vector<Annotation> Unitex::getAnnotations() {
    std::ifstream concord(getConcordTxt(), std::ios::in);
    std::vector<Annotation> annotations;
    if (concord) {
        std::string ind_contenu;
        while (concord) {
            getline(concord, ind_contenu);
            if (ind_contenu.compare("") != 0) {
                std::vector<std::string> elements = splitElements(ind_contenu);
                Annotation annotation = Annotation(split(elements.at(2), ':', 1), split(elements.at(2), ':', 0),
                                                   std::stoi(elements.at(0)), std::stoi(elements.at(1)));
                annotations.push_back(annotation);
            }
        }
        concord.close();
    } else {
        std::cerr << "A problem occurred while attempting to read concordance file" << std::endl;
    }
    return annotations;
}


std::string Unitex::getAnnotations(std::vector<Annotation> annotations) {
    std::string result = "";
    std::ostringstream stringStream;

    for (std::vector<Annotation>::iterator it = annotations.begin(); it != annotations.end(); ++it) {
        stringStream << it->getTermID() << '\t' << it->getFrom() << '\t' << it->getTo() << '\t'
                     << it->getTerm() << "\t1\n" << std::endl;
        result += stringStream.str();
        stringStream.str(std::string());
    }
    return result;
}
