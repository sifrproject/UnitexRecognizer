#include "Configuration.h"

/**
 * \file Configuration.cpp
 * \brief Load resources needed by Unitex according to text language
 * \author Stella Zevio
 * \date May 2017
 *
 * Load resources needed by Unitex :
 * alphabets
 * normalization rules files
 * sentence delimitation grammar files
 * replacement grammar files
 * dictionary
 * locate pattern graph
 */

Configuration::Configuration() {

}

void Configuration::initializeFrench() {
    this->alphabet = "data/French/Alphabet.txt";
    this->norm = "data/French/Norm.txt";
    this->merge_grf ="data/French/Graphs/Preprocessing/Sentence/Sentence.grf";
    this->merge_fst = "data/French/Graphs/Preprocessing/Sentence/Sentence.fst2";
    this->replace_grf = "data/French/Graphs/Preprocessing/Replace/Replace.grf";
    this->replace_fst = "data/French/Graphs/Preprocessing/Replace/Replace.fst2";
    this->dictionary_bin = "data/French/Dela/dictionary.bin";
    this->alphabet_sort = "data/French/Alphabet_sort.txt";
    this->norm_grf = "data/French/Graphs/Normalization/Norm.grf";
    this->norm_fst = "data/French/Graphs/Normalization/Norm.fst2";
    this->locate_fst = "data/French/Graphs/locate.fst2";
    this->locate_grf = "data/French/Graphs/locate.grf";
}

void Configuration::initializeEnglish() {
    this->alphabet = "data/English/Alphabet.txt";
    this->norm = "data/English/Norm.txt";
    this->merge_grf ="data/English/Graphs/Preprocessing/Sentence/Sentence.grf";
    this->merge_fst = "data/English/Graphs/Preprocessing/Sentence/Sentence.fst2";
    this->replace_grf = "data/English/Graphs/Preprocessing/Replace/Replace.grf";
    this->replace_fst = "data/English/Graphs/Preprocessing/Replace/Replace.fst2";
    this->dictionary_bin = "data/English/Dela/dico.bin";
    this->alphabet_sort = "data/English/Alphabet_sort.txt";
    this->norm_grf = "data/English/Graphs/Normalization/Norm.grf";
    this->norm_fst = "data/English/Graphs/Normalization/Norm.fst2";
    this->locate_grf = "data/English/Graphs/locate.grf";
    this->locate_fst = "data/English/Graphs/annot.fst2";
}

std::string Configuration::getAlphabet() {
    return this->alphabet;
}

std::string Configuration::getNorm() {
    return this->norm;
}

std::string Configuration::getMergeGrf() {
    return this->merge_grf;
}

std::string Configuration::getMergeFst() {
    return this->merge_fst;
}

std::string Configuration::getReplaceGrf() {
    return this->replace_grf;
}

std::string Configuration::getReplaceFst() {
    return this->replace_fst;
}

std::string Configuration::getDictionaryBin() {
    return this->dictionary_bin;
}

std::string Configuration::getAlphabetSort() {
    return this->alphabet_sort;
}

std::string Configuration::getNormGrf() {
    return this->norm_grf;
}

std::string Configuration::getNormFst() {
    return this->norm_fst;
}

std::string Configuration::getLocateFst() {
    return this->locate_fst;
}

std::string Configuration::getLocateGrf(){
    return this->locate_grf;
}