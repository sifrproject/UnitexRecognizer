#ifndef RECOGNIZER_CONFIGURATION_H
#define RECOGNIZER_CONFIGURATION_H

#include <string>

/**
 * \file Configuration.h
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

class Configuration {

private:
    std::string alphabet; /**< Alphabet.txt file path (characters of a language, as well as the correspondances between capitalized and non-capitalized letters) */
    std::string norm; /**< Norm.txt file path */
    std::string merge_grf; /**< Sentence.grf file path (sentence delimitation grammar) */
    std::string merge_fst; /**< Sentence.fst2 file path */
    std::string replace_grf; /**< Replace.grf file path (replacements grammar) */
    std::string replace_fst; /**< Replace.fst2 file path */
    std::string dictionary_bin; /**< dictionary.bin file path */
    std::string alphabet_sort; /**< Alphabet_sort.txt file path (sorting priorities of the letters of a language) */
    std::string norm_grf; /**< Norm.grf file path (normalization grammar) */
    std::string norm_fst; /**< Norm.fst2 file path */
    std::string locate_grf; /**< annot.fst2 file path (to locate pattern) */
    std::string locate_fst; /**< annot.fst2 file path (to locate pattern) */

public:
    /**
     * Configuration constructor
     */
    Configuration();

    /**
     * Initialize configuration for French
     */
    void initializeFrench();

    /**
     * Initialize configuration for English
     */
    void initializeEnglish();

    /**
     * Get Alphabet.txt file path
     * \return alphabet
     */
    std::string getAlphabet();

    /**
     * Get Norm.txt file path
     * \return norm
     */
    std::string getNorm();

    /**
     * Get Sentence.grf file path
     * \return merge_grf
     */
    std::string getMergeGrf();

    /**
     * Get Sentence.fst2 file path
     * \return merge_fst
     */
    std::string getMergeFst();

    /**
     * Get Replace.grf file path
     * \return replace_grf
     */
    std::string getReplaceGrf();

    /**
     * Get Replace.fst2 file path
     * \return replace_fst
     */
    std::string getReplaceFst();

    /**
     * Get dictionary.bin file path
     * \return dictionary_bin
     */
    std::string getDictionaryBin();

    /**
     * Get Alphabet.sort file path
     * \return alphabet_sort
     */
    std::string getAlphabetSort();

    /**
     * Get Norm.grf file path
     * \return norm_grf
     */
    std::string getNormGrf();

    /**
     * Get Norm.fst2 file path
     * \return norm_fst
     */
    std::string getNormFst();

    /**
     * Get locate.grf file path
     * \return locate_grf
     */
    std::string getLocateGrf();

    /**
     * Get annot.fst2 file path
     * \return locate_fst
     */
    std::string getLocateFst();
};

#endif
