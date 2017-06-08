#ifndef RECOGNIZER_ENVIRONMENT_H
#define RECOGNIZER_ENVIRONMENT_H

#include <filesystem/path.h>
#include <fstream>
#include <iostream>

/**
 * \file Environment.h
 * \brief Handling of files used by Unitex
 * \author Stella Zevio
 * \date May 2017
 *
 * Create and delete in temp directory files handled by Unitex :
 * base directory that will contain original text file
 * original text file
 * processed text file
 * Unitex's working directory
 * intermediary and result files
 */

class Environment {

private:
    filesystem::path text_path; /**< text file path */
    filesystem::path base_directory; /**< text file parent directory (in /tmp directory, automatically generated in this class) */
    filesystem::path working_directory; /**< Unitex's working directory where most of the files are stored */
    filesystem::path tokenized_text; /**< tokenized text file path (.snt : processed by Unitex) */
    filesystem::path normalize_offsets; /**< normalize offsets file path */
    filesystem::path tokenize_offsets; /**< tokenize offsets file path */
    filesystem::path dlc; /**< dlc file path (compound words dictionary) */
    filesystem::path dlc_n; /**< dlc.n file path (number of lignes of dlc file + CRLF) */
    filesystem::path dlf; /**< dlf file path (simple words dictionary) */
    filesystem::path dlf_n; /**< dlf.n file path (number of lignes of dlf file + CRLF) */
    filesystem::path err; /**< err file path (unkown words) */
    filesystem::path err_n; /**< err.n file path (number of lignes of err file + CRLF) */
    filesystem::path tags_err; /**< tags.err file path (unkown words, where simple words that have been matched in the tags.ind file do not appear) */
    filesystem::path tags_err_n; /**< tags.err.n file path (number of lignes of tags.err file + CRLF) */
    filesystem::path concord_ind; /**< concord.ind file path (index of the occurrences found by Locate during the application of a grammar) */
    filesystem::path concord_txt; /**< concord.txt file path (final concordance file) */
    filesystem::path concord_offsets; /**< concord offsets file path */
    filesystem::path text_tfst; /**< text.tfst file path (represents the text automaton) */

public:

    /**
     * \brief Environment constructor
     */
    Environment();

    /**
     * \brief Delete an intermediary file handled by Unitex that is in working directory, after use
     * \param filename - name of the file to delete
     */
    void deleteFileInWorkingDirectory(std::string filename);

    /**
     * \brief Delete files Unitex handles after use
     */
    void deleteFiles();

    /**
     * Delete working directory after all the files that it contains where deleted
     */
    void deleteWorkingDirectory();

    /**
     * Delete base directory after working directory has been deleted
     */
    void deleteBaseDirectory();

    /**
     * \brief Delete directories
     */
    void deleteDirectories();

    /**
     * \brief Environment destructor
     */
    ~Environment(void);

    /**
     * \brief Get text file path
     * \return text_path
     */
    filesystem::path getTextPath();

    /**
     * \brief Get base directory path
     * \return base_directory
     */
    std::string getBaseDirectory();

    /**
     * \brief Get working directory path
     * \return working_directory
     */
    std::string getWorkingDirectory();

    /**
     * \brief Get tokenized text file path
     * \return tokenized_text
     */
    std::string getTokenizedText();

    /**
     * \brief Get normalize.offsets file path
     * \return normalize_offsets
     */
    std::string getNormalizeOffsets();

    /**
     * \brief Get tokenize.offsets file path
     * \return tokenize_offsets
     */
    std::string getTokenizeOffsets();

    /**
     * \brief Get dlc file path
     * \return dlc
     */
    std::string getDlc();

    /**
     * \brief Get dlc.n file path
     * \return dlc_n
     */
    std::string getDlcN();

    /**
     * \brief Get dlf file path
     * \return dlf
     */
    std::string getDlf();

    /**
     * \brief Get dlf.n file path
     * \return dlf_n
     */
    std::string getDlfN();

    /**
     * \brief Get err file path
     * \return err
     */
    std::string getErr();

    /**
     * \brief Get err.n file path
     * \return err_n
     */
    std::string getErrN();

    /**
     * \brief Get tags.err file path
     * \return tags_err
     */
    std::string getTagsErr();

    /**
     * \brief Get tags.err.n file path
     * \return tags_err_n
     */
    std::string getTagsErrN();

    /**
     * \brief Get concord.ind file path
     * \return concord_ind
     */
    std::string getConcord();

    /**
     * \brief Get concord.txt file path
     * \return concord_txt
     */
    std::string getConcordTxt();

    /**
     * \brief Get concord.offsets file path
     * \return concord_offsets
     */
    std::string getConcordOffsets();

    /**
     * \brief Get text.tfst file path
     * \return text_tfst
     */
    std::string getTextTfst();

    /**
     * \brief Create base directory in /tmp
     */
    void createBaseDirectory();

    /**
     * \brief Create file giving a file path
     * @param file - path of the file to create
     */
    void createFile(filesystem::path file);

    /**
     * \brief Create text file
     */
    void createTextFile();

    /**
     * \brief Fill text file with text to annotate
     * \param text - text to annotate
     */
    void fillTextFile(std::string text);

    /**
     * \brief Create working directory
     */
    void createWorkingDirectory();

    /**
     * \brief Create tokenized text (text processed by Unitex)
     */
    void createTokenizedText();

    /**
     * Create a file in working directory
     * @param filename - name of the file to create
     * @return filepath - path of the created file
     */
    std::string createFileInWorkingDirectory(std::string filename);

    /**
     * \brief Create normalize.offsets file
     */
    void createNormalizeOffsets();

    /**
     * \brief Create tokenize.offsets file
     */
    void createTokenizeOffsets();

    /**
     * \brief Create dictionary files (dlc, dlf, err, tags_err, dlc.n, dlf.n, err.n, tags_err.n)
     */
    void createDictionaryFiles();

    /**
     * \brief Create concord.ind file
     */
    void createConcord();

    /**
     * \brief Create concord.txt file
     */
    void createConcordTxt();

    /**
     * \brief Create concord.offsets file
     */
    void createConcordOffsets();

    /**
     * \brief Create text.tfst file
     */
    void createTextTfst();

    /**
     * \brief Create files handled by Unitex
     */
    void createFiles();

   /**
    * \brief Initialize the environment from a text to annotate
    * \param text - text to annotate
    */
    void initialize(std::string text);
};

#endif
