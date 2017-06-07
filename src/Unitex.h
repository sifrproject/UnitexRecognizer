#ifndef RECOGNIZER_UNITEX_H
#define RECOGNIZER_UNITEX_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <codecvt>

#include <UnitexTool.h>
#include <filesystem/path.h>
#include "utf8/utf8.h"

#include "Environment.h"
#include "Configuration.h"
#include "Annotation.h"


#include <iostream>
#include <cpprest/http_listener.h>
#include <thread>
#include <cpprest/http_listener.h>
#include <thread>

/**
 * \file Unitex.h
 * \brief Unitex/GramLab library
 * \author Stella Zevio
 * \date May 2017
 *
 * Use Unitex/GramLab library to construct a semantic annotation workflow for (biomedical) texts by exploiting BioPortal's ontologies' terms dictionary.
 *
 */

class Unitex {

private:
    Environment environment; /**< contains URLs of processing files handled by Unitex, creates and deletes them as needed. */
    Configuration configuration; /**< contains URLs of processing files needed by Unitex according to a specific language */
    bool replace; /**< true if replacements in the text are operated */
    bool longest_only; /**< true if longest matches only are kept as annotations, false if all matches are kept as annotations */

public:
    /**
     * \brief Unitex class constructor
     * \param text - text to annotate
     * \param language - language of the text to annotate
     * \param replace - true if replacements in the text are operated
     * \param longest_only - true if longest matches only are kept as annotations, false if all matches are kept as annotations
     */
    Unitex(std::string text, std::string language, bool replace, bool longestOnly);

    /**
     * \brief Get replace
     * \return replace
     */
    bool getReplace();

    /**
     * \brief Get longest only
     * \return longest_only
     */
    bool getLongestOnly();

    /**
     * \brief Get text file path from environment
     * \return text_path
     */
    std::string getText();

    /**
     * \brief Get tokenized text file path from environment
     * \return tokenized_text
     */
    std::string getTokenizedText();

    /**
     * \brief Get normalize.offsets file path from environment
     * \return normalize_offsets
     */
    std::string getNormalizeOffsets();

    /**
     * \brief Get tokenize.offsets file path from environment
     * \return tokenize_offsets
     */
    std::string getTokenizeOffsets();

    /**
     * \brief Get dlc file path from environment
     * \return dlc
     */
    std::string getDlc();

    /**
     * \brief Get dlc.n file path from environment
     * \return dlc_n
     */
    std::string getDlcN();

    /**
     * \brief Get dlf file path from environment
     * \return dlf
     */
    std::string getDlf();

    /**
     * \brief Get dlf.n file path from environment
     * \return dlf_n
     */
    std::string getDlfN();

    /**
     * \brief Get err file path from environment
     * \return err
     */
    std::string getErr();

    /**
     * \brief Get err.n file path from environment
     * \return err_n
     */
    std::string getErrN();

    /**
     * \brief Get tags_err file path from environment
     * \return tags_err
     */
    std::string getTagsErr();

    /**
     * \brief Get tags_err.n file path from environment
     * \return tags_err_n
     */
    std::string getTagsErrN();

    /**
     * \brief Get concord.ind file path from environment
     * \return concord_ind
     */
    std::string getConcord();

    /**
     * \brief Get concord.txt file path from environment
     * \return concord_txt
     */
    std::string getConcordTxt();

    /**
     * \brief Get concord.offsets file path from environment
     * \return concord_offsets
     */
    std::string getConcordOffsets();

    /**
     * \brief Get text.tfst file path from environment
     * \return text_tfst
     */
    std::string getTextTfst();

    /**
     * Get Alphabet.txt file path from configuration
     * \return alphabet
     */
    std::string getAlphabet();

    /**
     * Get Norm.txt file path from configuration
     * \return norm
     */
    std::string getNorm();

    /**
     * Get Sentence.grf file path from configuration
     * \return merge_grf
     */
    std::string getMergeGrf();

    /**
     * Get Sentence.fst2 file path from configuration
     * \return merge_fst
     */
    std::string getMergeFst();

    /**
     * Get Replace.grf file path from configuration
     * \return replace_grf
     */
    std::string getReplaceGrf();

    /**
     * Get Replace.fst2 file path from configuration
     * \return replace_fst
     */
    std::string getReplaceFst();

    /**
     * Get dictionary.bin file path from configuration
     * \return dictionary_bin
     */
    std::string getDictionaryBin();

    /**
     * Get Alphabet.sort file path from configuration
     * \return alphabet_sort
     */
    std::string getAlphabetSort();

    /**
     * Get Norm.grf file path from configuration
     * \return norm_grf
     */
    std::string getNormGrf();

    /**
     * Get Norm.fst2 file path from configuration
     * \return norm_fst
     */
    std::string getNormFst();

    /**
     * Get annot.fst2 file path from configuration
     * \return locate_fst
     */
    std::string getLocateFst();

    /**
     * \brief Normalize text
     */
    void normalize();

    /**
     * \brief Tokenize text
     */
    void tokenize();

    /**
     * \brief Split text in sentences
     */
    void applyGraphMerge();

    /**
     * \brief Apply replacement rules
     */
    void applyGraphReplace();

    /**
     * \brief Apply dictionary
     */
    void applyDictionary();

    /**
     * \brief Construct text automaton
     */
    void constructAutomaton();

    /**
     * \brief Preprocess text
     */
    void preprocessing();

    /**
     * \brief Locate pattern
     */
    void locatePattern();

    /**
     * \brief Split a string according to a separator and get the n. number section of string splitted
     * For an example, if the string is "hello:world:!", the separator is ':' and number is 2
     * \param str - string to split
     * \param separator - a character used to split the string
     * \param number - number of section of string to get
     * \return section - the section of string to get after the split
     */
    std::string split(std::string str, char separator, int number);

    /**
     * \brief Split a string in its three composing elements
     * \param str - string to split
     * \return elements - vector containing all three composing elements of the string to split
     */
    std::vector<std::string> splitElements(std::string str);

    /**
     * \brief Get text annotations as a vector of annotations
     * \return annotations - text annotations
     */
    std::vector<Annotation> getAnnotations();

    /**
     * \brief Get text annotations as a formatted string
     * \param annotations - text annotations as a vector of annotations
     * \return annotation - annotations as a formatted string
     */
    std::string getAnnotations(std::vector<Annotation> annotations);
};

#endif
