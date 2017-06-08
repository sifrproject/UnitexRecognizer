#include "Environment.h"

/**
 * \file Environment.cpp
 * \brief Handling of files needed by Unitex
 * \author Stella Zevio
 * \date May 2017
 *
 * Create and delete in temp directory files needed by Unitex :
 * base directory that will contain original text file
 * original text file
 * processed text file
 * Unitex's working directory
 * intermediary and result files
 */

Environment::Environment() {
}

void Environment::deleteFileInWorkingDirectory(std::string filename) {
    std::stringstream file;
    file << getWorkingDirectory() << "/" << filename; // get file path
    filesystem::path filepath = file.str();
    filepath.remove_file(); // delete file in working directory
}

void Environment::deleteFiles() {
    this->text_path.remove_file();
    this->tokenized_text.remove_file();
    this->normalize_offsets.remove_file();
    this->tokenize_offsets.remove_file();
    this->dlc.remove_file();
    this->dlc_n.remove_file();
    this->dlf.remove_file();
    this->dlf_n.remove_file();
    this->err.remove_file();
    this->err_n.remove_file();
    this->tags_err.remove_file();
    this->tags_err_n.remove_file();
    this->concord_ind.remove_file();
    this->concord_txt.remove_file();
    this->concord_offsets.remove_file();
    this->text_tfst.remove_file();
    deleteFileInWorkingDirectory("tokens.txt");
    deleteFileInWorkingDirectory("text.cod");
    deleteFileInWorkingDirectory("text.tind");
    deleteFileInWorkingDirectory("concord.n");
    deleteFileInWorkingDirectory("enter.pos");
    deleteFileInWorkingDirectory("snt.offsets.pos");
    deleteFileInWorkingDirectory("snt_offsets.pos");
    deleteFileInWorkingDirectory("tags.ind");
    deleteFileInWorkingDirectory("stat_dic.n");
    deleteFileInWorkingDirectory("stats.n");
    deleteFileInWorkingDirectory("tok_by_alph.txt");
    deleteFileInWorkingDirectory("tok_by_freq.txt");
    deleteFileInWorkingDirectory("tfst_tags_by_alph.txt");
    deleteFileInWorkingDirectory("tfst_tags_by_freq.txt");
    deleteFileInWorkingDirectory("cursentence.grf");
    deleteFileInWorkingDirectory("cursentence.start");
    deleteFileInWorkingDirectory("cursentence.tok");
    deleteFileInWorkingDirectory("cursentence.txt");
}

void Environment::deleteWorkingDirectory() {
    char *wd = &working_directory.str()[0u]; // get working directory path
    if(rmdir(wd) == -1){
        perror("rmdir failed : could not remove working directory");
        EXIT_FAILURE;
    }
}

void Environment::deleteBaseDirectory() {
    char *bd = &base_directory.str()[0u]; // get base directory path
    if(rmdir(bd) == -1){
        perror("rmdir failed : could not remove base directory");
        EXIT_FAILURE;
    }
}

void Environment::deleteDirectories() {
    deleteWorkingDirectory(); // delete working directory
    deleteBaseDirectory(); // delete base directory when working directory is deleted
}

Environment::~Environment(void) {
    deleteFiles(); // delete files
    deleteDirectories(); // delete directories when files are deleted
}

filesystem::path Environment::getTextPath() {
    return this->text_path;
}

std::string Environment::getBaseDirectory() {
    return this->base_directory.str();
}

std::string Environment::getWorkingDirectory() {
    return this->working_directory.str();
}

std::string Environment::getTokenizedText() {
    return this->tokenized_text.str();
}

std::string Environment::getNormalizeOffsets() {
    return this->normalize_offsets.str();
}

std::string Environment::getTokenizeOffsets() {
    return this->tokenize_offsets.str();
}

std::string Environment::getDlc() {
    return this->dlc.str();
}

std::string Environment::getDlcN() {
    return this->dlc.str();
}

std::string Environment::getDlf() {
    return this->dlf.str();
}

std::string Environment::getDlfN() {
    return this->dlf_n.str();
}

std::string Environment::getErr() {
    return this->err.str();
}

std::string Environment::getErrN() {
    return this->err_n.str();
}

std::string Environment::getTagsErr() {
    return this->tags_err.str();
}

std::string Environment::getTagsErrN() {
    return this->tags_err_n.str();
}

std::string Environment::getConcord() {
    return this->concord_ind.str();
}

std::string Environment::getConcordTxt() {
    return this->concord_txt.str();
}

std::string Environment::getConcordOffsets() {
    return this->concord_offsets.str();
}

std::string Environment::getTextTfst() {
    return this->text_tfst.str();
}

void Environment::createBaseDirectory() {
    char template_name[] = "/tmp/tmpdir.unitex.XXXXXXXXXXXXX"; // automatically replaces XXXXXXXXXXXXX by random characters
    char * tmp_dir_path = mkdtemp(template_name); // create base directory in tmp directory
    if(tmp_dir_path == NULL) {
        perror("tmpdir error : could not create tmp directory");
        exit(EXIT_FAILURE);
    }
    this->base_directory = std::string(tmp_dir_path); // assign base directory file path
}

void Environment::createFile(filesystem::path file) {
    std::fstream fs;
    fs.open(file.str(), std::ios::out); // create file
    fs.close();
}

void Environment::createTextFile() {
    std::stringstream file;
    file << getBaseDirectory() << "/request.txt"; // text file is in base directory. Text filename is always "request.txt" : only base directory name changes
    createFile(file.str()); // create text file
    this->text_path = file.str(); // assign text file path
}

void Environment::fillTextFile(std::string text) {
    std::ofstream text_file(text_path.str(), std::ios::out | std::ios::trunc); // open text file
    if(!text_file){
        perror("tmpdir error : could not open text file for filling it with text");
        exit(EXIT_FAILURE);
    }
    text_file << text; // fill text file with text
    text_file.close(); // close text file
}

void Environment::createWorkingDirectory() {
    std::stringstream working_directory;
    working_directory << getBaseDirectory() << "/request_snt"; // working directory is in base directory. Working directory name is always "request_snt" : only base directory name changes
    filesystem::create_directory(filesystem::path(working_directory.str())); // create working directory
    this->working_directory = working_directory.str(); // assign working directory path
}

void Environment::createTokenizedText() {
    std::stringstream file;
    file << getBaseDirectory() << "/request.snt"; // tokenized text is in base directory. Tokenized text filename is always "request.snt" : only base directory name changes
    createFile(file.str()); // create tokenized text
    this->tokenized_text = file.str(); // assign tokenized text file path
}

std::string Environment::createFileInWorkingDirectory(std::string filename) {
    std::stringstream file;
    file << getWorkingDirectory() << "/" << filename; // file is in working directory
    createFile(file.str()); // create file
    return file.str();
}

void Environment::createNormalizeOffsets() {
    std::string normalize_offsets = createFileInWorkingDirectory("normalize.offsets"); // create normalize offsets file in working directory
    this->normalize_offsets = normalize_offsets; // assign normalize.offsets file path
}

void Environment::createTokenizeOffsets() {
    std::string tokenize_offsets = createFileInWorkingDirectory("tokenize.offsets"); // create tokenize offsets file in working directory
    this->tokenize_offsets = tokenize_offsets; // assign tokenize.offsets file path
}

void Environment::createDictionaryFiles() {
    std::string dlc = createFileInWorkingDirectory("dlc"); // create dlc file
    this->dlc = dlc; // assign dlc file path
    std::string dlc_n = createFileInWorkingDirectory("dlc.n"); // create dlc.n file
    this->dlc_n = dlc_n; // assign dlc.n file path
    std::string dlf = createFileInWorkingDirectory("dlf"); // create dlf file
    this->dlf = dlf; // assign dlf file path
    std::string dlf_n = createFileInWorkingDirectory("dlf.n"); // create dlf.n file
    this->dlf_n = dlf_n; // assign dlf.n file path
    std::string err = createFileInWorkingDirectory("err"); // create err file
    this->err = err; // assign err file path
    std::string err_n = createFileInWorkingDirectory("err.n"); // create err.n file
    this->err_n = err_n; // assign err.n file path
    std::string tags_err = createFileInWorkingDirectory("tags_err"); // create tags_err file
    this->tags_err = tags_err; // assign tags_err file path
    std::string tags_err_n = createFileInWorkingDirectory("tags_err.n"); // create tags_err.n file
    this->tags_err_n = tags_err_n; // assign tags_err.n file path
}

void Environment::createConcord() {
    std::string concord_ind = createFileInWorkingDirectory("concord.ind");
    this->concord_ind = concord_ind;
}

void Environment::createConcordTxt() {
    std::string concord_txt = createFileInWorkingDirectory("concord.txt");
    this->concord_txt = concord_txt;
}

void Environment::createConcordOffsets() {
    std::string concord_offsets = createFileInWorkingDirectory("concord.offsets");
    this->concord_offsets = concord_offsets;
}

void Environment::createTextTfst() {
    std::string text_tfst = createFileInWorkingDirectory("text.tfst");
    this->text_tfst = text_tfst;
}

void Environment::createFiles() {
    createTokenizedText();
    createNormalizeOffsets();
    createTokenizeOffsets();
    createDictionaryFiles();
    createConcord();
    createConcordTxt();
    createConcordOffsets();
    createTextTfst();
    createFileInWorkingDirectory("tokens.txt"); /**< tokens.txt file path (contains the list of all lexical units of the text) */
    createFileInWorkingDirectory("text.cod"); /**< text.cod file path (binary file containing a sequence of integers that represent the text) */
    createFileInWorkingDirectory("text.tind"); /**< text.tind file path (index file used to jump at correct byte offset in the text.tfst file when we want to load a given sentence) */
    createFileInWorkingDirectory("snt.offsets.pos");
}

void Environment::initialize(std::string text) {
    createBaseDirectory();
    createTextFile();
    fillTextFile(text);
    createWorkingDirectory();
    createFiles();
}