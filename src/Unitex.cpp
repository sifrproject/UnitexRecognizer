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
    if(language=="English") {
        this->configuration.initializeEnglish(); // configure Unitex for English text
    }
    else if(language=="French") {
        this->configuration.initializeFrench(); // configure Unitex for French text
    }
    else {
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

std::string Unitex::getCorpusSntMerge() {
    return this->environment.getCorpusSntMerge();
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
                 << " -a"  << filesystem::path::getcwd().str() << "/"<< getAlphabet()
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
    if(getReplace()) {
        applyGraphReplace();
    }
    tokenize();
    applyDictionary();
    constructAutomaton();
}


std::string Unitex::split(std::string str, char separator, int number){
    std::string section;
    std::istringstream split(str);
    for (; number>=0; number--) {
        std::getline(split, section, separator);
    }
    return section;
}



std::vector<std::string> Unitex::splitElements(std::string str){
    std::istringstream iss(str);
    std::vector<std::string> elements;
    std::string first="";
    std::string second="";
    std::string third="";
    if(iss) {
        iss >> first;
    }
    if(iss) {
        iss >> second;
    }
    while (iss) {
        std::string sub;
        iss >> sub;
        if(iss && sub!="\0" && third!="") {
            third += " ";
        }
        third+=sub;
    }
    elements.push_back(first);
    elements.push_back(second);
    elements.push_back(third);
    return elements;
}


void Unitex::locatePattern() {
    std::ostringstream stringStream;
    stringStream << "UnitexToolLogger Locate -t" << getTokenizedText()
                 << " " << filesystem::path::getcwd().str() << "/" << getLocateFst()
                 << " -a" << filesystem::path::getcwd().str() << "/" << getAlphabet()
                 << (getLongestOnly() ? " -L" : " -A") << " -M -l --all -x -m"
                 << filesystem::path::getcwd().str() << "/" << getDictionaryBin()
                 << " -b -Y -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());

    stringStream.str(std::string());
    stringStream << "UnitexToolLogger Concord " << getConcord()
                 << " --uima=" << getTokenizeOffsets()
                 << " -m " << getCorpusSntMerge()
                 << " --output_offsets=" << getConcordOffsets()
                 << " --TO -qutf8-no-bom";
    UnitexTool_public_run_string(stringStream.str().c_str());
}


std::vector<Annotation> Unitex::getAnnotations() {
    // concord.ind reading
    std::ifstream concord(getConcord(), std::ios::in);
    std::vector<std::string> IDs_1;
    std::vector<std::string> IDs_2;
    std::vector<std::string> tokens;
    std::vector<std::string> annotations;
    if (concord) {
        std::string ind_contenu;
        while (concord) {
            getline(concord, ind_contenu);
            if (ind_contenu.rfind("#M") == std::string::npos && ind_contenu.compare("") != 0) {
                std::vector<std::string> elements = splitElements(ind_contenu);
                IDs_1.push_back((std::basic_string<char, std::char_traits<char>, std::allocator<char>> &&)elements.at(0));
                IDs_2.push_back(
                        (std::basic_string<char, std::char_traits<char>, std::allocator<char>> &&) elements.at(1));
                tokens.push_back(split(elements.at(2), ':', 0));
                annotations.push_back(split(elements.at(2), ':', 1));
            }
        }
        concord.close();
    }
    else {
        std::cerr << "A problem occurred while attempting to read concordance build file" << std::endl;
    }
    // concord.offsets reading
    std::ifstream concord_offsets(getConcordOffsets(), std::ios::in);
    std::vector<int> pos_deb;
    std::vector<int> pos_fin;
    if (concord_offsets) {
        std::string off_contenu;
        while (concord_offsets) {
            getline(concord_offsets, off_contenu);
            std::istringstream iss(off_contenu);
            std::string pos;
            int cpt = 0;
            while (std::getline(iss, pos, ' ')) {
                if (cpt == 0) {
                    pos_deb.push_back(std::stoi(pos));
                }
                if (cpt == 1) {
                    pos_fin.push_back(std::stoi(pos));
                }
                cpt += 1;
            }
        }
        concord_offsets.close();
    } else {
        std::cerr << "A problem occurred while attempting to read concordance offsets file" << std::endl;
    }
    // annotations creation
    std::vector<Annotation> annot;
    std::string previous_ID1;
    std::string previous_ID2;
    int i = 0;
    int j = 0;
    for (std::string t : tokens) {
        if(i > 0) {
            previous_ID1 = IDs_1.at(i-1);
            previous_ID2 = IDs_2.at(i-1);
            if(IDs_1.at(i).compare(previous_ID1) != 0 && IDs_2.at(i).compare(previous_ID2) != 0) {
                j++;
            }
        }
        Annotation an = Annotation(annotations.at(i), tokens.at(i), pos_deb.at(j), pos_fin.at(j));
        annot.push_back(an);
        i++;
    }
    return annot;
}


std::string Unitex::getAnnotations(std::vector<Annotation> annotations) {
    std::string annot = "termID\tfrom\tto\tterm\tlineID\n";
    std::ostringstream stringStream;
    for(Annotation annotation : annotations) {
        stringStream<<annotation.getTermID()<<'\t'<<annotation.getFrom()<<'\t'<<annotation.getTo()<<'\t'<<annotation.getTerm()<<"\t1\n"<<std::endl;
        annot += stringStream.str();
        stringStream.str(std::string());
    }
    return annot;
}


int main(int argc, char *argv[]) {
    std::string text = "Le docteur ne lui a pas diagnostiqué un mal de tête.\nLe docteur lui a diagnostiqué plusieurs maux de tête.";
    std::string language = "French";
    //std::string text = "The doctor has not diagnosed her a headache.\nThe doctor diagnosed her many headaches.";
    //std::string language = "English";
    bool replace = true;
    bool longestOnly = false;
    Unitex uni = Unitex(text, language, replace, longestOnly);
    uni.preprocessing();
    uni.locatePattern();
    std::vector<Annotation> annotations = uni.getAnnotations();
    std::string annotation = uni.getAnnotations(annotations);
    std::cout<<annotation<<std::endl;
    return 0;
}